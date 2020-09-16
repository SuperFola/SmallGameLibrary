/**
 * @file SceneManager.hpp
 * @author Alexandre Plateau (lexplt.dev@gmail.com)
 * @brief Define the scene manager (creating, handling and destroying them)
 * @version 0.1
 * @date 2020-04-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef sgl_core_scenemanager
#define sgl_core_scenemanager

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <Small/Core/Scene.hpp>
#include <Small/Scripting/Config.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <typeinfo>
#include <unordered_map>

namespace sgl
{
    /**
     * @brief Scene manager, in charge of creating, handling and destroying scenes
     * 
     */
    class SceneManager
    {
    public:
        /**
         * @brief Construct a new Scene Manager object
         * 
         */
        SceneManager();

        /**
         * @brief Destroy the Scene Manager object, setting all the scenes state to stopped
         * 
         */
        ~SceneManager();

        /**
         * @brief Return the identifier of the current scene
         * 
         * @return int 
         */
        inline int current() const;

        /**
         * @brief Remove a scene by searching it from its identifier
         * 
         * @param id 
         * @return true On success
         * @return false If the scene couldn't be found
         */
        bool remove(int id);

        /**
         * @brief Return a scene by its identifier
         * 
         * @param id 
         * @return Scene* will be nullptr if the scene couldn't be found
         */
        inline Scene* operator[](int id);

        /**
         * @brief Set the Current scene
         * 
         * @tparam S The type of the scene
         * @param data Default to nullptr. Points to data owned by the scene calling setCurrent, to give to the next scene
         * @return SceneManager& 
         */
        template <typename Scene>
        SceneManager& setCurrent(void* data=nullptr);
        {
            const std::type_info& type(typeid(Scene));
            int id = m_hashCodeToSceneId[type.hash_code()];

            if (0 <= id && id < static_cast<int>(m_scenes.size()))
            {
                if (m_current != -1)
                    m_scenes[m_current]->setState(State::Stopped);
                m_current = id;
                m_scenes[m_current]->setState(State::Running);

                // call the onChange method of the scene to notify it
                // that the current running scene has changed
                m_scenes[m_current]->onChange(data);
            }
            return *this;
        }

        /**
         * @brief Initialize needed scenes with scripting informations
         * 
         * @param config 
         * @return SceneManager& 
         */
        SceneManager& init(const Scripting::Config& config);

        /**
         * @brief Dispatch the event to the active scenes
         * 
         * @param event 
         * @return SceneManager& 
         */
        SceneManager& onEvent(const sf::Event& event);

        /**
         * @brief Update the active scenes
         * 
         * @param dt 
         * @return SceneManager& 
         */
        SceneManager& onUpdate(const sf::Time dt);

        /**
         * @brief Render the active scenes
         * 
         * @param screen 
         * @return SceneManager& 
         */
        SceneManager& onRender(sf::RenderTarget& screen);

        /**
         * @brief Quit all the scenes
         * 
         * @return SceneManager& 
         */
        SceneManager& onQuit();

        /**
         * @brief Register a scene and return its identifier
         * 
         * @tparam S The type of the scene
         * @tparam Args 
         * @param args Arguments for the constructor of the scene
         */
        template <typename S, typename... Args>
        void add(Args&&... args)
        {
            m_scenes.push_back(std::make_unique<S>(static_cast<int>(m_scenes.size()), std::forward<Args>(args)...));
            // register the scene manger in the newly created scene
            m_scenes.back().get()->m_sceneManager = this;

            const std::type_info& type(std::type_info(typeid(S)));
            m_hashCodeToSceneId[type.hash_code()] = static_cast<int>(m_scenes.size()) - 1;
        }

    private:
        std::vector<std::unique_ptr<Scene>> m_scenes;
        std::unordered_map<std::size_t, std::size_t> m_hashCodeToSceneId;
        int m_current;
        sf::Transform m_transform;  ///< This transform never change, we just use it as a base when rendering
    };
}

#include "SceneManager.inl"

#endif