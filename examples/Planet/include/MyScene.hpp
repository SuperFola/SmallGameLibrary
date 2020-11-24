#ifndef examples_tilemap_myscene
#define examples_tilemap_myscene

#include <Small/Core/Scene.hpp>
#include <SFML/Graphics.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Icosahedron.h>

class MyScene : public sgl::Scene
{
public:
    MyScene(int id);

    void onRender(sf::RenderTarget& screen, const sf::Transform& transform);
    void onUpdate(const sf::Time dt);

private:
    float m_time;
    sf::Shader m_shader;
    Icosahedron m_icosahedron;

    glm::vec3 m_cameraPos, m_cameraTarget;
    glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 m_view;
};

#endif