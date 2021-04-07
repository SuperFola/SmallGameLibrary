#ifndef examples_disney_game
#define examples_disney_game

#include <Small/Core/Scene.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/audio.hpp>
#include <Small/Graphics/Animation.hpp>
#include <string>
#include <array>

enum class Direction
{
    Left,
    Right
};

constexpr int maxPotCount = 5;

class Game : public sgl::Scene
{
public:
    Game(int id);

    void onUpdate(const sf::Time dt);
    void onEvent(const sf::Event& event);
    void onRender(sf::RenderTarget& screen, const sf::Transform& transform);
    void onQuit();
    void onChange(void*);

private:
    // animations
    sgl::Graphics::AnimationLoader m_player;
    sgl::Graphics::AnimationLoader m_vendor;
    sgl::Graphics::AnimationLoader m_gem;
    sgl::Graphics::AnimationLoader m_gemcount;
    std::array<sgl::Graphics::AnimationLoader, maxPotCount - 1> m_pots;
    // sprites
    sgl::Graphics::AnimatedSprite m_playerS;
    sgl::Graphics::AnimatedSprite m_vendorS;
    sgl::Graphics::AnimatedSprite m_gemS;
    sgl::Graphics::AnimatedSprite m_gemcountS;
    std::array<sgl::Graphics::AnimatedSprite, maxPotCount - 1> m_potsS;

    // controls related
    bool m_keyPressed;
    bool m_left = false;
    bool m_right = false;
    int m_direction;
    bool m_jumping;
    sf::Vector2f m_jump;
    bool m_controls = true;

    // background
    sf::Texture m_bgtex;
    sf::Sprite m_bgsprite;

    // sound
    sf::Music m_music;

    // points related
    sf::Font m_font;
    sf::Text m_pointstxt;
    int m_points = 0;

    // lives related
    int m_lives = 3;
    sf::Texture m_livesTex;
    sf::Sprite m_livesSprite;

    // waves related
    std::vector<sf::Vector2f> m_potsPos;
    sf::Vector2f m_gempos;
    sf::Time m_waitTime = sf::seconds(5.f);
    bool m_generate = true;
    int m_invicible = 0;

    void generateWave();
};

#endif