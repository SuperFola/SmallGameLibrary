/**
 * @file Profiler.hpp
 * @author bwrsandman, Alexandre Plateau (lexplt.dev@gmail.com)
 * @brief Profiler from https://github.com/bwrsandman/imgui-flame-graph/ (example/main.cpp), updated for the project needs
 * @version 0.2
 * @date 2020-04-06
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef sgl_debug_profiler
#define sgl_debug_profiler

#include <array>
#include <chrono>
#include <imgui_widget_flamegraph.hpp>

namespace sgl::internal
{
    /**
     * @brief Profiler used to display the time spent in each section of the application
     * 
     */
    class Profiler
    {
    public:
        enum Stage
        {
            Input,
            Update,
            Plot,
            NewFrame,
            DebugWindow,
            ProfilerWindow,
            ImGuiRender,
            SFML,
            SwapWindow,
            Rendering,

            _StageCount,
        };

        struct Scope
        {
            unsigned char _level;
            std::chrono::system_clock::time_point _start;
            std::chrono::system_clock::time_point _end;
            bool _finalized = false;
        };

        struct Entry
        {
            std::chrono::system_clock::time_point _frameStart;
            std::chrono::system_clock::time_point _frameEnd;
            std::array<Scope, _StageCount> _stages;
        };

        void Frame()
        {
            auto& prevEntry = _entries[_currentEntry];
            _currentEntry = (_currentEntry + 1) % _bufferSize;
            prevEntry._frameEnd = _entries[_currentEntry]._frameStart = std::chrono::system_clock::now();
        }

        void Begin(Stage stage)
        {
            assert(_currentLevel < 255);
            auto& entry = _entries[_currentEntry]._stages[stage];
            entry._level = _currentLevel;
            _currentLevel++;
            entry._start = std::chrono::system_clock::now();
            entry._finalized = false;
        }

        void End(Stage stage)
        {
            assert(_currentLevel > 0);
            auto& entry = _entries[_currentEntry]._stages[stage];
            assert(!entry._finalized);
            _currentLevel--;
            assert(entry._level == _currentLevel);
            entry._end = std::chrono::system_clock::now();
            entry._finalized = true;
        }

        unsigned char GetCurrentEntryIndex() const
        {
            return (_currentEntry + _bufferSize - 1) % _bufferSize;
        }

        static const unsigned char _bufferSize = 100;
        std::array<Entry, _bufferSize> _entries;

    private:
        unsigned char _currentEntry = _bufferSize - 1;
        unsigned char _currentLevel = 0;
    };

    /**
     * @brief Names of the fields in the Profiler stages
     * 
     */
    static const std::array<const char*, Profiler::_StageCount> stageNames = {
        "Input",
        "Update",
        "Plot",
        "New Frame",
        "Debug Window",
        "Profiler Window",
        "ImGui::Render",
        "SFML",
        "SwapWindow",
        "Rendering"
    };

    static void ProfilerValueGetter(float* startTimestamp, float* endTimestamp, unsigned char* level, const char** caption, const void* data, int idx)
    {
        auto entry = reinterpret_cast<const Profiler::Entry*>(data);
        auto& stage = entry->_stages[idx];

        if (startTimestamp)
        {
            std::chrono::duration<float, std::milli> fltStart = stage._start - entry->_frameStart;
            *startTimestamp = fltStart.count();
        }

        if (endTimestamp)
        {
            *endTimestamp = stage._end.time_since_epoch().count() / 1000000.0f;

            std::chrono::duration<float, std::milli> fltEnd = stage._end - entry->_frameStart;
            *endTimestamp = fltEnd.count();
        }

        if (level)
            *level = stage._level;

        if (caption)
            *caption = stageNames[idx];
    }
}

#endif