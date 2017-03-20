/*******************************************************************************************
 *
 * StreamingW unit test.
 * See StreamingW.h for information on this library.
 *
 *******************************************************************************************
 * License:
 * This file is part of the ButtonInterrup library.
 *
 * ButtonInterrupt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * ButtonInterrupt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public in
 * ../ButtonInterrupt/extras/gpl-3.0.txt. If not, see:
 * <http://www.gnu.org/licenses/licenses.html>.
 * 
 *******************************************************************************************
 */

#include <StreamingW.h>
#include <Streaming.h>                                                  
#include <limits.h>                                     // Min and max int etc.
#include <float.h>
#include <PString.h>

//#define DEBUG_LOOP                                      // Debug loop();
//#define DEBUG_TESTS                                     // Debug various doXX() tests;

#define LNEGMX (-LONG_MAX - 1)

const byte          VER_MAJOR       =                1; // Major version.
const byte          VER_MINOR       =                4; // Minor version.
const float         MULT            =            1.001; // Multiplier value.

// Forward references.
void printCharLine(size_t charCnt = 80U, char c = '-');

void setup() {
  unsigned long       nu            =              1UL; // unsigned long initialized to 1UL;
  float               nf            =             -1.0; // float initialized to -1.0.
  long                nl            =              -1L; // long initialized to -1L;
 
  // initialize serial communications at 115200 bps:
  Serial.begin(115200);
  Serial.printf(F("Starting StreamingW_Unit_Test version %d.%d, Build date %s %s\n"),
                                                                          VER_MAJOR,
                                                                          VER_MINOR,
                                                                          __DATE__,
                                                                          __TIME__);
  Serial.printf(F("Arduino version %d, Streaming version %d, StreamingW version %d.%d\n"),
                                                      ARDUINO,
                                                      STREAMING_LIBRARY_VERSION,
                                                      StreamingW::STREAMING_W_VER_MAJOR,
                                                      StreamingW::STREAMING_W_VER_MINOR);
                                                                    

  Serial.println(F("\nsizeof() objects."));
  Serial << F("  sizeof(void *)  ") << _UINTW(sizeof(void *),   6) << endl;
  Serial << F("  sizeof(char)    ") << _UINTW(sizeof(char),     6) << endl;
  Serial << F("  sizeof(int)     ") << _UINTW(sizeof(int),      6) << endl;
  Serial << F("  sizeof(long)    ") << _UINTW(sizeof(long),     6) << endl;
  Serial << F("  sizeof(float)   ") << _UINTW(sizeof(float),    6) << endl;
  Serial << F("  sizeof(double)  ") << _UINTW(sizeof(double),   6) << endl;
  Serial << F("  sizeof Print    ") << _UINTW(sizeof(Print),    6) << endl;
  Serial << F("  sizeof _TrivStr ") << _UINTW(sizeof(_TrivStr), 6) << endl;
  Serial << F("  sizeof PString  ") << _UINTW(sizeof(PString),  6) << endl;
  Serial << F("  sizeof Stream   ") << _UINTW(sizeof(Stream),   6) << endl;
  Serial << F("  sizeof Serial   ") << _UINTW(sizeof(Serial),   6) << endl;

  Serial.println(F("\nMaximum values."));
  Serial << F("  (signed char) CHAR_MAX ") << _SCHARW(    (signed char) CHAR_MAX, 28) << endl;  
  Serial << F("  (signed char)-CHAR_MAX ") << _SCHARW(    (signed char)-CHAR_MAX, 28) << endl;  
  Serial << F("               UCHAR_MAX ") << _UCHARW(                 UCHAR_MAX, 28) << endl;  
  Serial << F("      (uint8_t)UCHAR_MAX ") << _UCHARW(        (uint8_t)UCHAR_MAX, 28) << endl;  
  Serial << F("                 INT_MAX ") << _INTW(                     INT_MAX, 28) << endl;  
  Serial << F("                -INT_MAX ") << _INTW(                    -INT_MAX, 28) << endl;  
  Serial << F("                UINT_MAX ") << _UINTW(                   UINT_MAX, 28) << endl;  
  Serial << F("      (uint16_t)UINT_MAX ") << _UINTW(         (uint16_t)UINT_MAX, 28) << endl;  
  Serial << F("                LONG_MAX ") << _LONGW(                   LONG_MAX, 28) << endl;  
  Serial << F("               -LONG_MAX ") << _LONGW(                  -LONG_MAX, 28) << endl;  
  Serial << F("               ULONG_MAX ") << _ULONGW(                 ULONG_MAX, 28) << endl;  
  Serial << F("     (uint32_t)ULONG_MAX ") << _ULONGW(       (uint32_t)ULONG_MAX, 28) << endl;
  Serial << F("           -_MAX_FLOAT_P ") << _FLOATW(  (float)-_MAX_FLOAT_P, 16, 28) << endl;  

  nu /= 0UL;
  nf /= 0.0;
  nl /= 0L;
  Serial.println(F("\nInfinite value 1 divided by 0 tests."));
  Serial << F("         (float)-1.0/0.0 ") << _FLOATW(nf, 16, 28);
  Serial << F(" isinf(-1.0/0.0) ")        << (isinf(nf) ? "true" : "false") << endl;  
  Serial << F("  (unsigned long)1UL/0UL ") << _ULONGW(nu, 28)               << endl;  
  Serial << F("           (long)-11L/0L ") << _LONGW( nl, 28)               << endl;  
  
  Serial.println(F("\nWidth adjusted templated value tests."));
  Serial << F("  char         'X'  width default <")  << _CHARW('X')            << '>' << endl;
  Serial << F("  char         'X'  width       12 <") << _CHARW('X', 12)        << '>' << endl;
  Serial << F("  fill '.'     'X'  width       12 <") << _CHARW('X', 12, '.')   << '>' << endl;
  Serial << F("  uchar        255  width default <" ) << _UCHARW(255)           << '>' << endl;
  Serial << F("  uchar        255  width       12 <") << _UCHARW(255, 12)       << '>' << endl;
  Serial << F("  byte         255  width default <" ) << _BYTEW(255)            << '>' << endl;
  Serial << F("  byte         255  width       12 <") << _BYTEW(255, 12)        << '>' << endl;
  Serial << F("  byte         255  width       12 <") << _BYTEW(255, 12, '0')   << '>' << endl;
  Serial << F("  int       -32767  width default <" ) << _INTW(-32767)          << '>' << endl;
  Serial << F("  int       -32767  width       12 <") << _INTW(-32767, 12)      << '>' << endl;
  Serial << F("  uint       65535  width default <" ) << _UINTW(65535)          << '>' << endl;
  Serial << F("  uint       65535  width       12 <") << _UINTW(65535, 12)      << '>' << endl;
  Serial << F("  uint       65535  width       12 <") << _UINTW(65535, 12, '0') << '>' << endl;
  Serial << F("  long   -1L        width default <" ) << _LONGW(-1L)            << '>' << endl;
  Serial << F("  long   -1L        width       12 <") << _LONGW(-1L, 12)        << '>' << endl;
  Serial << F("  ulong  ULONG_MAX  width default <" ) << _ULONGW(ULONG_MAX)     << '>' << endl;
  Serial << F("  ulong  ULONG_MAX  width       12 <") << _ULONGW(ULONG_MAX, 12) << '>' << endl;
  Serial << F("  ulong  ULONG_MAX  width       12 <") << _ULONGW(ULONG_MAX, 12, '0') << '>'
                                                      << endl;
  Serial << F("  char * <Cat>      width default <" ) << _PCHARW("Cat")         << '>' << endl;
  Serial << F("  char * <Cat>      width       12 <") << _PCHARW("Cat", 12)     << '>' << endl;
  Serial << F("  fill '.'          width       12 <") << _PCHARW("Cat", 12, '.')<< '>' << endl;
  Serial << F("  char * Empty      width default <" ) << _PCHARW("")            << '>' << endl;
  Serial << F("  char * Empty      width       12 <") << _PCHARW("", 12)        << '>' << endl;
  Serial << F("  char * NULL       width default <" ) << _PCHARW((char *)0)     << '>' << endl;
  Serial << F("  char * NULL       width       12 <") << _PCHARW((char *)0, 12) << '>' << endl;
  Serial << F("  Fchar * <Cat>     width default <" ) << _PCHARFW(F("Cat"))     << '>' << endl;
  Serial << F("  Fchar * <Cat>     width       12 <") << _PCHARFW(F("Cat"), 12) << '>' << endl;
  Serial << F("  fill '.'          width       12 <") << _PCHARFW(F("Cat"), 12, '.')
                                                      << '>' << endl;
  Serial << F("  Fchar * Empty     width default <" ) << _PCHARFW(F(""))        << '>' << endl;
  Serial << F("  Fchar * Empty     width       12 <") << _PCHARFW(F(""), 12)    << '>' << endl;
  Serial << F("  Fchar * NULL      width default <" ) << _PCHARFW(0)            << '>' << endl;
  Serial << F("  Fchar * NULL      width       12 <") << _PCHARFW(0, 12)        << '>' << endl;
  
  Serial.println(F("\nWidth adjusted base macros tests."));
  Serial << F("  -1L         default, width default <") << _DECW(-1L)         << '>' << endl;
  Serial << F("  -1L             DEC, width      34 <") << _DECW(-1L, 34)     << '>' << endl;
  Serial << F("  -1L             DEC, width      34 <") << _DECW(-1L, 34)     << '>' << endl;
  Serial << F("  -1L             HEX, width      34 <") << _HEXW(-1L, 34)     << '>' << endl;
  Serial << F("  -1L             OCT, width      34 <") << _OCTW(-1L, 34)     << '>' << endl;
  Serial << F("  -1L             BIN, width      34 <") << _BINW(-1L, 34)     << '>' << endl;
  Serial << F("   1        with leading zeros     <0x") << _HEXW( 1L, 8, '0') << '>' << endl;
  Serial << F("   ULONG_MAX, default, width default <") << _DECW((uint32_t)ULONG_MAX) << '>'
                                                                                      << endl;

  Serial.println(F("\nWidth adjusted base macros tests of chars and ints."));
  Serial << F("   -1 int8 DEC, width      34 <") <<  _DECW( (signed char)-1, 34) << '>' << endl;
  Serial << F("   -1 int8 HEX, width      34 <") <<  _HEXW( (signed char)-1, 34) << '>' << endl;
  Serial << F("   -1 int8 OCT, width      34 <") <<  _OCTW( (signed char)-1, 34) << '>' << endl;
  Serial << F("   -1 int8 BIN, width      34 <") <<  _BINW( (signed char)-1, 34) << '>' << endl;
  Serial << F(" 255 uint8 DEC, width      34 <") <<  _DECW(       (byte)255, 34) << '>' << endl;
  Serial << F(" 255 uint8 HEX, width      34 <") <<  _HEXW(       (byte)255, 34) << '>' << endl;
  Serial << F(" 255 uint8 OCT, width      34 <") <<  _OCTW(       (byte)255, 34) << '>' << endl;
  Serial << F(" 255 uint8 BIN, width      34 <") <<  _BINW(       (byte)255, 34) << '>' << endl;
  Serial << F("  -1   int DEC, width      34 <") <<  _DECW(         (int)-1, 34) << '>' << endl;
  Serial << F("  -1   int HEX, width      34 <") <<  _HEXW(         (int)-1, 34) << '>' << endl;
  Serial << F("  -1   int OCT, width      34 <") <<  _OCTW(         (int)-1, 34) << '>' << endl;
  Serial << F("  -1   int BIN, width      34 <") <<  _BINW(         (int)-1, 34) << '>' << endl;
  Serial << F(" MAX  uint DEC, width      34 <") <<  _DECW(  (word)UINT_MAX, 34) << '>' << endl;
  Serial << F(" MAX  uint HEX, width      34 <") <<  _HEXW(  (word)UINT_MAX, 34) << '>' << endl;
  Serial << F(" MAX  uint OCT, width      34 <") <<  _OCTW(  (word)UINT_MAX, 34) << '>' << endl;
  Serial << F(" MAX  uint BIN, width      34 <") <<  _BINW(  (word)UINT_MAX, 34) << '>' << endl;
  Serial << F("-MAX  long DEC, width      34 <") <<  _DECW(  (long)LNEGMX,   34) << '>' << endl;
  Serial << F("-MAX  long HEX, width      34 <") <<  _HEXW(  (long)LNEGMX,   34) << '>' << endl;
  Serial << F("-MAX  long OCT, width      34 <") <<  _OCTW(  (long)LNEGMX,   34) << '>' << endl;
  Serial << F("-MAX  long BIN, width      34 <") <<  _BINW(  (long)LNEGMX,   34) << '>' << endl;
  Serial << F(" MAX ulong DEC, width      34 <") <<  _DECW((uint32_t)ULONG_MAX, 34)<< '>'<< endl;
  Serial << F(" MAX ulong HEX, width      34 <") <<  _HEXW((uint32_t)ULONG_MAX, 34)<< '>'<< endl;
  Serial << F(" MAX ulong OCT, width      34 <") <<  _OCTW((uint32_t)ULONG_MAX, 34)<< '>'<< endl;
  Serial << F(" MAX ulong BIN, width      34 <") <<  _BINW((uint32_t)ULONG_MAX, 34)<< '>'<< endl;
  

  Serial.println(F("\nWidth adjusted float tests."));
  Serial << F("  default                      <") << _FLOATW(-1.23456      ) << '>' << endl;
  Serial << F("  precision        3, default  <") << _FLOATW(-1.23456, 3   ) << '>' << endl;  
  Serial << F("  precision        3, width 24 <") << _FLOATW(-1.23456, 3,24) << '>' << endl;
  Serial << F("  precision       16, width 24 <") << _FLOATW(-1.23456,16,24) << '>' << endl;
  Serial << F("  prec. too large 17, width 24 <") << _FLOATW(-1.23456,17,24) << '>' << endl;
  Serial << F("  leading . chars   , width 24 <") << _FLOATW(-1.23456,16,24, '.') << '>'
                                                  << endl;
  Serial << F("  width too small 10, width 12 <") << _FLOATW(-1.23456,16,10) << '>' << endl;
}

