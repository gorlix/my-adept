# Ploopy Adept - Custom "Gorlix" Firmware

A highly advanced QMK firmware designed for the **Ploopy Adept** trackball.
Engineered for **Linux (KDE Plasma/Wayland)** power users, focusing on fluid navigation, gesture control, and precision.

## 🌟 Key Features

### � Advanced Motion Engine
- **Quadratic Acceleration**: Replaces standard linear acceleration with a custom quadratic curve (`speed^2`).
    - *Low Speed*: Ultra-precise 1:1 tracking for pixel-perfect editing.
    - *High Speed*: Exponential boost allowing you to cross 4K screens with a single flick.
- **1600 CPI Base**: High native logic for responsiveness.

### � High-Resolution Fluid Tracking
- **Float Accumulators**: Scroll calculations use floating-point math for sub-pixel precision.
- **Scroll Sensitivity**: Tuned to **0.5x** independent of cursor DPI, ensuring buttery smooth web navigation.
- **Smart Axis Locking (Hysteresis)**:
    - Automatically detects if you are scrolling Vertically or Horizontally.
    - "Locks" the axis to prevent accidental diagonal drift.
    - Uses **Hysteresis** memory: once locked, it stays locked until you intentionally break out with a strong movement.

### 🔍 Gesture Controls & Zoom
- **Smooth Zoom / Pinch Emulation**:
    - Hold **Top Left** button to enter Zoom Mode.
    - Emulates `Ctrl + Shift + Scroll` (Libinput Pinch Zoom standard).
    - Works natively in browsers (Firefox/Chrome) and design apps for true smooth zooming.

### �️ Desktop & Media Navigation
- **Desktop Switcher**: Hold **Bot Right** (`NAV`) and flick the ball Left/Right to switch virtual desktops (KDE standard).
- **Mission Control**: Hold `NAV` and flick Up/Down for Overview.
- **Media Mode**: Hold **Top Right** (`MEDIA`) to control Volume (Up/Down) or Brightness (Left/Right).

---

## 🖱️ Button Layout

| Position | Label | Tap (Click) | Hold (Function) | Double Tap |
| :--- | :--- | :--- | :--- | :--- |
| **Top Left** | `ZOOM` | Middle Click | **Pinch Zoom Mode** | - |
| **Mid Left** | `SCROLL` | Middle Click | **Drag Scroll Mode** | **Home** (2x) / **End** (3x) |
| **Bot Left** | `LMB` | Left Click | - | - |
| **Top Right** | `MEDIA` | Back (Btn 4) | **Media Layer** | **Playback Layer** |
| **Mid Right** | `RMB` | Right Click | - | - |
| **Bot Right** | `NAV` | Forward (Btn 5) | **Desktop Nav** | - |

### 🎥 Playback Layer (Top Right 2x)
Dedicated controls for video/music consumption.
- **Ball**: Standard Cursor.
- **Top Left**: Rewind 10s.
- **Mid Right**: Forward 10s.
- **Bot Left**: Play/Pause.
- **Top Right**: Exit Layer.

---

## ⚙️ Technical Details

- **Poll Rate**: 1ms (1000Hz) throttle for instant response.
- **Math Library**: Uses `<math.h>` for advanced acceleration curves.
- **Wayland Optimized**: Specific tuning for high-res scroll events in Wayland compositors.

## 🛠️ Compilation

This firmware includes complex C logic. Compile using the standard QMK CLI:

```bash
qmk compile -kb ploopyco/madromys -km gorlix
```

*Note: Requires QMK Firmware 0.22+*
