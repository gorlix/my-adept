# Ploopy Adept - Advanced Firmware

An advanced QMK firmware designed for the **Ploopy Adept** trackball.
Optimized for **Linux (KDE Plasma/Wayland)** power users, focusing on fluid navigation, gesture control, and absolute precision.

## Key Features

### Advanced Motion Engine
- **Quadratic Acceleration**: Replaces standard linear acceleration with a custom quadratic curve (`speed^2`).
    - *Low Speed*: Ultra-precise 1:1 tracking for pixel-perfect editing.
    - *High Speed*: Exponential boost allowing you to cross 4K screens with a single "flick".
- **Base 1600 CPI**: Native high-resolution logic for maximum responsiveness.

### Smooth High-Resolution Scrolling
- **Float Accumulators**: Scroll calculations use floating-point math for sub-pixel precision.
- **Tuned Sensitivity**: Calibrated to **0.9x** (independent of cursor DPI), ensuring "buttery smooth" web navigation.
- **Omnidirectional Scrolling**:
    - Full support for 2D scrolling (Simultaneous Vertical and Horizontal).
    - Unlocked axes for natural diagonal movement.

### Gesture Controls & Zoom
- **Fluid Zoom / Pinch Emulation**:
    - Hold **Top Left** to enter Zoom Mode.
    - Emulates `Ctrl + Shift + Scroll` (Standard Libinput Pinch Zoom).
    - Works natively in browsers (Firefox/Chrome) and design apps for real fluid zooming.
    
### Desktop & Media Navigation
- **Desktop Switcher**: Hold **Bot Right** (`NAV`) and flick the ball Left/Right to switch virtual desktops (Standard KDE shortcuts).
- **Mission Control**: Hold `NAV` and flick Up/Down for window overview.
- **Media Mode**: Hold **Top Right** (`MEDIA`) to control Volume (Up/Down) or Brightness (Left/Right) via ball movement.

---

## 🆚 Differences vs Base Firmware

This keymap introduces significant logic changes compared to the stock Ploopy firmware:

| Feature | Base Firmware | **This Custom Firmware** |
| :--- | :--- | :--- |
| **Acceleration** | Custom QMK Accel or None | **Quadratic Curve** (Math-based `v^2`) for distinct low/high speed profiles. |
| **Drag Scroll** | Standard QMK (Integer based, Axis Locking) | **Float-based Omnidirectional**: Smoother, supports diagonal scrolling, uses accumulators for high-res feel. |
| **Zoom** | Button Mapped or Key combo | **Ball-driven Zoom**: Turns the trackball into a precision zoom dial. |
| **Navigation** | Buttons | **Gesture Based**: Uses ball flicks for Desktop/Window management. |
| **Media Control**| Buttons / Layer | **Gesture Based**: Uses ball movement for intuitive Volume/Brightness control. |
| **Layout** | Static Layers | **Tap-Dance Heavy**: Buttons perform dual roles (Tap/Hold/Double-Tap) to maximize the 6-button layout. |

---

## Button Layout

| Position | Label | Tap (Click) | Hold (Function) | Double Tap |
| :--- | :--- | :--- | :--- | :--- |
| **Top Left** | `ZOOM` | Middle Click | **Zoom Mode** | - |
| **Mid Left** | `SCROLL` | Middle Click | **Drag Scroll Mode** | **Home** (2x) / **End** (3x) |
| **Bot Left** | `LMB` | Left Click | - | - |
| **Top Right** | `MEDIA` | Back (Btn 4) | **Media Layer** | **Playback Layer** |
| **Mid Right** | `RMB` | Right Click | - | - |
| **Bot Right** | `NAV` | Forward (Btn 5) | **Desktop Nav** | - |

### Playback Layer (Top Right 2x)
Dedicated controls for video/music consumption.
- **Ball**: Standard Cursor.
- **Top Left**: Rewind 10s.
- **Mid Right**: Forward 10s.
- **Bot Left**: Play/Pause.
- **Top Right**: Exit Layer.

---

## Technical Details

- **Poll Rate**: 1ms (1000Hz) for instant response.
- **Math Library**: Uses `<math.h>` for complex acceleration curves.
- **Wayland Optimization**: Tuned specifically for high-resolution scroll events in Wayland compositors.

## Compiling

This firmware includes complex C logic. Compile using the standard QMK CLI:

```bash
qmk compile -kb ploopyco/madromys -km gorlix
```

*Note: Requires QMK Firmware 0.22+*
