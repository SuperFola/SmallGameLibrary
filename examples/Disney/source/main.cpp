#include <Small/Core.hpp>

#include <Menu.hpp>
#include <Game.hpp>
#include <Quit.hpp>

#include <iostream>

int main(int argc, char** argv)
{
    sgl::Settings settings = {};
    settings.width = 600;
    settings.height = 600;
    sgl::Application app(settings);

    app.setTitle("Disney")
        .setFPSLimit(60);

    app.add<Menu>()
        .add<Game>()
        .add<Quit>();
    app.setCurrentScene<Menu>();

    app.run();

    return 0;
}