// Test states in loop().
enum testStep {
  PSTR                              =              'C', // PString performance.
  BYTET                             =              'B', // Explicit vs general performance.
  STRT                              =              'S', // String performance.
  PF                                =              'P', // Stream vs printf performance.
  FP                                =              'F', // Float performance.
  MLOOP                             =              'M', // Multiply tests.
  END                               =              'E', // End tests.
  STOP                              =              '0', // Terminal state. Do nothing.
};

void loop() {
  static char         tStep         =             PSTR; // Test step.
  
  // State machine run through test steps,
  switch (tStep) {
    case PSTR:
      // Test PString or _TrivStr performance.
      if (doPSTR() == false) {
        tStep = BYTET;
        #ifdef DEBUG_LOOP
        Serial << F(">> Going to tStep ") << tStep << endl;
        #endif // DEBUG_LOOP
      }
      break;
      
    case BYTET:
      // Test _BYTEW(byte) versus _BASEDW(byte) << methods.
      if (doByte() == false) {
        tStep = STRT;
        #ifdef DEBUG_LOOP
        Serial << F(">> Going to tStep ") << tStep << endl;
        #endif // DEBUG_LOOP
      }
      break;
      
     case STRT:
      // Test _PCHAW and _PCHARFW << methods.
      if (doSTRT() == false) {
        tStep = PF;
        #ifdef DEBUG_LOOP
        Serial << F(">> Going to tStep ") << tStep << endl;
        #endif // DEBUG_LOOP
      }
      break;
      
     case PF:
      // Test printf vs << methods.
      if (doPF() == false) {
        tStep = FP;
        #ifdef DEBUG_LOOP
        Serial << F(">> Going to tStep ") << tStep << endl;
        #endif // DEBUG_LOOP
      }
      break;
      
     case FP:
      // Test _FLOATW << methods.
      if (doFP() == false) {
        tStep = MLOOP;
        #ifdef DEBUG_LOOP
        Serial << F(">> Going to tStep ") << tStep << endl;
        #endif // DEBUG_LOOP
      }
      break;
     
    case MLOOP:
      // Test repeated float multiplication and print.
      if (doMLOOP() == false) {
        tStep = END;
        #ifdef DEBUG_LOOP
        Serial << F(">> Going to tStep ") << tStep << endl;
        #endif // DEBUG_LOOP
      }
      break;
      
    case END:
      // End the tests.
      tStep = STOP;
      #ifdef DEBUG_LOOP
      Serial << F(">> Going to tStep ") << tStep << endl;
      #endif // DEBUG_LOOP
      printCharLine();
      Serial.println(F("All tests have completed."));
      break;

    case STOP:
      // Activity stopped. Do nothing.
      #ifdef DEBUG_LOOP
      Serial.println(F("In STOP state."));
      delay(5000UL);
      #endif // DEBUG_LOOP
      break;
  }
}

