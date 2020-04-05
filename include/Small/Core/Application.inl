namespace sgl
{
    inline void Application::handleEvents()
    {
        sf::Event event;
        while (m_screen.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_screen.close();
            else if (event.type == sf::Event::KeyPressed && event.key.code == m_debugKey)
                m_showDebug = !m_showDebug;

            if (m_showDebug)
                ImGui::SFML::ProcessEvent(event);
            
            m_sceneManager.handleEvent(event);
        }
    }

    inline void Application::update(const sf::Time dt)
    {
        if (m_showDebug)
        {
            static bool wireframe = false;

            ImGui::SFML::Update(m_screen, dt);

            ImGui::Begin("Debug");
            ImGui::Text("dt: %d ms", dt.asMilliseconds());
//            ImGui::PlotVariable("Frame time: ", dt.asMilliseconds());

            if (ImGui::Checkbox("Wireframe", &wireframe))
            {
                if (wireframe)
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                else
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }

            ImGui::End();
        }
        
        m_sceneManager.update(dt);
    }

    inline void Application::render()
    {
        if (m_showDebug)
            ImGui::SFML::Render(m_screen);

        m_sceneManager.render(m_screen);
        m_screen.display();
    }
}