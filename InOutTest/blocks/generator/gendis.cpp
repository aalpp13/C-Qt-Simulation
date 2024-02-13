#include "gendis.h"
#include "math.h"

gendis::gendis(float freq)
{
    //freq = 5, interval = 200ms
    if(freq==5.0){
        a11 = 0.998750260394966;
        a12 = 0.199916677082713;
        a21 = -0.012494792317670;
        a22 = 0.998750260394966;

        b11 = 0.019995833680539;
        b21 = 0.199916677082713;
    }


    //freq = 25, interval = 40ms
    else if(freq==25){
        a11 = 0.999950000416665;
        a12 = 0.039999333336667;
        a21 = -0.002499958333542;
        a22 = 0.999950000416665;

        b11 = 7.999933333557863e-04;
        b21 = 0.039999333336667;
    }


    //freq = 100, interval = 10ms
    else if(freq==100){
        a11 = 0.999996875001628;
        a12 = 0.009999989583337;
        a21 = -6.249993489585368e-04;  // Note the exponent notation for clarity
        a22 = 0.999996875001628;

        b11 = 4.999997395849221e-05;   // Again, using exponent notation
        b21 = 0.009999989583337;
    }

}


float gendis :: update(){
    float tmpX1 = X1;
    float tmpX2 = X2;

    X1 = a11*tmpX1 + a12*tmpX2 + b11*u1;
    X2 = a21*tmpX1 + a22*tmpX2 +b21*u2;

      return X1 + 0.55;
  }

  float gendis::getValue() const
  {

      return X1 + 0.55;
  }
