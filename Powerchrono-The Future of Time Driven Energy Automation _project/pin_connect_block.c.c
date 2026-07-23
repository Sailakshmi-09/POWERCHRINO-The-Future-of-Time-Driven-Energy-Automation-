#include "types.h"                 // User-defined data types (u32, etc.)
#include "pin_function_defines.h"  // Pin function selection macros
#include <LPC21xx.h>                // LPC214x register definitions

// Function to configure the function of a specific port pin
// Parameters:
//   portNo  - Port number (0 or 1)
//   pinNo   - Pin number within the port
//   pinFunc - Function to assign to the pin (GPIO, UART, SPI, I2C, etc.)
void CfgPortPinFunc(u32 portNo, u32 pinNo, u32 pinFunc)
{
    // Check if the selected port is Port 0
    if(portNo == 0)
    {
        // Pins P0.0 to P0.15 are configured using PINSEL0
        if(pinNo <= 15)
        {
            // Clear the existing 2-bit function field for the selected pin
            // Then set the new function value
            PINSEL0 = ((PINSEL0 & ~(3 << (pinNo * 2))) | (pinFunc << (pinNo * 2)));
        }

        // Pins P0.16 to P0.31 are configured using PINSEL1
        else if(pinNo >= 16 && pinNo <= 31)
        {
            // Subtract 16 because PINSEL1 starts from P0.16
            PINSEL1 = ((PINSEL1 & ~(3 << ((pinNo - 16) * 2))) | (pinFunc << ((pinNo - 16) * 2)));
        }
    }

    // Check if the selected port is Port 1
    else if(portNo == 1)
    {
        // Pins P1.16 to P1.31 are configured using PINSEL2
        if(pinNo >= 16 && pinNo <= 31)
        {
            // Subtract 16 because PINSEL2 starts from P1.16
            PINSEL2 = ((PINSEL2 & ~(3 << ((pinNo - 16) * 2))) |(pinFunc << ((pinNo - 16) * 2)));
        }
    }
}
