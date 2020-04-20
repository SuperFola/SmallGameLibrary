#ifndef examples_scripting_myscene
#define examples_scripting_myscene

#include <Small/Scenes/ArkScene.hpp>

class MyScene : public sgl::Scenes::ArkScene
{
public:
    MyScene(int id, const std::string& scriptName);
};

#endif