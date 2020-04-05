#include <MyScene.hpp>

#include <Small/Core/SceneManager.hpp>
#include <iostream>

MyScene::MyScene(int id, int test_argument) :
    sgl::Scene(id), m_argument(test_argument), m_octagon(80.f, 8);
{
    std::cout << "MyScene::MyScene()" << std::endl;

    m_octagon.setFillColor(sf::Color::Green);
    m_octagon.setPos(100, 100);
}

void MyScene::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
        std::cout << "key pressed" << std::endl;
}

void MyScene::update(const sf::Time dt, SceneManager& scm)
{}

void MyScene::render(sf::RenderTarget& screen)
{
    screen.render(m_octagon);
}