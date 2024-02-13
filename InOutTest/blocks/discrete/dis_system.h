#ifndef DIS_SYSTEM_H
#define DIS_SYSTEM_H


class dis_system
{
public:
    dis_system(float freq);
    float update(float signal);
    float getValue();

private:
    float X1=0;
    float X2=0;
    float X3=0;

    float a11 = 0;
    float a12 = 0;
    float a13 = 0;
    float a21 = 0;
    float a22 = 0;
    float a23 = 0;
    float a31 = 0;
    float a32 = 0;
    float a33 = 0;

    float b1=0;
    float b2=0;
    float b3=0;

    float c1 = 1;
    float c2 = 0.5;
    float c3 = 0;

};

#endif // DIS_SYSTEM_H
