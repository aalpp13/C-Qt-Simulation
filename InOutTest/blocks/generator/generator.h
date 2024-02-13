#ifndef GENERATOR_H
#define GENERATOR_H

#include "blocks/Integrator/integrator.h"

class generator
{
public:
    generator(float init1, float init2);
    ~generator();


    float update(float dt);

private:
    Integrator* m_integrator1 = nullptr;
    Integrator* m_integrator2 = nullptr;
};

#endif // GENERATOR_H
