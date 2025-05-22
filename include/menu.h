#pragma once

namespace OOP_Game {
    // Handles game pause and running state
    class Menu {
    public:
        // Getters and setters
        bool GetPaused() const { return m_is_paused; }
        void TogglePause() { m_is_paused = !m_is_paused; }
        bool GetRunning() const { return m_running; }
        void SetRunning(bool run) { m_running = run; }
    private:
        // Pause and running states
        bool m_is_paused = false;
        bool m_running = true;
    };
}
