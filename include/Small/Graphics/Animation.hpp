/**
 * @file Animation.hpp
 * @author Alexandre Plateau (lexplt.dev@gmail.com)
 * @brief Handling animated sprites
 * @version 0.1
 * @date 2020-04-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef sgl_small_graphics_animation
#define sgl_small_graphics_animation

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <toml.hpp>
#include <string>
#include <unordered_map>

namespace sgl::Graphics
{
    /**
     * @brief Handling animated sprites
     * 
     */
    class Animation
    {
    public:
        /**
         * @brief Construct a new Animation object
         * 
         */
        Animation();

        /**
         * @brief Add a new frame contained in a given rect of the texture
         * 
         * @param rect 
         */
        void addFrame(const sf::IntRect& rect);

        /**
         * @brief Set the Sprite Sheet object
         * 
         * @param texture 
         */
        void setSpriteSheet(const sf::Texture& texture);

        /**
         * @brief Get the Sprite Sheet object
         * 
         * @return const sf::Texture* 
         */
        const sf::Texture* getSpriteSheet() const;

        /**
         * @brief Number of frames in the animation
         * 
         * @return std::size_t 
         */
        std::size_t size() const;

        /**
         * @brief Invert frames on the x axis
         * 
         */
        void invertX();

        /**
         * @brief Return a given frame of the animation
         * 
         * @param n 
         * @return const sf::IntRect& 
         */
        const sf::IntRect& operator[](std::size_t n) const;

        bool isXInverted() const;

    private:
        std::vector<sf::IntRect> m_frames;
        const sf::Texture* m_texture;
        bool m_invertX = false;
    };

    /**
     * @brief Animated sprite based on the animation class
     * 
     */
    class AnimatedSprite : public sf::Drawable, public sf::Transformable
    {
    public:
        /**
         * @brief Construct a new Animated Sprite object
         * 
         * @param frameTime Time spent drawing a single frame
         * @param paused Is the animation paused?
         * @param looped Is the animation looping?
         */
        AnimatedSprite(sf::Time frameTime=sf::seconds(0.2f), bool paused=false, bool looped=true);

        /**
         * @brief Update the sprite
         * 
         * @param deltaTime Delta of time since last update
         */
        void update(sf::Time deltaTime);

        /**
         * @brief Set the Animation object
         * 
         * @param animation 
         */
        void setAnimation(const Animation& animation);

        /**
         * @brief Set the Frame Time object
         * 
         * @param time 
         */
        void setFrameTime(sf::Time time);

        /**
         * @brief Play animation
         * 
         */
        void play();

        /**
         * @brief Play given animation
         * 
         * @param animation 
         */
        void play(const Animation& animation);

        /**
         * @brief Pause animation
         * 
         */
        void pause();

        /**
         * @brief Stop animation
         * 
         */
        void stop();

        /**
         * @brief Set looped
         * 
         * @param looped 
         */
        void setLooped(bool looped);

        /**
         * @brief Set the Color object
         * 
         * @param color 
         */
        void setColor(const sf::Color& color);

        /**
         * @brief Get the Animation object
         * 
         * @return const Animation* 
         */
        const Animation* getAnimation() const;

        /**
         * @brief Get the Local Bounds object
         * 
         * @return sf::FloatRect 
         */
        sf::FloatRect getLocalBounds() const;

        /**
         * @brief Get the Global Bounds object
         * 
         * @return sf::FloatRect 
         */
        sf::FloatRect getGlobalBounds() const;

        /**
         * @brief Is the animation looping?
         * 
         * @return true 
         * @return false 
         */
        bool isLooped() const;

        /**
         * @brief Is the animation playing?
         * 
         * @return true 
         * @return false 
         */
        bool isPlaying() const;

        /**
         * @brief Get the Frame Time object
         * 
         * @return sf::Time 
         */
        sf::Time getFrameTime() const;

        /**
         * @brief Set the Frame object
         * 
         * @param newFrame 
         * @param resetTime 
         */
        void setFrame(std::size_t newFrame, bool resetTime=true);

    private:
        const Animation* m_animation;
        sf::Time m_frameTime;
        sf::Time m_currentTime;
        std::size_t m_currentFrame;
        bool m_isPaused;
        bool m_isLooped;
        const sf::Texture* m_texture;
        sf::Vertex m_vertices[4];

        /**
         * @brief Draw the sprite using SFML API
         * 
         * @param target 
         * @param states 
         */
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    };

    /**
     * @brief Load an animated sprite and its animation from a TOML configuration file
     * @details An animation sprite configuration file should look this:
     * @code
     * [data]
     * spriteSheet="path to your spritesheet"
     * steps=["idleRight", "idleLeft", "runRight", ...]
     * frameTime=0.2
     * 
     * [idleRight]
     * framesCount=3
     *     [idleRight.frame0]
     *     left=0
     *     top=0
     *     width=15
     *     height=15
     * ...
     * 
     * [idleLeft]
     * copy="idleRight"
     * invertX=true
     * 
     * ...
     * @endcode
     */
    class AnimationLoader
    {
    public:
        /**
         * @brief Construct a new Animation Loader object
         * 
         */
        AnimationLoader();

        /**
         * @brief Load the data from the TOML configuration file
         * 
         * @param configFile 
         * @return true If loading was successful
         * @return false Otherwise
         */
        bool load(const std::string& configFile);

        /**
         * @brief Return a reference to an animation by its name
         * 
         * @param key Name of the wanted animation
         * @return Animation& 
         */
        Animation& operator[](const std::string& key);

        /**
         * @brief Return a reference to the underlying animated sprite
         * 
         * @return AnimatedSprite& 
         */
        AnimatedSprite& sprite();

    private:
        toml::Value m_config;
        std::unordered_map<std::string, Animation> m_animations;
        sf::Texture m_texture;
        AnimatedSprite m_sprite;
    };
}

#endif