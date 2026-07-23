#include "types.h"   // Includes user-defined data types such as u32

// Function declaration to initialize the keypad module
// Configures keypad row pins as outputs and prepares the keypad for scanning
void Init_KPM(void);

// Function declaration to scan keypad columns
// Returns:
//   0 if any key is pressed
//   1 if no key is pressed
u32 Colscan(void);

// Function declaration to identify which row contains the pressed key
// Returns:
//   Row number (0 to 3)
u32 Rowcheck(void);

// Function declaration to identify which column contains the pressed key
// Returns:
//   Column number (0 to 3)
u32 Colcheck(void);

// Function declaration to scan the keypad and return the pressed key
// Returns:
//   ASCII value of the pressed key from the keypad lookup table
u32 Keyscan(void);

// Function declaration to read a multi-digit number from the keypad
// Parameter:
//   u32 *num - Pointer to a variable where the entered number will be stored
void ReadNum(u32 *num);
