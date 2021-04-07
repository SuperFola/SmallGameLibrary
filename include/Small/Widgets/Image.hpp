/**
 * @file Image.hpp
 * @author Alexandre Plateau (lexplt.dev@gmail.com)
 * @brief Basic image widget
 * @version 0.2
 * @date 2020-04-19
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef SMALL_WIDGETS_IMAGE_HPP
#define SMALL_WIDGETS_IMAGE_HPP

#include <Small/Widgets/Base.hpp>

#include <SFML/Graphics/Sprite.hpp>

namespace sgl::Widgets
{
    /**
     * @brief Basic image widget
     * 
     */
    class Image : public Base
    {
    public:
        /**
         * @brief Construct a new Image widget
         * 
         * @param id Unique identifier for the widget (automatically set)
         * @param parent Pointer to the parent widget (automatically set)
         * @param bounds Local bounds of the button
         */
        Image(int id, Base::Ptr parent, const sf::IntRect& bounds);

        /**
         * @brief Destroy the Image widget
         * 
         */
        ~Image();

        /**
         * @brief Return a pointer to the sprite to set and modify it
         * @details Usage example:
         * @code
         * auto image = sgl::Widgets::make<Image>(sf::IntRect(12, 12, 32, 32));
         * sgl::GameObjects::SpriteManager::get().add("my_sprite", my_sprite);
         * image.sprite() = &sgl::GameObjects::SpriteManager::get().["my_sprite"];
         * @endcode
         * 
         * @return sf::Sprite* 
         */
        sf::Sprite* sprite();

        /**
         * @brief Render the widget on screen
         * 
         * @param screen 
         * @param transform Given by parent automatically
         */
        void onRender(sf::RenderTarget& screen, const sf::Transform& transform);

    protected:
        sf::Sprite* m_sprite;  ///< The image itself
    };
}

#endif
