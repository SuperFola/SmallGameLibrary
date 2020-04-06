/**
 * @file Scene.hpp
 * @author Alexandre Plateau (lexplt.dev@gmail.com)
 * @brief The base scene class and the scene states are defined here
 * @version 0.1
 * @date 2020-04-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef sgl_core_scene
#define sgl_core_scene

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <string>

namespace sgl
{
    class SceneManager;

    /**
     * @brief Describe the current state of a scene
     * 
     */
    enum class State
    {
        Running,  //< The scene is active and running
        Idle,     //< The scene is rendered / updated / processing events after the running one
        Stopped   //< The scene isn't rendered, updated, and doesn't receive events
    };

    /**
     * @brief 
     * 
     */
    class Scene
    {
    public:
        /**
         * @brief Construct a new Scene object
         * @details This is an abstract class, thus you will need to create your own Scenes, inheriting from this one.
         * 
         * @param id 
         */
        Scene(int id);

        /**
         * @brief Destroy the Scene object
         * 
         */
        virtual ~Scene();

        /**
         * @brief Event handling method
         * 
         * @param event 
         */
        virtual void onEvent(const sf::Event& event);

        /**
         * @brief Scene updating method, called after having handled the events
         * 
         * @param dt 
         * @param scm The scene manager itself, to be able to change the current scene
         */
        virtual void onUpdate(const sf::Time dt, SceneManager& scm);

        /**
         * @brief Rendering method, called after having updated the scene
         * 
         * @param screen 
         */
        virtual void onRender(sf::RenderTarget& screen);

        /**
         * @brief Method called when the application is closing
         * 
         */
        virtual void onQuit();

        /**
         * @brief Set the State object
         * 
         * @param state 
         */
        virtual void setState(State state);

        /**
         * @brief Get the Id of the scene
         * 
         * @return const int 
         */
        inline const int getId() const;

        /**
         * @brief Get the State of the scene
         * 
         * @return const State 
         */
        inline const State getState() const;

        friend class SceneManager;
    
    protected:
        State m_state;   //< The state of the scene (running, idle, stopped)
        const int m_id;  //< The unique identifier of the scene
    };
}

#include "Scene.inl"

#endif