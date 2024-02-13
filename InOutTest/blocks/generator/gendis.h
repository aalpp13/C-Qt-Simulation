#ifndef GENDIS_H
#define GENDIS_H
#include <math.h>

class gendis
{
public:
    gendis(float freg);
    float update();
    float getValue() const;

private:
    //float X1 = sin(0.25);
    float X1 = 0.25 * cos(0.25);
    //float X2 = 0.25 * cos(0.25);
    float X2 = sin(0.25);

    float a11=0.0;
    float a12 =0.0;
    float a21 =0.0;
    float a22 =0.0;
    float b11 =0.0;
    float b21 =0.0;

    float u1 = 0.0;
    float u2 = 0.0;
};

#endif // GENDIS_H
