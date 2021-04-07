#include <Menu.hpp>
#include <Game.hpp>

#include <Small/Core/SceneManager.hpp>

Menu::Menu(int id) :
    sgl::Scene(id)
{
    m_font.loadFromFile("assets/yoster.ttf");
    m_layout = this->attach<sgl::Widgets::Layout>(0, nullptr, sf::IntRect(0, 0, 600, 600));

    sgl::Widgets::Label* labelMenu = m_layout->add<sgl::Widgets::Label>(sf::IntRect(260, 20, 0, 0));
    {
        labelMenu->text().setString("Menu");
        labelMenu->text().setFont(m_font);
        labelMenu->text().setCharacterSize(24);
        labelMenu->text().setFillColor(sf::Color::White);
    }

    sgl::Widgets::Label* labelHelp = m_layout->add<sgl::Widgets::Label>(sf::IntRect(80, 200, 0, 0));
    {
        labelHelp->text().setString(
            "Utilisez Q et D pour deplacer Abu,\n" \
            "espace pour le faire sauter\n" \
            "\n" \
            "Appuyez sur n'importe quelle touche\n" \
            "pour lancer le jeu"
        );
        labelHelp->text().setFont(m_font);
        labelHelp->text().setCharacterSize(24);
        labelHelp->text().setFillColor(sf::Color::White);
    }
}

void Menu::onEvent(const sf::Event& event)
{
    m_layout->onEvent(event);

    if (event.type == sf::Event::KeyReleased)
        m_sceneManager->setCurrent<Game>();  // Game
}

void Menu::onUpdate(const sf::Time dt)
{
    m_layout->onUpdate(dt);
}

void Menu::onRender(sf::RenderTarget& screen, const sf::Transform& transform)
{}