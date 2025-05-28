#ifndef PLAYTRON_SDK_OS_H
#define PLAYTRON_SDK_OS_H

#include "common.hxx"

namespace playtron { namespace sdk { namespace os {
    /**
     * Returns true if running on Playtron GameOS, otherwise false.
     */
    PLAYTRONAPI bool is_playtron();
}}}

#endif /* PLAYTRON_SDK_OS_H */