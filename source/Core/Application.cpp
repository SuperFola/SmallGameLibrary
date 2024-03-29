#include <glad.h>

#include <Small/Core/Application.hpp>

#include <Small/Scripting/Engine.hpp>
#include <Small/Scripting/Bindings.hpp>
#include <Small/System/FileSystem.hpp>

namespace sgl
{
    Application::Application(const Settings& settings) :
        m_screen(
            sf::VideoMode(settings.width, settings.height, settings.bitsPerPixel),
            "SmallGameLibray default application",
            settings.style,
            sf::ContextSettings(settings.depth, settings.stencil, settings.antiAliasing, settings.major, settings.minor)
        ),
        // we don't want to remove unused variables
        m_state(Ark::FeaturePersist | Ark::FeatureFunctionArityCheck),
        m_vm(&m_state),
        m_showDebug(false), m_scriptingEnabled(false)
    {
        if (!gladLoadGL())
        {
            std::cout << "Failed to load glad" << std::endl;
            exit(-1);
        }

        m_screen.resetGLStates();
        glViewport(0, 0, settings.width, settings.height);

        ImGui::SFML::Init(m_screen);
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
        m_vsync = state;
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

    Application& Application::setCurrentSceneId(int id)
    {
        m_sceneManager.setCurrentId(id);
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
        m_state.setLibDir(config.arkscriptLibDir);

        // save an owned pointer to this app into the VM to retrieve it from the binded functions
        m_vm.setUserPointer(static_cast<void*>(this));

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
        // scripting related
        if (m_scriptingEnabled)
            m_vm.call("onLoad");
        m_sceneManager.init(m_scriptingConfig);

        // game loop
        while (m_screen.isOpen())
        {
            m_profiler.Frame();

            auto dt = m_clock.restart();

            onEvents();
            onUpdate(dt);
            onRender();
        }

        if (m_scriptingEnabled)
            m_vm.call("onQuit");
    }
}