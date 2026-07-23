// ---------------- LCD Command Definitions ----------------

// Clear the LCD display and move cursor to home position
#define CLEAR_LCD 0x01

// Return cursor to home position (first line, first column)
#define RET_CUR_HOME 0x02

// Move cursor one position to the right after writing a character
#define SHIFT_CUR_RIGHT 0x06

// Move cursor one position to the left after writing a character
#define SHIFT_CUR_LEFT 0x07

// Turn OFF the LCD display
#define DSP_OFF 0x08

// Turn ON display with cursor OFF
#define DSP_ON_CUR_OFF 0x0C

// Turn ON display with cursor ON (no blinking)
#define DSP_ON_CUR_ON 0x0E

// Turn ON display with blinking cursor
#define DSP_ON_CUR_BLINK 0x0F

// Shift entire display one position to the left
#define SHIFT_DISP_LEFT 0x10

// Shift entire display one position to the right
#define SHIFT_DISP_RIGHT 0x14

// Configure LCD in 8-bit mode, 1-line display
#define MODE_8BIT_1LINE 0x30

// Configure LCD in 4-bit mode, 1-line display
#define MODE_4BIT_1LINE 0x20

// Configure LCD in 8-bit mode, 2-line display, 5x7 font
#define MODE_8BIT_2LINE 0x38

// Configure LCD in 4-bit mode, 2-line display, 5x7 font
#define MODE_4BIT_2LINE 0x28

// ---------------- LCD Cursor Position Commands ----------------

// Move cursor to Line 1, Position 0
#define GOTO_LINE1_POS0 0x80

// Move cursor to Line 2, Position 0
#define GOTO_LINE2_POS0 0xC0

// Move cursor to Line 3, Position 0 (for 20x4 LCD)
#define GOTO_LINE3_POS0 0x94

// Move cursor to Line 4, Position 0 (for 20x4 LCD)
#define GOTO_LINE4_POS0 0xD4

// Move cursor to the beginning of CGRAM
// Used for creating custom characters
#define GOTO_CGRAM_START 0x40

// ---------------- LCD Hardware Configuration ----------------

// LCD mode selection
// 8 means LCD is operating in 8-bit mode
#define LCD_MODE 8

// Starting bit position of LCD data bus
// LCD data pins are connected from P0.8 onwards
#define LCD_DATA 8

// LCD Register Select (RS) pin connected to P0.16
#define LCD_RS 16

// LCD Read/Write (RW) pin connected to P0.18
#define LCD_RW 18

// LCD Enable (EN) pin connected to P0.17
#define LCD_EN 17
