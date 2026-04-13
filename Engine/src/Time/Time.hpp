#pragma once
#include "../Core/API.hpp"

#include <chrono>
#include <string>
#include <unordered_map>

namespace zui {

using HighResClock = std::chrono::high_resolution_clock;
using TimePoint = std::chrono::time_point<HighResClock>;
using Duration = std::chrono::duration<float>;

class ZUI_API Clock {
public:
    Clock();
    ~Clock() = default;

    float Tick();

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


class ZUI_API GClock {
public:
    static inline void Init() {
        s_instance = std::make_unique<Clock>();
    }

    static inline void Shutdown() {
        s_instance.reset();
    }

    static inline float Tick() {
        return s_instance->Tick();
    }

    static inline float GetDeltaTime() {
        return s_instance->GetDeltaTime();
    }


    static inline double GetElapsedTime() {
        return s_instance->GetElapsedTime();
    }

    static inline float GetFps() {
        return s_instance->GetFps();
    }

    static inline void Pause() {
        s_instance->Pause();
    }

    static inline void Resume() {
        s_instance->Resume();
    }

    static inline void TogglePause() {
        s_instance->TogglePause();
    }

    static inline bool IsPaused() {
        return s_instance->IsPaused();
    }

    static inline float GetTimeScale() {
        return s_instance->GetTimeScale();
    }

    static inline void SetTimeScale(float scale) {
        s_instance->SetTimeScale(scale);
    }

    static inline void Reset() {
        s_instance->Reset();
    }

    static inline void SetFpsUpdateInterval(float interval) {
        s_instance->SetFpsUpdateInterval(interval);
    }

    static Clock& Get() {
        return *s_instance;
    }

private:
    static std::unique_ptr<Clock> s_instance;
};



class Profiler {
public:
    Profiler() = default;
    ~Profiler() = default;

    void Begin(const std::string& label);
    void End(const std::string& label);

    float GetDuration(const std::string& label);

private:
    std::unordered_map<std::string, TimePoint> m_beginTimePoint;
    std::unordered_map<std::string, TimePoint> m_endTimePoint;
};

} // namespace zui