// Print a line of characters.
void printCharLine(size_t charCnt = 80U, char c = '-') {
  while (charCnt-- > 0U) {
    Serial.write(c);
  }
  Serial.println();
}

// Print Results.
void prRslts( unsigned long t1,     const char *t1Str,
              unsigned long t2 = 0, const char *t2Str = "", bool printT1 = true)
{
  const size_t        TSTR_WIDTH    =               16; // Width of strings.
  const size_t        UL_WIDTH      =               12; // Width of unsigned long str.
  const size_t        FL_WIDTH      =                7; // Width of 100.000 str.
  float               pct;                              // Percentage difference.
  const char          *bStr;                            // "better" or "worse".

  if (printT1 == true) {
    Serial << _PCHARW(t1Str, TSTR_WIDTH) << F(" test complete - test time ");
    Serial << _ULONGW(t1, UL_WIDTH) << F("us.") << endl;
  }

  if (t2 != 0U) {    
    Serial << _PCHARW(t2Str, TSTR_WIDTH) << F(" test complete - test time ");
    Serial << _ULONGW(t2, UL_WIDTH) << F("us. ");

    if (t2 <= t1) {
      // t2 shorter than baseline t1.
      pct = (float)((t1 - t2) * 100UL) / (float)t1;
      bStr = "better";
    }
    else {
      // t2 longer than baseline t1.
      pct = (float)((t2 - t1) * 100UL) / (float)t1;
      bStr = "worse";
    }
    
    Serial << _FLOATW(pct, 3, FL_WIDTH);
    Serial << F("% ") << _PCHARW(bStr, 6) <<  '.' << endl;
  }  
}

