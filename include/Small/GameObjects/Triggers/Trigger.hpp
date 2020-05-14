/**
 * @file Trigger.hpp
 * @author Alexandre Plateau (lexplt.dev@gmail.com)
 * @brief Define a base trigger class
 * @version 0.1
 * @date 2020-05-14
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef sgl_small_gameobjects_triggers_trigger
#define sgl_small_gameobjects_triggers_trigger

#include <functional>

namespace sgl::GameObjects
{
    /**
     * @brief A base trigger class to implement your own type of triggers
     * 
     */
    class Trigger
    {
    public:
        using Callback_t = std::function<void(void)>;

        /**
         * @brief Construct a new Trigger object
         * 
         * @param repetions Default to 0: one time trigger
         */
        Trigger(int repetions=0);

        /**
         * @brief Destroy the Trigger object
         * 
         */
        virtual ~Trigger();

        /**
         * @brief Call the trigger function and decrease repetitions count
         * 
         * @param dt 
         */
        virtual void operator()();

        /**
         * @brief Get the Repetitions object
         * 
         * @return int 
         */
        int getRepetitions() const;

    protected:
        bool m_active;
        int m_repetions;
        Callback_t m_action;
    };
}

#endif