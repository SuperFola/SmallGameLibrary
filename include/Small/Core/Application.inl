namespace sgl
{
    inline void Application::onEvents()
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
            
            m_sceneManager.onEvent(event);
        }
    }

    inline void Application::onUpdate(const sf::Time dt)
    {
        if (m_showDebug)
        {
            ImGui::SFML::Update(m_screen, dt);

            ImGui::Begin("Debug");

            if (m_time % m_sampleRate == 0)
                ImGui::PlotVariable("Frame time: ", dt.asSeconds() * 1000.0f);
            else
                ImGui::PlotVariable("Frame Time: ", FLT_MAX);
            ImGui::SliderInt("Debug Sample Rate", &m_sampleRate, 1, 60);

            if (ImGui::Checkbox("Wireframe", &m_wireframe))
            {
                if (m_wireframe)
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                else
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }

            ImGui::End();
        }
        
        m_sceneManager.onUpdate(dt);

        ++m_time;
        if (m_time >= 3600)
            m_time = 0;
    }

    inline void Application::onRender()
    {
        m_screen.clear();

        // first the content
        m_sceneManager.onRender(m_screen);

        // then the debug interface on top of it
        if (m_showDebug)
        {
            if (m_wireframe)
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            ImGui::SFML::Render(m_screen);
            if (m_wireframe)
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }

        m_screen.display();
    }
}