// <<<<<<<<<<<<<<<<<<<<<<<< Starting indiviual tests. >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
              
// Test the performance of _TrivStr versus PString.
bool doPSTR() {
  const unsigned long LOOP_CNT      =          10000UL; // Number of test loops to run.
  unsigned long       il;                               // ULONG index variable.
  unsigned long       start;                            // Start time in microseconds.
  unsigned long       t1;                               // PString time.
  unsigned long       t2;                               // _TrivStr time.
  static bool         firstCall     =             true; // True on 1st call to method.
 
  // Print header text.
  if (firstCall == true) {
    firstCall = false;
    printCharLine();
    Serial << F("Starting PString versus _TrivStr tests.") << endl;
  }

  start = micros();
  for (il = 0UL; il < LOOP_CNT; il++) {
    testPString();
  }
  t1 = micros();

  // Handle micros() rollover.
  t1 = start < t1 ? t1 - start : t1 + ULONG_MAX - start;
  
  prRslts(t1, "PString");

  start = micros();
  for (il = 0UL; il < LOOP_CNT; il++) {
    test_TrivStr();
  }
  t2 = micros();

  // Handle micros() rollover.
  t2 = start < t2 ? t2 - start : t2 + ULONG_MAX - start;

  prRslts(t1, "PString", t2, "_TrivStr", false);
  
  return false;
} // End doPSTR.

