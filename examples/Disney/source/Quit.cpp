#include <Quit.hpp>
#include <Game.hpp>

#include <Small/Core/SceneManager.hpp>

Quit::Quit(int id) :
    sgl::Scene(id), m_layout()
{
    m_font.loadFromFile("assets/yoster.ttf");
    m_layout = this->attach<sgl::Widgets::Layout>(0, nullptr, sf::IntRect(0, 0, 600, 600));

    sgl::Widgets::Label* label = m_layout->add<sgl::Widgets::Label>(sf::IntRect(150, 200, 0, 0));
    {
        label->text().setString(
            "        Game Over     \n\n"
            "Appuyez sur une touche\n"
            "    pour recommencer    ");
        label->text().setFont(m_font);
        label->text().setCharacterSize(24);
        label->text().setFillColor(sf::Color::Red);
    }

    m_labelScore = m_layout->add<sgl::Widgets::Label>(sf::IntRect(210, 340, 0, 0));
    {
        m_labelScore->text().setFont(m_font);
        m_labelScore->text().setCharacterSize(24);
        m_labelScore->text().setFillColor(sf::Color::Red);
    }
}

void Quit::onEvent(const sf::Event& event)
{
    m_layout->onEvent(event);

    if (event.type == sf::Event::KeyPressed)
        m_sceneManager->setCurrent<Game>();  // Game
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