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
        .setDebug(true)
        .setScripting(true)
        .configureScriptingEngine(sgl::Scripting::Config {
            "assets/scripts",
            "assets/compiled",
            "assets/lib"
        });

    int id = app.add<MyScene>();
    // app.setCurrentScene(id);

    app.run();

    return 0;
}