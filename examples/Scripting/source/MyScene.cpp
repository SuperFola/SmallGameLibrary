#include <MyScene.hpp>

#include <iostream>

MyScene::MyScene(int id) :
    sgl::Scene(id)
{}

void MyScene::onEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
        std::cout << "key pressed" << std::endl;
}