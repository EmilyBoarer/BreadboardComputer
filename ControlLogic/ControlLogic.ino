#define SHIFT_CLK 3
#define SHIFT_DATA 4
#define SHIFT_LATCH 2
#define EEPROM_D0 5
#define EEPROM_D7 12
#define WRITE_EN 13

// address:   00 000 00000000     flags | T step | Instruction Register

 // #define

const unsigned long HLT = 0b000000010000000000000000L; 
const unsigned long CE  = 0b000000100000000000000000L; // PC_INC
const unsigned long J   = 0b000001000000000000000000L; // PC_IN
const unsigned long CO  = 0b000010000000000000000000L; // PC_OUT
const unsigned long II  = 0b000100000000000000000000L; // IR_IN
const unsigned long IO  = 0b001000000000000000000000L; // IR_OUT
const unsigned long EL  = 0b010000000000000000000000L; // ALU_LA
const unsigned long EO  = 0b100000000000000000000000L; // ALU_OUT
const unsigned long FI  = 0b000000000000000100000000L; // FLAG_LA
const unsigned long BI  = 0b000000000000001000000000L; // ALU_IN
const unsigned long AI  = 0b000000000000010000000000L; // ACC_IN
const unsigned long AO  = 0b000000000000100000000000L; // ACC_OUT
const unsigned long MI  = 0b000000000001000000000000L; // MAR_IN
const unsigned long RI  = 0b000000000010000000000000L; // RAM_IN
const unsigned long RO  = 0b000000000100000000000000L; // RAM_OUT
const unsigned long OI  = 0b000000001000000000000000L; // DSP_LA
const unsigned long SU  = 0b000000000000000000000001L; // SUB_EN
const unsigned long RST = 0b000000000000000000000010L; // T_RST
const unsigned long XO  = 0b000000000000000000000100L; // EX_OUT
const unsigned long XI  = 0b000000000000000000001000L; // EX_IN

// #define FLAGS_Z0C0 0
// #define FLAGS_Z0C1 1
// #define FLAGS_Z1C0 2
// #define FLAGS_Z1C1 3

