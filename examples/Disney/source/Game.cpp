#include <Game.hpp>
#include <Quit.hpp>

#include <Small/Core/SceneManager.hpp>

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

constexpr float speed = 64.f;
constexpr int floor_y = 520;

Game::Game(int id) :
    sgl::Scene(id), m_keyPressed(false),
    m_direction(static_cast<int>(Direction::Left)), m_jumping(false)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    if (!m_player.load("assets/Abu.toml"))
        std::cerr << "ERROR abu.toml" << std::endl;
    if (!m_vendor.load("assets/Vendor.toml"))
        std::cerr << "ERROR vendor.toml" << std::endl;
    if (!m_gem.load("assets/Items.toml"))
        std::cerr << "ERROR Items.toml" << std::endl;
    for (int i=0; i < maxPotCount - 1; ++i)
    {
        if (!m_pots[i].load("assets/Pot.toml"))
            std::cerr << "ERROR Pot.toml" << std::endl;
    }
    if (!m_font.loadFromFile("assets/yoster.ttf"))
        std::cerr << "Error yoster.ttf" << std::endl;

    if (!m_livesTex.loadFromFile("assets/abu_life.png"))
        std::cerr << "ERROR abu_life.png" << std::endl;
    m_livesSprite.setTexture(m_livesTex);

    if (!m_bgtex.loadFromFile("assets/market.png", sf::IntRect(1, 89, 600, 600)))
        std::cerr << "ERROR market.png" << std::endl;
    m_bgsprite.setTexture(m_bgtex);
    m_bgsprite.setPosition(0.f, 0.f);

    if (!m_music.openFromFile("assets/Aladdin, Disney's (GENESIS) Music - Stage 01 Prince Ali.ogg"))
        std::cerr << "ERROR Aladdin, Disney's (GENESIS) Music - Stage 01 Prince Ali.ogg" << std::endl;
}

void Game::onUpdate(const sf::Time dt)
{
    if (!m_controls)
        return;

    if (m_keyPressed || m_left || m_right)
    {
        if (m_left && m_direction == static_cast<int>(Direction::Left))
        {
            if (m_playerS.getPosition().x - speed * dt.asSeconds() >= 44.f)
            {
                if (!m_jumping)
                    m_playerS.play(m_player["runLeft"]);
                else
                    m_playerS.play(m_player["jumpLeft"]);
                m_playerS.move(-speed * dt.asSeconds() * 2.5f, 0.f);
            }
            else if (!m_jumping)
                m_playerS.play(m_player["idleLeft"]);
        }
        else if (m_right)
        {
            if (m_playerS.getPosition().x + 50 + speed * dt.asSeconds() < 600.f)
            {
                if (!m_jumping)
                    m_playerS.play(m_player["runRight"]);
                else
                    m_playerS.play(m_player["jumpRight"]);
                m_playerS.move(speed * dt.asSeconds() * 2.5f, 0.f);
            }
            else if (!m_jumping)
                m_playerS.play(m_player["idleRight"]);
        }
    }
    else
    {
        if (m_direction == static_cast<int>(Direction::Left))
        {
            if (!m_jumping)
                m_playerS.play(m_player["idleLeft"]);
            else
                m_playerS.play(m_player["jumpLeft"]);
        }
        else
        {
           if (!m_jumping)
                m_playerS.play(m_player["idleRight"]);
            else
                m_playerS.play(m_player["jumpRight"]);
        }
    }

    if (m_jumping)
    {
        m_playerS.move(0.f, dt.asSeconds() * m_jump.y);
        m_jump.y += dt.asSeconds() * speed * 2.f;
    }

    if (m_jumping && m_playerS.getPosition().y >= floor_y)
    {
        m_playerS.setPosition(m_playerS.getPosition().x, floor_y);
        m_jumping = false;
        m_jump.y = 0.f;
    }

    m_playerS.update(dt);
    m_vendorS.update(dt);
    m_gemS.update(dt);

    const float acceleration = 0.1f * (m_points / 150);

    // intersects with a pot?
    if (!m_potsPos.empty())
    {
        for (int i=0; i < maxPotCount - 1; ++i)
        {
            auto& vec = m_potsPos[i];

            // we can lose points if we touch a pot once per wave
            // and if the pot isn't in a crash state
            if (m_invicible == 0 && m_potsS[i].getAnimation() == &m_pots[i]["fall"] && sf::FloatRect(vec.x, vec.y, 28, 25).intersects(m_playerS.getGlobalBounds()))
            {
                m_points -= 400;
                m_pointstxt.setString(std::to_string(m_points));
                m_invicible = 1;
                m_lives -= 1;
                m_potsS[i].play(m_pots[i]["crash"]);
            }
            // update pots
            if (vec.y < floor_y + 20)
                vec.y += dt.asSeconds() * speed * (3.f + acceleration);
            if (vec.y >= floor_y + 20)
                m_potsS[i].play(m_pots[i]["crash"]);
            m_potsS[i].update(dt);
        }
    }
    // update gem pos
    m_gempos.y += dt.asSeconds() * speed * (3.3f + acceleration);
    m_gemS.setPosition(m_gempos.x, m_gempos.y);

    if (m_lives <= 0)
    {
        m_controls = false;
        m_sceneManager->setCurrent<Quit>(static_cast<void*>(&m_points));  // game over scene
    }

    // intersects with gem?
    if (sf::FloatRect(m_gempos.x, m_gempos.y, 16, 17).intersects(m_playerS.getGlobalBounds()))
    {
        m_points += 200;
        m_pointstxt.setString(std::to_string(m_points));

        m_gempos.x = -20;
    }

    // remove gem
    if (m_gempos.y >= floor_y)
        m_gempos.x = -20;

    // if all the pots are crashed and we can generate
    if (std::all_of(m_potsS.begin(), m_potsS.end(), [](auto& obj) { return obj.isEnd(); }) && !m_generate)
    {
        // time for next wave
        m_waitTime = sf::seconds(0.6f);
        m_generate = true;
    }

    // wait for next wave
    if (m_generate)
        m_waitTime -= dt;
    if (m_waitTime.asSeconds() <= 0.f && m_generate)
    {
        m_potsPos.clear();
        m_invicible = 0;
        generateWave();
        m_generate = false;
    }

    // m_invicible != 0 if we touch a pot during a wave
    // used to make abu blinking to say that he is invicible
    if (m_invicible)
        m_invicible++;
}

