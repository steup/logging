/*******************************************************************************
 *
 * Copyright (c) 2008-2010 Michael Schulze <mschulze@ivs.cs.uni-magdeburg.de>
 * All rights reserved.
 *
 *    Redistribution and use in source and binary forms, with or without
 *    modification, are permitted provided that the following conditions
 *    are met:
 *
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *    * Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in
 *      the documentation and/or other materials provided with the
 *      distribution.
 *
 *    * Neither the name of the copyright holders nor the names of
 *      contributors may be used to endorse or promote products derived
 *      from this software without specific prior written permission.
 *
 *
 *    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 *    IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 *    TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 *    PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *    OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *    LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *    THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * $Id$
 *
 ******************************************************************************/

#ifndef __PROGRAMMEMORYSTRING_h__
#define __PROGRAMMEMORYSTRING_h__

/*!
 * \def PROGMEMSTRING
 * \brief A %PROGMEMSTRING enables the placement of string constants in the
 *        text segment, allowing the reduction of needed RAM on some processor
 *        architectures like the AVRs.
 *
 *        Especially in the embedded field the RAM is often a constrained
 *        ressource. Enabling the placement of constant strings in e.g. the
 *        FLASH memory allows reducing the needed RAM. For the AVR platform,
 *        the %logging framework supports such a feature by using the
 *        %PROGMEMSTRING macro. This macro places the string constant in the
 *        none volatile memory, creates a temporarly variable that abstracts
 *        the access to the given string, and is used by the %logging
 *        framework. On architecture without the need for such a feature, or on
 *        those not yet supported, the macro substituation results in the
 *        string constant. Thus, the %PROGMEMSTRING macro can be used always.
 *
 * \param s the string constant
 */

#ifndef __AVR__

#define PROGMEMSTRING(s) s

#else

#include <avr/pgmspace.h>
namespace logging {
    struct ProgramMemoryString {

      char operator[](int index) const {
          return static_cast<char>(pgm_read_byte_far( str + index));
      }

      const prog_char *str;
    };

    inline ::logging::loggingReturnType&
    operator << (logging::loggingReturnType& out, const ProgramMemoryString& pms) {
        size_t c=0;
        while ( pms[c] )
            out << pms[c++];
        return out;
    }
}

#define PROGMEMSTRING(s)                                           \
    (__extension__({                                               \
        static prog_char __str[] = (s);                            \
        ::logging::ProgramMemoryString __pms={&__str[0]};          \
        __pms;                                                     \
    }))

#endif

#endif // __PROGRAMMEMORYSTRING_h__