const unsigned long ucode[4][31][8] PROGMEM = { 
  {     // NO FLAGS
    { MI|CO,  RO|II|CE,  HLT,         0,           0,        0,           0,     0   },   // 0000XXXX - HLT
    { MI|CO,  RO|II|CE,  IO|MI,       RO|AI,       RST,      0,           0,     0   },   // 0001XXXX - LOAD_A
    { MI|CO,  RO|II|CE,  IO|AI,       RST,         0,        0,           0,     0   },   // 0010XXXX - LOAD_D
    { MI|CO,  RO|II|CE,  IO|MI,       AO|RI,       RST,      0,           0,     0   },   // 0011XXXX - STOR_A
    { MI|CO,  RO|II|CE,  IO|MI,       RO|BI|EL,    EO|AI,    RST,         0,     0   },   // 0100XXXX - ADD_A
    { MI|CO,  RO|II|CE,  IO|BI|EL,    EO|AI,       RST,      0,           0,     0   },   // 0101XXXX - ADD_D
    { MI|CO,  RO|II|CE,  IO|MI,       RO|BI|EL|SU, EO|AI,    RST,         0,     0   },   // 0110XXXX - SUB_A
    { MI|CO,  RO|II|CE,  IO|BI|EL|SU, EO|AI,       RST,      0,           0,     0   },   // 0111XXXX - SUB_D
    { MI|CO,  RO|II|CE,  RST,         0,           0,        0,           0,     0   },   // 1000XXXX - NOP - nothing yet allocated
    { MI|CO,  RO|II|CE,  CO|MI,       RO|XI|CE,    XO|MI,    IO|RI,       RST,   0   },   // 1001XXXX - SET_D
    { MI|CO,  RO|II|CE,  IO|J,        RST,         0,        0,           0,     0   },   // 1010XXXX - JMP_A
    { MI|CO,  RO|II|CE,  RST,         0,           0,        0,           0,     0   },   // 1011XXXX - JMZ_A    //HERE ARE THE CONDITIONAL STATEMENTS
    { MI|CO,  RO|II|CE,  RST,         0,           0,        0,           0,     0   },   // 1100XXXX - JMO_A   
    { MI|CO,  RO|II|CE,  IO|MI,       RO|OI,       RST,      0,           0,     0   },   // 1101XXXX - OUT_A
    { MI|CO,  RO|II|CE,  AO|OI,       RST,         0,        0,           0,     0   },   // 1110XXXX - OUT
    { MI|CO,  RO|II|CE,  CO|MI,       RO|XI|CE,    XO|MI,    RO|AI,       RST,   0   },   // 11110000 - LOAD_L     
    { MI|CO,  RO|II|CE,  CO|MI,       RO|XI|CE,    XO|MI,    AO|RI,       RST,   0   },   // 11110001 - STOR_L    
    { MI|CO,  RO|II|CE,  CO|MI,       RO|XI|CE,    XO|MI,    RO|BI|EL,    EO|AI, RST },   // 11110010 - ADD_L        
    { MI|CO,  RO|II|CE,  CO|MI,       RO|XI|CE,    XO|MI,    RO|BI|EL|SU, EO|AI, RST },   // 11110011 - SUB_L
    { MI|CO,  RO|II|CE,  CO|MI,       RO|J,        RST,      0,           0,     0   },   // 11110100 - JMP_L
    { MI|CO,  RO|II|CE,  RST,         0,           0,        0,           0,     0   },   // 11110101 - JMZ_L    //HERE ARE THE CONDITIONAL STATEMENTS
    { MI|CO,  RO|II|CE,  RST,         0,           0,        0,           0,     0   },   // 11110110 - JMO_L
    { MI|CO,  RO|II|CE,  CO|MI,       RO|XI,       XO|MI,    RO|OI,       RST,   0   },   // 11110111 - OUT_L
    { MI|CO,  RO|II|CE,  RST,         0,           0,        0,           0,     0   },   // 11111000 - SET_L // not used because impossible with current hardware ? not tried using ACC, but that would probably work but would also mess up the point of this instruction :/
    { MI|CO,  RO|II|CE,  CO|MI,       RO|XI|CE,    XO|MI,    RO|XI,       XO|MI, RO|AI},  // 11111001 - LOAD_I
    { MI|CO,  RO|II|CE,  CO|MI,       RO|XI|CE,    XO|MI,    RO|XI,       XO|MI, AO|RI},   // 11111010 - STOR_I
    { MI|CO,  RO|II|CE,  RST,         0,           0,        0,           0,     0   },   // 11111011 - ADD_I  // impossible with current hardware
    { MI|CO,  RO|II|CE,  RST,         0,           0,        0,           0,     0   },   // 11111100 - SUB_I  // impossible with current hardware
    { MI|CO,  RO|II|CE,  RST,         0,           0,        0,           0,     0   },   // 11111101 - NOP - nothing yet allocated
    { MI|CO,  RO|II|CE,  RST,         0,           0,        0,           0,     0   },   // 11111110 - NOP - nothing yet allocated 
    { MI|CO,  RO|II|CE,  RST,         0,           0,        0,           0,     0   },   // 11111111 - NOP - nothing yet allocated   
  }, {  // ZERO FLAG ONLY
    { MI|CO,  RO|II|CE,  HLT,         0,           0,        0,           0,     0   },   // 0000XXXX - HLT
    { MI|CO,  RO|II|CE,  IO|MI,       RO|AI,       RST,      0,           0,     0   },   // 0001XXXX - LOAD_A
    { MI|CO,  RO|II|CE,  IO|AI,       RST,         0,        0,           0,     0   },   // 0010XXXX - LOAD_D
    { MI|CO,  RO|II|CE,  IO|MI,       AO|RI,       RST,      0,           0,     0   },   // 0011XXXX - STOR_A
    { MI|CO,  RO|II|CE,  IO|MI,       RO|BI|EL,    EO|AI,    RST,         0,     0   },   // 0100XXXX - ADD_A
    { MI|CO,  RO|II|CE,  IO|BI|EL,    EO|AI,       RST,      0,           0,     0   },   // 0101XXXX - ADD_D
    { MI|CO,  RO|II|CE,  IO|MI,       RO|BI|EL|SU, EO|AI,    RST,         0,     0   },   // 0110XXXX - SUB_A
    { MI|CO,  RO|II|CE,  IO|BI|EL|SU, EO|AI,       RST,      0,           0,     0   },   // 0111XXXX - SUB_D
    { MI|CO,  RO|II|CE,  RST,         0,           0,        0,           0,     0   },   // 1000XXXX - NOP - nothing yet allocated
    { MI|CO,  RO|II|CE,  CO|MI,       RO|XI|CE,    XO|MI,    IO|RI,       RST,   0   },   // 1001XXXX - SET_D
    { MI|CO,  RO|II|CE,  IO|J,        RST,         0,        0,           0,     0   },   // 1010XXXX - JMP_A
    { MI|CO,  RO|II|CE,  IO|J,        RST,         0,        0,           0,     0   },   // 1011XXXX - JMZ_A    //HERE ARE THE CONDITIONAL STATEMENTS
    { MI|CO,  RO|II|CE,  RST,         0,           0,        0,           0,     0   },   // 1100XXXX - JMO_A   
    { MI|CO,  RO|II|CE,  IO|MI,       RO|OI,       RST,      0,           0,     0   },   // 1101XXXX - OUT_A
    { MI|CO,  RO|II|CE,  AO|OI,       RST,         0,        0,           0,     0   },   // 1110XXXX - OUT
    { MI|CO,  RO|II|CE,  CO|MI,       RO|XI|CE,    XO|MI,    RO|AI,       RST,   0   },   // 11110000 - LOAD_L     
    { MI|CO,  RO|II|CE,  CO|MI,       RO|XI|CE,    XO|MI,    AO|RI,       RST,   0   },   // 11110001 - STOR_L    
    { MI|CO,  RO|II|CE,  CO|MI,       RO|XI|CE,    XO|MI,    RO|BI|EL,    EO|AI, RST },   // 11110010 - ADD_L        
    { MI|CO,  RO|II|CE,  CO|MI,       RO|XI|CE,    XO|MI,    RO|BI|EL|SU, EO|AI, RST },   // 11110011 - SUB_L
    { MI|CO,  RO|II|CE,  CO|MI,       RO|J,        RST,      0,           0,     0   },   // 11110100 - JMP_L
    { MI|CO,  RO|II|CE,  RST,         0,           0,        0,           0,     0   },   // 11110101 - JMZ_L    //HERE ARE THE CONDITIONAL STATEMENTS
    { MI|CO,  RO|II|CE,  CO|MI,       RO|J,        RST,      0,           0,     0   },   // 11110110 - JMO_L
    { MI|CO,  RO|II|CE,  CO|MI,       RO|XI,       XO|MI,    RO|OI,       RST,   0   },   // 11110111 - OUT_L
    { MI|CO,  RO|II|CE,  RST,         0,           0,        0,           0,     0   },   // 11111000 - SET_L // not used because impossible with current hardware ? not tried using ACC, but that would probably work but would also mess up the point of this instruction :/
    { MI|CO,  RO|II|CE,  CO|MI,       RO|XI|CE,    XO|MI,    RO|XI,       XO|MI, RO|AI},  // 11111001 - LOAD_I
    { MI|CO,  RO|II|CE,  CO|MI,       RO|XI|CE,    XO|MI,    RO|XI,       XO|MI, AO|RI},   // 11111010 - STOR_I
    { MI|CO,  RO|II|CE,  RST,         0,           0,        0,           0,     0   },   // 11111011 - ADD_I  // impossible with current hardware
    { MI|CO,  RO|II|CE,  RST,         0,           0,        0,           0,     0   },   // 11111100 - SUB_I  // impossible with current hardware
    { MI|CO,  RO|II|CE,  RST,         0,           0,        0,           0,     0   },   // 11111101 - NOP - nothing yet allocated
    { MI|CO,  RO|II|CE,  RST,         0,           0,        0,           0,     0   },   // 11111110 - NOP - nothing yet allocated 
    { MI|CO,  RO|II|CE,  RST,         0,           0,        0,           0,     0   },   // 11111111 - NOP - nothing yet allocated   
  }, {  // CARRY FLAG ONLY
    { MI|CO,  RO|II|CE,  HLT,         0,           0,        0,           0,     0   },   // 0000XXXX - HLT
    { MI|CO,  RO|II|CE,  IO|MI,       RO|AI,       RST,      0,           0,     0   },   // 0001XXXX - LOAD_A
    { MI|CO,  RO|II|CE,  IO|AI,       RST,         0,        0,           0,     0   },   // 0010XXXX - LOAD_D
    { MI|CO,  RO|II|CE,  IO|MI,       AO|RI,       RST,      0,           0,     0   },   // 0011XXXX - STOR_A
    { MI|CO,  RO|II|CE,  IO|MI,       RO|BI|EL,    EO|AI,    RST,         0,     0   },   // 0100XXXX - ADD_A
    { MI|CO,  RO|II|CE,  IO|BI|EL,    EO|AI,       RST,      0,           0,     0   },   // 0101XXXX - ADD_D
    { MI|CO,  RO|II|CE,  IO|MI,       RO|BI|EL|SU, EO|AI,    RST,         0,     0   },   // 0110XXXX - SUB_A
    { MI|CO,  RO|II|CE,  IO|BI|EL|SU, EO|AI,       RST,      0,           0,     0   },   // 0111XXXX - SUB_D
    { MI|CO,  RO|II|CE,  RST,         0,           0,        0,           0,     0   },   // 1000XXXX - NOP - nothing yet allocated
    { MI|CO,  RO|II|CE,  CO|MI,       RO|XI|CE,    XO|MI,    IO|RI,       RST,   0   },   // 1001XXXX - SET_D
    { MI|CO,  RO|II|CE,  IO|J,        RST,         0,        0,           0,     0   },   // 1010XXXX - JMP_A
    { MI|CO,  RO|II|CE,  RST,         0,           0,        0,           0,     0   },   // 1011XXXX - JMZ_A    //HERE ARE THE CONDITIONAL STATEMENTS
    { MI|CO,  RO|II|CE,  IO|J,        RST,         0,        0,           0,     0   },   // 1100XXXX - JMO_A   
    { MI|CO,  RO|II|CE,  IO|MI,       RO|OI,       RST,      0,           0,     0   },   // 1101XXXX - OUT_A
    { MI|CO,  RO|II|CE,  AO|OI,       RST,         0,        0,           0,     0   },   // 1110XXXX - OUT
    { MI|CO,  RO|II|CE,  CO|MI,       RO|XI|CE,    XO|MI,    RO|AI,       RST,   0   },   // 11110000 - LOAD_L     
    { MI|CO,  RO|II|CE,  CO|MI,       RO|XI|CE,    XO|MI,    AO|RI,       RST,   0   },   // 11110001 - STOR_L    
    { MI|CO,  RO|II|CE,  CO|MI,       RO|XI|CE,    XO|MI,    RO|BI|EL,    EO|AI, RST },   // 11110010 - ADD_L        
    { MI|CO,  RO|II|CE,  CO|MI,       RO|XI|CE,    XO|MI,    RO|BI|EL|SU, EO|AI, RST },   // 11110011 - SUB_L
    { MI|CO,  RO|II|CE,  CO|MI,       RO|J,        RST,      0,           0,     0   },   // 11110100 - JMP_L
    { MI|CO,  RO|II|CE,  RST,         0,           0,        0,           0,     0   },   // 11110101 - JMZ_L    //HERE ARE THE CONDITIONAL STATEMENTS
    { MI|CO,  RO|II|CE,  CO|MI,       RO|J,        RST,      0,           0,     0   },   // 11110110 - JMO_L
    { MI|CO,  RO|II|CE,  CO|MI,       RO|XI,       XO|MI,    RO|OI,       RST,   0   },   // 11110111 - OUT_L
    { MI|CO,  RO|II|CE,  RST,         0,           0,        0,           0,     0   },   // 11111000 - SET_L // not used because impossible with current hardware ? not tried using ACC, but that would probably work but would also mess up the point of this instruction :/
    { MI|CO,  RO|II|CE,  CO|MI,       RO|XI|CE,    XO|MI,    RO|XI,       XO|MI, RO|AI},  // 11111001 - LOAD_I
    { MI|CO,  RO|II|CE,  CO|MI,       RO|XI|CE,    XO|MI,    RO|XI,       XO|MI, AO|RI},   // 11111010 - STOR_I
    { MI|CO,  RO|II|CE,  RST,         0,           0,        0,           0,     0   },   // 11111011 - ADD_I  // impossible with current hardware
    { MI|CO,  RO|II|CE,  RST,         0,           0,        0,           0,     0   },   // 11111100 - SUB_I  // impossible with current hardware
    { MI|CO,  RO|II|CE,  RST,         0,           0,        0,           0,     0   },   // 11111101 - NOP - nothing yet allocated
    { MI|CO,  RO|II|CE,  RST,         0,           0,        0,           0,     0   },   // 11111110 - NOP - nothing yet allocated 
    { MI|CO,  RO|II|CE,  RST,         0,           0,        0,           0,     0   },   // 11111111 - NOP - nothing yet allocated  
  }, {  // CARRY & ZERO FLAGS
    { MI|CO,  RO|II|CE,  HLT,         0,           0,        0,           0,     0   },   // 0000XXXX - HLT
    { MI|CO,  RO|II|CE,  IO|MI,       RO|AI,       RST,      0,           0,     0   },   // 0001XXXX - LOAD_A
    { MI|CO,  RO|II|CE,  IO|AI,       RST,         0,        0,           0,     0   },   // 0010XXXX - LOAD_D
    { MI|CO,  RO|II|CE,  IO|MI,       AO|RI,       RST,      0,           0,     0   },   // 0011XXXX - STOR_A
    { MI|CO,  RO|II|CE,  IO|MI,       RO|BI|EL,    EO|AI,    RST,         0,     0   },   // 0100XXXX - ADD_A
    { MI|CO,  RO|II|CE,  IO|BI|EL,    EO|AI,       RST,      0,           0,     0   },   // 0101XXXX - ADD_D
    { MI|CO,  RO|II|CE,  IO|MI,       RO|BI|EL|SU, EO|AI,    RST,         0,     0   },   // 0110XXXX - SUB_A
    { MI|CO,  RO|II|CE,  IO|BI|EL|SU, EO|AI,       RST,      0,           0,     0   },   // 0111XXXX - SUB_D
    { MI|CO,  RO|II|CE,  RST,         0,           0,        0,           0,     0   },   // 1000XXXX - NOP - nothing yet allocated
    { MI|CO,  RO|II|CE,  CO|MI,       RO|XI|CE,    XO|MI,    IO|RI,       RST,   0   },   // 1001XXXX - SET_D
    { MI|CO,  RO|II|CE,  IO|J,        RST,         0,        0,           0,     0   },   // 1010XXXX - JMP_A
    { MI|CO,  RO|II|CE,  IO|J,        RST,         0,        0,           0,     0   },   // 1011XXXX - JMZ_A    //HERE ARE THE CONDITIONAL STATEMENTS
    { MI|CO,  RO|II|CE,  IO|J,        RST,         0,        0,           0,     0   },   // 1100XXXX - JMO_A   
    { MI|CO,  RO|II|CE,  IO|MI,       RO|OI,       RST,      0,           0,     0   },   // 1101XXXX - OUT_A
    { MI|CO,  RO|II|CE,  AO|OI,       RST,         0,        0,           0,     0   },   // 1110XXXX - OUT
    { MI|CO,  RO|II|CE,  CO|MI,       RO|XI|CE,    XO|MI,    RO|AI,       RST,   0   },   // 11110000 - LOAD_L     
    { MI|CO,  RO|II|CE,  CO|MI,       RO|XI|CE,    XO|MI,    AO|RI,       RST,   0   },   // 11110001 - STOR_L    
    { MI|CO,  RO|II|CE,  CO|MI,       RO|XI|CE,    XO|MI,    RO|BI|EL,    EO|AI, RST },   // 11110010 - ADD_L        
    { MI|CO,  RO|II|CE,  CO|MI,       RO|XI|CE,    XO|MI,    RO|BI|EL|SU, EO|AI, RST },   // 11110011 - SUB_L
    { MI|CO,  RO|II|CE,  CO|MI,       RO|J,        RST,      0,           0,     0   },   // 11110100 - JMP_L
    { MI|CO,  RO|II|CE,  CO|MI,       RO|J,        RST,      0,           0,     0   },   // 11110101 - JMZ_L    //HERE ARE THE CONDITIONAL STATEMENTS
    { MI|CO,  RO|II|CE,  CO|MI,       RO|J,        RST,      0,           0,     0   },   // 11110110 - JMO_L
    { MI|CO,  RO|II|CE,  CO|MI,       RO|XI,       XO|MI,    RO|OI,       RST,   0   },   // 11110111 - OUT_L
    { MI|CO,  RO|II|CE,  RST,         0,           0,        0,           0,     0   },   // 11111000 - SET_L // not used because impossible with current hardware ? not tried using ACC, but that would probably work but would also mess up the point of this instruction :/
    { MI|CO,  RO|II|CE,  CO|MI,       RO|XI|CE,    XO|MI,    RO|XI,       XO|MI, RO|AI},  // 11111001 - LOAD_I
    { MI|CO,  RO|II|CE,  CO|MI,       RO|XI|CE,    XO|MI,    RO|XI,       XO|MI, AO|RI},   // 11111010 - STOR_I
    { MI|CO,  RO|II|CE,  RST,         0,           0,        0,           0,     0   },   // 11111011 - ADD_I  // impossible with current hardware
    { MI|CO,  RO|II|CE,  RST,         0,           0,        0,           0,     0   },   // 11111100 - SUB_I  // impossible with current hardware
    { MI|CO,  RO|II|CE,  RST,         0,           0,        0,           0,     0   },   // 11111101 - NOP - nothing yet allocated
    { MI|CO,  RO|II|CE,  RST,         0,           0,        0,           0,     0   },   // 11111110 - NOP - nothing yet allocated 
    { MI|CO,  RO|II|CE,  RST,         0,           0,        0,           0,     0   },   // 11111111 - NOP - nothing yet allocated  
  }
};

