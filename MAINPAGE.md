# Documentation

A C++17 small game library relying on [SFML](https://www.sfml-dev.org) 2.5.x, trying to abstract heavy work (settings up an application, scene management, scripting system, networking...)

# Organization of an application

An `Application` will handle the window and scenes (through the `SceneManager`).

## Creating a Scene

User scenes must inherit from `sgl::Scene`, as in the following example:

~~~~{.cpp}
class MyScene : public sgl::Scene
{
public:
    // the identifier is a must-have argument, needed to identify a scene
    MyScene(int id, int test_argument) :
        sgl::Scene(id),
        m_argument(test_argument), m_octagon(80.f, 8)
    {
        std::cout << "MyScene::MyScene()" << std::endl;

        m_octagon.setFillColor(sf::Color::Green);
        m_octagon.setPosition(100, 100);
    }

    void onEvent(const sf::Event& event)
    {
        if (event.type == sf::Event::KeyPressed)
            std::cout << "key pressed" << std::endl;
    }

    void onUpdate(const sf::Time dt)
    {}

    void onRender(sf::RenderTarget& screen)
    {
        screen.draw(m_octagon);
    }

    void onQuit()
    {}

private:
    int m_argument;
    sf::CircleShape m_octagon;
};
~~~~

The methods `onXXX` can be not implemented, by default they won't do anything.

The call order is:
* constructor
* game loop
    * event
    * update
    * render
* quit

--------

Each scene has a `State` handled by the `SceneManager`, default state is `Stopped` (not rendered, not updated).

Only one scene at a time can be in `Running` state, it will be the first one to be rendered and updated, then the `Idle` scenes will be rendered and updated. This is useful to implement a widgets layer for example.  
Scenes can be manually stopped (if you don't want to run your inventory and your fighting system at the same time, since both will receive events).

## Creating and customizing an Application

~~~~{.cpp}
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

    app.add<MyScene>(12);
    app.setCurrentScene<MyScene>();

    app.run();

    return 0;
}
~~~~

The sgl::Settings can be modified to change the `width` and `height` of the window, as well as its `style` (presence of titlebar, close button...). Some other settings can be modified but are linked to the backend, OpenGL, so modify them only if you know what you are doing.

We add and create a new scene to an application by using `app.add<Scene>(args)`, and set it as the current one by using `app.setCurrentScene<MyScene>()`. This means that if we want to use the same scene multiple time with different parameters, for example a `Level` scene, we wouldn't be able to have more than a single level registered at a time since they are selected by the class name and not by their scene id. Thus we can use a workaround with templated classes:

~~~~{.cpp}
template <class T, int N>
class Wrapper : public T
{
public:
    template <typename... Args>
    Wrapper(Args&&... args) :
        T(std::forward<Args>(args)...)
    {}
};

int main(int argc, char** argv)
{
    const sgl::Settings settings = {};
    sgl::Application app(settings);

    app.setTitle("Hello world!")
        .setVSync(false)
        .setFPSLimit(60)
        .setDebug(true);

    app.add<Wrapper<Level, 1>>(12);
    app.add<Wrapper<Level, 2>>(15);
    app.add<Wrapper<Level, 3>>(32);
    app.setCurrentScene<Wrapper<Level, 1>>();

    app.run();

    return 0;
}
~~~~