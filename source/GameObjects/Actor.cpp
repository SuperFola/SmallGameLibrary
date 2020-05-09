#include <Small/GameObjects/Actor.hpp>

namespace sgl::GameObjects
{
    Actor::Actor() :
        Graphics::Node()
    {}

    Actor::~Actor()
    {}

    void Actor::onEvent(const sf::Event& event)
    {}

    void Actor::onUpdate(const sf::Time dt)
    {}
}