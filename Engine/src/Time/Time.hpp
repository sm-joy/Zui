#pragma once
#include "../Core/API.hpp"

#include <chrono>
#include <memory>
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
    static void Init();
    static void Shutdown();

    static inline float Tick() { return m_clock->Tick(); }

    static inline void Pause() { m_clock->Pause(); }

    static inline void Resume() { m_clock->Resume(); }

    static inline void TogglePause() { m_clock->TogglePause(); }

    static inline bool IsPaused() { return m_clock->IsPaused(); }

    static inline float GetFps() { return m_clock->GetFps(); }

    static inline float GetDeltaTime() { return m_clock->GetDeltaTime(); }

    static inline double GetElapsedTime() { return m_clock->GetElapsedTime(); }

    static inline float GetTimeScale() { return m_clock->GetTimeScale(); }

    static inline void SetTimeScale(float ts) { m_clock->SetTimeScale(ts); }

    static inline void Reset() { m_clock->Reset(); }

    static inline void SetFpsUpdateInterval(float interval) { m_clock->SetFpsUpdateInterval(interval); }

private:
    static std::unique_ptr<Clock> m_clock;
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

class ZUI_API GProfiler {
public:
    static void Init();

    static void Shutdown();

    static inline void Begin(const std::string& label) { m_profiler->Begin(label); }

    static inline void End(const std::string& label) { m_profiler->End(label); }

    static inline float GetDuration(const std::string& label) { return m_profiler->GetDuration(label); }

    static bool IsValid() { return m_profiler ? true : false; };

private:
    static std::unique_ptr<Profiler> m_profiler;
};

class ScopedProfile {
public:
    ScopedProfile(const std::string& label);
    ~ScopedProfile();

private:
    std::string m_label;
};

#define SCOPED_PROFILE(label) ScopedProfile profile(label)

} // namespace zui
