#include "Time.hpp"

namespace zui {

std::unique_ptr<Clock> GClock::s_instance = nullptr;

Clock::Clock()
    : m_startTime(HighResClock::now()), m_deltaTime(0.0f), m_rawDeltaTime(0.0f), m_totalTime(0.0f), m_timeScale(1.0f),
      m_isPaused(false), m_frameCount(0), m_fpsUpdateInterval(1.0f), m_fpsAccumulator(0.0f), m_fps(0.0f),
      m_useFixedTimestep(false), m_fixedTimestep(1.0f / 60.0f), m_fixedTimeAccumulator(0.0f) {
    m_currentTime = m_startTime;
    m_lastTime = m_startTime;
}

float Clock::Tick() {
    if (m_isPaused) {
        m_deltaTime = 0.0f;
        m_rawDeltaTime = 0.0f;
        return 0.0f;
    }

    m_lastTime = m_currentTime;
    m_currentTime = HighResClock::now();

    Duration dt = m_currentTime - m_lastTime;
    m_rawDeltaTime = dt.count();
    m_deltaTime = m_rawDeltaTime * m_timeScale;
    m_totalTime += m_deltaTime;

    m_frameCount++;
    m_fpsAccumulator += m_deltaTime;
    if (m_fpsAccumulator >= m_fpsUpdateInterval) {
        m_fps = static_cast<float>(m_frameCount) / m_fpsAccumulator;
        m_fpsAccumulator = 0.0f;
        m_frameCount = 0;
    }

    return m_deltaTime;
}

void Clock::Pause() {
    m_isPaused = true;
}
void Clock::Resume() {
    m_isPaused = false;
}
void Clock::TogglePause() {
    m_isPaused = !m_isPaused;
}
bool Clock::IsPaused() const {
    return m_isPaused;
}

float Clock::GetFps() const {
    return m_fps;
}
float Clock::GetDeltaTime() const {
    return m_deltaTime;
}
double Clock::GetElapsedTime() const {
    return m_totalTime;
};

float Clock::GetTimeScale() const {
    return m_timeScale;
}
void Clock::SetTimeScale(float timeScale) {
    m_timeScale = (timeScale > 0.0f) ? timeScale : 0.0f;
}

void Clock::Reset() {
    m_startTime = HighResClock::now();
    m_currentTime = m_startTime;
    m_lastTime = m_startTime;
    m_deltaTime = 0.0f;
    m_totalTime = 0.0f;
    m_frameCount = 0;
    m_fpsAccumulator = 0.0f;
    m_fps = 0.0f;
    m_fixedTimeAccumulator = 0.0f;
}

void Clock::SetFpsUpdateInterval(float interval) {
    m_fpsUpdateInterval = (interval > 0.0f) ? interval : 1.0f;
}

void Profiler::Begin(const std::string& label) {
    m_beginTimePoint.insert_or_assign(label, HighResClock::now());
}

void Profiler::End(const std::string& label) {
    m_endTimePoint.insert_or_assign(label, HighResClock::now());
}

float Profiler::GetDuration(const std::string& label) {
    std::unordered_map<std::string, TimePoint>::iterator it = m_beginTimePoint.find(label);
    if (it == m_beginTimePoint.end()) {
        return 0.0f;
    }
    TimePoint& beginTimePoint = it->second;

    it = m_endTimePoint.find(label);
    if (it == m_endTimePoint.end()) {
        return 0.0f;
    }

    TimePoint& endTimePoint = it->second;

    return Duration(endTimePoint - beginTimePoint).count();
}

} // namespace zui
