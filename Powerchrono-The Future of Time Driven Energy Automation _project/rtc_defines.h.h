#ifndef RTC_DEFINES_H        // Prevents multiple inclusion of this header file
#define RTC_DEFINES_H

// ---------------- System Clock and Peripheral Clock Macros ----------------

// Main oscillator frequency (12 MHz crystal)
#define FOSC 12000000

// CPU clock frequency (CCLK = 5 × FOSC = 60 MHz)
#define CCLK (5 * FOSC)

// Peripheral clock frequency (PCLK = CCLK / 4 = 15 MHz)
#define PCLK (CCLK / 4)

// ---------------- RTC Prescaler Macros ----------------

// PREINT value for RTC prescaler
// This divides the peripheral clock (PCLK) to generate a 32.768 kHz clock
// Formula: (PCLK / 32768) - 1
#define PREINT_VAL ((PCLK / 32768) - 1)

// PREFRAC value for RTC fractional divider
// This compensates for the remainder after integer division
// Formula: PCLK - ((PREINT_VAL + 1) × 32768)
#define PREFRAC_VAL ((PCLK - (PREINT_VAL + 1) * 32768))

// ---------------- RTC Clock Control Register (CCR) Bit Definitions ----------------

// RTC Enable bit (bit 0)
// Setting this bit starts the RTC counter
#define RTC_ENABLE (1 << 0)

// RTC Reset bit (bit 1)
// Setting this bit resets the RTC counters and prescaler
#define RTC_RESET (1 << 1)

// RTC Clock Source Select bit (bit 4)
// Setting this bit selects the external 32.768 kHz RTC clock source
#define RTC_CLKSRC (1 << 4)

// Uncomment this macro if compiling specifically for LPC2148
// #define LPC2148

#endif
