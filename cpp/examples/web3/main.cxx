#include <playtron/sdk/web3.hxx>
#include <iostream>
#include <string>
#include <limits>

using namespace playtron::sdk::web3;

int main() {
    try {
        // 1) Get and show the wallet address
        std::string addr = get_wallet_address();
        if (addr.empty()) {
            std::cerr << "No wallet address available.\n";
            return 1;
        }
        std::cout << "Current wallet address: " << addr << "\n\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Failed to get wallet address: " << e.what() << "\n";
        return 1;
    }

    // Interactive loop
    while (true) {
        std::cout << "Choose an action:\n"
                  << "  1) Sign a message\n"
                  << "  2) Sign & execute a transaction\n"
                  << "  q) Quit\n"
                  << "> ";

        char choice{};
        std::cin  >> choice;
        // consume leftover newline
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 'q' || choice == 'Q') {
            std::cout << "Goodbye!\n";
            break;
        }

        if (choice == '1') {
            // Sign message flow
            std::cout << "Enter message to sign: ";
            std::string msg;
            std::getline(std::cin, msg);

            try {
                // Provider app id is required and should be from the currently running app
                MessageResult res = sign_message("", msg);

                if (res.cancelled) {
                    std::cout << "[Cancelled] User declined to sign.\n";
                }
                else if (!res.error.empty()) {
                    std::cout << "[Error] " << res.error << "\n";
                }
                else {
                    std::cout << "[Success] Signature: " << res.signature << "\n";
                }
            }
            catch (const std::exception& e) {
                std::cout << "[Exception] " << e.what() << "\n";
            }
        }
        else if (choice == '2') {
            // Sign & execute transaction flow
            std::cout << "Building transaction and sending for signing";
            // TODO: Add transaction building in the example
            std::string txBytes = "xxx";

            try {
                // Provider app id is required and should be from the currently running app
                TransactionResult res = sign_and_execute_transaction("", txBytes);

                if (res.cancelled) {
                    std::cout << "[Cancelled] User declined transaction.\n";
                }
                else if (!res.error.empty()) {
                    std::cout << "[Error] " << res.error << "\n";
                }
                else {
                    std::cout << "[Success] Submitted at: " << res.completed_at << "with Result: " << res.result << "\n";
                }
            }
            catch (const std::exception& e) {
                std::cout << "[Exception] " << e.what() << "\n";
            }
        }
        else {
            std::cout << "Invalid option. Please choose 1, 2, or q.\n";
        }

        std::cout << "\n";  // blank line before next loop
    }

    return 0;
}
