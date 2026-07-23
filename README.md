PowerChrono – The Future of Time-Driven Energy Automation
Project Overview:

PowerChrono is an intelligent, time-based power management system developed using the LPC2148 microcontroller. The project is designed to 
automate electrical devices based on predefined ON and OFF schedules, thereby optimizing energy usage,reducing power wastage, and improving operational reliability.
The system continuously monitors the Real-Time Clock (RTC) and controls a connected device (LED/Bulb) according to the user-programmed timing settings.

Key Features:

1.Real-time clock display on LCD.
2.Automatic device control based on RTC schedule.
3.User-friendly keypad-based editing.
4.External interrupt-driven menu access.
5.Custom LCD CGRAM symbols for bulb ON/OFF indication.
6.Input validation for reliable operation.
7.Modular code structure with separate drivers for LCD, Keypad, RTC, Delay, and Pin Configuration.

Hardware Requirements:

LPC2148 ARM7 Microcontroller,
16×2 LCD Display,
4×4 Matrix Keypad,
LED/Bulb (as the controlled device),
Push Button Switch (for EINT0 interrupt),
32.768 kHz RTC Crystal,
USB-UART Converter / DB-9 Cable,
Power Supply.

Software Requirements:

Embedded C Programming,
Keil uVision IDE,
Flash Magic,
LPC2148 Header Files.

Block Diagram:

               +------------------+
               |     KEYPAD       |
               +------------------+
                        |
                        v
        +--------------------------------+
        |            LPC2148             |
        |                                |
        |      +------------------+      |
        |      |       RTC        |      |
        |      +------------------+      |
        |                                |
        |  EINT <---------------- SWITCH |
        +--------------------------------+
                |                    |
                v                    v
        +---------------+      +---------------+
        |      LCD      |      |    DEVICE     |
        +---------------+      +---------------+

 Applications:

* Automatic street light control.
* Home and office appliance automation.
* Industrial load scheduling and control.
* Agricultural irrigation pump automation.
* Energy-saving lighting systems.
* Commercial building power management.







