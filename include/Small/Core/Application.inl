namespace sgl
{
    inline void Application::onEvents()
    {
        m_profiler.Begin(internal::Profiler::Stage::Input);

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

        m_profiler.End(internal::Profiler::Stage::Input);
    }

    inline void Application::onUpdate(const sf::Time dt)
    {
        m_profiler.Begin(internal::Profiler::Stage::Update);

        if (m_showDebug)
        {
            m_screen.pushGLStates();

            m_profiler.Begin(internal::Profiler::Stage::Plot);

            m_profiler.Begin(internal::Profiler::Stage::NewFrame);
            ImGui::SFML::Update(m_screen, dt);
            m_profiler.End(internal::Profiler::Stage::NewFrame);

            // Debug window
            {
                m_profiler.Begin(internal::Profiler::Stage::DebugWindow);
                ImGui::Begin("Debug");

                ImGui::PlotVariable("Frame time: ", dt.asSeconds() * 1000.0f);
                ImGui::Text("FPS: %0.2f", 1.f / dt.asSeconds());

                ImGui::Checkbox("Wireframe", &m_wireframe);

                if (ImGui::Checkbox("VSync", &m_vsync))
                {
                    setVSync(m_vsync);
                }

                ImGui::End();
                m_profiler.End(internal::Profiler::Stage::DebugWindow);
            }

            // Profiler window
            {
                m_profiler.Begin(internal::Profiler::Stage::ProfilerWindow);
                ImGui::Begin("Profiler Window");

                auto& entry = m_profiler._entries[m_profiler.GetCurrentEntryIndex()];
                ImGuiWidgetFlameGraph::PlotFlame(
                    "", &internal::ProfilerValueGetter, &entry, internal::Profiler::_StageCount,
                    0, "Main Thread", FLT_MAX, FLT_MAX, ImVec2(400, 200)
                );

                std::chrono::duration<float, std::milli> frameDuration = entry._frameEnd - entry._frameStart;
                ImGui::Text("Full Frame: %0.3f", frameDuration.count());
                auto cursorX = ImGui::GetCursorPosX();
                auto indentSize = ImGui::CalcTextSize("    ").x;

                for (uint8_t i = 0; i < static_cast<uint8_t>(internal::Profiler::Stage::_StageCount); ++i)
                {
                    std::chrono::duration<float, std::milli> duration = entry._stages[i]._end - entry._stages[i]._start;
                    ImGui::SetCursorPosX(cursorX + indentSize * entry._stages[i]._level);
                    ImGui::Text("    %s: %0.3f", internal::stageNames[i], duration.count());
                    if (entry._stages[i]._level == 0)
                        frameDuration -= duration;
                }
                ImGui::Text("    Unaccounted: %0.3f", frameDuration.count());

                ImGui::End();
                m_profiler.End(internal::Profiler::Stage::ProfilerWindow);
            }

            m_profiler.End(internal::Profiler::Stage::Plot);

            m_screen.popGLStates();
        }

        m_sceneManager.onUpdate(dt);

        m_profiler.End(internal::Profiler::Stage::Update);
    }

    inline void Application::onRender()
    {
        m_profiler.Begin(internal::Profiler::Stage::Rendering);
        m_profiler.Begin(internal::Profiler::Stage::SFML);

        m_screen.clear();

        // first the content
        m_sceneManager.onRender(m_screen);

        // then the debug interface on top of it
        if (m_showDebug)
        {
            m_screen.pushGLStates();

            m_profiler.Begin(internal::Profiler::Stage::ImGuiRender);

            if (m_wireframe)
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            ImGui::SFML::Render(m_screen);

            m_profiler.End(internal::Profiler::Stage::ImGuiRender);

            m_screen.popGLStates();

            if (m_wireframe)
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            else
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        m_profiler.Begin(internal::Profiler::Stage::SwapWindow);
        m_screen.display();
        m_profiler.End(internal::Profiler::Stage::SwapWindow);
        m_profiler.End(internal::Profiler::Stage::SFML);

        m_profiler.End(internal::Profiler::Stage::Rendering);
    }
}