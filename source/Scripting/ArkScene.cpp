#include <Small/Scripting/ArkScene.hpp>

namespace sgl::Scripting
{
    ArkScene::ArkScene(int id, const Ark::Value& eventFunc, const Ark::Value& updateFunc, const Ark::Value& renderFunc, const Ark::Value& quitFunc) :
        Scene(id), m_eventFunc(eventFunc), m_updateFunc(updateFunc), m_renderFunc(renderFunc), m_quitFunc(quitFunc)
    {}

    ArkScene::~ArkScene()
    {}

    void ArkScene::onEvent(const sf::Event& event)
    {}

    void ArkScene::onUpdate(const sf::Time dt)
    {}

    void ArkScene::onRender(sf::RenderTarget& screen)
    {}

    void ArkScene::onQuit()
    {
        m_quitFunc.resolve();
    }
}