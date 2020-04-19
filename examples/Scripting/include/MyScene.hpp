#ifndef examples_scripting_myscene
#define examples_scripting_myscene

#include <Small/Core/Scene.hpp>

class MyScene : public sgl::Scene
{
public:
    MyScene(int id);
    void onEvent(const sf::Event& event);
};

#endif