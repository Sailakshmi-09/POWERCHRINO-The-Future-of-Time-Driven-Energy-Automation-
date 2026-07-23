// ---------------- Generic Pin Function Codes ----------------

// PINFUNC1 corresponds to Function 0 (usually GPIO mode)
#define PINFUNC1 0

// PINFUNC2 corresponds to Function 1
#define PINFUNC2 1

// PINFUNC3 corresponds to Function 2
#define PINFUNC3 2

// PINFUNC4 corresponds to Function 3
#define PINFUNC4 3

// ---------------- External Interrupt Pin Functions ----------------

// Configure P0.1 as EINT0 (External Interrupt 0)
#define EINT0_0_1    PINFUNC4

// Configure P0.3 as EINT1 (External Interrupt 1)
#define EINT1_0_3    PINFUNC4

// Configure P0.7 as EINT2 (External Interrupt 2)
#define EINT2_0_7    PINFUNC4

// ---------------- UART0 Pin Functions ----------------

// Configure P0.0 as UART0 Transmit pin (TxD0)
#define UART0_TXD_0_0 PINFUNC2

// Configure P0.1 as UART0 Receive pin (RxD0)
#define UART0_RXD_0_1 PINFUNC2
