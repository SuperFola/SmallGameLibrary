/**
 * @file Node.hpp
 * @author Alexandre Plateau (lexplt.dev@gmail.com)
 * @brief A scene graph node
 * @version 0.1
 * @date 2020-05-06
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef sgl_small_graphics_node
#define sgl_small_graphics_node

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <memory>

namespace sgl::Graphics
{
    /**
     * @brief Abstract base class for a scene graph node
     * 
     */
    class Node
    {
    public:
        /**
         * @brief Construct a new Node object
         * 
         */
        Node();

        /**
         * @brief Destroy the Node object
         * 
         */
        virtual ~Node();

        /**
         * @brief Combine the current transform with a translation
         * 
         * @param x x offset
         * @param y y offset
         * @return Node& 
         */
        Node& move(float x, float y);

        /**
         * @brief Combine the current transform with a translation
         * 
         * @param offset translation to apply
         * @return Node& 
         */
        Node& move(const sf::Vector2f& offset);

        /**
         * @brief Combine the current transform with a rotation
         * 
         * @param angle Rotation angle in degrees
         * @return Node& 
         */
        Node& rotate(float angle);

        /**
         * @brief Combine the current transform with a rotation
         * @details The center of rotation is provied for convenience so that you can
         *          build rotations around arbitrary points more easily.
         * 
         * @param angle Rotation angle in degrees
         * @param centerX x coordinate of the center of rotation
         * @param centerY y coordinate of the center of rotation
         * @return Node& 
         */
        Node& rotate(float angle, float centerX, float centerY);

        /**
         * @brief Combine the current transform with a rotation
         * @details The center of rotation is provied for convenience so that you can
         *          build rotations around arbitrary points more easily.
         * 
         * @param angle Rotation angle in degrees
         * @param center coordinates of the center of rotation
         * @return Node& 
         */
        Node& rotate(float angle, const sf::Vector2d& center);

        /**
         * @brief Combine the current transform with a scaling
         * 
         * @param scaleX factor on the x axis
         * @param scaleY factor on the y axis
         * @return Node& 
         */
        Node& scale(float scaleX, float scaleY);

        /**
         * @brief Combine the current transform with a scaling
         * 
         * @param factors scaling factors
         * @return Node& 
         */
        Node& scale(const sf::Vector2f& factors);

        /**
         * @brief Combine the current transform with a scaling
         * @details The center of scaling is provided for convenience so that you can
         *          build scaling arund arbitrary points more easily.
         * 
         * @param scaleX factor on the x axis
         * @param scaleY factor on the y axis
         * @param centerX x coordinate of the center of scaling
         * @param centerY y coordinate of the center of scaling
         * @return Node& 
         */
        Node& scale(float scaleX, float scaleY, float centerX, float centerY);

        /**
         * @brief Combine the current transform with a scaling
         * @details The center of scaling is provided for convenience so that you can
         *          build scaling arund arbitrary points more easily.
         * 
         * @param factors scaling factors
         * @param center coordinates of the center of scaling
         * @return Node& 
         */
        Node& scale(const sf::Vector2f& factors, const sf::Vector2f& center);

        /**
         * @brief Attach a child node to this node
         * 
         * @tparam N 
         * @tparam Args 
         * @param args 
         * @return int 
         */
        template <typename N, typename... Args>
        int attach(Args&&... args)
        {
            m_children.push_back(std::make_shared<N>(static_cast<int>(m_children.size()), this, std::forward<Args>(args)...));
            return static_cast<int>(m_children.size()) - 1;
        }

        /**
         * @brief Render a node using the parent transform, then its children
         * @details Shouldn't be reimplemented in subclasses
         * 
         * @param target Surface to render the object to
         * @param parent Parent transformation data
         */
        void render(sf::RenderTarget& target, const sf::Transform& parent);

        /**
         * @brief Rendering method of an object, to be implemented in subclasses
         * 
         * @param target Surface to render the object to
         * @param transform Parent transformation data
         */
        virtual void onRender(sf::RenderTarget& target, const sf::Transform& transform) = 0;

    private:
        sf::Transform m_transform;
        std::vector<std::shared_ptr<Node>> m_children;
    };
}

#endif