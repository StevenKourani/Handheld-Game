# Handheld Game
A custom-built handheld console powered by an STM32 microcontroller, featuring a 2.8" TFT display, joystick/button controls, and modular game firmware.  This repository contains  both the hardware design files (KiCad) and firmware source code.


## 🔧 Hardware Overview

- **MCU:** STM32F411RE (Nucleo board in development, custom PCB for production)  
- **Display:** ILI9341 2.8" TFT LCD (SPI)  
- **Controls:** Analog joystick + push buttons  
- **Audio:** Passive buzzer with PWM for sound effects  
- **Power:** Li-ion battery with power management  
- **PCB Design:** Created in KiCad 8, includes Gerbers, BOM, and pick-and-place files.

---

## 💻 Firmware Overview

- Written in **C** using STM32 HAL drivers.
- Includes:
  - LCD graphics rendering
  - Joystick input via ADC
  - Button input with debouncing
  - Game logic (Breakout, menu system, sound effects)
- Developed in **STM32CubeIDE**.

---

## 🚀 Getting Started

### 1. Hardware
- Open `hardware/` in **KiCad 9.0**.
- Gerber and BOM files are available in `hardware/gerbers` and `hardware/fabrication` for PCB fabrication.

### 2. Firmware
- Open the `firmware/` folder in **STM32CubeIDE**.
- Connect your STM32 board (e.g., Nucleo-F411RE or your custom PCB).
- Compile and flash the firmware.

---
