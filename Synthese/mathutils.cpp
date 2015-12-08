#include "mathutils.h"
#include <cmath>
#include <iostream>

MathUtils::MathUtils()
{
}

double MathUtils::fonctionQuadratique(double min, double max, double x) {

    return x<min?0:x>=max?1:1-pow((1-pow((x-min)/(max-min),2)),2);
}

double MathUtils::fonctionQuadratiqueInv(double min, double max, double x) {

    return 1-fonctionQuadratique(max,min,x);
}

double MathUtils::interpolate(double before_p0, double p0, double p1, double after_p1, double t)
{
    //Calcul des coefficients de notre polynôme
    double a3 = -0.5*before_p0 + 1.5*p0 - 1.5*p1 + 0.5*after_p1;
    double a2 = before_p0 - 2.5*p0 + 2*p1 - 0.5*after_p1;
    double a1 = -0.5*before_p0 + 0.5*p1;
    double a0 = p0;

    //Calcul de la valeur de ce polynôme en t
    return (a3 * t*t*t) + (a2 * t*t) + (a1 * t) + a0;
}

double MathUtils::ridge(double n, double s) {
    //std::cout<<s<<std::endl;
    return n>s?2*s-n:n;
}

double MathUtils::mod(double a, double b) {
    while(a>b) {a-=b;}
    return a;
}

double MathUtils::dabs(double d) {
    return d>=0?d:-d;
}

double MathUtils::clamp(double min, double max, double val)
{
    return val<min?min:val>max?max:val;
}

double MathUtils::random(double min, double max)
{
    double f = (double)rand() / RAND_MAX;
    return min + f * (max - min);
}