// Longest print string used by PString or _TrivStr. MAX_ULONG as BIN.
const char            *UL_STR = "11111111111111111111111111111111";

// Simulate call to _BASEDW using PString to manage the buffer.
void testPString() {
  size_t              length;                           // Length of string.
  char                buf[_BASEDW::BUF_SIZ];            // _BASEDW::BUF_SIZ if biggest buffer.
  PString             ps(buf, sizeof(buf));             // Test PString object.

  length = ps.print(UL_STR);
}

// Simulate call to _BASEDW using _Trivstr to manage the buffer.
void test_TrivStr() {
  size_t              length;                           // Length of string.
  char                buf[_BASEDW::BUF_SIZ];            // _BASEDW::BUF_SIZ if biggest buffer.
  _TrivStr            ps(buf);                          // Test _TrivStr object.

  length = ps.print(UL_STR); 
}

// Test _BYTEW(byte) versus _BASEDW(byte) << methods.
bool doByte() {
  const unsigned long LOOP_CNT      =          10000UL; // Number of test loops to run.
  unsigned long     il;                                 // ULONG index variable.
  unsigned long     start;                              // Start time in microseconds.
  unsigned long     t1;                                 // Test 1 time.
  unsigned long     t2;                                 // Test 2 time.
  static bool       firstCall       =             true; // True on 1st call to method.
  char              buf[34];                            // Char buffer for PString.
  PString           ps(buf, sizeof(buf));               // Object to handle << calls.

  // Print header text.
  if (firstCall == true) {
    firstCall = false;
    printCharLine();
    Serial << F("Starting _BASEDW tests.") << endl;
  }

  // Begin _BASEW test.
  start = micros();
  for (il = 0UL; il < LOOP_CNT; il++) {
    ps.begin();
    ps << _BASEDW(255U, DEC, 6);
  }
  t1 = micros();

  // Handle micros() rollover.
  t1 = start < t1 ? t1 - start : t1 + ULONG_MAX - start;

  prRslts(t1, "_BASEDW");
  
  // Begin _BYTEW test
  start = micros();
  for (il = 0UL; il < LOOP_CNT; il++) {
    ps.begin();
    ps << _BYTEW((byte)255U, 6);
  }
  t2 = micros();

  // Handle micros() rollover.
  t2 = start < t2 ? t2 - start : t2 + ULONG_MAX - start;

  prRslts(t1, "_BASEDW", t2, "_BYTEW", false);
  // End _BYTEW test.
  
  // Begin _UINTW test.
  start = micros();
  for (il = 0UL; il < LOOP_CNT; il++) {
    ps.begin();
    ps << _UINTW((unsigned int)255U, 6);
  }
  t2 = micros();

  // Handle micros() rollover.
  t2 = start < t2 ? t2 - start : t2 + ULONG_MAX - start;

  prRslts(t1, "_BASEDW", t2, "_UINTW", false);
  // End _UINTW test.
  
  // Begin _ULONGW test.
  start = micros();
  for (il = 0UL; il < LOOP_CNT; il++) {
    ps.begin();
    ps << _ULONGW((unsigned long)255UL, 6);
  }
  t2 = micros();

  // Handle micros() rollover.
  t2 = start < t2 ? t2 - start : t2 + ULONG_MAX - start;

  prRslts(t1, "_BASEDW", t2, "_ULONGW", false);
  // End _ULONGW test.
    
  return false;
} // End doByte.

