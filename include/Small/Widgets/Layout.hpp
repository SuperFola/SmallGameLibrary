/**
 * @file Layout.hpp
 * @author Alexandre Plateau (lexplt.dev@gmail.com)
 * @brief A widget acting as a collection of widgets
 * @version 0.3
 * @date 2020-04-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef sgl_small_widgets_layout
#define sgl_small_widgets_layout

#include <Small/Widgets/Base.hpp>

namespace sgl::Widgets
{
    /**
     * @brief A collection of widgets working together, graphically united
     * 
     */
    class Layout : public Base
    {
    public:
        /**
         * @brief Construct a new Layout object
         * 
         * @param id Unique identifier for the widget (automatically set)
         * @param parent Pointer to parent layout (automatically set)
         * @param bounds Local bounds of the layout
         */
        Layout(int id, Base::Ptr parent, const sf::IntRect& bounds);

        /**
         * @brief Destroy the Layout object
         * 
         */
        virtual ~Layout();

        /**
         * @brief Update the layout and its children
         * 
         * @param dt Delta of time since last update
         */
        virtual void onUpdate(const sf::Time dt);

        /**
         * @brief Called when an event is received, dispatching the event to all the children corresponding to the event type
         * 
         * @param event 
         */
        virtual void onEvent(const sf::Event& event);

        /**
         * @brief Create a new widget in place and add it to the layout
         * 
         * @tparam W Class name of the widget to add
         * @tparam 
         * @param args Args arguments (other than the identifier and the parent's pointer)
         * @return W* Raw owned pointer to the widget
         */
        template <typename W, typename... Args>
        W* add(Args&&... args)
        {
            return this->attach<W>(static_cast<int>(m_children.size()), this, std::forward<Args>(args)...);
        }

        /**
         * @brief Render the widget on screen
         * @details This function will be empty because all the nodes are automatically rendered
         *          by the base class sgl::Graphics::Node, and because a layout has nothing to show.
         * 
         * @param screen 
         * @param transform Given by parent automatically
         */
        void onRender(sf::RenderTarget& screen, const sf::Transform& transform);
    };
}

#endif