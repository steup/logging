/*******************************************************************************
 *
 * Copyright (c) 2008, 2009 Michael Schulze <mschulze@ivs.cs.uni-magdeburg.de>
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

#define LOGGING_DEFINE_EXTENDED_OUTPUT_TYPE

#include "logging/logging.h"
LOGGING_DEFINE_OUTPUT( ::logging::config::StdLogRunTimeSwitchType )

int main(int, char**) {
    ::logging::log::emit() << "Hello World! with the logging framework"
        << ::logging::log::endl << ::logging::log::endl;

    // Disable Output at all. nothing is outputed until logging
    // output is enabled again
    ::logging::log::emit()
        << ::logging::setLoggingLevel(::logging::Level::disable);
    ::logging::log::emit() << "Print 15 in hexadecimal "
        << ::logging::log::hex << 15 << ::logging::log::endl;
    ::logging::log::emit() << "Print 15 in decimal "
        << ::logging::log::dec << 15 << ::logging::log::endl;
    ::logging::log::emit() << "Print 15 in octal "
        << ::logging::log::oct << 15 << ::logging::log::endl;
    ::logging::log::emit() << "Print 15 in binary with a tab"
        << ::logging::log::bin << ::logging::log::tab << 15
        << ::logging::log::endl << ::logging::log::endl;

    // Enable Output for error and info, only
    ::logging::log::emit()
        << ::logging::setLoggingLevel(::logging::Level::error | ::logging::Level::warning);
    ::logging::log::emit< ::logging::Error>() << "Logging an Error"
        << ::logging::log::endl;
    ::logging::log::emit< ::logging::Trace>() << "Logging a Trace"
        << ::logging::log::endl;
    ::logging::log::emit< ::logging::Warning>() << "Logging a Warning"
        << ::logging::log::endl;
    ::logging::log::emit< ::logging::Info>() << "Logging an Info"
        << ::logging::log::endl;
    return 0;
}
