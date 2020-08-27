#ifndef examples_disney_quit
#define examples_disney_quit

#include <Small/Core/Scene.hpp>
#include <Small/Widgets.hpp>
#include <SFML/Graphics/Font.hpp>

class Quit : public sgl::Scene
{
public:
    Quit(int id);

    void onEvent(const sf::Event& event);
    void onUpdate(const sf::Time dt);
    void onRender(sf::RenderTarget& screen, const sf::Transform& transform);
    void onChange(void* data);

private:
    sgl::Widgets::Layout* m_layout;
    sf::Font m_font;
    sgl::Widgets::Label* m_labelScore;
};

#endif