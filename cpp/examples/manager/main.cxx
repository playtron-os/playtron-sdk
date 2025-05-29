#include <playtron/sdk/manager.hxx>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

using namespace playtron::sdk::manager;

int main() {
    std::cout << "Running manager example..." << "\n";

    // Virtual Keyboard
    std::cout << "Opening virtual keyboard..." << "\n";
    show_keyboard();

    std::cout << "Waiting for 5 seconds..." << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::cout << "Closing virtual keyboard..." << "\n";
    hide_keyboard();

    /** ------- */

    std::cout << "Waiting for 2 seconds..." << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));

    // Browser
    const std::string URL = "https://google.com";
    std::cout << "Opening browser for URL " << URL << "..." << "\n";
    open_browser(URL);

    std::cout << "Waiting for 5 seconds..." << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::cout << "Closing browser..." << "\n";
    close_browser();

    return 0;
}
