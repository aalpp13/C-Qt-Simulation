#ifndef CONTINUOUS_H
#define CONTINUOUS_H

#include "blocks/Integrator/integrator.h"

class continuous
{
public:
    continuous(float init3, float init4, float init5);

    float update (float input, float dt);

private:

    Integrator* m_continuous1 = nullptr;
    Integrator* m_continuous2 = nullptr;
    Integrator* m_continuous3 = nullptr;
};

#endif // CONTINUOUS_H