void Game::onEvent(const sf::Event& event)
{
    switch (event.type)
    {
        case sf::Event::KeyPressed:
            switch (event.key.code)
            {
                case sf::Keyboard::Q:
                    m_keyPressed = true;
                    m_left = true;
                    m_direction = static_cast<int>(Direction::Left);
                    break;

                case sf::Keyboard::D:
                    m_keyPressed = true;
                    m_right = true;
                    m_direction = static_cast<int>(Direction::Right);
                    break;

                case sf::Keyboard::Space:
                    if (!m_jumping)
                    {
                        m_jumping = true;
                        m_keyPressed = true;
                        m_jump.x = 0.f;
                        m_jump.y = -speed * 2.4f;
                    }
                    break;

                case sf::Keyboard::Escape:
                    m_controls = !m_controls;
                    break;

                default:
                    break;
            }
            break;

        case sf::Event::KeyReleased:
            switch (event.key.code)
            {
                case sf::Keyboard::Q:
                    m_keyPressed = m_left = false;
                    break;

                case sf::Keyboard::D:
                    m_keyPressed = m_right = false;
                    break;

                case sf::Keyboard::Space:
                    m_keyPressed = false;
                    break;

                default:
                    break;
            }
            break;

        default:
            break;
    }
}

void Game::onRender(sf::RenderTarget& screen, const sf::Transform& transform)
{
    screen.draw(m_bgsprite, transform);
    screen.draw(m_vendorS, transform);
    if (!m_potsPos.empty())
    {
        for (int i=0; i < maxPotCount - 1; ++i)
        {
            m_potsS[i].setPosition(m_potsPos[i].x, m_potsPos[i].y);
            screen.draw(m_potsS[i], transform);
        }
    }
    screen.draw(m_gemS, transform);
    if (m_invicible % 4 == 0)
        screen.draw(m_playerS, transform);

    screen.draw(m_gemcountS, transform);
    screen.draw(m_pointstxt, transform);

    // does not count the life lost during a wave, make it blink
    const int lives =  m_lives + ((m_invicible == 0) ? 0 : 1);
    for (int i=0; i < lives; ++i)
    {
        m_livesSprite.setPosition(16 + i * 24, 48);
        if (i == lives - 1 && m_invicible % 4 == 0)
            screen.draw(m_livesSprite, transform);
        else if (i != lives - 1)
            screen.draw(m_livesSprite, transform);
    }
}

void Game::onQuit()
{
    m_music.stop();
}

void Game::onChange(void*)
{
    m_points = 0;
    m_jumping = false;
    m_lives = 3;

    m_potsPos.clear();

    for (int i=0; i < maxPotCount - 1; ++i)
        m_potsS[i].play(m_pots[i]["fall"]);

    m_pointstxt.setFont(m_font);
    m_pointstxt.setPosition(42, 16);
    m_pointstxt.setCharacterSize(18);
    m_pointstxt.setString(std::to_string(m_points));

    m_gemcount = m_gem;
    m_gemcountS.play(m_gemcount["static_gem"]);
    m_gemcountS.setPosition(16, 20);

    m_playerS.setPosition(276, floor_y);
    m_playerS.play(m_player["idleLeft"]);

    m_vendorS.setPosition(12, 500);
    m_vendorS.play(m_vendor["idleRight"]);

    m_gemS.play(m_gem["gem"]);
    m_gempos.x = -20.f;
    m_gemS.setPosition(m_gempos.x, m_gempos.y);

    m_music.setLoop(true);
    m_music.play();

    m_keyPressed = false;
    m_left = false;
    m_right = false;
    m_controls = true;

    m_waitTime = sf::seconds(5.f);
    m_generate = true;
    m_invicible = 0;
}

void Game::generateWave()
{
    // max 6 items on screen
    int randGem = std::rand() % maxPotCount;
    int spaceX = (std::rand() % 200) + 40;

    for (int i=0; i < maxPotCount - 1; ++i)
        m_potsS[i].play(m_pots[i]["fall"]);

    const int pattern = std::rand() % 3;  // 0 line, 1 diag 1, 2: diag 2

    for (int i=0; i < maxPotCount; ++i)
    {
        float y = -50.f + 
            ((pattern == 1) ? 30.f + i * -20.f :
                ((pattern == 2) ? 30.f + (maxPotCount - i - 1) * -20.f :
                    0.f));

        if (i == randGem)
        {
            m_gempos.x = i * 85.f + spaceX;
            m_gempos.y = y;
        }
        else
            m_potsPos.push_back(sf::Vector2f(i * 85.f + spaceX, y));
    }
}