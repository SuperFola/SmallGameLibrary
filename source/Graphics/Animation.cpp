#include <Small/Graphics/Animation.hpp>

#include <iostream>
#include <sstream>
#include <fstream>

namespace sgl::Graphics
{
    Animation::Animation() :
        m_texture(nullptr)
    {}

    void Animation::addFrame(const sf::IntRect& rect)
    {
        m_frames.push_back(rect);
    }

    void Animation::setSpriteSheet(const sf::Texture& texture)
    {
        m_texture = &texture;
    }

    const sf::Texture* Animation::getSpriteSheet() const
    {
        return m_texture;
    }

    std::size_t Animation::size() const
    {
        return m_frames.size();
    }

    void Animation::invertX()
    {
        m_invertX = !m_invertX;
    }

    const sf::IntRect& Animation::operator[](std::size_t n) const
    {
        return m_frames[n];
    }

    bool Animation::isXInverted() const
    {
        return m_invertX;
    }

    ///////////////////////////////////////////////////////////////

    AnimatedSprite::AnimatedSprite(sf::Time frameTime, bool paused, bool looped) :
        m_animation(nullptr), m_frameTime(frameTime), m_currentFrame(0),
        m_isPaused(paused), m_isLooped(looped), m_texture(nullptr)
    {}

    void AnimatedSprite::setAnimation(const Animation& animation)
    {
        m_animation = &animation;
        m_texture = m_animation->getSpriteSheet();
        m_currentFrame = 0;
        setFrame(m_currentFrame);
    }

    void AnimatedSprite::setFrameTime(sf::Time time)
    {
        m_frameTime = time;
    }

    void AnimatedSprite::play()
    {
        m_isPaused = false;
    }

    void AnimatedSprite::play(const Animation& animation)
    {
        if (getAnimation() != &animation)
            setAnimation(animation);
        play();
    }

    void AnimatedSprite::pause()
    {
        m_isPaused = true;
    }

    void AnimatedSprite::stop()
    {
        m_isPaused = true;
        m_currentFrame = 0;
        setFrame(m_currentFrame);
    }

    void AnimatedSprite::setLooped(bool looped)
    {
        m_isLooped = looped;
    }

    void AnimatedSprite::setColor(const sf::Color& color)
    {
        // Update the vertices' color
        m_vertices[0].color = color;
        m_vertices[1].color = color;
        m_vertices[2].color = color;
        m_vertices[3].color = color;
    }

    const Animation* AnimatedSprite::getAnimation() const
    {
        return m_animation;
    }

    sf::FloatRect AnimatedSprite::getLocalBounds() const
    {
        sf::IntRect rect = (*m_animation)[m_currentFrame];

        float width = static_cast<float>(std::abs(rect.width));
        float height = static_cast<float>(std::abs(rect.height));

        return sf::FloatRect(0.f, 0.f, width, height);
    }

    sf::FloatRect AnimatedSprite::getGlobalBounds() const
    {
        return getTransform().transformRect(getLocalBounds());
    }

    bool AnimatedSprite::isLooped() const
    {
        return m_isLooped;
    }

    bool AnimatedSprite::isPlaying() const
    {
        return !m_isPaused;
    }

    sf::Time AnimatedSprite::getFrameTime() const
    {
        return m_frameTime;
    }

    void AnimatedSprite::setFrame(std::size_t newFrame, bool resetTime)
    {
        if (m_animation)
        {
            // calculate new vertex positions and texture coordiantes
            sf::IntRect rect = (*m_animation)[newFrame];
            sf::FloatRect rectf = sf::FloatRect(rect);

            m_vertices[0].position = sf::Vector2f(0.f, 0.f);
            m_vertices[1].position = sf::Vector2f(0.f, rectf.height);
            m_vertices[2].position = sf::Vector2f(rectf.width, rectf.height);
            m_vertices[3].position = sf::Vector2f(rectf.width, 0.f);

            float left = rectf.left + 0.0001f;
            float right = left + rectf.width;
            float top = rectf.top;
            float bottom = top + rectf.height;

            if (m_animation->isXInverted())
            {
                left = rectf.left + rectf.width;
                right = rectf.left;
                top = rectf.top;
                bottom = top + rectf.height;
            }

            m_vertices[0].texCoords = sf::Vector2f(left, top);
            m_vertices[1].texCoords = sf::Vector2f(left, bottom);
            m_vertices[2].texCoords = sf::Vector2f(right, bottom);
            m_vertices[3].texCoords = sf::Vector2f(right, top);
        }

        if (resetTime)
            m_currentTime = sf::Time::Zero;
    }

    void AnimatedSprite::update(sf::Time deltaTime)
    {
        // if not paused and we have a valid animation
        if (!m_isPaused && m_animation)
        {
            // add delta time
            m_currentTime += deltaTime;

            // if current time is bigger then the frame time advance one frame
            if (m_currentTime >= m_frameTime)
            {
                // reset time, but keep the remainder
                m_currentTime = sf::microseconds(m_currentTime.asMicroseconds() % m_frameTime.asMicroseconds());

                // get next Frame index
                if (m_currentFrame + 1 < m_animation->size())
                    m_currentFrame++;
                else
                {
                    // animation has ended
                    if (!m_isLooped)
                        m_isPaused = true;
                    else
                        m_currentFrame = 0; // reset to start
                }

                // set the current frame, not reseting the time
                setFrame(m_currentFrame, false);
            }
        }
    }