void setAddress(int address, bool outputEnable) {
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (address >> 8) | (outputEnable ? 0x00 : 0x80));
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, address);

  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
}

byte readEEPROM(int address) {
  for (int pin = EEPROM_D0; pin <= EEPROM_D7; pin += 1) {
    pinMode(pin, INPUT);
  }
  setAddress(address, /*outputEnable*/ true);

  byte data = 0;
  for (int pin = EEPROM_D7; pin >= EEPROM_D0; pin -= 1) {
    data = (data << 1) + digitalRead(pin);
  }
  return data;
}

void writeEEPROM(int address, byte data) {
  setAddress(address, /*outputEnable*/ false);
  for (int pin = EEPROM_D0; pin <= EEPROM_D7; pin += 1) {
    pinMode(pin, OUTPUT);
  }

  for (int pin = EEPROM_D0; pin <= EEPROM_D7; pin += 1) {
    digitalWrite(pin, data & 1);
    data = data >> 1;
  }
  digitalWrite(WRITE_EN, LOW);
  delayMicroseconds(5);
  digitalWrite(WRITE_EN, HIGH);
  delay(20);
}

void printContents(int start, int length) {
  for (int base = start; base < length; base += 16) {
    byte data[16];
    for (int offset = 0; offset <= 15; offset += 1) {
      data[offset] = readEEPROM(base + offset);
    }

    char buf[80];
    sprintf(buf, "%03x:  %02x %02x %02x %02x %02x %02x %02x %02x   %02x %02x %02x %02x %02x %02x %02x %02x",
            base, data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7],
            data[8], data[9], data[10], data[11], data[12], data[13], data[14], data[15]);

    Serial.println(buf);
  }
}

