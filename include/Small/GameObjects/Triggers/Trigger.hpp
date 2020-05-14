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
#include <string>

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
         * @param action A void() function to call when the trigger is executed
         * @param triggerType The typename of the inheriting children, used for inspection (name of the class to string)
         * @param repetitions Default to 0: one time trigger. Infinite is any number below -1 (starting from -2)
         */
        Trigger(Callback_t&& action, const std::string& triggerType, int repetitions=0);

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
        virtual const int getRepetitions() const final;

        /**
         * @brief Get the Trigger Type object
         * 
         * @return const std::string& 
         */
        virtual const std::string& getTriggerType() const final;

        /**
         * @brief Return the trigger as another type (should be a trigger subclass)
         * 
         * @tparam T The trigger type
         * @return T* A pointer to the trigger (use at your own risks, if it's not a trigger subclass, it will result in an undefined behaviour)
         */
        template <typename T>
        T* as()
        {
            return static_cast<T*>(this);
        }

    protected:
        bool m_active;
        int m_repetitions;
        Callback_t m_action;
        const std::string m_triggerType;
    };
}

#endif