#include "types.h"   // Includes user-defined data types such as u8, s8, u32, s32, and f32

// Function declaration to send a byte to the LCD
// This is the low-level function used internally for both commands and data
// Parameter:
//   u8 byte - Byte to send to the LCD
void WriteLCD(u8 byte);

// Function declaration to send a command to the LCD
// Commands control LCD operations such as clearing the display,
// moving the cursor, turning the display ON/OFF, etc.
// Parameter:
//   u8 cmdByte - LCD command byte
void cmdLCD(u8 cmdByte);

// Function declaration to initialize the LCD
// Configures the LCD in the required mode and prepares it for display
void InitLCD(void);

// Function declaration to display a single ASCII character on the LCD
// Parameter:
//   u8 asciival - ASCII value of the character to display
void charLCD(u8 asciival);

// Function declaration to display a string on the LCD
// Parameter:
//   s8 * - Pointer to the string to be displayed
void strLCD(s8 *);

// Function declaration to display an unsigned 32-bit integer on the LCD
// Parameter:
//   u32 - Unsigned integer value to display
void u32LCD(u32);

// Function declaration to display a signed 32-bit integer on the LCD
// Parameter:
//   s32 - Signed integer value to display
void s32LCD(s32);

// Function declaration to display a 32-bit floating-point number on the LCD
// Parameters:
//   f32 - Floating-point value to display
//   u8  - Number of digits to display after the decimal point
void f32LCD(f32, u8);

// Function declaration to create a custom character in LCD CGRAM
// Parameters:
//   u8 * - Pointer to the custom character pattern (8 bytes)
//   u8  - CGRAM location (0 to 7)
void BuildCGRAM(u8 *, u8);

