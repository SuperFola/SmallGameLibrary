#include <MyScene.hpp>

#include <Small/Core/SceneManager.hpp>
#include <iostream>

MyScene::MyScene(int id, int test_argument) :
    sgl::Scene(id), m_argument(test_argument), m_octagon(80.f, 8)
{
    std::cout << "MyScene::MyScene()" << std::endl;

    m_octagon.setFillColor(sf::Color::Green);
    m_octagon.setPosition(100, 100);
}

void MyScene::onEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
        std::cout << "key pressed" << std::endl;
}

void MyScene::onRender(sf::RenderTarget& screen, const sf::Transform& transform)
{
    screen.draw(m_octagon, transform);
}