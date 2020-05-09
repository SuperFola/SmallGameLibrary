#include <Small/Graphics/Node.hpp>

namespace sgl::Graphics
{
    Node::Node()
    {}

    Node::~Node()
    {}

    Node& Node::move(float x, float y)
    {
        m_transform.translate(x, y);
        return *this;
    }

    Node& Node::move(const sf::Vector2f& offset)
    {
        m_transform.translate(offset);
        return *this;
    }

    Node& Node::rotate(float angle)
    {
        m_transform.rotate(angle);
        return *this;
    }

    Node& Node::rotate(float angle, float centerX, float centerY)
    {
        m_transform.rotate(angle, centerX, centerY);
        return *this;
    }

    Node& Node::rotate(float angle, const sf::Vector2f& center)
    {
        m_transform.rotate(angle, center);
        return *this;
    }

    Node& Node::scale(float scaleX, float scaleY)
    {
        m_transform.scale(scaleX, scaleY);
        return *this;
    }

    Node& Node::scale(const sf::Vector2f& factors)
    {
        m_transform.scale(factors);
        return *this;
    }

    Node& Node::scale(float scaleX, float scaleY, float centerX, float centerY)
    {
        m_transform.scale(scaleX, scaleY, centerX, centerY);
        return *this;
    }

    Node& Node::scale(const sf::Vector2f& factors, const sf::Vector2f& center)
    {
        m_transform.scale(factors, center);
        return *this;
    }

    sf::Transform& Node::getTransform()
    {
        return m_transform;
    }

    void Node::render(sf::RenderTarget& target, const sf::Transform& parent)
    {
        sf::Transform combined = parent * m_transform;
        onRender(target, combined);
        for (std::size_t i=0, size=m_children.size(); i < size; ++i)
            m_children[i]->render(target, combined);
    }
}