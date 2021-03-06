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

namespace sgl::Scripting
{
    void bindCore(Ark::State* state, Application* app)
    {
        state->loadFunction("sglCoreAppSetTitle", [=](std::vector<Ark::Value>& args) {
            ARK_AWAIT("sglCoreAppSetTitle", 1);
            ARK_CHECK_ARG("sglCoreAppSetTitle", 0, String);

            app->setTitle(args[0].string());

            return Ark::Nil;
        });

        state->loadFunction("sglCoreAppSetVSync", [=](std::vector<Ark::Value>& args) {
            ARK_AWAIT("sglCoreAppSetVSync", 1);
            ARK_CHECK_BOOL("sglCoreAppSetVSync", 0);

            app->setVSync(args[0] == Ark::True);

            return Ark::Nil;
        });

        state->loadFunction("sglCoreAppSetFPSLimit", [=](std::vector<Ark::Value>& args) {
            ARK_AWAIT("sglCoreAppSetFPSLimit", 1);
            ARK_CHECK_ARG("sglCoreAppSetFPSLimit", 0, Number);

            app->setFPSLimit(static_cast<int>(args[0].number()));

            return Ark::Nil;
        });

        state->loadFunction("sglCoreAppSetDebug", [=](std::vector<Ark::Value>& args) {
            ARK_AWAIT("sglCoreAppSetDebug", 1);
            ARK_CHECK_BOOL("sglCoreAppSetDebug", 0);

            app->setDebug(args[0] == Ark::True);

            return Ark::Nil;
        });

        state->loadFunction("sglCoreAppSetCurrentScene", [=](std::vector<Ark::Value>& args) {
            ARK_AWAIT("sglCoreAppSetCurrentScene", 1);
            ARK_CHECK_ARG("sglCoreAppSetCurrentScene", 0, Number);

            app->setCurrentScene(static_cast<int>(args[0].number()));

            return Ark::Nil;
        });
    }

    void bindGraphics(Ark::State* state)
    {
        // sf::RenderTarget

        state->loadFunction("sglGraphics", [](std::vector<Ark::Value>& args) {
            return Ark::Nil;
        });
    }

    void bindScenes(Ark::State* state)
    {
        state->loadFunction("sglScenes", [](std::vector<Ark::Value>& args) {
            return Ark::Nil;
        });
    }

    void bindSystem(Ark::State* state)
    {
        state->loadFunction("sglSystem", [](std::vector<Ark::Value>& args) {
            return Ark::Nil;
        });
    }

    void bindWidgets(Ark::State* state)
    {
        state->loadFunction("sglWidgets", [](std::vector<Ark::Value>& args) {
            return Ark::Nil;
        });
    }
}