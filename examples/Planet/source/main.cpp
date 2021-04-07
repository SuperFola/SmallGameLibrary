#include <Small/All.hpp>

#include <MyScene.hpp>
#include <iostream>

int main(int argc, char** argv)
{
    sgl::Settings settings;
    settings.width = 640;
    settings.height = 448;
    settings.depth = 24;
    settings.stencil = 8;
    settings.major = 3;
    settings.minor = 3;

    sgl::Application app(settings);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_TRUE);

    app.setTitle("Planet renderer")
        .setVSync(false)
        .setFPSLimit(60)
        .setDebug(false);

    app.add<MyScene>();
    app.setCurrentScene<MyScene>();

    app.run();

    return 0;
}