// Test _PCHAW and _PCHARFW << methods.
#define TST_CHARS ("123456789012345678901234567890")
bool doSTRT() {
  const unsigned long LOOP_CNT      =          10000UL; // Number of test loops to run.
  const char         *TST_STR       =       TST_CHARS;  // 30 char string.
  const __FlashStringHelper* TST_PSTRF = F(TST_CHARS);  // In Flash.
  const size_t      STR_SIZE        =               30; // Length of test string.
  const size_t      PRT_WIDTH       =    STR_SIZE + 10; // Printed string width.
  unsigned long     il;                                 // ULONG index variable.
  unsigned long     start;                              // Start time in microseconds.
  unsigned long     t1;                                 // Test 1 time.
  unsigned long     t2;                                 // Test 2 time.
  static bool       firstCall       =             true; // True on 1st call to method.
  char              buf[PRT_WIDTH + 1];                 // Char buffer for PString.
  PString           ps(buf, sizeof(buf));               // Object to handle << calls.

  // Print header text.
  if (firstCall == true) {
    firstCall = false;
    printCharLine();
    Serial << F("Starting _CHARW and _CHARFW tests. Print width ") << PRT_WIDTH;
    Serial << F(" characters.") << endl;
  }

  // Begin _PCHARW test.
  start = micros();
  for (il = 0UL; il < LOOP_CNT; il++) {
    ps.begin();
    ps << _PCHARW(TST_STR, 40);
  }
  t1 = micros();

  // Handle micros() rollover.
  t1 = start < t1 ? t1 - start : t1 + ULONG_MAX - start;

  prRslts(t1, "_PCHARW");
  // End _PCHARW test.
  
  // Begin _PCHARFW test.
  start = micros();
  for (il = 0UL; il < LOOP_CNT; il++) {
    ps.begin();
    ps << _PCHARFW(TST_PSTRF, 40);
  }
  t2 = micros();

  // Handle micros() rollover.
  t2 = start < t2 ? t2 - start : t2 + ULONG_MAX - start;

  prRslts(t1, "_PCHARW", t2, "_PCHARFW", false);
  // End _PCHARFW test.
  
  // Begin char * test.
  start = micros();
  for (il = 0UL; il < LOOP_CNT; il++) {
    ps.begin();
    ps << TST_STR;
  }
  t2 = micros();

  // Handle micros() rollover.
  t2 = start < t2 ? t2 - start : t2 + ULONG_MAX - start;

  prRslts(t1, "_PCHARW", t2, "<< char *", false);
  // End char * test.
  
  // Begin F() test.
  start = micros();
  for (il = 0UL; il < LOOP_CNT; il++) {
    ps.begin();
    ps << TST_PSTRF;
  }
  t2 = micros();

  // Handle micros() rollover.
  t2 = start < t2 ? t2 - start : t2 + ULONG_MAX - start;

  prRslts(t1, "_PCHARW", t2, "<< F()", false);
  // End F() test.
  
  // Begin print(char *) test.
  start = micros();
  for (il = 0UL; il < LOOP_CNT; il++) {
    ps.begin();
    ps.print(TST_STR);
  }
  t2 = micros();

  // Handle micros() rollover.
  t2 = start < t2 ? t2 - start : t2 + ULONG_MAX - start;

  prRslts(t1, "_PCHARW", t2, "print(char *)", false);
  // End char print(char *).
  
  // Begin print(F()) test.
  start = micros();
  for (il = 0UL; il < LOOP_CNT; il++) {
    ps.begin();
    ps.print(TST_PSTRF);
  }
  t2 = micros();

  // Handle micros() rollover.
  t2 = start < t2 ? t2 - start : t2 + ULONG_MAX - start;

  prRslts(t1, "_PCHARW", t2, "print(F())", false);
  // End char print(F()).
  
  return false;
} // End doSTRT.

