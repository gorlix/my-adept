#include QMK_KEYBOARD_H

// Definiamo i keycode custom
enum custom_keycodes {
    DESDESK_NAV = SAFE_RANGE,
    CUSTOM_DRAG_SCROLL
};

// Tap Dance Enum
enum {
    TD_SCROLL_CLICK,
    TD_MEDIA_CTRL
};

// Definiamo i layer (usati anche da VIA)
enum layers {
    _BASE,
    _MEDIA,
    _PLAYBACK,
    _VIA2,
    _VIA3
};

// Variabili di stato
static bool is_nav_mode = false;
static bool is_scroll_mode = false;
static uint16_t last_nav_time = 0;
int16_t nav_acum_x = 0;
int16_t nav_acum_y = 0;
int16_t media_acum_x = 0;
int16_t media_acum_y = 0;
uint16_t media_timer = 0;

// Configurazione Scroll
#define SCROLL_DIVIDER 40 // Più basso = scroll più veloce
#define MEDIA_THRESHOLD 150 // Sensibilità media

// --- TAP DANCE LOGIC ---
void scroll_click_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        if (!state->pressed) {
            // Tapped once: Middle Click
            tap_code(QK_MOUSE_BUTTON_3);
        } else {
            // Held: Drag Scroll Mode
            is_scroll_mode = true;
        }
    } else if (state->count == 3) {
        // Triple Tap: Home
        tap_code(KC_HOME);
    } else if (state->count == 4) {
        // Quad Tap: End
        tap_code(KC_END);
    }
}

void scroll_click_reset(tap_dance_state_t *state, void *user_data) {
    is_scroll_mode = false;
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_SCROLL_CLICK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, scroll_click_finished, scroll_click_reset)
};

// --- LAYOUT ---
// Layout richiesto:
// TL: DESDESK_NAV    TR: <da valutare> (metto KC_BTN4/, DESDESK_NAV    Back)
// ML: CUSTOM_DRAG_SCROLL    MR: Tasto Destro
// BL: Tasto Sinistro BR: Click Rotella
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(

        QK_MOUSE_BUTTON_3, QK_MOUSE_BUTTON_4,      // Top Left, Top Right
        TD(TD_SCROLL_CLICK), QK_MOUSE_BUTTON_2,      // Mid Left, Mid Right
        QK_MOUSE_BUTTON_1, DESDESK_NAV       // Bot Left, Bot Right
    ),
    // Layer vuoti per VIA
    [_VIA1] = LAYOUT(_______, _______, _______, _______, _______, _______),
    [_VIA2] = LAYOUT(_______, _______, _______, _______, _______, _______),
    [_VIA3] = LAYOUT(_______, _______, _______, _______, _______, _______)
};

// --- LOGICA DEI TASTI ---
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
            return false; // Non inviare nulla al PC
            
            return false; // Non inviare nulla al PC

        default:
            return true;
    }
}

// --- LOGICA DELLA SFERA ---
// --- LOGICA DELLA SFERA ---
// int16_t scroll_acum_y = 0; // Removed for fluid scroll
// char scroll_acum_x = 0; // Decommenta per scroll orizzontale

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    // 1. MODALITÀ NAVIGAZIONE DESKTOP
    if (is_nav_mode) {
        nav_acum_x += mouse_report.x;
        nav_acum_y += mouse_report.y;

        if (timer_elapsed(last_nav_time) > NAV_COOLDOWN) {
            
            // Movimento Orizzontale (Desktop DX/SX)
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
            // Movimento Verticale (Mission Control / Desktop overview)
            else if (nav_acum_y > NAV_THRESHOLD) {
                tap_code16(LCTL(LGUI(KC_DOWN))); // O KC_UP a seconda dell'OS
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

        // Blocca il cursore
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    
    // 2. MODALITÀ DRAG SCROLL
    else if (is_scroll_mode) {
        // Scroll Fluido: Assegna direttamente il movimento Y allo scroll V
        // MOUSE_EXTENDED_REPORT e POINTING_DEVICE_HIRES_SCROLL_ENABLE gestiscono la risoluzione
        mouse_report.v = -mouse_report.y;
        mouse_report.h = mouse_report.x; // Abilita scroll orizzontale

        // Blocca il cursore
        mouse_report.x = 0;
        mouse_report.y = 0;
    }

    return mouse_report;
}