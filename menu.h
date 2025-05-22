#pragma once

// Handles game pause and running state
class Menu {
public:
    // Getters and setters
    bool GetPaused() const { return isPaused; }
    void TogglePause() { isPaused = !isPaused; }
    bool GetRunning() const { return running; }
    void SetRunning(bool run) { running = run; }
private:
    // Pause and running states
    bool isPaused = false;
    bool running = true;
};
