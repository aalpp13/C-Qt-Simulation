#include "integrator.h"
Integrator::Integrator(float initValue) : m_state(initValue), m_prevInput(0.0) {}

float Integrator::update(float input, float dt) {
    m_state += rungeKuttaStep(input, dt);
    m_prevInput = input;
    return m_state;
}

float Integrator::state() const {
    return m_state;
}

float Integrator::rungeKuttaStep(float input, float dt) {
    float k1 = dt * m_prevInput;
    float k2 = dt * (m_prevInput + k1 / 2.0);
    float k3 = dt * (m_prevInput + k2 / 2.0);
    float k4 = dt * (m_prevInput + k3);

    return (k1 + 2.0 * k2 + 2.0 * k3 + k4) / 6.0;
}
