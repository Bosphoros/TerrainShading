#ifndef TERRAINTEST_H
#define TERRAINTEST_H
#include "terrain.h"
#include "vector2d.h"
#include <cmath>
#include "smoothnoise.h"
#include "mathutils.h"

/**
 * @brief The TerrainTest class, test class
 */
class TerrainTest:public Terrain
{
public:
    TerrainTest(Vector2D& a, Vector2D& b);
    virtual double getHauteur(const Vector2D &p) const;
    virtual double getHauteurMin() const;
    virtual double getHauteurMax() const;
    virtual double getPenteMax() const;
};

inline TerrainTest::TerrainTest(Vector2D &a, Vector2D &b):Terrain(a,b)
{

}

Vector2D warp(const Vector2D& p, double freq, double ampl, double mod1, double mod2){
    return p+Vector2D(-ampl/2+ampl*raw_noise_2d(p.x()*(1/freq)+mod1, p.y()*(1/freq)),-ampl/2+ampl*raw_noise_2d(p.x()*(1/freq)+0.162, p.y()*(1/freq)+mod2));
}

inline double TerrainTest::getHauteur(const Vector2D &p) const
{
    //return 255/2*(sin(p.x()/100)+1);
    double h = 0;
    Vector2D pwarp=warp(p,80,10,0.1654,0.894);
    /*Vector2D pwarp2=p+Vector2D(-10+20*raw_noise_2d(p.x()*(1/600.0), p.y()*(1/600.0)),-10+20*raw_noise_2d(p.x()*(1/600.0)+0.162, p.y()*(1/600.0)));
    Vector2D pwarp3=p+Vector2D(-10+20*raw_noise_2d(p.x()*(1/600.0), p.y()*(1/600.0)),-10+20*raw_noise_2d(p.x()*(1/600.0)+0.162, p.y()*(1/600.0)));
    Vector2D pwarp4=p+Vector2D(-10+20*raw_noise_2d(p.x()*(1/600.0), p.y()*(1/600.0)),-10+20*raw_noise_2d(p.x()*(1/600.0)+0.162, p.y()*(1/600.0)));
    Vector2D pwarp5=p+Vector2D(-10+20*raw_noise_2d(p.x()*(1/600.0), p.y()*(1/600.0)),-10+20*raw_noise_2d(p.x()*(1/600.0)+0.162, p.y()*(1/600.0)));
    Vector2D pwarp6=p+Vector2D(-10+20*raw_noise_2d(p.x()*(1/600.0), p.y()*(1/600.0)),-10+20*raw_noise_2d(p.x()*(1/600.0)+0.162, p.y()*(1/600.0)));//*/

    double th = 150*raw_noise_2d(pwarp.x()*(1/600.0), pwarp.y()*(1/600.0));
    th=MathUtils::ridge(th, 90+10*raw_noise_2d(pwarp.x()*(1/200.0), pwarp.y()*(1/200.0)));
    h+=th;
    th=((-15)+30*raw_noise_2d(pwarp.x()*(1/160.0)+0.335, pwarp.y()*(1/160.0)))*MathUtils::fonctionQuadratique(50, 100, h);
    th=MathUtils::ridge(th, 8+2*raw_noise_2d(pwarp.x()*(1/50.0), pwarp.y()*(1/50.0)));
    h += th;
    th=3*raw_noise_2d(pwarp.x()*(1/20.0)+0.754, pwarp.y()*(1/20.0))*MathUtils::fonctionQuadratique(80, 90, h);
    //th=MathUtils::ridge(th, 2+0.5*raw_noise_2d(p.x()*(1/8.0), p.y()*(1/8.0)));
    h += th;

    th=1*raw_noise_2d(pwarp.x()*(1/40.0)+1.914, pwarp.y()*(1/40.0))*MathUtils::fonctionQuadratiqueInv(150, 80, h);
    //th=1*raw_noise_2d(pwarp.x()*(1/10.0)+1.914, pwarp.y()*(1/10.0))*MathUtils::fonctionQuadratiqueInv(0, 150, h);
    h += th;
    return h;
}

inline double TerrainTest::getHauteurMin() const
{
    return 0;
}

inline double TerrainTest::getHauteurMax() const
{
    return 510;
}

inline double TerrainTest::getPenteMax() const
{
    return 510.0/600.0*2.0;
}


#endif // TERRAINTEST_H
