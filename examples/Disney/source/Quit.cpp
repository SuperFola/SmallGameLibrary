#include <Quit.hpp>

Quit::Quit(int id) :
    sgl::Scene(id), m_layout()
{
    m_font.loadFromFile("assets/yoster.ttf");
    m_layout = this->attach<sgl::Widgets::Layout>(0, nullptr, sf::IntRect(0, 0, 600, 600));

    sgl::Widgets::Label* label = m_layout->add<sgl::Widgets::Label>(sf::IntRect(230, 270, 0, 0));
    {
        label->text().setString("Game Over");
        label->text().setFont(m_font);
        label->text().setCharacterSize(24);
        label->text().setFillColor(sf::Color::Red);
    }

    m_labelScore = m_layout->add<sgl::Widgets::Label>(sf::IntRect(230, 300, 0, 0));
    {
        m_labelScore->text().setFont(m_font);
        m_labelScore->text().setCharacterSize(24);
        m_labelScore->text().setFillColor(sf::Color::Red);
    }
}

void Quit::onEvent(const sf::Event& event)
{
    m_layout->onEvent(event);
}

void Quit::onUpdate(const sf::Time dt)
{
    m_layout->onUpdate(dt);
}

void Quit::onRender(sf::RenderTarget& screen, const sf::Transform& transform)
{}

void Quit::onChange(void* data)
{
    m_labelScore->text().setString("Score: " + std::to_string(*static_cast<int*>(data)));
}