# Ploopy Adept - Custom Firmware

This is a highly customized QMK firmware for the Ploopy Adept trackball, designed for advanced productivity on Linux (KDE Plasma) with specific gesture controls.

## ✨ Key Features

### 🖱️ Button Layout & Logic

| Button Pos | Label | Primary Function (Tap) | Secondary Actions |
| :--- | :--- | :--- | :--- |
| **Top Left** | `BTN 3` | Middle Click | - |
| **Mid Left** | `SCROLL` | **Middle Click** | **Hold**: Drag Scroll (All Directions)<br>**3x Tap**: Home<br>**4x Tap**: End |
| **Bot Left** | `BTN 1` | Left Click | - |
| **Top Right** | `MEDIA` | **Button 4 (Back)** | **Hold**: Media Mode (Vol/Bri)<br>**2x Tap**: Enter **Playback Layer** |
| **Mid Right** | `BTN 2` | Right Click | - |
| **Bot Right** | `NAV` | Button 5 (Forward)* | **Hold**: Desktop Navigation |

> *Note: Bottom Right tap function might be customized or defaulting to layer/click depending on specific iteration.*

---

### 🎥 Playback Control Layer
Activated by **Double Tapping** the Top Right Button.

| Button Pos | Function | Description |
| :--- | :--- | :--- |
| **Top Left** | `←` Left Arrow | Rewind 10s (Youtube/VLC default) |
| **Top Right** | **EXIT** | Return to Base Layer |
| **Mid Right** | `→` Right Arrow | Forward 10s |
| **Bot Left** | `⏯` Play/Pause | Toggle Playback |
| **Ball** | - | *Standard Mouse Movement* |

---

### 📜 Fluid Drag Scroll (Mid Left Button)
Powered by QMK High-Resolution Scrolling for pixel-perfect smoothness.
- **Hold & Move Ball**: Scrolling in **all directions** (Vertical + Horizontal).
- **Single Click**: Middle Mouse Click (open tabs, close tabs).
- **Double Click + Hold**: Also activates Drag Scroll.
- **Triple Click**: Sends `HOME` key (jump to top of page).
- **Quadruple Click**: Sends `END` key (jump to bottom of page).

---

### 🖥️ Desktop Navigation (Bot Right Button `DESDESK_NAV`)
Optimized for KDE Plasma / Linux shortcuts (`Ctrl` + `Meta` + `Arrows`).
- **Hold & Move Ball Right/Left**: Switch Virtual Desktop (Next/Prev).
- **Hold & Move Ball Up/Down**: Mission Control / Overview (Present Windows).
- *Features accelerated threshold logic to prevent accidental triggers.*

---

### 🔊 Media Control Mode (Hold Top Right)
Control your system media without touching the keyboard.
- **Hold & Move Ball Up/Down**: Volume Up / Down.
- **Hold & Move Ball Right/Left**: Brightness Up / Down.

---

## ⚙️ Customization Details

- **Responsive Scrolling**: Manual quantization removed in favor of direct sensor-to-scroll variable mapping (`mouse_report.v = -mouse_report.y`).
- **Hi-Res support**: Enabled `MOUSE_EXTENDED_REPORT` and `POINTING_DEVICE_HIRES_SCROLL_ENABLE`.
- **VIA Disabled**: Disabled to allow for complex C-based logic and custom variables.

## 🛠️ Compilation

```bash
qmk compile -kb ploopyco/madromys -km gorlix
```
