#include QMK_KEYBOARD_H
#include <math.h>

// --- SCROLL ORIENTATION STATE ---
enum scroll_orientations {
    SCROLL_NONE,
    SCROLL_VERT,
    SCROLL_HORZ
};

// --- CUSTOM KEYCODE DEFINITIONS ---
enum custom_keycodes {
    DESDESK_NAV = SAFE_RANGE,
    CUSTOM_DRAG_SCROLL,
    ZOOM_BTN3
};

// --- TAP DANCE ENUMERATION ---
enum {
    TD_SCROLL_CLICK,
    TD_MEDIA_CTRL
};

// --- LAYER DEFINITIONS ---
// _VIA layers reserved for future configuration
enum layers {
    _BASE,
    _MEDIA,
    _PLAYBACK,
    _VIA2,
    _VIA3
};

// --- STATE VARIABLES ---
static bool is_nav_mode = false;
static bool is_scroll_mode = false;
static bool is_zoom_mode = false;
static uint16_t last_nav_time = 0;
static uint16_t zoom_timer = 0;
int16_t nav_acum_x = 0;
int16_t nav_acum_y = 0;
int16_t media_acum_x = 0;
int16_t media_acum_y = 0;

static uint8_t scroll_dir = SCROLL_NONE;
// High-Res Scroll Accumulators
static float scroll_accum_x = 0.0f;
static float scroll_accum_y = 0.0f;

// --- CONFIGURATION ---
// #define SCROLL_DIVIDER 40  // Removed
#define MEDIA_THRESHOLD 150   // Sensitivity threshold for media controls

// --- TAP DANCE LOGIC ---
void scroll_click_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        if (!state->pressed) {
            // Single Tap: Standard Middle Click
            tap_code(QK_MOUSE_BUTTON_3);
        } else {
            // Hold: Activate Drag Scroll Mode
            is_scroll_mode = true;
        }
    } else if (state->count == 2) {
        // Double Tap: Home
        tap_code(KC_HOME);
    } else if (state->count == 3) {
        // Triple Tap: End
        tap_code(KC_END);
    }
}

void scroll_click_reset(tap_dance_state_t *state, void *user_data) {
    is_scroll_mode = false;
    scroll_dir = SCROLL_NONE; // Reset Hysteresis
}

// --- MEDIA TAP DANCE ---
void media_click_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        if (!state->pressed) {
            // Single Tap: Button 4 (Back)
            tap_code(QK_MOUSE_BUTTON_4);
        } else {
            // Hold: Media Layer (Momentary)
            layer_on(_MEDIA);
            media_acum_x = 0;
            media_acum_y = 0;
        }
    } else if (state->count == 2) {
        if (!state->pressed) {
             // Double Tap: Switch to Playback Layer (Toggle/One-shot logic if needed, user requested change layer)
             layer_on(_PLAYBACK);
        }
    }
}

void media_click_reset(tap_dance_state_t *state, void *user_data) {
    // Always turn off temporary media layer on release
    if (IS_LAYER_ON(_MEDIA)) {
        layer_off(_MEDIA);
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_SCROLL_CLICK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, scroll_click_finished, scroll_click_reset),
    [TD_MEDIA_CTRL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, media_click_finished, media_click_reset)
};

// --- LAYOUT DEFINITIONS ---
// TL: Zoom/Mid      TR: Media/Back
// ML: Drag Scroll   MR: Right Click
// BL: Left Click    BR: Desktop Nav
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        ZOOM_BTN3,              TD(TD_MEDIA_CTRL),            // Top Left, Top Right
        TD(TD_SCROLL_CLICK),    QK_MOUSE_BUTTON_2,            // Mid Left, Mid Right
        QK_MOUSE_BUTTON_1,      DESDESK_NAV                   // Bot Left, Bot Right
    ),
    
    // Media Layer - Transparent (handled via C code logic)
    [_MEDIA] = LAYOUT(_______, _______, _______, _______, _______, _______),
    
    // Playback Layer - Media Controls
    [_PLAYBACK] = LAYOUT(
        KC_LEFT,  TO(_BASE),  // TL: Rewind 10s   TR: Exit Layer
        _______,  KC_RIGHT,   // ML: No Action    MR: Forward 10s
        KC_MPLY,  _______     // BL: Play/Pause   BR: No Action
    ),
    [_VIA2] = LAYOUT(_______, _______, _______, _______, _______, _______),
    [_VIA3] = LAYOUT(_______, _______, _______, _______, _______, _______)
};

