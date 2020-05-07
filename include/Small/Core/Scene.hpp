/**
 * @file Scene.hpp
 * @author Alexandre Plateau (lexplt.dev@gmail.com)
 * @brief The base scene class and the scene states are defined here
 * @version 0.2
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
#include <Small/Scripting/Config.hpp>
#include <Small/Graphics/Node.hpp>

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
     * @brief Base class which every user scene must derive from
     * 
     */
    class Scene : public Graphics::Node
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
         * @brief Initialize scripting data if needed
         * 
         * @param config 
         */
        virtual void init(const Scripting::Config& config);

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
         */
        virtual void onUpdate(const sf::Time dt);

        /**
         * @brief Rendering method, called after having updated the scene
         * @details This method is called first, then all the children (if any) attached to it
         *          are rendered one after another, in the order they were attached.
         * 
         * @param screen 
         * @param transform transformation used as a base when rendering something, eg:
         * @code
         * screen.draw(sprite, transform);
         * @endcode
         */
        virtual void onRender(sf::RenderTarget& screen, const sf::Transform& transform);

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
        virtual void setState(State state) final;

        /**
         * @brief Get the Id of the scene
         * 
         * @return const int 
         */
        inline virtual const int getId() const final;

        /**
         * @brief Get the State of the scene
         * 
         * @return const State 
         */
        inline virtual const State getState() const final;

        friend class SceneManager;

    protected:
        State m_state;   //< The state of the scene (running, idle, stopped)
        const int m_id;  //< The unique identifier of the scene
        SceneManager* m_sceneManager;  //< The SceneManager to be able to change active scene
    };
}

#include "Scene.inl"

#endif