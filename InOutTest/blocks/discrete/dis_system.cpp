#include "dis_system.h"

dis_system::dis_system(float freq)
{
    if (freq == 5) {
        a11 = 0.620297146860522;
        a12 = -0.276819001943988;
        a13 = -0.322690910033844;
        a21 = 0.322690910033844;
        a22 = 0.942988056894366;
        a23 = -0.069601638837209;
        a31 = 0.034800819418605;
        a32 = 0.196146274435527;
        a33 = 0.995189286022273;

        b1 = 0.161345455016922;
        b2 = 0.034800819418605;
        b3 = 0.002405356988864;
    }
    else if (freq == 25) {
        a11 = 0.920800521460496;
        a12 = -0.059173553003816;
        a13 = -0.076821341708222;
        a21 = 0.076821341708222;
        a22 = 0.997621863168718;
        a23 = -0.003115093445299;
        a31 = 0.001557546722650;
        a32 = 0.039968217576760;
        a33 = 0.999958183252692;

        b1 = 0.038410670854111;
        b2 = 0.001557546722650;
        b3 = 2.090837365388035e-05;
    }
    else if (freq == 100) {
        a11 = 0.980050002071685;
        a12 = -0.014949584172901;
        a13 = -0.019800333341628;
        a21 = 0.019800333341628;
        a22 = 0.999850335413313;
        a23 = -0.000198668333610001;
        a31 = 0.00009933416668050007;
        a32 = 0.009999500837494;
        a33 = 0.999999336663333;

        b1 = 0.009900166670814;
        b2 = 0.00009933416668050007;
        b3 = 3.316683333531054e-07;
    }

    }
float dis_system::update(float signal)
{
    float tmX1 = X1;
    float tmX2 = X2;
    float tmX3 = X3;

    X1 = a11*tmX1+a12*tmX2+a13*tmX3+b1*signal;
    X2 = a21*tmX1+a22*tmX2+a23*tmX3+b2*signal;
    X3 = a31*tmX1+a32*tmX2+a33*tmX3+b3*signal;

    return (c1*X1+c2*X2+c3*X3);
}
float dis_system::getValue()
{
    return c1*X1+c2*X2+c3*X3;
}
