#include <glad.h>

#include <MyScene.hpp>

#include <Small/Core/SceneManager.hpp>
#include <iostream>

sf::Glsl::Mat4 glm2sf(const glm::mat4& mat4)
{
    float temp[16];
    for (int i=0; i < 16; temp[i] = ((float*)glm::value_ptr(mat4))[i], ++i);
    return static_cast<sf::Glsl::Mat4>(temp);
}

MyScene::MyScene(int id) :
    sgl::Scene(id),
    m_time(0.f),
    m_icosahedron(0.5f),
    m_cameraPos(0.f, 0.f, 3.f),
    m_cameraTarget(0.f, 0.f, 0.f)
{
    m_icosahedron.setEdgeLength(0.8f);

    m_view = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 3.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    // shader
    m_shader.loadFromFile("assets/shader.vert", "assets/shader.frag");

    glm::mat4 projection = glm::perspective(glm::radians(30.0f), 600.f / 480.f, 0.01f, 100.0f);
    m_shader.setUniform(
        "projection",
        glm2sf(projection)
    );

    m_view = glm::lookAt(glm::vec3(-3.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    m_shader.setUniform(
        "view",
        glm2sf(m_view)
    );
}

void MyScene::onRender(sf::RenderTarget& screen, const sf::Transform& transform)
{
    // clear the buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    sf::Shader::bind(&m_shader);

    m_icosahedron.draw();
}

void MyScene::onUpdate(const sf::Time dt)
{
    m_time += dt.asSeconds();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(m_time * 20.f), glm::vec3(1.f, 1.f, 1.f));
    m_shader.setUniform("model", glm2sf(model));
}