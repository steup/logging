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

#ifndef __OutputLevelSwitchDisabled_h__
#define __OutputLevelSwitchDisabled_h__

#include "logging/LoggerLevel.h"

namespace logging {

    /*! \brief The dynamic treatment of %logging levels is switched off if this
     *         class is a base class of the output-type of the %logging framework
     */
    template < typename Base >
    class OutputLevelSwitchDisabled : public Base {
        public:
            /*! \brief Matches only on correct type and used for switching
             *         %levels. However, here the implementation is empty
             *         due to the fact, that level switching is disabled
             *         by this class
             */
            OutputLevelSwitchDisabled& operator<<(const ::logging::Level::levels&) {
                return *this;
            }

            /*! \brief Matches only on correct type and used for switching
             *         %levels. However, here the implementation is empty
             *         due to the fact, that level switching is disabled
             *         by this class
             */
            OutputLevelSwitchDisabled& operator<<(const ::logging::RunTimeLevel& l) {
                return *this;
            }

            /*! \brief The operator matches on every type, and delegates further
             *         work to the base class.
             */
            template< typename T>
            OutputLevelSwitchDisabled& operator<<(T t) {
                Base::operator<<(t);
                return *this;
            }
    };

} /* logging */

#endif