// Test printf vs << methods.
#define PRINTF_FMT  "%6u%12s: %12c, %12u, %12u, %12lu."
#define PRINTF_ARGS UCHAR_MAX, "Test", 'X', UCHAR_MAX, UINT_MAX, ULONG_MAX

bool doPF() {
  const unsigned long LOOP_CNT      =          10000UL; // Number of test loops to run.
  unsigned long     il;                                 // ULONG index variable.
  unsigned long     start;                              // Start time in microseconds.
  unsigned long     t1;                                 // Test 1 time.
  unsigned long     t2;                                 // Test 2 time.
  static bool       firstCall       =             true; // True on 1st call to method.
  static char       buf[80];                            // Char buffer for PString.
  static PString    ps(buf, sizeof(buf));               // Object to handle << calls.

  // Print header text.
  if (firstCall == true) {
    firstCall = false;
    printCharLine();
    Serial << F("Starting printf() tests. Print width ");
    ps.printf(F(PRINTF_FMT), PRINTF_ARGS);
    Serial << ps.length() << F(" characters.") << endl;
  }
 
  // Begin << test.
  start = micros();
  for (il = 0UL; il < LOOP_CNT; il++) {
    ps.begin();
    ps << _BASEDW(UCHAR_MAX, DEC, 6);
    ps << _PCHARW(   "Test",     12) << F(": ");
    ps << _CHARW(       'X',     12) << F(", ");
    ps << _UCHARW(UCHAR_MAX,     12) << F(", ");
    ps << _UINTW(  UINT_MAX,     12) << F(", ");
    ps << _ULONGW(ULONG_MAX,     12) << '.';

    #ifdef DEBUG_TESTS
    if (il == 0UL) {
      Serial << F("            << \"") << buf << '\"' << endl;
    }
    #endif // DEBUG_TESTS
  }
  t1 = micros();

  // Handle micros() rollover.
  t1 = start < t1 ? t1 - start : t1 + ULONG_MAX - start;

  prRslts(t1, "<<");

  // Begin printf(F()) test
  start = micros();
  for (il = 0UL; il < LOOP_CNT; il++) {
    ps.begin();
    ps.printf(F(PRINTF_FMT), PRINTF_ARGS);
    
    #ifdef DEBUG_TESTS
    if (il == 0UL) {
      Serial << F("printf(char *) \"") << buf << '\"' << endl;
    }
    #endif // DEBUG_TESTS
  }
  t2 = micros();

  // Handle micros() rollover.
  t2 = start < t2 ? t2 - start : t2 + ULONG_MAX - start;

  prRslts(t1, "<<", t2, "printf(F())", false);
  // End printf(F()) test.
  
  // Begin printf(char *) test
  start = micros();
  for (il = 0UL; il < LOOP_CNT; il++) {
    ps.begin();
    ps.printf(PRINTF_FMT, PRINTF_ARGS);

    #ifdef DEBUG_TESTS
    if (il == 0UL) {
      Serial << F("printf(F()   ) \"") << buf << '\"' << endl;
    }
    #endif // DEBUG_TESTS
  }
  t2 = micros();

  // Handle micros() rollover.
  t2 = start < t2 ? t2 - start : t2 + ULONG_MAX - start;

  prRslts(t1, "<<", t2, "printf(char *)", false);
  // End printf(char *) test.
 
  return false;
} // End doPF.

