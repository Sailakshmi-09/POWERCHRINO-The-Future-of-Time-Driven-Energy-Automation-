#ifndef RTC_H          // Prevents multiple inclusion of this header file
#define RTC_H

#include "types.h"       // Includes user-defined data types such as u32

// Function to initialize the Real Time Clock (RTC)
// Configures the RTC prescaler and enables the RTC
void RTC_Init(void);

// Function to get the current RTC time
// Parameters:
//   u32 * - Pointer to store the hour value
//   u32 * - Pointer to store the minute value
//   u32 * - Pointer to store the second value
void GetRTCTimeInfo(u32 *, u32 *, u32 *);

// Function to display the RTC time on the LCD
// Parameters:
//   u32 - Hour value
//   u32 - Minute value
//   u32 - Second value
void DisplayRTCTime(u32, u32, u32);

// Function to get the current RTC date
// Parameters:
//   u32 * - Pointer to store the date (day of month)
//   u32 * - Pointer to store the month
//   u32 * - Pointer to store the year
void GetRTCDateInfo(u32 *, u32 *, u32 *);

// Function to display the RTC date on the LCD
// Parameters:
//   u32 - Date (day of month)
//   u32 - Month
//   u32 - Year
void DisplayRTCDate(u32, u32, u32);

// Function to set the RTC time
// Parameters:
//   u32 - Hour value (0 to 23)
//   u32 - Minute value (0 to 59)
//   u32 - Second value (0 to 59)
void SetRTCTimeInfo(u32, u32, u32);

// Function to set the RTC date
// Parameters:
//   u32 - Date (1 to 31)
//   u32 - Month (1 to 12)
//   u32 - Year
void SetRTCDateInfo(u32, u32, u32);

// Function to get the current day of the week from RTC
// Parameter:
//   u32 * - Pointer to store the day value
void GetRTCDay(u32 *);

// Function to display the day of the week on the LCD
// Parameter:
//   u32 - Day value
void DisplayRTCDay(u32);

// Function to set the day of the week in RTC
// Parameter:
//   u32 - Day value (0 to 6, depending on implementation)
void SetRTCDay(u32);

#endif