// --- KEYCODE LOGIC ---
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DESDESK_NAV:
            if (record->event.pressed) {
                is_nav_mode = true;
                nav_acum_x = 0;
                nav_acum_y = 0;
            } else {
                is_nav_mode = false;
            }
            return false; // Prevent sending keycode to host

        case ZOOM_BTN3:
            if (record->event.pressed) {
                is_zoom_mode = true;
                zoom_timer = timer_read();
                register_code(KC_LCTL); 
                register_code(KC_LSFT); // Add Shift for broader browser support (Pinch Zoom emulation)
            } else {
                is_zoom_mode = false;
                unregister_code(KC_LSFT);
                unregister_code(KC_LCTL); 
                if (timer_elapsed(zoom_timer) < TAPPING_TERM) {
                    tap_code(QK_MOUSE_BUTTON_3); // Tap Middle Click if short press
                }
            }
            return false;

        default:
            return true;
    }
}

// --- POINTING DEVICE LOGIC ---
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    // --- MOUSE ACCELERATION ALGORITHM (QUADRATIC) ---
    // Calculate 2D velocity magnitude (speed)
    float speed = sqrt(pow(mouse_report.x, 2) + pow(mouse_report.y, 2));

    if (speed > ACCEL_OFFSET) {
        // Quadratic acceleration formula
        // Use a smaller divisor (0.001) since we are squaring the speed difference
        float factor = 1.0f + pow(speed - ACCEL_OFFSET, 2) * 0.001f * ACCEL_SLOPE;
        
        // Cap the acceleration factor
        if (factor > ACCEL_LIMIT) {
            factor = ACCEL_LIMIT;
        }

        // Apply scaling
        mouse_report.x = (int16_t)(mouse_report.x * factor);
        mouse_report.y = (int16_t)(mouse_report.y * factor);
    }

    // 1. DESKTOP NAVIGATION MODE
    if (is_nav_mode) {
        nav_acum_x += mouse_report.x;
        nav_acum_y += mouse_report.y;

        if (timer_elapsed(last_nav_time) > NAV_COOLDOWN) {
            
            // Horizontal Movement (Switch Desktop Next/Prev)
            if (nav_acum_x > NAV_THRESHOLD) {
                tap_code16(LCTL(LGUI(KC_RIGHT))); 
                last_nav_time = timer_read();
                nav_acum_x = 0;
                nav_acum_y = 0;
            } 
            else if (nav_acum_x < -NAV_THRESHOLD) {
                tap_code16(LCTL(LGUI(KC_LEFT)));
                last_nav_time = timer_read();
                nav_acum_x = 0;
                nav_acum_y = 0;
            }
            // Vertical Movement (Mission Control / Overview)
            else if (nav_acum_y > NAV_THRESHOLD) {
                tap_code16(LCTL(LGUI(KC_DOWN))); // Or KC_UP depending on OS
                last_nav_time = timer_read();
                nav_acum_x = 0;
                nav_acum_y = 0;
            } 
            else if (nav_acum_y < -NAV_THRESHOLD) {
                tap_code16(LCTL(LGUI(KC_UP)));
                last_nav_time = timer_read();
                nav_acum_x = 0;
                nav_acum_y = 0;
            }
        }

        // Lock cursor movement
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    
    // 2. DRAG SCROLL MODE
    else if (is_scroll_mode) {
        // --- SCROLL STRAIGHTENING WITH HYSTERESIS ---
        int16_t abs_x = abs(mouse_report.x);
        int16_t abs_y = abs(mouse_report.y);

        if (scroll_dir == SCROLL_NONE) {
            if (abs_y > abs_x * SCROLL_STRAIGHT_FACTOR) {
                scroll_dir = SCROLL_VERT;
            } else if (abs_x > abs_y * SCROLL_STRAIGHT_FACTOR) {
                scroll_dir = SCROLL_HORZ;
            }
        } 
        else if (scroll_dir == SCROLL_VERT) {
            if (abs_x > abs_y + SCROLL_UNLOCK_THRESHOLD) {
                scroll_dir = SCROLL_HORZ;
            }
        }
        else if (scroll_dir == SCROLL_HORZ) {
            if (abs_y > abs_x + SCROLL_UNLOCK_THRESHOLD) {
                scroll_dir = SCROLL_VERT;
            }
        }
        
        // --- HIGH-RESOLUTION ACCUMULATION ---
        // Accumulate raw input * sensitivity
        scroll_accum_x += (float)mouse_report.x * SCROLL_SENSITIVITY;
        scroll_accum_y += (float)mouse_report.y * SCROLL_SENSITIVITY; // Note: Invert is applied later or logic? 
        // Standard mouse_report.y is down-positive. Scroll down is naturally negative V in QMK usually? 
        // Wait, normally we did mouse_report.v = -mouse_report.y. 
        // So let's accumulate -y to v.
        
        // Let's use temporary variables for the "Report" value
        int8_t report_v = 0;
        int8_t report_h = 0;

        // Calculate Integer part from Accumulator
        int8_t v_part = (int8_t)(scroll_accum_y * -1.0f); // Invert Y for Scroll V
        int8_t h_part = (int8_t)(scroll_accum_x);

        // Apply Locking to the OUTPUT
        if (scroll_dir == SCROLL_VERT) {
             report_v = v_part;
             report_h = 0;
             // We should also clear the H accumulator to prevent "building up" pressure while locked?
             // Yes, or at least dampen it. For strict locking, clear it.
             scroll_accum_x = 0.0f; 
        } else if (scroll_dir == SCROLL_HORZ) {
             report_v = 0;
             report_h = h_part;
             scroll_accum_y = 0.0f;
        } else {
             // Free movement
             report_v = v_part;
             report_h = h_part;
        }

        // Assign to report
        mouse_report.v = report_v;
        mouse_report.h = report_h;

        // Subtract the consumed integer part from the accumulators
        // Note: We tracked (accum * -1) for V. 
        // Logic: 
        // accum_y += raw_y * 0.5. 
        // output_v = (int)(accum_y * -1).
        // consumed_y = output_v * -1.
        // accum_y -= consumed_y.
        
        if (mouse_report.v != 0) {
            scroll_accum_y -= (float)(mouse_report.v * -1); 
        }
        if (mouse_report.h != 0) {
            scroll_accum_x -= (float)(mouse_report.h);
        }

        // Lock cursor movement
        mouse_report.x = 0;
        mouse_report.y = 0;
    }

    // 3. MEDIA CONTROL MODE
    else if (IS_LAYER_ON(_MEDIA)) {
        media_acum_x += mouse_report.x;
        media_acum_y += mouse_report.y;

        // Volume (Y-axis)
        if (media_acum_y > MEDIA_THRESHOLD) {
            tap_code(KC_VOLD);
            media_acum_y = 0;
        } else if (media_acum_y < -MEDIA_THRESHOLD) {
            tap_code(KC_VOLU);
            media_acum_y = 0;
        }

        // Brightness (X-axis)
        if (media_acum_x > MEDIA_THRESHOLD) {
            tap_code(KC_BRIU);
            media_acum_x = 0;
        } else if (media_acum_x < -MEDIA_THRESHOLD) {
            tap_code(KC_BRID);
            media_acum_x = 0;
        }

        mouse_report.x = 0;
        mouse_report.y = 0;
        mouse_report.v = 0;
        mouse_report.h = 0;
    }

    // 4. ZOOM MODE (Ctrl + Scroll)
    else if (is_zoom_mode) {
        // Map Y-axis to Vertical Scroll (v)
        // With Control held, this is interpreted as Zoom by the OS
        mouse_report.v = -mouse_report.y; 
        
        // Lock cursor and other axes
        mouse_report.x = 0;
        mouse_report.y = 0;
        mouse_report.h = 0;
    }

    return mouse_report;
}