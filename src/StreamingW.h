/*******************************************************************************************
 *
 * The StreamingW library overloads the << operator with optional leading fill characters.
 * The Examples show a variety of ways you can print out values of fixed widths.
 * StreamingW is based on the Streaming library by Mikal Hart. See this link:
 * <http://arduiniana.org/libraries/streaming/>
 *
 *******************************************************************************************
 * License:
 * This file is part of the StreamingW library.
 *
 * StreamingW is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * StreamingW is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public in
 * ../StreamingW/extras/gpl-3.0.txt. If not, see:
 * <http://www.gnu.org/licenses/licenses.html>.
 * 
 *******************************************************************************************
 */
 
#ifndef STREAMING_W_H
#define STREAMING_W_H

#include <Arduino.h>
#include <Print.h>
#include <Streaming.h>  // For endl & other << methods.

namespace StreamingW {
  static const byte   STREAMING_W_VER_MAJOR     =    1; // Major version.
  static const byte   STREAMING_W_VER_MINOR     =    4; // Minor version.
}

// Stripped down version of PString that does not protect against buffer overflow, etc.
class _TrivStr : public Print
{
  public:
    // Basic constructor requires a preallocated buffer
    _TrivStr(char *buf) : _buf(buf) { *_buf = '\0'; }

  virtual size_t write(uint8_t b) {
    *_buf++ = (char)b;
    *_buf   = '\0';
    return 1;
  }
  
  private:
    char              *_buf;                            // Buffer pointer. 
};

// Template struct to width adjust arbitrary types with arbitrary print sizes.
template <class T, size_t W> struct _WIDTH {
  static const size_t BUF_SIZ       =                W; // Buffer size.
  T                   val;
  size_t              width;
  char                fill;
  _WIDTH(T v, size_t w = 0, char c = ' ') : val(v), width(w), fill(c) {}
};

// Template method to handle << for _WIDTH arbitrary types.
template <class T, size_t W> Print &operator <<(Print &obj, const _WIDTH <T, W> &arg) {
  size_t              length;                           // Print length.
  size_t              i;                                // Index variable.
  char                buf[W];                           // Buffer to hold T chars.                       
  _TrivStr            ps(buf);                          // print target.
  
  // Print arg.val and store result in ps.
  length = ps.print(arg.val);

  // Print fill characters.
  for (i = length; i < arg.width; i++) {
    obj.write(arg.fill);
  }

  // Print arg.val print() result in ps.
  obj.write(buf, length);
  
  return obj;
}

/*
 *             Printed character counts for basic data types
 *  
 *  type                             chars + \0         Char # Passed Width
 *  -----------------------------------------------------------------------
 *  char                                         X\0         2            2
 *  signed char                               -127\0         5            6
 *  unsigned char                              255\0         4            4
 *  int                                     -32767\0         7            8
 *  unsigned int                             65535\0         6            6
 *  long                               -2147483647\0        12           12
 *  unsigned long                       4294967295\0        11           12
 *  BIN ulong     11111111111111111111111111111111\0        33           34
 *  float             -4294967040.0000000000000000\0        29           30
 */

// Specializations of _WIDTH for common types.
typedef _WIDTH<char,           2>   _CHARW;
typedef _WIDTH<signed char,    6>   _SCHARW;
typedef _WIDTH<unsigned char,  4>   _UCHARW;
typedef _WIDTH<int,            8>   _INTW;
typedef _WIDTH<unsigned int,   6>   _UINTW;
typedef _WIDTH<long,          12>   _LONGW;
typedef _WIDTH<unsigned long, 12>   _ULONGW;

// Define _BYTEW for old and new system libraries.
#if ARDUINO >= 100

// Define _BYTEW for byte data type,
// Testing showed that _UCHARW works as well as creating an explicit _BYTEW type.
//typedef _WIDTH<byte,           4>   _BYTEW;
typedef _UCHARW                     _BYTEW;

#else

// byte does not exist. Use _BASEDW with BYTE at the base.
typedef _UCHARW                     _BYTEW;

#endif // ARDUINO >= 100

