// ---------------- Bit Manipulation Macros ----------------

// Set a specific bit in WORD
// Example: SETBIT(PORT, 3) sets bit 3 to 1
#define SETBIT(WORD,BIT)    (WORD |= 1 << BIT)

// Clear a specific bit in WORD
// Example: CLEARBIT(PORT, 3) clears bit 3 to 0
#define CLEARBIT(WORD,BIT)  (WORD &= ~(1 << BIT))

// Read the value of a specific bit
// Returns 0 if the bit is cleared, 1 if the bit is set
#define READBIT(WORD,BIT)   ((WORD >> BIT) & 1)

// Write a specific bit with a given level (0 or 1)
// If BITLEVEL is 1, the bit is set; otherwise, it is cleared
#define WRITEBIT(WORD,BITPOS,BITLEVEL) \
        (BITLEVEL ? (WORD |= 1 << BITPOS) : (WORD &= ~(1 << BITPOS)))

// Copy a bit from one word to another
// DBIT = destination bit position
// SBIT = source bit position
// The value of SBIT in SWORD is copied to DBIT in DWORD
#define READWRITEBIT(DWORD,DBIT,SWORD,SBIT) \
        DWORD = ((DWORD & ~(1 << DBIT)) | (((SWORD >> SBIT) & 1) << DBIT))

// Write a bit to either PORT0 or PORT1 of LPC214x
// PORTNO = 0 for Port0, 1 for Port1
// BITPOS = bit position
// BITLEVEL = 0 or 1
#define WRITE2PORTBIT(PORTNO,BITPOS,BITLEVEL) \
  (PORTNO == 0) ? \
        (BITLEVEL ? (IOSET0 = 1 << BITPOS) : (IOCLR0 = 1 << BITPOS)) : \
        (BITLEVEL ? (IOSET1 = 1 << BITPOS) : (IOCLR1 = 1 << BITPOS))

// Write an 8-bit byte at a specified bit position
// Existing 8 bits are cleared before writing the new byte
#define WRITEBYTE(WORD,BITSTARTPOS,BYTE) \
        (WORD = (WORD & ~(0xFF << BITSTARTPOS)) | (BYTE << BITSTARTPOS))

// ---------------- Nibble Manipulation Macros ----------------

// Write a 4-bit nibble at a specified bit position
// Existing 4 bits are cleared before writing the new nibble
#define WRITENIBBLE(WORD,BITSTARTPOS,NIBBLE) \
      WORD = ((WORD & ~(15 << BITSTARTPOS)) | (NIBBLE << BITSTARTPOS))

// Read a 4-bit nibble from a specified bit position
// Returns the value of the selected nibble
#define READNIBBLE(WORD,BITSTARTPOS) ((WORD >> BITSTARTPOS) & 15)
