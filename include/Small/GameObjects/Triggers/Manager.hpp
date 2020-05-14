/**
 * @file Manager.hpp
 * @author Alexandre Plateau (lexplt.dev@gmail.com)
 * @brief Handle triggers and destroy them when needed
 * @version 0.1
 * @date 2020-05-14
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef sgl_small_gameobjects_triggers_manager
#define sgl_small_gameobjects_triggers_manager

#include <SFML/System/Time.hpp>
#include <Small/GameObjects/Manager.hpp>
#include <Small/GameObjects/Triggers/Trigger.hpp>

namespace sgl::GameObjects
{
    /**
     * @brief Specialization of sgl::GameObjects::Manager to handle triggers
     * 
     */
    class TriggerManager : public Manager<Trigger>
    {
    public:
        /**
         * @brief Update all the triggers and destroy them if it's time for them to go
         * 
         * @param dt 
         * @return TriggerManager& 
         */
        TriggerManager& onUpdate(const sf::Time dt);
    };
}

#endif