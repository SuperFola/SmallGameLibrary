#ifndef examples_basic_myscene
#define examples_basic_myscene

#include <Small/Core/Scene.hpp>
#include <SFML/Graphics/CircleShape.hpp>

class MyScene : public sgl::Scene
{
public:
    MyScene(int id, int test_argument);

    void handleEvent(const sf::Event& event);
    void update(const sf::Time dt);
    void render(sf::RenderTarget& screen);

private:
    int m_argument;
    sf::CircleShape m_octagon;
};

#endif