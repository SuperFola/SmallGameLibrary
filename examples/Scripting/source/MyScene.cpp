#include <MyScene.hpp>

#include <iostream>

MyScene::MyScene(int id, const std::string& scriptName) :
    sgl::Scenes::ArkScene(id, scriptName)
{
    m_state.loadFunction("helloScene", [](std::vector<Ark::Value>&, Ark::VM*) {
        return Ark::True;
    });
}