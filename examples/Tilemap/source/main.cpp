#include <Small/All.hpp>

#include <MyScene.hpp>
#include <iostream>

int main(int argc, char** argv)
{
    sgl::Settings settings;
    settings.width = 640;
    settings.height = 448;

    sgl::Application app(settings);

    app.setTitle("Tilemap renderer")
        .setVSync(false)
        .setFPSLimit(60)
        .setDebug(true);

    app.add<MyScene>();
    app.setCurrentScene<MyScene>();

    app.run();

    return 0;
}