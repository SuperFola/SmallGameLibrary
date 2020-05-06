/**
 * @file Image.hpp
 * @author Alexandre Plateau (lexplt.dev@gmail.com)
 * @brief Basic image widget
 * @version 0.1
 * @date 2020-04-19
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef sgl_small_widgets_image
#define sgl_small_widgets_image

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
         * @brief Return a reference to the sprite to modify it
         * 
         * @return sf::Sprite& 
         */
        sf::Sprite& sprite();

        /**
         * @brief Render the widget on screen
         * 
         * @param screen 
         * @param transform Given by parent automatically
         */
        void onRender(sf::RenderTarget& screen, const sf::Transform& transform);

    protected:
        sf::Sprite m_sprite;  //< The image itself
    };
}

#endif