// Test _FLOATW << methods.
bool doFP() {
  const unsigned long LOOP_CNT      =          10000UL; // Number of test loops to run.
  unsigned long     il;                                 // ULONG index variable.
  unsigned long     start;                              // Start time in microseconds.
  unsigned long     t1;                                 // Test 1 time.
  unsigned long     t2;                                 // Test 2 time.
  static bool       firstCall       =             true; // True on 1st call to method.
  char              buf[34];                            // Char buffer for PString.
  PString           ps(buf, sizeof(buf));               // Object to handle << calls.

  // Print header text.
  if (firstCall == true) {
    firstCall = false;
    printCharLine();
    Serial << F("Starting _FLOATW tests.") << endl;
  }

  // Begin _FLOATW test.
  start = micros();
  for (il = 0UL; il < LOOP_CNT; il++) {
    ps.begin();
    ps << _FLOATW((float)-_MAX_FLOAT_P, 16, 30);
  }
  t1 = micros();

  // Handle micros() rollover.
  t1 = start < t1 ? t1 - start : t1 + ULONG_MAX - start;

  prRslts(t1, "_FLOATW");
  
  // Begin _FLOAT test
  start = micros();
  for (il = 0UL; il < LOOP_CNT; il++) {
    ps.begin();

    // Pad _FLOAT bu 2 spaces to match _FLOATW width.
    ps << "  " << _FLOAT((float)-_MAX_FLOAT_P, 16);
  }
  t2 = micros();

  // Handle micros() rollover.
  t2 = start < t2 ? t2 - start : t2 + ULONG_MAX - start;

  prRslts(t1, "_FLOATW", t2, "_FLOAT", false);
  // End _FLOAT test.
  
  // Begin print() test.
  start = micros();
  for (il = 0UL; il < LOOP_CNT; il++) {
    ps.begin();
    // Pad _FLOAT bu 2 spaces to match _FLOATW width.
    ps.print("  ");    
    ps.print((float)-_MAX_FLOAT_P, 16);
  }
  t2 = micros();

  // Handle micros() rollover.
  t2 = start < t2 ? t2 - start : t2 + ULONG_MAX - start;

  prRslts(t1, "_FLOATW", t2, "print()", false);
  // End print().
  
  return false;
} // End doFP.

// Repeatedly loop multiplying and printing a float until overflow is reached.
bool doMLOOP() {
  static bool           firstCall   =             true; // True on 1st call to method.
  static unsigned long  loopCnt     =              0UL; // Loop count.
  static unsigned long  start;                          // Start time in milliseconds.
  static float          d           =             -1.0; // float value.
  static float          lastD       =                d; // Last good float.
  char                  buf[_FLOATW::BUF_SIZ];          // Float string buffer.
  PString               fStr(buf, sizeof(buf));         // PString to manage buf[].

  // Print header text.
  if (firstCall == true) {
    firstCall = false;
    loopCnt = 0UL;
    printCharLine();
    Serial << F("Starting incremental test. Multiplier ") << _FLOAT(MULT, 6) << endl;
    start = millis();
  }  

  ++loopCnt;
  lastD = d;
  d = d * MULT;

  // Print progress message every 1000 loops.
  if ((loopCnt % 1000) == 0UL) {
    Serial.printf(F("Loops %10lu, "), loopCnt);
    Serial << F("d ") << _FLOATW(d, 4, 18) << endl;
  }
  
  fStr.begin();
  fStr.print(-1.0 * d, 16);
  if (fStr == "ovf") {
    Serial.printf(F(">> Overflow occurred %10lums, Loops %10lu\n"), millis() - start, loopCnt);
    Serial << F("Last good value     ") << _FLOATW(        lastD, 16);
    Serial << F(", Next value ") <<        _FLOATW(            d, 16) << endl;
    Serial << F("Inverse of lastD    ") << _FLOATW(1.0/lastD,     16) << endl;
    Serial << F("Max printable value ") << _FLOATW(-_MAX_FLOAT_P, 16) << endl;

    // Return false to seop running this test.
    return false;
  }

  // Return true to keep running this test.
  return true; 
} // End doMLOOP.

