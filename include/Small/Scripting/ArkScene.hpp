/**
 * @file ArkScene.hpp
 * @author Alexandre Plateau (lexplt.dev@gmail.com)
 * @brief A special scene intended to be created and used only from ArkScript code
 * @version 0.1
 * @date 2020-04-19
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef sgl_small_scripting_arkscene
#define sgl_small_scripting_arkscene

#include <Small/Core/Scene.hpp>

#include <Ark/Ark.hpp>

namespace sgl::Scripting
{
    /**
     * @brief A special scene intended to be created and used only from ArkScript code
     * 
     */
    class ArkScene : public Scene
    {
    public:
        /**
         * @brief Construct a new Ark Scene object
         * 
         * @param id Unique identifier for the scene, automatically set
         * @param eventFunc The event function of the scene (in ArkScript)
         * @param updateFunc The update function of the scene (in ArkScript)
         * @param renderFunc The render function of the scene (in ArkScript)
         * @param quitFunc The quit function of the scene (in ArkScript)
         */
        ArkScene(int id, const Ark::Value& eventFunc, const Ark::Value& updateFunc, const Ark::Value& renderFunc, const Ark::Value& quitFunc);

        /**
         * @brief Destroy the Ark Scene object
         * 
         */
        ~ArkScene();

        /**
         * @brief Event handling method
         * @details Call the function held by m_eventFunc
         * 
         * @param event 
         */
        void onEvent(const sf::Event& event);

        /**
         * @brief Scene updating method, called after having handled the events
         * @details Call the function held by m_updateFunc
         * 
         * @param dt 
         */
        void onUpdate(const sf::Time dt);

        /**
         * @brief Rendering method, called after having updated the scene
         * @details Call the function held by m_renderFunc
         * 
         * @param screen 
         */
        void onRender(sf::RenderTarget& screen);

        /**
         * @brief Method called when the application is closing
         * @details Call the function held by m_quitFunc
         * 
         */
        void onQuit();

    protected:
        Ark::Value m_eventFunc;
        Ark::Value m_updateFunc;
        Ark::Value m_renderFunc;
        Ark::Value m_quitFunc;
    };
}

#endif