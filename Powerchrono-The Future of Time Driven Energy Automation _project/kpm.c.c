//kpm.c^M
#include "types.h"
#include<LPC21xx.h>
#include "defines.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "kpm_defines.h"
#include "kpm.h"
#include "delay.h"
u32 kpmLUT[4][4]=
{
{'1','2','3','a'},
{'4','5','6','b'},
{'7','8','9','c'},
{'*','0','#',':'}
};
/*u32 kpmLUT[4][4]=^M

{^M

        {'7','8','9','/'},^M

        {'4','5','6','X'},^M

        {'1','2','3','-'},^M

        {'C','0','=','+'}^M

};*/
void Init_KPM(void)
{
//cfg row lines as gpio out^M
WRITENIBBLE(IODIR1,ROW0,15);
//cfg col lines as gpio in and they be default^M
//WRITENIBBLE(IODIR1,COL0,0);^M
}
u32 Colscan(void)
{
u32 status;
status=READNIBBLE(IOPIN1,COL0);
	return(status<15)?0:1;
}
u32 Rowcheck(void)
{
u32 r;
for(r=0;r<=3;r++)
{
//starting from row 0 check if key was pressed in that row^M
WRITENIBBLE(IOPIN1,ROW0,~(1<<r));
if(Colscan()==0)
{
break;
}
}
//re-initialise all rows ground^M
WRITENIBBLE(IOPIN1,ROW0,0);
return r;
}
u32 Colcheck(void)
{
u32 c;
for(c=0;c<=3;c++)
{
if(READBIT(IOPIN1,COL0+c)==0)
break;
}
return c;
}
u32 Keyscan(void)
{
u32 r,c,keyv;
//wait for any key press^M
while(Colscan());
//if key pressed detected^M
//identify row in which key was pressed^M
r=Rowcheck();
//identify col in which key was pressed
c=Colcheck();
keyv=kpmLUT[r][c];
	delay_ms(200);
return keyv;
}
void ReadNum(u32 *num)
{
        u32 lastkey;
        u8 keyv;
        s8 cnt=0;
        *num=0;
        while(1)
        {
                keyv=Keyscan();
                delay_ms(200);
                lastkey=keyv;
                if(keyv>='0' && keyv<='9')
                {
                        cnt++;
                        *num=(*num*10)+(keyv-48);
                        while(Colscan()==0);
                                cmdLCD(CLEAR_LCD);
                                u32LCD(*num);
                }
                else if(lastkey=='b')
                {
                        if(cnt>0)
                        {
                                while(Colscan()==0);
                                cnt--;
                                *num=*num/10;
                                cmdLCD(GOTO_LINE1_POS0+cnt);
                                charLCD(' ');
                                cmdLCD(GOTO_LINE1_POS0+cnt);
                        }
                }
                else if(lastkey=='a')
                {
                        continue;
                }
                else if(lastkey=='*')
                {
									 while(Colscan()==0);
                        break;
                }
        }
}
