#include <MyScene.hpp>

MyScene::MyScene(int id) :
    sgl::Scene(id)
{
    m_font.loadFromFile("assets/arial.ttf");
    m_layout = this->attach<sgl::Widgets::Layout>(0, nullptr, sf::IntRect(120, 90, 80, 400));

    m_label = m_layout->add<sgl::Widgets::Label>(sf::IntRect(10, 20, 0, 0));
    {
        m_label->text().setString("hello world!");
        m_label->text().setFont(m_font);
        m_label->text().setCharacterSize(24);
        m_label->text().setFillColor(sf::Color::Blue);
    }
}

void MyScene::onEvent(const sf::Event& event)
{
    m_layout->onEvent(event);
}

void MyScene::onUpdate(const sf::Time dt)
{
    m_layout->onUpdate(dt);
}

void MyScene::onRender(sf::RenderTarget& screen, const sf::Transform& transform)
{}