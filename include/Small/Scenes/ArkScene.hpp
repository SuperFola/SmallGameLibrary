/**
 * @file ArkScene.hpp
 * @author Alexandre Plateau (lexplt.dev@gmail.com)
 * @brief Define a scene scriptable through ArkScript
 * @version 0.1
 * @date 2020-04-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef sgl_small_scenes_arkscene
#define sgl_small_scenes_arkscene

#include <Small/Core/Scene.hpp>
#include <Ark/Ark.hpp>
#include <Small/Scripting/Config.hpp>

#include <string>

namespace sgl::Scenes
{
    /**
     * @brief Define a scene scriptable through ArkScript
     * @details Each scene is given a script with different functions to work
     *          correctly:
     * @code
     * (let onLoad   (fun () {  loading code  }))
     * (let onEvent  (fun (event) {  event handling code  }))
     * (let onUpdate (fun (dt) {  update handling code  }))
     * (let onRender (fun (screen) {  rendering code  }))
     * (let onQuit   (fun () {  unloading code  }))
     * @endcode
     * 
     */
    class ArkScene : public Scene
    {
    public:
        /**
         * @brief Construct a new Ark Scene object
         * 
         * @param id The identifier of the scene
         * @param scriptName Filename of the ArkScript file for this scene
         */
        ArkScene(int id, const std::string& scriptName);

        /**
         * @brief Destroy the Ark Scene object
         * 
         */
        ~ArkScene();

        /**
         * @brief Initialize scripting data
         * 
         * @param config 
         */
        void init(const Scripting::Config& config);

        /**
         * @brief Event handling method
         * 
         * @param event 
         */
        void onEvent(const sf::Event& event);

        /**
         * @brief Scene updating method, called after having handled the events
         * 
         * @param dt 
         */
        void onUpdate(const sf::Time dt);

        /**
         * @brief Rendering method, called after having updated the scene
         * 
         * @param screen 
         */
        void onRender(sf::RenderTarget& screen);

        /**
         * @brief Method called when the application is closing
         * 
         */
        void onQuit();

    protected:
        std::string m_scriptName;
        Ark::State m_state;
        Ark::VM m_vm;
    };
}

#endif