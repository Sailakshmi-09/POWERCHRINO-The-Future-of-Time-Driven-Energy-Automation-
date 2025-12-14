#include "types.h"
void WriteLCD(u8 byte);
void cmdLCD(u8 cmdByte);
void InitLCD(void);
void charLCD(u8 asciival);
void strLCD(s8 *);
void u32LCD(u32);
void s32LCD(s32);
void f32LCD(f32,u8);
void BuildCGRAM(u8 *,u8);

