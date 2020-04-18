/**
 * @file Base.hpp
 * @author Alexandre Plateau (lexplt.dev@gmail.com)
 * @brief Contain base classes to create interoperable SFML widgets
 * @version 0.7
 * @date 2020-04-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef sgl_small_widgets_base
#define sgl_small_widgets_base

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

namespace sgl::Widgets
{
    /**
     * @brief Styling options for widgets
     * 
     */
    enum class Style
    {
        Text,    //< Display text only, if available (default)
        Sprite,  //< Display sprite only, if available
        Both     //< Display both, first the sprite, then the text over it
    };

    /**
     * @brief Base class for all widgets. This class can not be used as is.
     * @details Providing base features like: focus management, update on event,
     *          rendering, transformations. Position is **always** relative to the parent.
     * 
     */
    class Base : public sf::Transformable
    {
    public:
        using Ptr = Base*;

        /**
         * @brief Construct a new Base widget object
         * 
         * @param id Unique identifier for the widget (automatically set)
         * @param parent Pointer to the parent widget (automatically set)
         * @param bounds Local bounds of the widget
         */
        Base(int id, Ptr parent, const sf::IntRect& bounds);

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
         * @brief Render the widget on screen
         * 
         * @param screen 
         * @param transform Given by parent automatically
         */
        virtual void onRender(sf::RenderTarget& screen, const sf::Transform& transform);

        /**
         * @brief Called when an event is received, calling the subfunctions corresponding to the event type
         * 
         * @param event 
         */
        virtual void onEvent(const sf::Event& event);

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

        /**
         * @brief Get the local bounding rectangle of the entity
         * @details The returned rectangle is in local coordinates, ignoring transformations.
         * 
         * @return sf::FloatRect 
         */
        virtual sf::FloatRect getLocalBounds() const final;

        /**
         * @brief Get the global bounding rectangle of the entity
         * @details The returned rectangle is in global coordinates, taking into account
         *          transformations.
         * 
         * @return sf::FloatRect 
         */
        virtual sf::FloatRect getGlobalBounds() const final;

        /**
         * @brief Activate a widget event listener or not
         * 
         * @param value 
         */
        virtual void setListenToEvents(bool value) final;

        /**
         * @brief Return a boolean telling if the widget is listening to events
         * 
         * @return true If the widget can receive events
         * @return false Otherwise
         */
        virtual bool isListeningToEvents() const final;

        /**
         * @brief Tell if the widget is being focused or not
         * 
         * @return true If the widget has the focus
         * @return false Otherwise
         */
        virtual bool hasFocus() const final;

        /**
         * @brief Set the style of the object
         * 
         * @param style a Style enumeration value
         */
        virtual void setStyle(Style style) final;

        /**
         * @brief Get the style of the widget
         * 
         * @return Style 
         */
        virtual Style getStyle() const final;

        /**
         * @brief Set the relative position of the widget
         * 
         * @param x 
         * @param y 
         */
        virtual void setPosition(int x, int y) final;

        /**
         * @brief Function in charge of drawing our widget
         * @details This method shouldn't be modified unless you need to do specific 
                    things like playing with transformations, otherwise implement your 
                    rendering methods in onRender
         * 
         * @param target 
         * @param parentTransform 
         */
        virtual void draw_(sf::RenderTarget& target, const sf::Transform& parentTransform);

    protected:
        const int m_id;  //< Unique identifier for the widget
        bool m_focused;  //< Tell if the widget is being focused or not
        bool m_listening;  //< Tell if a widget can receive events
        sf::IntRect m_rect;  //< Rectangle in which the widget is
        Ptr m_parent;  //< Pointer to the parent widget
        Style m_style;
    };
}

#endif