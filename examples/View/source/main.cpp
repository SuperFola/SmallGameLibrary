#include <Small/All.hpp>

#include <MyScene.hpp>
#include <Bis.hpp>
#include <iostream>

int main(int argc, char** argv)
{
    sgl::Settings settings = {};
    settings.width = settings.height = 16 * 8 * 6;
    sgl::Application app(settings);

    app.setTitle("Hello world!")
        .setFPSLimit(60);
    
    int id = app.add<Bis>();
    app.setCurrentScene(id);

    app.run();

    return 0;
}