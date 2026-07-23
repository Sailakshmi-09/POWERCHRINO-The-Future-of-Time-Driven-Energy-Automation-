#include <LPC21xx.h>
#include "lcd.h"
#include "lcd_defines.h"
#include "kpm_defines.h"
#include "kpm.h"
#include "rtc_defines.h"
#include "rtc.h"
#include "pin_connect_block.h"
#include "pin_function_defines.h"
#include "delay.h"
//for bulb off purpose array
u8 bulboff[8]={0x0e,0x11,0x11,0x11,0x1f,0x0a,0x0a,0x0a};
//for bulb on purpose array
u8 bulbon[8]={0x0e,0x1f,0x1f,0x1f,0x1f,0x0a,0x0a,0x0a};
#define EINT0_VIC_CHNO 14//def p0.1
#define LED  4 //       p0.2
void setONtime(void);
void setOFFtime(void);
void eint0_isr(void)__irq;
void display_menu(void);
void edit_RTC(void);
void edit_ONOFFtime(void);
//gloabal variables declaration
u32 hour,min,sec,date,month,year,day,ONhour,ONmin,OFFhour,OFFmin;
int main()
{
InitLCD();//initialising lcd
Init_KPM();//initialising keypad
RTC_Init();//initialize rtc
while(1)
{
//cfg p0.1 pin as eint0 input pin
CfgPortPinFunc(0,1,PIN_FUNC4);
//cfg VIC peripheral & cfg eint0 as irq types,default all are irq type
//VICIntSelect=0;
//enable eint0 via VIC
VICIntEnable=1<<EINT0_VIC_CHNO;
//cfg eint0 as v.irq with highest priority & allow to load eint0 isr addr
VICVectCntl0=(1<<5)|EINT0_VIC_CHNO;
VICVectAddr0=(u32)eint0_isr;
	//cfg eint0 as edge triggered
EXTMODE=1<<0;
//cfg led status as gpio output
IODIR0 |=1<<LED;
while(1)
{
GetRTCTimeInfo(&hour,&min,&sec);
DisplayRTCTime(hour,min,sec);
GetRTCDateInfo(&date,&month,&year);
DisplayRTCDate(date,month,year);
GetRTCDay(&day);
DisplayRTCDay(day);
cmdLCD(GOTO_LINE1_POS0+11);
strLCD("DEV:");
cmdLCD(GOTO_LINE1_POS0+15);
BuildCGRAM(bulboff,8);
charLCD(0);
//check if rtc hour and rtc min is equal to onhour and onmin
if((HOUR==ONhour)&&(MIN==ONmin))
{
while(1)
{
   //set the led
   IOSET0=1<<LED;
   //on the bulb in lcd
   BuildCGRAM(bulbon,8);
   charLCD(0);
   //after equal of onhour and onmin time will stop ,so to continue time we again dispaly the rtc time functions
   GetRTCTimeInfo(&hour,&min,&sec);
   DisplayRTCTime(hour,min,sec);
   GetRTCDateInfo(&date,&month,&year);
   DisplayRTCDate(date,month,year);
   GetRTCDay(&day);
   DisplayRTCDay(day);
   //check if rtc hour and min is equal to offhour and offmin
   if((HOUR==OFFhour)&&(MIN==OFFmin))
   {
           //bulb off in lcd
   BuildCGRAM(bulboff,8);
   charLCD(0);
		 //clearing the led
   IOCLR0=1<<LED;
   break;
   }
}
}
}
}
}
void eint0_isr(void)__irq
{
display_menu();
//clear eint0 status in external interrupt peripheral
EXTINT=1<<0;
//clear eint0 status in vic
VICVectAddr=0;
}
void display_menu(void)
{
u32 keyV;
cmdLCD(CLEAR_LCD);
cmdLCD(GOTO_LINE1_POS0);
strLCD("interrupt raised");
delay_s(1);
cmdLCD(CLEAR_LCD);
label:cmdLCD(CLEAR_LCD);
strLCD("1.EDITRTCINFO");
cmdLCD(GOTO_LINE2_POS0);
strLCD("2.E.ONOFFT 3.EXT");
//read keypad input
keyV=Keyscan();
delay_ms(1000);
cmdLCD(CLEAR_LCD);
switch(keyV)
{
case '1':edit_RTC();
         goto label;
case '2':edit_ONOFFtime();
         goto label;
case '3':return ;
	default:cmdLCD(CLEAR_LCD);
strLCD("invalid menu");
delay_ms(1000);
goto label;
}
}
//set function for edit RTC
void edit_RTC(void)
{
u32 keyV;
rtc:cmdLCD(CLEAR_LCD);
strLCD("1.H2.MIN3.S4.D");
cmdLCD(GOTO_LINE2_POS0);
strLCD("5.date6.M7.Y8.E");
keyV=Keyscan();
delay_ms(200);
cmdLCD(CLEAR_LCD);
switch(keyV)
{
case '1':
	//edit hours
         h:ReadNum(&hour);
                      if(hour<1 || hour>23)
                      {
                                        cmdLCD(CLEAR_LCD);
                            strLCD("invalid hour!enter again");
                                        delay_ms(500);
                                        cmdLCD(CLEAR_LCD);
                            goto h;
                            }
                                        HOUR=hour;
          goto rtc;
case '2':
	//edit minutes
        m:ReadNum(&min);
         if(min<1 || min>59)
                     {
                      strLCD("invalid min! enter again");
                          delay_ms(500);
                          cmdLCD(CLEAR_LCD);
                           goto m;
                         }
										 MIN=min;
           goto rtc;
case '3':
	//edit seconds
         s:ReadNum(&sec);
         if(sec>59)
                     {
                         cmdLCD(CLEAR_LCD);
                     strLCD("invalid sec! enter again");
                         delay_ms(500);
                         cmdLCD(CLEAR_LCD);
                          goto s;
                         }
                         SEC=sec;
           goto rtc;
case '4':
	//edit day of week
         dow:cmdLCD(GOTO_LINE2_POS0+10);
                     ReadNum(&day);
                     if(day>6)
                     {
                          cmdLCD(CLEAR_LCD);
                      strLCD("invalid day");
                          delay_ms(500);
                          cmdLCD(CLEAR_LCD);
                      goto dow;
                         }
                         DOW=day;
             goto rtc;
case '5':
	//edit day of month
        dom:cmdLCD(GOTO_LINE2_POS0);
         ReadNum(&date);
                     if(date<1 || date>31)
                     {
                     strLCD("invalid date");
                     delay_ms(500);
                     cmdLCD(CLEAR_LCD);
                     goto dom;
                     }
                         DOM=date;
                     goto rtc;
case '6':
	//edit month
        mon:ReadNum(&month);
         if(month<1 ||month>12)
                     {
                     strLCD("invalid month");
                                 delay_ms(500);
                                 cmdLCD(CLEAR_LCD);
                           goto mon;
                           }
                                 MONTH=month;
                           goto rtc;
case '7':
	//edit year
        y:ReadNum(&year);
          if(year>2035)
                     {
                     strLCD("invalid year");
                                 delay_ms(500);
                                 cmdLCD(CLEAR_LCD);
                           goto y;
                           }
                                 YEAR=year;
                           goto rtc;
case '8':return;   //exit RTC editing
default:cmdLCD(CLEAR_LCD);
strLCD("invalid rtc");
delay_ms(1000);
cmdLCD(CLEAR_LCD);
goto rtc;
}
cmdLCD(CLEAR_LCD);
strLCD("RTC updated");
delay_ms(1000);
cmdLCD(CLEAR_LCD);
}
void edit_ONOFFtime(void)
{
u32 keyV;
label:cmdLCD(CLEAR_LCD);
cmdLCD(GOTO_LINE1_POS0);
strLCD("1.D.OnT 2.D.OffT");
	cmdLCD(GOTO_LINE2_POS0);
strLCD("3.Exit");
keyV=Keyscan();
delay_ms(200);
cmdLCD(CLEAR_LCD);
switch(keyV)
{
case '1':setONtime();
          goto label;
case '2':setOFFtime();
          goto label;
case '3':return;
default:cmdLCD(CLEAR_LCD);;
strLCD("invalid on &off time");
delay_ms(500);
cmdLCD(CLEAR_LCD);
goto label;
}
}
//set on time function
void setONtime(void)
{
onh:cmdLCD(CLEAR_LCD);
strLCD("enter on hr(0-23)");
ReadNum(&ONhour);
if(ONhour>23 || ONhour<1)
{
cmdLCD(CLEAR_LCD);
strLCD("invalid onhour ");
delay_ms(500);
cmdLCD(CLEAR_LCD);
goto onh;
}
onmin:cmdLCD(CLEAR_LCD);
strLCD("enter on min(0-59)");
ReadNum(&ONmin);
if(ONmin>59 || ONmin<1)
{
cmdLCD(CLEAR_LCD);
strLCD("invalid on min ");
delay_ms(500);
	cmdLCD(CLEAR_LCD);
goto onmin;
}
}
//set off time function
void setOFFtime(void)
{
offh:cmdLCD(CLEAR_LCD);
strLCD("enter off hr(0-23)");
ReadNum(&OFFhour);
if(OFFhour>23 || OFFhour<1)
{
cmdLCD(CLEAR_LCD);
strLCD("invalid offhour ");
delay_ms(500);
cmdLCD(CLEAR_LCD);
goto offh;
}
offmin:cmdLCD(CLEAR_LCD);
strLCD("enter off min(0-59)");
ReadNum(&OFFmin);
if(OFFmin>59 || OFFmin<1)
{
cmdLCD(CLEAR_LCD);
strLCD("invalid off min ");
delay_ms(500);
cmdLCD(CLEAR_LCD);
goto offmin;
}
}
