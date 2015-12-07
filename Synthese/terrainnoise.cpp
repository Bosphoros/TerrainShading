#include "terrainnoise.h"
#include "smoothnoise.h"
#include "mathutils.h"

TerrainNoise::TerrainNoise(double am, double ampl, double freq, const Vector2D& aa, const Vector2D& bb):Terrain(aa,bb), altitudeMinimun(am), amplitude(ampl), invfrequence(1/freq)
{
}


double TerrainNoise::getHauteur(const Vector2D &p) const
{
    return altitudeMinimun+amplitude*raw_noise_2d(p.x()*invfrequence,p.y()*invfrequence);
}

double TerrainNoise::getPenteMax() const
{

    double max=0;
    for(int i=a.y();i<b.y()-1;i++){
        for(int j=a.x();j<=b.x()-1;j++){
            Vector2D v(j,i);
            Vector2D vi(j,i+1);
            Vector2D vj(j+1,i);
            double tmp=MathUtils::dabs(getHauteur(v)-getHauteur(vj));
            if(max<tmp){
                max=tmp;
            }
            tmp=MathUtils::dabs(getHauteur(v)-getHauteur(vi));
            if(max<tmp){
                max=tmp;
            }
        }
    }
    return max;
}
