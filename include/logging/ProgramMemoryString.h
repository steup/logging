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

#ifndef __ProgramMemoryString_h__
#define __ProgramMemoryString_h__

#define __STRINGIFICATION__(x) #x
#define __TOSTR__(x) __STRINGIFICATION__(x)

/*!
 * \def PROGMEMSTRING
 * \brief A %PROGMEMSTRING enables the placement of string constants in the
 *        text segment, allowing the reduction of needed RAM on some processor
 *        architectures like the AVRs.
 *
 *        Especially in the embedded field the RAM is often a constrained
 *        ressource. Enabling the placement of constant strings in e.g. the
 *        FLASH memory allows reducing the needed RAM. For the AVR platform,
 *        the logging framework supports such a feature by using the
 *        PROGMEMSTRING macro. This macro places the string constant in the non
 *        volatile memory, creates a temporarily variable that abstracts the
 *        access to the given string as it would be a pointer to a character
 *        array. This variable then is used by the logging framework. On
 *        architecture without the need for such a feature, or on those not yet
 *        supported, the only changing thing is the placement of the string
 *        into normal RAM, but the provided abstraction works as well. Thus,
 *        the PROGMEMSTRING macro can be used always.
 *
 * \param s the string constant
 */
#define PROGMEMSTRING(S)                                                    \
    (__extension__({                                                        \
        static                                                              \
           char __attribute__  ((                                           \
                            section(                                        \
                                __TOSTR__(                                  \
                                    __TOSTR__(.progmem.logging-cpp.S)       \
                                )                                           \
                            )                                               \
                        ))  __str[] = (S);                                  \
        const ::logging::ProgramMemoryString __pms = {&__str[0]};           \
        __pms;                                                              \
    }))

#define PROGMEMSTRINGTYPE const ::logging::ProgramMemoryString

#include "logging/ProgramMemoryStringImpl.h"

#endif // __ProgramMemoryString_h__

