/*******************************************************************************************
 *
 * StreamingW library method implementations.
 * See StreamingW.h for information on this library.
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
 
#include <StreamingW.h>

// Implementation of method to handle << for _PCHARW.
Print &operator <<(Print &obj, const _PCHARW &arg) {
  size_t              length        =                0; // char[] length. Assume 0.
  size_t              i;                                // Index variable.

  // Calculate length of the string arg.val.
  if (arg.val != 0) {
    length = strlen(arg.val);
  }

  // Print fill characters before the string in arg.val.
  for (i = length; i < arg.width; i++) {
    obj.write(arg.fill);
  }

  // Print characters pointed to by arg.val.
  if (arg.val != 0) {
    obj.write(arg.val, length);
  }

  return obj;
}

// Implementation of method to handle << for _PCHARFW.
Print &operator <<(Print &obj, const _PCHARFW &arg) {
  size_t              length        =                0; // char[] length. Assume 0.
  size_t              i;                                // Index variable.
  PGM_P               p = reinterpret_cast<PGM_P>(arg.val); // Program memory pointer.
  char                c;                                // Character variable.

  // Calculate length of the Flash string pointed to by p.
  if (p != 0) {
    length = strlen_P(p);
  }

  // Print fill characters before the Flash string in p.
  for (i = length; i < arg.width; i++) {
    obj.write(arg.fill);
  }

  // Print Flash characters pointed to by p.
  if (p != 0) {
    while (true) {
      if ((c = pgm_read_byte(p++)) == 0) {
        break;
      }
      if (obj.write(c) == 0) {
        break;
      }
    }
  }
  
  return obj;
}

// Implementation of method to handle << for _BASEDW.
Print &operator <<(Print &obj, const _BASEDW &arg) {
  size_t              length;                           // Float print length.
  size_t              i;                                // Index variable.
  char                buf[_BASEDW::BUF_SIZ];            // Buffer to hold float chars.                       
  _TrivStr            ps(buf);                          // print target.

  // Print arg.val and store result in ps.
  if (arg.isSigned == true) {
    length = ps.print((signed long)arg.val, arg.base);
  }
  else {
    length = ps.print((unsigned long)arg.val, arg.base);
  }

  // Print fill characters.
  for (i = length; i < arg.width; i++) {
    obj.write(arg.fill);
  }

  // Print arg.val print() result in buf.
  obj.write(buf, length);
  
  return obj;
}

#if ARDUINO >= 18

// Method to handle << for _FLOATW.
Print & operator <<(Print &obj, const _FLOATW &arg) {
  size_t              length;                           // Float print length.
  size_t              i;                                // Index variable.
  char                buf[_FLOATW::BUF_SIZ];            // Buffer to hold float chars.                       
  _TrivStr            ps(buf);                          // print target.
  
  // Print arg.val and store result in ps.
  length = ps.print(arg.val, arg.digits);

  // Print fill characters.
  for (i = length; i < arg.width; i++) {
    obj.write(arg.fill);
  }
  
  // Print arg.val print() result in buf.
  obj.write(buf, length);
  
  return obj;
}

#endif // ARDUINO >= 18
