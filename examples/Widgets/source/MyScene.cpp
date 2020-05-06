#include <MyScene.hpp>

MyScene::MyScene(int id) :
    sgl::Scene(id), m_layout(0, nullptr, sf::IntRect(120, 90, 80, 400))
{
    m_font.loadFromFile("assets/arial.ttf");

    m_labelId = m_layout.add<sgl::Widgets::Label>(sf::IntRect(10, 20, 0, 0));
    {
        sgl::Widgets::Label* label = reinterpret_cast<sgl::Widgets::Label*>(m_layout[m_labelId]);
        label->text().setString("hello world!");
        label->text().setFont(m_font);
        label->text().setCharacterSize(24);
        label->text().setFillColor(sf::Color::Blue);
    }
}

void MyScene::onEvent(const sf::Event& event)
{
    m_layout.onEvent(event);
}

void MyScene::onUpdate(const sf::Time dt)
{
    m_layout.onUpdate(dt);
}

void MyScene::onRender(sf::RenderTarget& screen, const sf::Transform& transform)
{
    m_layout.render(screen, transform);
}