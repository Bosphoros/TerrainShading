#include "terrainnoisesmultiples.h"
#include "smoothnoise.h"
#include "mathutils.h"

TerrainNoisesMultiples::TerrainNoisesMultiples(double am,const std::vector<double>& lFreqs,const std::vector<double>& lAmpl, const Vector2D &aa, const Vector2D &bb): Terrain(aa,bb), altitudeMinimum(am), amplitudes(lAmpl), frequences(lFreqs)
{
    for(int i = 0; i < frequences.size(); ++i) {
        frequences[i]= 1 / frequences[i];
    }
}

double TerrainNoisesMultiples::getHauteur(const Vector2D& p) const {
    int nbFreq = frequences.size();
    int nbAmpl = amplitudes.size();

    double h = altitudeMinimum;
    int i = 0;
    for(i; i < nbFreq && i < nbAmpl; ++i) {
        h += amplitudes[i]*raw_noise_2d(p.x()*frequences[i], p.y()*frequences[i]);
    }

    return h;

}
double TerrainNoisesMultiples::getHauteurMax() const {
    int hMax = altitudeMinimum;
    int nbAmpl = amplitudes.size();
    for(int i = 0; i < nbAmpl; ++i) {
        hMax += amplitudes[i];
    }
    return hMax;
}
double TerrainNoisesMultiples::getPenteMax() const {
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
