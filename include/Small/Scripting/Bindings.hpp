/**
 * @file Bindings.hpp
 * @author Alexandre Plateau (lexplt.dev@gmail.com)
 * @brief Binding the small game library in ArkScript
 * @version 0.1
 * @date 2020-04-19
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef sgl_small_scripting_bindings
#define sgl_small_scripting_bindings

#include <Ark/VM/State.hpp>

namespace sgl::Core
{
    class Application;
}

namespace sgl::Scripting
{
    /**
     * @brief Bind the Core module of the library to ArkScript
     * 
     * @param state Pointer to a valid ArkScript state
     * @param app Pointer to the running application
     */
    void bindCore(Ark::State* state, Application* app);

    /**
     * @brief Bind the Graphics module of the library to ArkScript
     * 
     * @param state Pointer to a valid ArkScript state
     */
    void bindGraphics(Ark::State* state);

    /**
     * @brief Bind the Scenes module of the library to ArkScript
     * 
     * @param state Pointer to a valid ArkScript state
     */
    void bindScenes(Ark::State* state);

    /**
     * @brief Bind the System module of the library to ArkScript
     * 
     * @param state Pointer to a valid ArkScript state
     */
    void bindSystem(Ark::State* state);

    /**
     * @brief Bind the Widgets module of the library to ArkScript
     * 
     * @param state Pointer to a valid ArkScript state
     */
    void bindWidgets(Ark::State* state);
}

#endif