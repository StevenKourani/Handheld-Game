# Handheld Game
A custom-built handheld console powered by an STM32 microcontroller, featuring a 2.8" TFT display, joystick/button controls, and modular game firmware.  
This repository contains both the **hardware design files** (KiCad) and **firmware source code**.

---

## 🔧 Hardware Overview

- **MCU:** STM32F411RE (Nucleo board in development, custom PCB for production)  
- **Display:** ILI9341 2.8" TFT LCD (SPI)  
- **Controls:** Analog joystick + push buttons  
- **Audio:** Passive buzzer with PWM for sound effects  
- **Power:**
  - Li-ion battery with power management
  - **Buck-boost converter** allows the battery to be used both above and below 3.3V
  - USB-C charging option
  - Current switch for allowing fast charging of the battery
  - Power switch (on/off)
  - LED indicators for low battery and fully charged states  
- **PCB Design:** Created in KiCad 9, includes Gerbers, BOM, and KiCad project files.
- **Status:** Board was fabricated, and the power system was tested successfully.

---

## 💻 Firmware Overview

- Written in **C** using STM32 HAL drivers.
- Includes:
  - LCD graphics rendering
  - Joystick input via ADC
  - Button input with debouncing
  - Passive buzzer using PWM for sound effects
  - Game logic (Breakout, menu system, sound effects)
- Developed in **STM32CubeIDE**.
- Board is flashed using **Serial Wire Debug (SWD)**.
- Two additional onboard peripherals are available: **USART** and **I²C**.
- **Important:**  
  The code works, but you must update all pin numbers and peripheral configurations to match your own board.  
  In the first PCB revision, firmware flashing on the custom board was not possible due to a missing capacitor on the **VCAP** pin, preventing the CPU from running.  
  The current version in this repository has been updated to include this capacitor.

---

## 🎮 Game Details

- **Breakout** is implemented and functional but currently missing:
  - Pause function
  - Game Over function  
- Work is in progress to complete these features and to add more games, including **Snake**.

---

## 🚀 Getting Started

### 1. Hardware
- Open `kicad/` in **KiCad 9.0**.
- Gerber and BOM files are available in `gerbers/` and `fabrication/` for PCB fabrication.

### 2. Firmware
- Open the `Inc/` and `Src/` folders in **STM32CubeIDE**.
- Connect your STM32 board (e.g., Nucleo-F411RE or your custom PCB).
- Compile and flash the firmware using **SWD**.

---

## 🤝 Contributing

This is my **first time designing and fabricating a PCB**.  
If anyone has improvements for the KiCad design or firmware, please:
- **Fork** this repository
- Make your changes
- Submit a **Pull Request** so the improvements can be reviewed and merged.

I would love to know if this updated version of the handheld works for you!

---

## 📜 License

This project is licensed under the **MIT License** (see `LICENSE` file).

---
