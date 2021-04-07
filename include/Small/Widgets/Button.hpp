/**
 * @file Button.hpp
 * @author Alexandre Plateau (lexplt.dev@gmail.com)
 * @brief Basic button widget
 * @version 0.1
 * @date 2020-04-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef SMALL_WIDGETS_BUTTON_HPP
#define SMALL_WIDGETS_BUTTON_HPP

#include <Small/Widgets/Base.hpp>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <functional>

namespace sgl::Widgets
{
    /**
     * @brief Basic button widget
     * 
     */
    class Button : public Base
    {
    public:
        using Callback_t = std::function<void ()>;

        /**
         * @brief Construct a new Button widget
         * 
         * @param id Unique identifier for the widget (automatically set)
         * @param parent Pointer to the parent widget (automatically set)
         * @param bounds Local bounds of the button
         */
        Button(int id, Base::Ptr parent, const sf::IntRect& bounds);

        /**
         * @brief Destroy the Button widget
         * 
         */
        ~Button();

        /**
         * @brief Set the function to be called when we click on the button
         * 
         * @param callback A void() function
         */
        void setCallback(Callback_t&& callback);

        /**
         * @brief Return a reference to the sf::Text held, to modify it
         * 
         * @return sf::Text& 
         */
        sf::Text& text();

        /**
         * @brief Return a pointer to the sprite to set and modify it
         * @details Usage example:
         * @code
         * auto button = sgl::Widgets::make<Button>(sf::IntRect(12, 12, 32, 32));
         * sgl::GameObjects::SpriteManager::get().add("my_sprite", my_sprite);
         * button.sprite() = &sgl::GameObjects::SpriteManager::get().["my_sprite"];
         * @endcode
         * 
         * @return sf::Sprite* 
         */
        sf::Sprite* sprite();

        /**
         * @brief Return a pointer to the sprite to set and modify it
         * @details Usage example:
         * @code
         * auto button = sgl::Widgets::make<Button>(sf::IntRect(12, 12, 32, 32));
         * sgl::GameObjects::ShapeManager::get().add("my_shape", my_shape);
         * button.shape() = &sgl::GameObjects::ShapeManager::get().["my_shape"];
         * @endcode
         * 
         * @return sf::RectangleShape* 
         */
        sf::RectangleShape* shape();

        /**
         * @brief Render the widget on screen
         * 
         * @param screen 
         * @param transform Given by parent automatically
         */
        void onRender(sf::RenderTarget& screen, const sf::Transform& transform);

        /**
         * @brief Called when a mouse button is pressed, on focus
         * @details Focus is handled before calling the method
         * 
         * @param button the button pressed (sf::Mouse::Button)
         * @param x position of the click
         * @param y position of the click
         */
        void onMouseButtonPressed(int button, int x, int y);

        /**
         * @brief Called when a mouse button is released, on focus
         * @details Focus is handled before calling the method
         * 
         * @param button the button released (sf::Mouse::Button)
         * @param x position of the click
         * @param y position of the click
         */
        void onMouseButtonReleased(int button, int x, int y);

    protected:
        sf::Text m_text;                 ///< Text for the button
        union {
            sf::Sprite* m_sprite;         ///< Sprite for the button
            sf::RectangleShape* m_shape;  ///< Background for the button in text-only mode
        };
        bool m_click;                    ///< Is the button being clicked on?
        Callback_t m_callback;           ///< Function to call when we click on the button
    };
}

#endif
