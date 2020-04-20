#include <Small/Scenes/ArkScene.hpp>

#include <Small/Scripting/Bindings.hpp>
#include <Small/Scripting/SFMLtoArk.hpp>

namespace sgl::Scenes
{
    ArkScene::ArkScene(int id, const std::string& scriptName) :
        Scene(id), m_scriptName(scriptName), m_vm(&m_state)
    {}

    ArkScene::~ArkScene()
    {}

    void ArkScene::init(const Scripting::Config& config)
    {
        m_state.setLibDir(config.arkscriptLibDir);

        // Core module isn't binded because a sc
        Scripting::bindGraphics(&m_state);
        Scripting::bindScenes(&m_state);
        Scripting::bindSystem(&m_state);
        Scripting::bindWidgets(&m_state);

        m_state.feed(config.compiledScriptsDir + "/" + m_scriptName);
        m_vm.run();

        m_vm.call("onLoad");
    }

    void ArkScene::onEvent(const sf::Event& event)
    {
        m_vm.call("onEvent", Scripting::sfEventToArk(event));
    }

    void ArkScene::onUpdate(const sf::Time dt)
    {
        m_vm.call("onUpdate", Scripting::sfTimeToArk(dt));
    }

    void ArkScene::onRender(sf::RenderTarget& screen)
    {
        auto a = Ark::Value(Ark::UserType(&screen));
        m_vm.call("onRender", a);
    }

    void ArkScene::onQuit()
    {
        m_vm.call("onQuit");
    }
}