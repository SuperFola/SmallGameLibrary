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

#include <functional>
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
        using Visitor_t = std::function<void(Trigger*)>;

        /**
         * @brief Update all the triggers and destroy them if it's time for them to go
         * @details Example:
         * @code
         * sgl::GameObjects::TriggerManager::get().update([&dt](sgl::GameObjects::Triger* trigger) {
         *      if (trigger->getTriggerType() == "UpdateTrigger")
         *          trigger->as<sgl::GameObjects::UpdateTrigger>()->update(dt);
         *      else if (trigger->getTriggerType() == "...")
         *          ...
         *      else
         *          (*trigger)();  // update the trigger with the basic thing
         * });
         * @endcode
         * 
         * @param visitor Visitor function to update all the triggers
         * @return TriggerManager& 
         */
        TriggerManager& update(Visitor_t&& visitor);

        /**
         * @brief Add / replace a visitor for a given trigger type
         * 
         * @param triggerType 
         * @param visitor 
         * @return TriggerManager& 
         */
        TriggerManager& addVisitor(const std::string& triggerType, Visitor_t&& visitor);
    };
}

#endif