#pragma once
#include <chrono>
#include <string>
#include <unordered_map>

namespace zui {

using HighResClock = std::chrono::high_resolution_clock;
using TimePoint    = std::chrono::time_point<HighResClock>;
using Duration     = std::chrono::duration<float>;

class Clock {
public:
    Clock();
    ~Clock() = default;

    void Tick();

    void Pause();
    void Resume();
    void TogglePause();
    bool IsPaused() const;

    float GetFps() const;
    float GetDeltaTime() const;
    double GetElapsedTime() const;

    float GetTimeScale() const;
    void SetTimeScale(float timeScale);

    void Reset();

    void SetFpsUpdateInterval(float interval);

private:
    TimePoint m_currentTime;
    TimePoint m_lastTime;
    TimePoint m_startTime;

    float m_deltaTime;
    float m_rawDeltaTime;
    double m_totalTime;
    float m_timeScale;

    unsigned int m_frameCount;
    float m_fpsUpdateInterval;
    float m_fpsAccumulator;
    float m_fps;

    double m_fixedTimestep;
    double m_fixedTimeAccumulator; // i will do it later

    bool m_isPaused;
    bool m_useFixedTimestep;
};

class Profiler {
public:
    Profiler()  = default;
    ~Profiler() = default;

    void Begin(const std::string &label);
    void End(const std::string &label);

    float GetDuration(const std::string &label);

private:
    std::unordered_map<std::string, TimePoint> m_beginTimePoint;
    std::unordered_map<std::string, TimePoint> m_endTimePoint;
};

} // namespace zui
