#include <Small/All.hpp>

#include <MyScene.hpp>
#include <iostream>

int main(int argc, char** argv)
{
    const sgl::Settings settings = {};
    sgl::Application app(settings);

    app.setTitle("Hello world!")
        .setVSync(false)
        .setFPSLimit(60)
        .setDebug(true);
    
    int id = app.add<MyScene>(12);
    std::cout << id;
    app.setCurrentScene(id);

    app.run();

    return 0;
}