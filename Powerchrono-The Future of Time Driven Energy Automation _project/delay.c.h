#include "types.h"   // Includes user-defined data types such as u32
#include "delay.h"   // Includes delay function declarations

// Function to generate a delay in microseconds
void delay_us(u32 dlyus)
{
    // Convert microseconds into loop count
    // Assuming CPU clock is 12 MHz:
    // approximately 12 loop iterations = 1 microsecond
    dlyus *= 12;

    // Decrement the counter until it reaches zero
    // This creates a blocking delay
    while(dlyus--);
}

// Function to generate a delay in milliseconds
void delay_ms(u32 dlyms)
{
    // Convert milliseconds into loop count
    // Assuming CPU clock is 12 MHz:
    // approximately 12,000 loop iterations = 1 millisecond
    dlyms *= 12000;

    // Decrement the counter until it reaches zero
    // This creates a blocking delay
    while(dlyms--);
}

// Function to generate a delay in seconds
void delay_s(u32 dlys)
{
    // Convert seconds into loop count
    // Assuming CPU clock is 12 MHz:
    // approximately 12,000,000 loop iterations = 1 second
    dlys *= 12000000;

    // Decrement the counter until it reaches zero
    // This creates a blocking delay
    while(dlys--);
}
