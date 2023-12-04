#include "pch.h"
#include "Util/Timer.h"

Timer::Timer() { }
Timer::~Timer() { }

void Timer::SetTimeScale(float timeScale) {
    m_timeScale = timeScale;
}

float Timer::GetDeltaTime() const {
    return m_deltaTime;
}

float Timer::GetTimeScale() const {
    return m_timeScale;
}

float Timer::GetTimeElapsed() const {
    return m_timeElapsed;
}

float Timer::GetDeltaTimeMS() const {
    return m_deltaTime / 1000.f;
}

float Timer::GetFrame() const {
    return m_fps;
}

void Timer::Init() {
    QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&m_tick));
    QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&m_prev));
}

void Timer::Update() {
    // ���� �������� �ð� ���
    uint64 currentFrameTime;
    QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentFrameTime));

    // ���� �����Ӱ� ���� ������ ������ �ð� ���� ���
    m_deltaTime = (currentFrameTime - m_prev) / static_cast<float>(m_tick);

    // ������� �帥 �ð� ���
    m_timeElapsed += m_deltaTime;

    // ������ ���
    m_frameCount++;
    // �帥 �ð��� 1�ʺ��� ũ�ٸ�
    if (m_timeElapsed >= 1.0f) {
        // ������ �� ����� �ٽ� �帥 �ð� �ʱ�ȭ
        m_fps = (float)m_frameCount / m_timeElapsed;
        m_frameCount = 0;
        m_timeElapsed = 0.0f;
        std::cout << m_fps << std::endl;
    }

    // ���� �ð��� ����ð����� ����
    m_prev = currentFrameTime;
}