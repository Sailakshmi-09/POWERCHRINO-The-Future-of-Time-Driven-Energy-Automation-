#include "types.h"   // Includes user-defined data types such as u32

// Function declaration to configure the function of a specific port pin
// Parameters:
//   u32 - Port number (0 or 1)
//   u32 - Pin number within the selected port
//   u32 - Pin function value (GPIO, UART, SPI, I2C, EINT, etc.)
void CfgPortPinFunc(u32, u32, u32);

