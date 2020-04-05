#include <Small/Core/Application.hpp>

namespace sgl
{
    Application::Application(const Settings& settings) :
        m_screen(
            sf::VideoMode(settings.width, settings.height, settings.bitsPerPixel),
            "SmallGameLibray default application",
            settings.style,
            sf::ContextSettings(settings.depth, settings.stencil, settings.antiAliasing)
        )
    {
        ImGui::SFML::Init(m_screen);
        m_screen.resetGLStates();
    }

    Application::~Application()
    {
        ImGui::SFML::Shutdown();
    }

    Application& Application::setTitle(const std::string& title)
    {
        m_screen.setTitle(title);
        return *this;
    }

    Application& Application::setVSync(bool state)
    {
        m_screen.setVerticalSyncEnabled(state);
        return *this;
    }

    Application& Application::setFPSLimit(int value)
    {
        m_screen.setFramerateLimit(value);
        return *this;
    }

    Application& Application::setDebug(bool state)
    {
        m_showDebug = state;
        return *this;
    }

    Application& Application::setCurrentScene(int id)
    {
        m_sceneManager.setCurrent(id);
        return *this;
    }

    void Application::run()
    {
        while (m_screen.isOpen())
        {
            auto dt = m_clock.restart();

            handleEvents();
            update(dt);
            render();
        }
    }
}