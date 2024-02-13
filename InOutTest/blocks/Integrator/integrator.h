#ifndef INTEGRATOR_H
#define INTEGRATOR_H


class Integrator {
public:
    Integrator(float initValue);

    float update(float input, float dt);
    float state() const;

private:
    float m_state;
    float m_prevInput;
    float rungeKuttaStep(float input, float dt);
};

#endif // INTEGRATOR_H
