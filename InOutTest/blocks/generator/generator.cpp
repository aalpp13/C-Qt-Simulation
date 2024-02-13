#include "generator.h"

generator::generator(float init1, float init2)
{
    m_integrator1= new Integrator(init1);
    m_integrator2= new Integrator(init2);
}

generator::~generator()
{
    delete m_integrator1;
    delete m_integrator2;
}

float generator ::  update (float dt)
{
    float tmpX1 = m_integrator1 -> state();
    float tmpX2 = m_integrator2 -> state();

    // gain "-1"
    m_integrator1 ->update(tmpX2*(-1), dt);
    m_integrator2 ->update (tmpX1, dt);

    return tmpX2;
}
