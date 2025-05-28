#ifndef PLAYTRON_SDK_COMMON_H
#define PLAYTRON_SDK_COMMON_H

#include <string>
#include <exception>

#ifdef _WIN32
    #ifdef PLAYTRON_BUILD // Define PLAYTRON_BUILD when building the DLL
        #define PLAYTRONAPI __declspec(dllexport)
    #else
        #define PLAYTRONAPI __declspec(dllimport)
    #endif
#else
    #define PLAYTRONAPI
#endif

namespace playtron { namespace sdk { namespace common {
    /**
     * Common exception for identifying initialization failures.
     */
    class PLAYTRONAPI UninitializedException : public std::exception
    {
    public:
        UninitializedException(const std::string& message) : m_message(message)
        {
        }

        const char* what() const noexcept override { return m_message.c_str(); }
    private:
        std::string m_message;
    };
}}}

#endif /* PLAYTRON_SDK_COMMON_H */