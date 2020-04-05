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
        virtual ~Scene() {}

        /**
         * @brief Event handling method, will need to be implemented in your own Scenes
         * 
         * @param event 
         */
        virtual void handleEvent(const sf::Event& event) = 0;

        /**
         * @brief Scene updating method, will need to be implemented in your own Scenes
         * 
         * @param dt 
         */
        virtual void update(const sf::Time dt, SceneManager& scm) = 0;

        /**
         * @brief Rendering method, will need to be implemented in your own Scenes
         * 
         * @param screen 
         */
        virtual void render(sf::RenderTarget& screen) = 0;

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

        friend class SceneManager;
    
    protected:
        State m_state;
        const int m_id;
    };
}

#include "Scene.inl"

#endif