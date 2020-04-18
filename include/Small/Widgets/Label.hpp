/**
 * @file Label.hpp
 * @author Alexandre Plateau (lexplt.dev@gmail.com)
 * @brief Basic label widget
 * @version 0.1
 * @date 2020-04-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef sgl_small_widgets_label
#define sgl_small_widgets_label

#include <Small/Widgets/Base.hpp>

#include <SFML/Graphics/Text.hpp>
#include <string>

namespace sgl::Widgets
{
    /**
     * @brief Basic label widget, doesn't listen to events by default
     * 
     */
    class Label : public Base
    {
    public:
         /**
         * @brief Construct a new Label widget
         * 
         * @param id Unique identifier for the widget (automatically set)
         * @param parent Pointer to the parent widget (automatically set)
         * @param bounds Local bounds of the button
         */
        Label(int id, Base::Ptr parent, const sf::IntRect& bound);

        /**
         * @brief Destroy the Label widget
         * 
         */
        ~Label();

        /**
         * @brief Return a reference to the sf::Text held, to modify it
         * 
         * @return sf::Text& 
         */
        sf::Text& text();

        /**
         * @brief Render the widget on screen
         * 
         * @param screen 
         * @param transform Given by parent automatically
         */
        void onRender(sf::RenderTarget& screen, const sf::Transform& transform);

    protected:
        sf::Text m_text;  //< Text of the label
    };
}

#endif