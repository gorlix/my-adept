#pragma once

/* --- Sensor Configuration (Ploopy Adept) --- */
// Standard high-resolution settings
#define PLOOPY_TRACKBALL_CPI 1600 
#define PLOOPY_DRAGSCROLL_DPI 100  // Lower DPI for precision during scroll
#define PLOOPY_DRAGSCROLL_INVERT_Y // Invert vertical scroll direction
#define POINTING_DEVICE_HIRES_SCROLL_ENABLE // Enable fluid high-resolution scrolling

/* --- Mouse Acceleration (Quadratic) --- */
#define ACCEL_OFFSET 10      // Threshold (counts) to start acceleration
#define ACCEL_SLOPE 1.5      // Aggressiveness of acceleration (Curve Steepness)
#define ACCEL_LIMIT 4.0      // Maximum multiplier cap

/* --- Desktop Navigation Configuration --- */
// Movement threshold: accumulated sensitivity to trigger action (100-500)
#define NAV_THRESHOLD 450 

/* --- Scroll Configuration (Hysteresis) --- */
// Axis locking factor. 1.5 means Primary axis must be > 1.5x Secondary to lock.
#define SCROLL_STRAIGHT_FACTOR 1.5
#define SCROLL_UNLOCK_THRESHOLD 30 // Force required to break out of an axis lock0 

/* --- Scroll Configuration --- */
// Axis locking factor. 1.5 means Primary axis must be > 1.5x Secondary to lock.
#define SCROLL_STRAIGHT_FACTOR 1.5

// Cooldown: Minimum time (ms) between desktop switches
#define NAV_COOLDOWN 300 

/* --- Click Configuration --- */
#define TAPPING_TERM 200
#define MOUSEKEY_INTERVAL 16
#define MOUSEKEY_DELAY 0
#define MOUSEKEY_TIME_TO_MAX 60
#define MOUSEKEY_MAX_SPEED 7
#define MOUSEKEY_WHEEL_DELAY 0