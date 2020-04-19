/**
 * @file SFMLtoArk.hpp
 * @author Alexandre Plateau (lexplt.dev@gmail.com)
 * @brief Convert SFML values to ArkScript values
 * @version 0.1
 * @date 2020-04-19
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef sgl_small_scripting_sfmltoark
#define sgl_small_scripting_sfmltoark

#include <Ark/Ark.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Utf.hpp>

namespace sgl::Scripting
{
    /**
     * @brief Enumeration of SFML event types, needed when binding events in ArkScript
     * 
     */
    enum class sfEventType
    {
        TextEntered = 0,
        KeyPressed,
        KeyReleased,
        MouseWheelScrolled,
        MouseButtonPressed,
        MouseButtonReleased
    };

    /**
     * @brief Convert a sf::Event to an ArkScript value
     * 
     * @param event 
     * @return Ark::Value 
     */
    Ark::Value sfEventToArk(const sf::Event& event);

    /**
     * @brief Convert a sf::time to an ArkScript value
     * @details Return the time as seconds
     * 
     * @param dt
     * @return Ark::Value 
     */
    Ark::Value sfTimeToArk(const sf::Time dt);
}

#endif