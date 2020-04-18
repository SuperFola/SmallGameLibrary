#ifndef examples_widgets_myscene
#define examples_widgets_myscene

#include <Small/Core/Scene.hpp>
#include <Small/Widgets.hpp>
#include <SFML/Graphics/Font.hpp>

class MyScene : public sgl::Scene
{
public:
    MyScene(int id);

    void onEvent(const sf::Event& event);
    void onUpdate(const sf::Time dt);
    void onRender(sf::RenderTarget& screen);

private:
    sgl::Widgets::Layout m_layout;
    int m_labelId;
    sf::Font m_font;
};

#endif