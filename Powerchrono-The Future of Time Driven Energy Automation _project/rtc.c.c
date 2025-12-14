#include <LPC21xx.h>
#include "rtc_defines.h"
#include "rtc.h"
#include "types.h"
#include "lcd.h"
#include "lcd_defines.h"
//array to hold names of days of the week
char week[][4]={"SUN","MON","TUE","WED","THU","FRI","SAT"};
/*Initialize the real time clock (RTC) this function disables the rtc, sets the prescalar values,and then enables the rtc*/
void RTC_Init(void)
{
//disable and reset the rtc
CCR=RTC_RESET;
#ifdef _LPC2148
//enable the rtc & select the clock source
CCR=RTC_ENABLE|RTC_CLKSRC;
#else
//set prescalar integer and fractional parts
PREINT=PREINT_VAL;
PREFRAC=PREFRAC_VAL;
//enable the rtc
CCR=RTC_ENABLE;
#endif
}
/*get the current rtc time hour pointer to  store the current hour, minute pointer to store the current minute,
second pointer to store current seconds*/
void GetRTCTimeInfo(u32 *hour,u32 *minute,u32 *second)
{
*hour=HOUR;
*minute=MIN;
*second=SEC;
}
/*display the rtc time on lcd hour value (0-23),minute value (0-59),seconds value(0-59) separated by':'*/
void DisplayRTCTime(u32 hour,u32 minute,u32 second)
{
cmdLCD(GOTO_LINE1_POS0);
charLCD((hour/10)+48);
charLCD((hour%10)+48);
charLCD(':');
charLCD((minute/10)+48);
	charLCD((minute%10)+48);
charLCD(':');
charLCD((second/10)+48);
charLCD((second%10)+48);
}
/*get the current rtc date pointer to store current data(1-31),month pointer to store surrent month(1-12),year pointer to store current year (four digits)*/
void GetRTCDateInfo(u32 *date,u32 *month,u32 *year)
{
*date=DOM;
*month=MONTH;
*year=YEAR;
}
/*display the rtc date on lcd display day of month(1-31),month(1-12),year(four digit) and separated by'/'*/
void DisplayRTCDate(u32 date,u32 month,u32 year)
{
cmdLCD(GOTO_LINE2_POS0);
charLCD((date/10)+48);
charLCD((date%10)+48);
charLCD('/');
charLCD((month/10)+48);
charLCD((month%10)+48);
charLCD('/');
u32LCD(year);
}
void SetRTCTimeInfo(u32 hour,u32 minute,u32 second)
{
HOUR=hour;
MIN=minute;
SEC=second;
}
/*set the rtc  date day of month(1-31),month(1-12),year of set(four digits)*/
void SetRTCDateInfo(u32 date,u32 month,u32 year)
{
DOM=date;
MONTH=month;
YEAR=year;
}
/*get the current day of the week dow pointer to store day of week(0=sun.....6=sat)*/
void GetRTCDay(u32 *day)
{
*day=DOW;
}
/*display the current day of the week on lcd dow (day of week)(0=sun....6=sat)*/
void DisplayRTCDay(u32 dow)
{
cmdLCD(GOTO_LINE2_POS0+11);
strLCD(week[dow]);
}
/*set the day of the week in rtc day of week to set(0=sun.....6=sat)*/
void SetRTCDay(u32 day)
{
DOW=day;
}