// struct to handle width adjust for pointer to char (const char *).
struct _PCHARW
{ 
  const char          *val; 
  size_t              width;
  char                fill;
  _PCHARW(const char *v, size_t w = 0, char c = ' '): val(v), width(w), fill(c) {}
};

// Method to handle << for _PCHARW.
Print &operator <<(Print &obj, const _PCHARW &arg);

// struct to handle width adjust for Flash stored pointer to char (const char *).
struct _PCHARFW
{ 
  const __FlashStringHelper *val; 
  size_t                    width;
  char                      fill;
  _PCHARFW(const __FlashStringHelper *v, size_t w = 0, char c = ' ') :
  val(v), width(w), fill(c) {}
};

// Method to handle << for _PCHARFW.
Print &operator <<(Print &obj, const _PCHARFW &arg);

// struct to handle  width adjust for print objects that include the base (DEC, HEX, etc.).
struct _BASEDW 
{ 
  static const size_t BUF_SIZ       =               34; // Max ulong as BIN + '\0'.
  long                val; 
  int                 base;
  size_t              width;
  char                fill;
  bool                isSigned;
  
  // Create explicit constructors for each data type to suppress sign extenstion for
  // signed char and signed int data types. Other data types are below.
  _BASEDW(long          v, int b = DEC, size_t w = 0, int c = ' '): val(v), base(b), width(w), fill(c) { isSigned = true;  }  
  _BASEDW(unsigned long v, int b = DEC, size_t w = 0, int c = ' '): val(v), base(b), width(w), fill(c) { isSigned = false; }  
  _BASEDW(unsigned char v, int b = DEC, size_t w = 0, int c = ' '): val(v), base(b), width(w), fill(c) { isSigned = false; }  
  _BASEDW(unsigned int  v, int b = DEC, size_t w = 0, int c = ' '): val(v), base(b), width(w), fill(c) { isSigned = false; }  

  // Suppress sign extension for the signed char data type unless it is in the DEC base.
  _BASEDW(signed char   v, int b = DEC, size_t w = 0, int c = ' '): val(v), base(b), width(w), fill(c) {
    isSigned = true;
    if (base != DEC) {
      val &= 0xFF;
    }
  }
    
  // Suppress sign extension for the signed int data type unless it is in the DEC base.
  _BASEDW(signed int    v, int b = DEC, size_t w = 0, int c = ' '): val(v), base(b), width(w), fill(c) {
    isSigned = true;
    if (base != DEC) {
      val &= 0xFFFF;
    }
  }
};

// Method to handle << for _BASEDW.
Print &operator <<(Print &obj, const _BASEDW &arg);

#define _HEXW(a, ...)   _BASEDW(a, HEX, ##__VA_ARGS__)
#define _DECW(a, ...)   _BASEDW(a, DEC, ##__VA_ARGS__)
#define _OCTW(a, ...)   _BASEDW(a, OCT, ##__VA_ARGS__)
#define _BINW(a, ...)   _BASEDW(a, BIN, ##__VA_ARGS__)

#if ARDUINO >= 18

/*  _MAX_FLOAT_P is the largest float the Print::print routines will print.
 *  This is 1.7FFFFFe31 base 2 or 0xFFFFFF00.
 */
const float           _MAX_FLOAT_P  =     4294967040.0;

// struct to handle width adjust for (float) values.
struct _FLOATW
{
  static const size_t BUF_SIZ       =               30; // Max float with 16 bit precision.
  static const size_t MAX_DIGITS    =               16; // Max digits of precision.
  float               val;
  int                 digits;
  size_t              width;
  char                fill;
  _FLOATW(float v, int d = 2, int w = 0, char c = ' '): val(v), digits(d), width(w), fill(c) {
    // Limit precision to MAX_DIGITS to limit formatted string length.
    if (digits > MAX_DIGITS) {
      digits = MAX_DIGITS;
    }
  }
};

// Method to handle << for _FLOATW.
Print &operator <<(Print &obj, const _FLOATW &arg);

#endif // ARDUINO >= 18

#endif // STREAMING_W_H
