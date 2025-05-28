#ifndef PLAYTRON_SDK_PACT_H
#define PLAYTRON_SDK_PACT_H

#include "common.hxx"

#include <cstdint>
#include <string>

#include <curl/curl.h>

namespace playtron { namespace sdk { namespace pact {
    /**
     * Stores the information for a given session.
     */
    struct PLAYTRONAPI SessionInfo {
        /**
         * A unique value to be used for each attestation request.
         */
        std::string nonce;

        /**
         * The ID of the attestation session.
         */
        std::string sessionId;
    };

    /**
     * Exception for indicating attestation failures.
     */
    class PLAYTRONAPI AttestationException : std::exception {
    public:
        AttestationException(std::string msg) : m_message(msg)
        {}

        const char* what() const noexcept override { return m_message.c_str(); }
    private:
        std::string m_message;
    };

    /**
     * Client used for initiating remote attestation sessions
     * and interfacing with the TPM 2.0 chip on the Playtron device.
     */
    class PLAYTRONAPI AttestationClient
    {
    public:
        AttestationClient();
        ~AttestationClient();

        /**
         * Creates the remote attestation session.
         *
         * This method only needs to be invoked once to create a new session.
         */
        SessionInfo create_session();

        /**
         * Gets the quote from the TPM.
         *
         * It is then the callers responsibility to send the quote to the
         * PACT attestation server to actually do the remote attestation.
         */
        std::string get_quote(const std::string& nonce);
    private:
        CURL* m_client = nullptr;
        const char* m_pact_base_url;
    };
}}}

#endif /* PLAYTRON_SDK_PACT_H */