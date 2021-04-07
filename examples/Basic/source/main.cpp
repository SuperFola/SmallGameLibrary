#include <Small/All.hpp>

#include <MyScene.hpp>

int main(int argc, char** argv)
{
    const sgl::Settings settings = {};
    sgl::Application app(settings);

    app.setTitle("Hello world!")
        .setVSync(false)
        .setFPSLimit(60)
        .setDebug(true);

    app.add<MyScene>(12);
    app.setCurrentScene<MyScene>();

    app.run();

    return 0;
}