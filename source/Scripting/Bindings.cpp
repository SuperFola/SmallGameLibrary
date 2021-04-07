#include <Small/Scripting/Bindings.hpp>

#include <Small/Core/Application.hpp>

#define ARK_AWAIT(func, argc)                                             \
    if (args.size() != argc) {                                            \
        throw std::runtime_error("'" func "' needs " #argc " arguments"); \
    }
#define ARK_CHECK_ARG(func, n, type)                                            \
    if (args[n].valueType() != Ark::ValueType::type) {                          \
        throw Ark::TypeError("'" func "' argument no " #n " must be a " #type); \
    }
#define ARK_CHECK_BOOL(func, n)                                               \
    if (args[n].valueType() != Ark::ValueType::True &&                        \
        args[n].valueType() != Ark::ValueType::False) {                       \
        throw Ark::TypeError("'" func "' argument no " #n " must be a Bool"); \
    }
#define ARK_CHECK_FUNC(func, n)                                                   \
    if (!args[n].isFunction()) {                                                  \
        throw Ark::TypeError("'" func "' argument no " #n " must be a Function"); \
    }
#define RETRIEVE_SGL_APP(vm) Application* app = static_cast<Application*>(vm->getUserPointer())

namespace sgl::Scripting
{
    // ---------------------------------
    //        sgl::Application
    // ---------------------------------

    Ark::Value sglCoreAppSetTitle(std::vector<Ark::Value>& args, Ark::VM* vm)
    {
        ARK_AWAIT("sgl:core:app:setTitle", 1);
        ARK_CHECK_ARG("sgl:core:app:setTitle", 0, String);
        RETRIEVE_SGL_APP(vm);

        app->setTitle(args[0].string().c_str());

        return Ark::Nil;
    }

    Ark::Value sglCoreAppSetVSync(std::vector<Ark::Value>& args, Ark::VM* vm)
    {
        ARK_AWAIT("sgl:core:app:setVSync", 1);
        ARK_CHECK_BOOL("sgl:core:app:setVSync", 0);
        RETRIEVE_SGL_APP(vm);

        app->setVSync(args[0] == Ark::True);

        return Ark::Nil;
    }

    Ark::Value sglCoreAppSetFPSLimit(std::vector<Ark::Value>& args, Ark::VM* vm)
    {
        ARK_AWAIT("sgl:core:app:setFPSLimit", 1);
        ARK_CHECK_ARG("sgl:core:app:setFPSLimit", 0, Number);
        RETRIEVE_SGL_APP(vm);

        app->setFPSLimit(static_cast<int>(args[0].number()));

        return Ark::Nil;
    }

    Ark::Value sglCoreAppSetDebug(std::vector<Ark::Value>& args, Ark::VM* vm)
    {
        ARK_AWAIT("sgl:core:app:setDebug", 1);
        ARK_CHECK_BOOL("sgl:core:app:setDebug", 0);
        RETRIEVE_SGL_APP(vm);

        app->setDebug(args[0] == Ark::True);

        return Ark::Nil;
    }

    Ark::Value sglCoreAppSetCurrentScene(std::vector<Ark::Value>& args, Ark::VM* vm)
    {
        ARK_AWAIT("sgl:core:app:setCurrentScene", 1);
        ARK_CHECK_ARG("sgl:core:app:setCurrentScene", 0, Number);
        RETRIEVE_SGL_APP(vm);

        app->setCurrentSceneId(static_cast<int>(args[0].number()));

        return Ark::Nil;
    }

    void bindCore(Ark::State* state, Application* app)
    {
        state->loadFunction("sgl:core:app:setTitle", sglCoreAppSetTitle);
        state->loadFunction("sgl:core:app:setVSync", sglCoreAppSetVSync);
        state->loadFunction("sgl:core:app:setFPSLimit", sglCoreAppSetFPSLimit);
        state->loadFunction("sgl:core:app:setDebug", sglCoreAppSetDebug);
        state->loadFunction("sgl:core:app:setCurrentScene", sglCoreAppSetCurrentScene);
    }

    // ---------------------------------
    //        sgl::Graphics
    // ---------------------------------

    Ark::Value sglGraphics(std::vector<Ark::Value>& args, Ark::VM* vm)
    {
        ARK_AWAIT("sgl:graphics", 1);
        ARK_CHECK_ARG("sgl:graphics", 0, Number);
        RETRIEVE_SGL_APP(vm);

        return Ark::Nil;
    }

    void bindGraphics(Ark::State* state)
    {
        // sf::RenderTarget

        state->loadFunction("sgl:graphics", sglGraphics);
    }

    // ---------------------------------
    //        sgl::Scenes
    // ---------------------------------

    Ark::Value sglScenes(std::vector<Ark::Value>& args, Ark::VM* vm)
    {
        ARK_AWAIT("sgl:scenes", 1);
        ARK_CHECK_ARG("sgl:scenes", 0, Number);
        RETRIEVE_SGL_APP(vm);

        return Ark::Nil;
    }

    void bindScenes(Ark::State* state)
    {
        state->loadFunction("sgl:scenes", sglScenes);
    }

    // ---------------------------------
    //        sgl::System
    // ---------------------------------

    Ark::Value sglSystem(std::vector<Ark::Value>& args, Ark::VM* vm)
    {
        ARK_AWAIT("sgl:system", 1);
        ARK_CHECK_ARG("sgl:system", 0, Number);
        RETRIEVE_SGL_APP(vm);

        return Ark::Nil;
    }

    void bindSystem(Ark::State* state)
    {
        state->loadFunction("sgl:system", sglSystem);
    }

    // ---------------------------------
    //        sgl::Widgets
    // ---------------------------------

    Ark::Value sglWidgets(std::vector<Ark::Value>& args, Ark::VM* vm)
    {
        ARK_AWAIT("sgl:widgets", 1);
        ARK_CHECK_ARG("sgl:widgets", 0, Number);
        RETRIEVE_SGL_APP(vm);

        return Ark::Nil;
    }

    void bindWidgets(Ark::State* state)
    {
        state->loadFunction("sgl:widgets", sglWidgets);
    }
}