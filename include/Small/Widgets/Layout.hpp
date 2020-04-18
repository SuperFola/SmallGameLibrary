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

#include <SFML/Graphics/Drawable.hpp>
#include <vector>
#include <memory>

namespace sgl::Widgets
{
    /**
     * @brief A collection of widgets working together, graphically united
     * @details This class **must** be used to create, host, and render the widgets ;
     *          other widget can not and shouldn't live alone.
     * 
     */
    class Layout : public Base, public sf::Drawable
    {
    public:
        using Ptr = std::shared_ptr<Base>;

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
         * @brief Return a pointer to a child widget by its identifer
         * 
         * @param i Identifier of the widget
         * @return Base* 
         */
        virtual Base* operator[](int i) const final;

        /**
         * @brief Create a new widget in place and attach it to the layout
         * 
         * @tparam W Class name of the widget to add
         * @tparam 
         * @param args Args arguments (other than the identifier and the parent's pointer)
         * @return int Unique identifier for the widget
         */
        template <typename W, typename... Args>
        int attach(Args&&... args)
        {
            m_children.push_back(std::make_shared<W>(static_cast<int>(m_children.size()), this, std::forward<Args>(args)...));
            return static_cast<int>(m_children.size()) - 1;
        }

        /**
         * @brief Function in charge of drawing our widget, using the SFML API
         * 
         * @param target 
         * @param parentTransform 
         */
        void draw_(sf::RenderTarget& target, const sf::Transform& parentTransform);

    protected:
        std::vector<Layout::Ptr> m_children;

        /**
         * @brief To be able to draw the layout using the SFML API :
         * @code
         * screen.draw(my_layout);
         * @endcode
         * 
         * @param target 
         * @param states 
         */
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    };
}

#endif