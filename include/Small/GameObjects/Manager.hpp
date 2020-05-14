/**
 * @file Manager.hpp
 * @author Alexandre Plateau (lexplt.dev@gmail.com)
 * @brief Providing a basic ressource management throughout the lifetime of the program
 * @version 0.1
 * @date 2020-05-08
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef sgl_small_gameobjects_manager
#define sgl_small_gameobjects_manager

#include <string>
#include <unordered_map>

namespace sgl::GameObjects
{
    /**
     * @brief Templated singleton to hold ressources throughout the lifetime of the program
     * 
     * @tparam T Type of ressource held
     */
    template <typename T>
    class Manager
    {
    public:
        /**
         * @brief Get the instance of the singleton
         * 
         * @return Manager<T>& 
         */
        static Manager<T>& get();

        /**
         * @brief Constructor is deleted since this class is a singleton, thus shouldn't be copied
         * 
         */
        Manager(const Manager<T>&) = delete;

        /**
         * @brief Assignement operator is deleted since this class is a singleton, thus shouldn't be copied
         * 
         */
        Manager<T>& operator=(const Manager<T>&) = delete;

        /**
         * @brief Add an object in the container, with a given name
         * 
         * @param name The key which will be used to retrieve the object later on
         * @param object The object itself
         * @return Manager<T>& 
         */
        Manager<T>& add(const std::string& name, T&& object);

        /**
         * @brief Check if the container is holding with a value under a given name
         * 
         * @param name 
         * @return true On success
         * @return false Otherwise
         */
        bool has(const std::string& name) const;

        /**
         * @brief Return an element by its name
         * 
         * @param name 
         * @return T& 
         */
        T& operator[](const std::string& name);

    private:
        Manager() {}

    protected:
        std::unordered_map<std::string, T> m_container;
    };
}

#include "Manager.inl"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Text.hpp>

namespace sgl::GameObjects
{
    using FontManager    = Manager<sf::Font>;     ///< sf::Font ressource manager
    using ImageManager   = Manager<sf::Image>;    ///< sf::Image ressource manager
    using ShaderManager  = Manager<sf::Shader>;   ///< sf::Shader ressource manager
    using ShapeManager   = Manager<sf::Shape>;    ///< sf::Shape ressource manager
    using SpriteManager  = Manager<sf::Sprite>;   ///< sf::Sprite ressource manager
    using TextureManager = Manager<sf::Texture>;  ///< sf::Texture ressource manager
    using TextManager    = Manager<sf::Text>;     ///< sf::Text ressource manager
}

#endif