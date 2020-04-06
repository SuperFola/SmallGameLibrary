# Documentation

A C++17 small game library relying on [SFML](https://www.sfml-dev.org) 2.5.x, trying to abstract heavy work (settings up an application, scene management, scripting system, networking...)

# Organization of an application

An `Application` will handle the window and scenes (through the `SceneManager`).

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

    void onUpdate(const sf::Time, sgl::SceneManager& scm)
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