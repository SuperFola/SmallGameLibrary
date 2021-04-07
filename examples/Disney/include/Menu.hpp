#ifndef examples_disney_menu
#define examples_disney_menu

#include <Small/Core/Scene.hpp>
#include <Small/Widgets.hpp>
#include <SFML/Graphics/Font.hpp>

class Menu : public sgl::Scene
{
public:
    Menu(int id);

    void onEvent(const sf::Event& event);
    void onUpdate(const sf::Time dt);
    void onRender(sf::RenderTarget& screen, const sf::Transform& transform);

private:
    sgl::Widgets::Layout* m_layout;
    sf::Font m_font;
};

#endif