#include <Small/Core/Application.hpp>

#include <Small/System/FileSystem.hpp>

namespace sgl
{
    Application::Application(const Settings& settings) :
        m_screen(
            sf::VideoMode(settings.width, settings.height, settings.bitsPerPixel),
            "SmallGameLibray default application",
            settings.style,
            sf::ContextSettings(settings.depth, settings.stencil, settings.antiAliasing)
        ),
        m_vm(&m_state),
        m_showDebug(false), m_scriptingEnabled(false)
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

    Application& Application::setScripting(bool value)
    {
        m_scriptingEnabled = value;
        return *this;
    }

    Application& Application::configureScriptingEngine(const Scripting::Config& config)
    {
        m_scriptingConfig = config;

        // perform bindings before compiling
        Scripting::bindCore(&m_state, this);
        Scripting::bindGraphics(&m_state);
        Scripting::bindScenes(&m_state);
        Scripting::bindSystem(&m_state);
        Scripting::bindWidgets(&m_state);

        // compile scripts
        int compiled = Scripting::compileAllScriptsIn(
            m_scriptingConfig.scriptsDirectory,
            m_scriptingConfig.compiledScriptsDir,
            m_scriptingConfig.arkscriptLibDir
        );

        m_state.feed(m_scriptingConfig.compiledScriptsDir + "/main.arkc");
        // register all the functions and constants
        m_vm.run();

        return *this;
    }

    void Application::run()
    {
        if (m_scriptingEnabled)
            m_vm.call("onLoad");

        // game loop
        while (m_screen.isOpen())
        {
            m_profiler.Frame();

            auto dt = m_clock.restart();

            onEvents();
            onUpdate(dt);
            onRender();
        }
    }
}