void setup() {
  pinMode(SHIFT_DATA, OUTPUT);
  pinMode(SHIFT_CLK, OUTPUT);
  pinMode(SHIFT_LATCH, OUTPUT);
  digitalWrite(WRITE_EN, HIGH);
  pinMode(WRITE_EN, OUTPUT);
  Serial.begin(57600);

  // Program data bytes
  Serial.print("Programming EEPROM");
  
  byte target;

  
  // address:   00 000 00000000     flags | T step | Instruction Register
  for (int address = 0; address < 8192; address += 1) {
    int flags           = (address & 0b1100000000000) >> 8+3;
    int fullinstruction = (address & 0b0000000001111);
    int partinstruction = (address & 0b0000011110000) >> 4;
    int step            = (address & 0b0011100000000) >> 8;

    // // char buf[6];
    // if (partinstruction < 0b1111){
    //   // sprintf(buf,"%06x",pgm_read_dword(&ucode[flags][partinstruction][step]));
    //   Serial.println(pgm_read_dword(&ucode[flags][partinstruction][step]), HEX);
    // }else{
    //   // sprintf(buf,"%06x",pgm_read_dword(&ucode[flags][partinstruction+fullinstruction][step]));
    //   Serial.println(pgm_read_dword(&ucode[flags][partinstruction][step]), HEX);
    // }
    // // Serial.println(buf);  // debugging

    if (partinstruction < 0b1111){
      // L EEPROM
      target = (pgm_read_dword(&ucode[flags][partinstruction][step]) & (255L<<16)) >> 16;

      // C EEPROM
      // target = (pgm_read_dword(&ucode[flags][partinstruction][step]) & (255<<8)) >> 8;

      // R EEPROM
      // target = (pgm_read_dword(&ucode[flags][partinstruction][step]) & (255));
    } else {
      // L EEPROM
      target = (pgm_read_dword(&ucode[flags][partinstruction + fullinstruction][step]) & (255L<<16)) >> 16;

      // C EEPROM
      // target = (pgm_read_dword(&ucode[flags][partinstruction + fullinstruction][step]) & (255<<8)) >> 8;

      // R EEPROM
      // target = (pgm_read_dword(&ucode[flags][partinstruction + fullinstruction][step]) & 255);
    }

    // write target to EEPROM, and check it wrote properly
    for (int i = 0; i < 10; i++){

      writeEEPROM(address, target);

      if (readEEPROM(address) == target){
        i = 100;
      }
    }
    
    if (address % 64 == 0) {
      Serial.print(".");
    }
  }
  

  Serial.println(" done");

  Serial.println("Reading EEPROM"); // output the actual contents of the EEPROM
  printContents(0,8192);
}


void loop() {
  // put your main code here, to run repeatedly:

}
