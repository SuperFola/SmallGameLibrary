/**
 * @file Application.hpp
 * @author Alexandre Plateau (lexplt.dev@gmail.com)
 * @brief Define the application hosting the scenes for the game
 * @version 0.1
 * @date 2020-04-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef sgl_core_application
#define sgl_core_application

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <string>
#include <imgui/imgui.h>
#include <imgui/imgui-SFML.h>
#include <SFML/OpenGL.hpp>
#include <Small/Core/SceneManager.hpp>
#include <Small/Debug/Profiler.hpp>

namespace sgl
{
    namespace Style
    {
        constexpr unsigned Titlebar   = sf::Style::Titlebar;  //< The window will have a titlebar
        constexpr unsigned Resizable  = sf::Style::Resize;  //< The window will be resizable
        constexpr unsigned Close      = sf::Style::Close;  //< The window will have a close button
        constexpr unsigned Fullscreen = sf::Style::Fullscreen;  //< The window will be in fullscren, can not be combined with others
    }

    /**
     * @brief Holding the application settings
     * 
     */
    struct Settings
    {
        unsigned width = 480;        //< Width of the window, in pixels
        unsigned height = 360;       //< Height of the window, in pixels
        unsigned style = Style::Titlebar | Style::Resizable | Style::Close;  //< Default mode for the window, titlebar, resizable and has a close button
        unsigned bitsPerPixel = 32;  //< By default, we request 32 bits per pixel
        unsigned depth = 0;          //< Depth buffer bits
        unsigned stencil = 0;        //< Stencil buffer bits
        unsigned antiAliasing = 1;   //< Anti aliasing level
    };

    /**
     * @brief The main component of the library, handling the scenes and running the app
     * 
     */
    class Application
    {
    public:
        /**
         * @brief Construct a new Application object
         * 
         * @param settings The settings for the application (size of the window, style, additional settings for the underlying opengl context)
         */
        Application(const Settings& settings);

        /**
         * @brief Destroy the Application object
         * 
         */
        ~Application();

        /**
         * @brief Set the Title of the SFML window
         * 
         * @param title 
         * @return Application& 
         */
        Application& setTitle(const std::string& title);

        /**
         * @brief Set the Virtual Synchronization ON or OFF
         * @details Settings the Virtual Synchronization ON will limit the FPS to 60
         * 
         * @param state 
         * @return Application& 
         */
        Application& setVSync(bool state);

        /**
         * @brief Set the FPS limit
         * 
         * @param value 
         * @return Application& 
         */
        Application& setFPSLimit(int value);

        /**
         * @brief Set the Debug mode
         * @details If the Debug mode is ON, ImGui tools will be displayed
         * 
         * @param state 
         * @return Application& 
         */
        Application& setDebug(bool state);

        /**
         * @brief Set the Current Scene
         * @details By default, no scene is selected, thus nothing will be rendered
         * 
         * @param id 
         * @return Application& 
         */
        Application& setCurrentScene(int id);

        /**
         * @brief Add a scene to the application
         * @details Create the scene in place, and return its identifier to refer to it later.
         * 
         * @tparam S The type of the scene
         * @tparam Args 
         * @param args Arguments for the constructor of the scene
         * @return int 
         */
        template <typename S, typename... Args>
        int add(Args&&... args)
        {
            return m_sceneManager.add<S>(std::forward<Args>(args)...);
        }

        /**
         * @brief Run the application until an error occurs or until the quit condition is met
         * @details The builtin quit condition is when the click on the close button,
         *          this will call the method `onQuit` of each scene.
         * 
         */
        void run();
    
    private:
        sf::RenderWindow m_screen;
        sf::Clock m_clock;
        SceneManager m_sceneManager;

        // debug related attributes
        internal::Profiler m_profiler;
        bool m_showDebug;
        const int m_debugKey = sf::Keyboard::F4;
        bool m_wireframe = false;

        /**
         * @brief Handling basic events (closing window, triggering debug mode), and passing the events to the active scene
         * 
         */
        inline void onEvents();

        /**
         * @brief Update the current scene by giving it the time passed since the last update
         * 
         * @param dt 
         */
        inline void onUpdate(const sf::Time dt);

        /**
         * @brief Rendering debug interface if requested, as well as the current scene
         * 
         */
        inline void onRender();
    };
}

#include "Application.inl"

#endif