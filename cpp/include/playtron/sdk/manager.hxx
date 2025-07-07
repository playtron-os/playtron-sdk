#ifndef PLAYTRON_SDK_MANAGER_H
#define PLAYTRON_SDK_MANAGER_H

#include "common.hxx"
#include <cstdint>

namespace playtron
{
    namespace sdk
    {
        namespace manager
        {
            /**
             * @brief Request to check if in-game virtual keyboard in GameOS is open
             */
            PLAYTRONAPI bool is_keyboard_open();

            /**
             * @brief Request opening of in-game virtual keyboard in GameOS
             */
            PLAYTRONAPI void show_keyboard();

            /**
             * @brief Request closing of in-game virtual keyboard in GameOS
             */
            PLAYTRONAPI void hide_keyboard();

            /**
             * @brief Request opening of browser navigating to specified URL in GameOS
             *
             * @param url URL to navigate to
             *
             * @throws std::invalid_argument if url parameter is empty.
             */
            PLAYTRONAPI void open_browser(const std::string &url);

            /**
             * @brief Request closing of GameOS browser
             */
            PLAYTRONAPI void close_browser();
        }
    }
}

#endif /* PLAYTRON_SDK_MANAGER_H */