    void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if (m_animation && m_texture)
        {
            states.transform *= getTransform();
            states.texture = m_texture;
            target.draw(m_vertices, 4, sf::Quads, states);
        }
    }

    ///////////////////////////////////////////////////////////////

    AnimationLoader::AnimationLoader()
    {}

    bool AnimationLoader::load(const std::string& configFile)
    {
        std::ifstream ifs(configFile);
        toml::ParseResult pr = toml::parse(ifs);
        ifs.close();

        if (!pr.valid())
        {
            std::cerr << "AnimationLoader configuration error: " << pr.errorReason << std::endl;
            return false;
        }
        else
            m_config = pr.value;

        if (m_config.find("data") == nullptr)
        {
            std::cerr << "AnimationLoader configuration needs a data section" << std::endl;
            return false;
        }

        const toml::Value* spriteSheet = m_config.find("data.spriteSheet");
        if (spriteSheet == nullptr || !spriteSheet->is<std::string>())
        {
            std::cerr << "AnimationLoader configuration: data.spriteSheet (string) missing" << std::endl;
            return false;
        }

        const toml::Value* steps = m_config.find("data.steps");
        if (steps == nullptr || !steps->is<std::vector<std::string>>())
        {
            std::cerr << "AnimationLoader configuration: data.steps (array of strings) missing" << std::endl;
            return false;
        }

        const toml::Value* frameTime = m_config.find("data.frameTime");
        if (frameTime == nullptr || !frameTime->is<double>())
        {
            std::cerr << "AnimationLoader configuration: data.frameTime (double) missing" << std::endl;
            return false;
        }

        if (!m_texture.loadFromFile(spriteSheet->as<std::string>()))
        {
            std::cerr << "AnimationLoader configuration: couldn't load spriteSheet: " << spriteSheet->as<std::string>() << std::endl;
            return false;
        }

        m_sprite.setFrameTime(sf::seconds(static_cast<float>(frameTime->as<double>())));
        std::vector<std::string> stepsData = steps->as<std::vector<std::string>>();

        for (std::size_t i=0, size=stepsData.size(); i < size; ++i)
        {
            const toml::Value* copy = m_config.find(stepsData[i] + ".copy");
            if (copy == nullptr)
            {
                const toml::Value* framesCount = m_config.find(stepsData[i] + ".framesCount");
                if (framesCount == nullptr || !framesCount->is<int>())
                {
                    std::cerr << "AnimationLoader configuration: " << stepsData[i] << ".framesCount is missing" << std::endl;
                    return false;
                }

                m_animations[stepsData[i]] = Animation();
                m_animations[stepsData[i]].setSpriteSheet(m_texture);

                int framesCountData = framesCount->as<int>();
                for (int frame=0; frame < framesCountData; ++frame)
                {
                    std::stringstream frameStr;
                    frameStr << "frame" << frame;

                    int top, left, width, height;

                    toml::Value* check = m_config.find(stepsData[i] + "." + frameStr.str() + ".left");
                    if (check == nullptr || !check->is<int>())
                    {
                        std::cerr << "AnimationLoader configuration: " << stepsData[i] << "." << frameStr.str() << ".left (integer) is missing" << std::endl;
                        return false;
                    }
                    else
                        left = check->as<int>();

                    check = m_config.find(stepsData[i] + "." + frameStr.str() + ".top");
                    if (check == nullptr || !check->is<int>())
                    {
                        std::cerr << "AnimationLoader configuration: " << stepsData[i] << "." << frameStr.str() << ".top (integer) is missing" << std::endl;
                        return false;
                    }
                    else
                        top = check->as<int>();

                    check = m_config.find(stepsData[i] + "." + frameStr.str() + ".width");
                    if (check == nullptr || !check->is<int>())
                    {
                        std::cerr << "AnimationLoader configuration: " << stepsData[i] << "." << frameStr.str() << ".width (integer) is missing" << std::endl;
                        return false;
                    }
                    else
                        width = check->as<int>();

                    check = m_config.find(stepsData[i] + "." + frameStr.str() + ".height");
                    if (check == nullptr || !check->is<int>())
                    {
                        std::cerr << "AnimationLoader configuration: " << stepsData[i] << "." << frameStr.str() << ".height (integer) is missing" << std::endl;
                        return false;
                    }
                    else
                        height = check->as<int>();

                    m_animations[stepsData[i]].addFrame(sf::IntRect(left, top, width, height));
                }
            }
            else
            {
                if (!copy->is<std::string>())
                {
                    std::cerr << "AnimationLoader configuration: " << stepsData[i] << ".copy should be a string" << std::endl;
                    return false;
                }
                m_animations[stepsData[i]] = m_animations[copy->as<std::string>()];

                const toml::Value* invertX = m_config.find(stepsData[i] + ".invertX");
                if (invertX && invertX->is<bool>() && invertX->as<bool>())
                    m_animations[stepsData[i]].invertX();
            }
        }

        return true;
    }

    Animation& AnimationLoader::operator[](const std::string& key)
    {
        return m_animations[key];
    }

    AnimatedSprite& AnimationLoader::sprite()
    {
        return m_sprite;
    }
}