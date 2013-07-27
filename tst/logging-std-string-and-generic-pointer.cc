/*******************************************************************************
 *
 * Copyright (c) 2011 Michael Schulze <mschulze@ivs.cs.uni-magdeburg.de>
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

#include <string>
#include <stdint.h>

#define LOGGING_DEFINE_EXTENDED_OUTPUT_TYPE
//#define LOGGING_DISABLE
#include "logging/logging.h"
using namespace ::logging;

// some helper struct for detection of pointer type and for selection
// of the correct overloaeded operator within the extension
template<typename T>
struct is_pointer {
    static const bool value = false;
};
template<typename T>
struct is_pointer<T*> {
    static const bool value = true;
};

template<bool, typename R=void>
struct enable_if {
    typedef R   type;
};

template<typename R>
struct enable_if<false,R> {
};

/*! \brief Defines the extended output type that is capable to interpret
 *         the std::string and generic pointer types
 */
template < typename Base>
struct StdStingAndGenericPointer : public Base {
    /*! \brief catch std::string type and call the correct method
     *         for the output generation
     */
    StdStingAndGenericPointer& operator << (const std::string s) {
        Base::operator <<(s.c_str());
        return *this;
    }

   /*! \brief forward all unknown types to the base output type for
     *         further processing.
     */
    template<typename T>
    typename enable_if< !is_pointer<T>::value, StdStingAndGenericPointer >::type & operator << (const T &t) {
        Base::operator<<(t);
        return *this;
    }

    template<typename T>
    typename enable_if< is_pointer<T>::value, StdStingAndGenericPointer >::type & operator << (const T &t) {
        Base::operator<<((void*)t);
        return *this;
    }

};

// extensions end
LOGGING_DEFINE_OUTPUT( StdStingAndGenericPointer< ::logging::LoggingType> )


int main(int, char**) {
    ::logging::log::emit() << "Hello World! with the logging framework"
                << ::logging::log::endl << ::logging::log::endl;

    std::string s("The famous Logging-Framework");
    std::string *sp=&s;
    // using the extension
    ::logging::log::emit()
                << "Output std::string " << s << ::logging::log::endl
                << "and the address of that string " << sp
                << ::logging::log::endl;
    return 0;
}
