/**
 * @file Base.hpp
 * @author Alexandre Plateau (lexplt.dev@gmail.com)
 * @brief Contain base classes to create interoperable SFML widgets
 * @version 0.1
 * @date 2020-04-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef sgl_small_widgets_base
#define sgl_small_widgets_base

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

namespace sgl::Widgets
{
    /**
     * @brief Base class for all widgets
     * @details Providing base features like: focus management, update on event,
     *          rendering, transformations.
     * 
     */
    class Base : public sf::Drawable, public sf::Transformable
    {
    public:
        /**
         * @brief Construct a new Base widget object
         * 
         * @param id Unique identifier for the widget
         */
        Base(int id);

        /**
         * @brief Destroy the Base widget object
         * 
         */
        virtual ~Base();

        /**
         * @brief Update the widget
         * 
         * @param dt Delta of time since last update
         */
        virtual void onUpdate(const sf::Time dt);

        /**
         * @brief Called when an event is received, calling the subfunctions corresponding to the event type
         * 
         * @param event 
         */
        void onEvent(const sf::Event& event);

        /**
         * @brief Called when a text entered event is produced, on focus
         * 
         * @param code character unicode
         */
        virtual void onTextEntered(sf::Uint32 code);

        /**
         * @brief Called when a key is pressed, on focus
         * 
         * @param key the key code of the key pressed
         */
        virtual void onKeyPressed(int key);

        /**
         * @brief Called when a key is released, on focus
         * 
         * @param key the key code of the key released
         */
        virtual void onKeyReleased(int key);

        /**
         * @brief Called when the mouse wheel is scrolled, on focus
         * 
         * @param delta Delta of movement of the wheel (positive is up/left, negative is down/right)
         */
        virtual void onMouseWheelScrolled(float delta);

        /**
         * @brief Called when a mouse button is pressed, on focus
         * @details Focus is handled before calling the method
         * 
         * @param button the button pressed (sf::Mouse::Button)
         * @param x position of the click
         * @param y position of the click
         */
        virtual void onMouseButtonPressed(int button, int x, int y);

        /**
         * @brief Called when a mouse button is released, on focus
         * @details Focus is handled before calling the method
         * 
         * @param button the button released (sf::Mouse::Button)
         * @param x position of the click
         * @param y position of the click
         */
        virtual void onMouseButtonReleased(int button, int x, int y);

        sf::FloatRect getLocalBounds() const;
        sf::FloatRect getGlobalBounds() const;

    protected:
        const int m_id;  //< Unique identifier for the widget
        bool m_focused;  //< Tell if the widget is being focused or not
        sf::IntRect m_rect;  //< Rectangle in which the widget is

        /**
         * @brief Function in charge of drawing our widget, using the SFML API
         * @details The inheriting widget must implement this method to be drawn using:
         * @code
         * screen.draw(my_widget);
         * @endcode
         * 
         * @param target 
         * @param states 
         */
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
    };
}

#endif