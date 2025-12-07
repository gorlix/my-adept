# Ploopy Adept - Custom Firmware

This is a highly customized QMK firmware for the **Ploopy Adept** trackball, engineered for maximum productivity on Linux (specifically KDE Plasma). It features gesture-based controls, fluid scrolling, and dedicated media layers.

## ✨ Key Features Overview

### 🖱️ Button Layout

| Position | Label | Click (Tap) | Hold (Function) | Double Tap |
| :--- | :--- | :--- | :--- | :--- |
| **Top Left** | `ZOOM` | Middle Click | **Smooth Zoom** | - |
| **Mid Left** | `SCROLL` | Middle Click | **Drag Scroll** | **Home** (2x) / **End** (3x) |
| **Bot Left** | `LMB` | Left Click | - | - |
| **Top Right** | `MEDIA` | Button 4 (Back) | **Media Mode** | **Playback Layer** |
| **Mid Right** | `RMB` | Right Click | - | - |
| **Bot Right** | `NAV` | Button 5 (Forward) | **Desktop Nav** | - |

---

## 🚀 Detailed Functionality

### 🔍 Smooth Zoom Mode (Top Left)
Emulates `Ctrl` + `Scroll Wheel` to provide smooth, pinch-like zooming in browsers and supported applications.
- **Activation**: Hold the **Top Left** button.
- **Action**: Move the ball **Up/Down**.
- **Result**: Smooth Zoom In/Out.

### 📜 Fluid Drag Scroll (Mid Left)
Leverages QMK's high-resolution scrolling for pixel-perfect navigation.
- **Activation**: Hold the **Mid Left** button.
- **Action**: Move the ball in **any direction** (Vertical & Horizontal).
- **Tap Gestures**:
    - **1x Tap**: Middle Click (Open/Close Tabs).
    - **2x Tap**: `HOME` Key (Jump to top).
    - **3x Tap**: `END` Key (Jump to bottom).

### 🔊 Media Control Mode (Top Right - Hold)
Adjust system settings without lifting your hand.
- **Activation**: Hold the **Top Right** button.
- **Volume**: Move ball **Up/Down**.
- **Brightness**: Move ball **Left/Right**.

### 🎥 Playback Control Layer (Top Right - Double Tap)
A dedicated layer for controlling video/music playback.
- **Activation**: Double-tap the **Top Right** button.
- **Controls**:
    - **Top Left**: Rewind 10s (Left Arrow).
    - **Mid Right**: Forward 10s (Right Arrow).
    - **Bot Left**: Play/Pause.
    - **Top Right**: **EXIT** (Return to normal mode).

### 🖥️ Desktop Navigation (Bot Right)
Designed for KDE Plasma shortcuts (`Ctrl` + `Meta` + `Arrows`).
- **Activation**: Hold the **Bot Right** button.
- **Switch Desktop**: Move ball **Left/Right**.
- **Overview / Mission Control**: Move ball **Up/Down**.
- *Includes a custom threshold to prevent accidental triggers.*

---

## ⚙️ Technical Specifications

- **DPI**: 1600 CPI base.
- **Acceleration**: **Quadratic Curve** (Ultra-precise at low speeds, exponential boost for fast flicks).
- **Scrolling**: Fluid 1:1 mapping with **Hysteresis-based Axis Locking** (Sticky axis memory to prevent drift).
- **Framework**: QMK Firmware (latest).
- **Target**: Ploopy Adept (RP2040).

## 🛠️ Compilation & Flashing

This project uses a GitHub Action workflow to auto-release new firmware versions.
To compile locally:

```bash
qmk compile -kb ploopyco/madromys -km gorlix
```
