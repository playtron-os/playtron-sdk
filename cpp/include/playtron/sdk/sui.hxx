#ifndef PLAYTRON_SDK_SUI_H
#define PLAYTRON_SDK_SUI_H

#include "common.hxx"
#include <cstdint>

namespace playtron
{
    namespace sdk
    {
        namespace sui
        {
            struct SignResult {
                std::string error;
                bool        cancelled;
                std::string signature;
            };

            struct TransactionResult {
                std::string error;
                bool        cancelled;
                uint64_t    completed_at;
                std::string result;
            };

            /**
             * @brief Returns the current user’s Sui wallet address.
             *
             * This will synchronously call into the Rust FFI, fetch the
             * wallet address for the currently-logged-in user, and return it
             * as a UTF-8 std::string.
             *
             * @throws playtron::sdk::common::UninitializedException if the
             *         underlying library could not be initialized (e.g. not
             *         running on a Playtron device).
             * @throws std::runtime_error on any other failure to retrieve
             *         the address.
             *
             * @return std::string The current wallet address, or an empty
             *         string if none is set.
             */
            PLAYTRONAPI std::string get_wallet_address();

            /**
             * @brief Request the user to sign an arbitrary message.
             *
             * Initiates a message-signing flow in the Playtron device wallet, waits
             * for the user to approve or cancel, and returns the result.
             *
             * @param providerAppId  Your application’s unique identifier from the provider (Steam/Epic/GOG/...)
             * @param msg            The UTF-8 message payload to be signed.
             *
             * @throws std::invalid_argument if msg parameter is empty.
             * @throws std::runtime_error on JSON parse errors or FFI failures.
             *
             * @return SignResult
             *   - error:     empty if no error, otherwise contains an error message  
             *   - cancelled: true if the user cancelled the flow  
             *   - signature: the hex-encoded signature if signing succeeded
             */
            PLAYTRONAPI SignResult sign_message(const std::string& providerAppId, const std::string& msg);

            /**
             * @brief Request the user to sign a transaction.
             *
             * Initiates a transaction-signing flow in the Playtron device wallet, waits
             * for the user to approve or cancel, and returns the result.
             *
             * @param providerAppId  Your application’s unique identifier from the provider (Steam/Epic/GOG/...)
             * @param txBytes        The serialized transaction payload as a base-64.
             *
             * @throws std::invalid_argument if txBytes parameter is empty.
             * @throws std::runtime_error on JSON parse errors or FFI failures.
             *
             * @return SignResult
             *   - error:     empty if no error, otherwise contains an error message  
             *   - cancelled: true if the user cancelled the flow  
             *   - signature: the hex-encoded signature if signing succeeded
             */
            PLAYTRONAPI SignResult sign_transaction(const std::string& providerAppId, const std::string& txBytes);

            /**
             * @brief Request the user to sign and immediately submit a transaction.
             *
             * Initiates a transaction-sign-and-execute flow in the Playtron wallet,
             * waits for the user to approve or cancel, and returns the result.
             *
             * @param providerAppId  Your application’s unique identifier from the provider (Steam/Epic/GOG/...)
             * @param txBytes        The serialized transaction payload as a base-64.
             *
             * @throws std::invalid_argument if txBytes parameter is empty.
             * @throws std::runtime_error on JSON parse errors or FFI failures.
             *
             * @return TransactionResult
             *   - error:        empty if no error, otherwise contains an error message  
             *   - cancelled:    true if the user cancelled the flow  
             *   - completed_at: UNIX timestamp (seconds) when the transaction was submitted
             *   - result: JSON string with details about the transaction
             */
            PLAYTRONAPI TransactionResult sign_and_execute_transaction(const std::string& providerAppId, const std::string& txBytes);
        }
    }
}

#endif /* PLAYTRON_SDK_SUI_H */