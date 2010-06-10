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

#ifndef __ProgramMemoryStringImpl_h__
#define __ProgramMemoryStringImpl_h__

#include "logging/ProgramMemoryString.h"

#ifdef __AVR__

#include <avr/pgmspace.h>
#define PROGMEMTYPE char __attribute__((section(".progmem.logging-cpp")))

#else /* !__AVR__ */

#define PROGMEMTYPE char

static inline char pgm_read_byte_far(const char* t) {
    return *t;
}

#endif  /* __AVR__ */


namespace logging {

    /*! \brief A ProgramMemoryString implements the interface to a
     *         string placed in program memory
     *
     *         It may be used as a usual char pointer, because it
     *         provides a pointer-like interface.
     */
    struct ProgramMemoryString {
        char operator[](int index) const {
            return static_cast<char>(pgm_read_byte_far(str+index));
        }

        char operator*() const {
            return static_cast<char>(pgm_read_byte_far(str));
        }

        const ProgramMemoryString& operator++() const {
            ++str;
            return *this;
        }

        ProgramMemoryString operator++(int) const {
            ProgramMemoryString p(*this);
            ++str;
            return p;
        }

        mutable const char *str;
    };
}

#endif // __ProgramMemoryStringImpl_h__

