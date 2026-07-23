// kpm.c - 4x4 Keypad Matrix Driver

#include "types.h"          // User-defined data types (u8, u32, etc.)
#include <LPC21xx.h>          // LPC214x register definitions
#include "defines.h"        // Bit and nibble manipulation macros
#include "lcd.h"            // LCD function declarations
#include "lcd_defines.h"    // LCD command macros
#include "kpm_defines.h"    // Keypad row and column pin definitions
#include "kpm.h"            // Keypad function declarations
#include "delay.h"          // Delay functions

// Keypad lookup table
// Maps row and column positions to actual keypad characters
u32 kpmLUT[4][4] =
{
    {'1','2','3','a'},
    {'4','5','6','b'},
    {'7','8','9','c'},
    {'*','0','#',':'}
};

/*
// Alternative keypad mapping (calculator style)
u32 kpmLUT[4][4] =
{
    {'7','8','9','/'},
    {'4','5','6','X'},
    {'1','2','3','-'},
    {'C','0','=','+'}
};
*/

// Function to initialize the keypad
void Init_KPM(void)
{
    // Configure ROW0 to ROW3 (P1.16-P1.19) as GPIO outputs
    // Value 15 (0xF) sets all 4 row bits as output
    WRITENIBBLE(IODIR1, ROW0, 15);

    // Column pins are left as inputs by default
    // No need to configure them explicitly as input
    // WRITENIBBLE(IODIR1, COL0, 0);
}

// Function to scan keypad columns
u32 Colscan(void)
{
    u32 status;

    // Read the 4 column bits from P1.20-P1.23
    status = READNIBBLE(IOPIN1, COL0);

    // If all columns are HIGH (1111 = 15), no key is pressed
    // If any column is LOW, a key is pressed
    return (status < 15) ? 0 : 1;
}

// Function to identify which row contains the pressed key
u32 Rowcheck(void)
{
    u32 r;

    // Scan each row one by one
    for(r = 0; r <= 3; r++)
    {
        // Drive one row LOW and keep others HIGH
        // ~(1<<r) creates the row scanning pattern
        WRITENIBBLE(IOPIN1, ROW0, ~(1 << r));

        // Check if any column becomes LOW
        if(Colscan() == 0)
        {
            break;  // Pressed key is in this row
        }
    }

    // Re-initialize all rows to LOW after scanning
    WRITENIBBLE(IOPIN1, ROW0, 0);

    return r;   // Return detected row number
}

// Function to identify which column contains the pressed key
u32 Colcheck(void)
{
    u32 c;

    // Check each column pin
    for(c = 0; c <= 3; c++)
    {
        // If column pin is LOW, key is pressed in this column
        if(READBIT(IOPIN1, COL0 + c) == 0)
            break;
    }

    return c;   // Return detected column number
}

// Function to scan the keypad and return the pressed key
u32 Keyscan(void)
{
    u32 r, c, keyv;

    // Wait until any key is pressed
    while(Colscan());

    // Identify the row in which the key was pressed
    r = Rowcheck();

    // Identify the column in which the key was pressed
    c = Colcheck();

    // Get the corresponding key value from lookup table
    keyv = kpmLUT[r][c];

    // Debounce delay to avoid multiple detections
    delay_ms(200);

    return keyv;   // Return the pressed key character
}

// Function to read a multi-digit number from the keypad
void ReadNum(u32 *num)
{
    u32 lastkey;
    u8 keyv;
    s8 cnt = 0;   // Counter for number of digits entered

    *num = 0;     // Initialize the number to zero

    while(1)
    {
        // Read a key from the keypad
        keyv = Keyscan();

        delay_ms(200);   // Debounce delay

        lastkey = keyv;

        // If the key is a numeric digit
        if(keyv >= '0' && keyv <= '9')
        {
            cnt++;

            // Convert ASCII digit to integer and append to number
            *num = (*num * 10) + (keyv - 48);

            // Wait until the key is released
            while(Colscan() == 0);

            // Display the entered number on LCD
            cmdLCD(CLEAR_LCD);
            u32LCD(*num);
        }

        // If 'b' is pressed, perform backspace
        else if(lastkey == 'b')
        {
            if(cnt > 0)
            {
                while(Colscan() == 0);

                cnt--;

                // Remove the last digit
                *num = *num / 10;

                // Clear the last character on LCD
                cmdLCD(GOTO_LINE1_POS0 + cnt);
                charLCD(' ');
                cmdLCD(GOTO_LINE1_POS0 + cnt);
            }
        }

        // If 'a' is pressed, ignore and continue
        else if(lastkey == 'a')
        {
            continue;
        }

        // If '*' is pressed, finish input
        else if(lastkey == '*')
        {
            while(Colscan() == 0);

            break;
        }
    }
}
