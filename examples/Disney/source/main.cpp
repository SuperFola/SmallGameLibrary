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

    int mid = app.add<Menu>();
    int gid = app.add<Game>();
    int qid = app.add<Quit>();
    app.setCurrentScene(mid);

    app.run();

    return 0;
}