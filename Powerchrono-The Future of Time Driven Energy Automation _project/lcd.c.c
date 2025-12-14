#include "types.h"
#include <LPC21xx.h>
#include "LCD_defines.h"
#include "delay.h"
#include "defines.h"
void writeLCD(u8 byte)
{
#if LCD_MODE==8
//select write operation
IOCLR0=1<<LCD_RW;
//write any byte onto datapin(do/p0.8-d7/p0.15)
WRITEBYTE(IOPIN0,LCD_DATA,byte);
//provide high to low pulse on en pin
IOSET0=1<<LCD_EN;
delay_us(1);
IOCLR0=1<<LCD_EN;
delay_ms(2);
#elif LCD_MODE==4
//statements to be added
#endif
}
void cmdLCD(u8 cmdByte)
{
//select cmd instructions reg
IOCLR0=1<<LCD_RS;
//write cmd to hd44780 controller
writeLCD(cmdByte);
}
void InitLCD(void)
{
//cfg p0.8 to p0.15,p0.16,p0.17,p0.18 as gpio output pins
IODIR0 |=((0xFF<<LCD_DATA)|(1<<LCD_RS)|(1<<LCD_RW)|(1<<LCD_EN));
//delay after power on
delay_ms(15);
cmdLCD(MODE_8BIT_1LINE);
delay_ms(4);
delay_us(100);
cmdLCD(MODE_8BIT_1LINE);
delay_us(100);
cmdLCD(MODE_8BIT_1LINE);
cmdLCD(MODE_8BIT_2LINE);
cmdLCD(DSP_ON_CUR_BLINK);
cmdLCD(CLEAR_LCD);
cmdLCD(SHIFT_CUR_RIGHT);
}
void charLCD(u8 asciival)
{
//select data reg
IOSET0=1<<LCD_RS;
//write to ddram viadata reg
writeLCD(asciival);
}
void strLCD(s8 *s)
{
while(*s)
charLCD(*s++);
}
void u32LCD(u32 n)
{
s32 i=0;
u8 a[10];
if(n==0)
{
charLCD('0');
}
else
{
while(n>0)
{
a[i++]=(n%10)+48;
n=n/10;
}
for(--i;i>=0;i--)
charLCD(a[i]);
}
}
void s32LCD(s32 n)
{
if(n<0)
{
	charLCD('-');
n=-n;
}
u32LCD(n);
}
void f32LCD(f32 fn,u8 nDP)
{
u32 n,i;
if(fn<0.0)
{
charLCD('-');
fn=-fn;
}
n=fn;
u32LCD(n);
charLCD('.');
for(i=0;i<nDP;i++)
{
fn=(fn-n)*10;
n=fn;
charLCD(n+48);
}
}
void BuildCGRAM(u8 *p,u8 nBytes)
{
u32 i;
//point to cgram start
cmdLCD(GOTO_CGRAM_START);
//select data reg
IOSET0=1<<LCD_RS;
//write to cgram vi adata reg
for(i=0;i<nBytes;i++)
{
writeLCD(p[i]);
}
//point back to ddram start
cmdLCD(GOTO_LINE1_POS0+15);
}
