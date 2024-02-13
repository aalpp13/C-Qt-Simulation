#include "continuous.h"

continuous::continuous(float init3, float init4, float init5)
{
    m_continuous1 = new Integrator(init3);
    m_continuous2 = new Integrator(init4);
    m_continuous3 = new Integrator(init5);
}

float continuous :: update(float input, float dt)
{

    float tmpX1 = m_continuous1 -> state();
    float tmpX2 = m_continuous2 -> state();
    float tmpX3 = m_continuous3 ->state();

    //x1' = x2
    //x2' = x3
    //x3' = -4x1 - 3x2 - 2x3 +u
    //y=x1+x2+x3

    m_continuous1 -> update(tmpX2,dt);
    m_continuous2 -> update(tmpX3,dt);
    m_continuous3 -> update(tmpX1*(-4)+ tmpX2*(-3)+tmpX3*(-2) +input, dt);

    return (tmpX2+tmpX3);
}
