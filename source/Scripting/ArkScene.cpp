#include <Small/Scripting/ArkScene.hpp>

#include <Small/Scripting/SFMLtoArk.hpp>

namespace sgl::Scripting
{
    ArkScene::ArkScene(int id, const Ark::Value& eventFunc, const Ark::Value& updateFunc, const Ark::Value& renderFunc, const Ark::Value& quitFunc) :
        Scene(id), m_eventFunc(eventFunc), m_updateFunc(updateFunc), m_renderFunc(renderFunc), m_quitFunc(quitFunc)
    {}

    ArkScene::~ArkScene()
    {}

    void ArkScene::onEvent(const sf::Event& event)
    {
        m_eventFunc.resolve(sfEventToArk(event));
    }

    void ArkScene::onUpdate(const sf::Time dt)
    {
        m_updateFunc.resolve(sfTimeToArk(dt));
    }

    void ArkScene::onRender(sf::RenderTarget& screen)
    {
        m_renderFunc.resolve(Ark::UserType(&screen));
    }

    void ArkScene::onQuit()
    {
        m_quitFunc.resolve();
    }
}