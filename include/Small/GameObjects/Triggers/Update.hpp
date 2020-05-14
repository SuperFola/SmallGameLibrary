/**
 * @file Update.hpp
 * @author Alexandre Plateau (lexplt.dev@gmail.com)
 * @brief A basic update trigger, executed when a delta of time is reached
 * @version 0.1
 * @date 2020-05-14
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef sgl_small_gameobjects_triggers_update
#define sgl_small_gameobjects_triggers_update

#include <Small/GameObjects/Triggers/Trigger.hpp>
#include <SFML/System/Time.hpp>

namespace sgl::GameObjects
{
    class UpdateTrigger : public Trigger
    {
    public:
        /**
         * @brief Construct a new Update Trigger object
         * 
         * @param delta Time to wait for between each action
         * @param action A void() function to call when the trigger is executed
         * @param repetitions Number of repetitions
         */
        UpdateTrigger(const sf::Time delta, Trigger::Callback_t&& action, int repetitions);

        /**
         * @brief Destroy the Update Trigger object
         * 
         */
        ~UpdateTrigger();

        void update(const sf::Time dt);

    protected:
        const sf::Time m_updateDelta;
        sf::Time m_currentTime;
    };
}

#endif