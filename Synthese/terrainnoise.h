#ifndef TERRAINNOISE_H
#define TERRAINNOISE_H
#include "terrain.h"

/**
 * @brief The TerrainNoise class, a Terrain using one noise
 */
class TerrainNoise: public Terrain
{
private:
    double altitudeMinimun; /**< The minimal height of the TerrainNoise */
    double amplitude; /**< The maximal additive height the noise can add */
    double invfrequence; /**< The periodicity of height changes*/
public:
    /**
     * Constructor of TerrainNoise
     * @param[in] am the minimal height of the TerrainNoise
     * @param[in] ampl the maximal additive height the noise can add
     * @param[in] freq the frequence of height changes, will be passed as 1/freq to invfrequence
     * @param[in] aa the first point of definition of the Terrain on the plane
     * @param[in] bb the second point of definition of the Terrain on the plane
     */
    TerrainNoise(double am, double ampl, double freq, const Vector2D &aa, const Vector2D &bb);

    /**
     * @brief Gets the height associated to 2D coordinates
     * @param[in] p the coordinates to find the corresponding height
     * @return the height at p
     */
    virtual double getHauteur(const Vector2D& p) const;

    /**
     * Finds the minimal height of the Terrain
     * @return the minimal height of the Terrain
     */
    virtual double getHauteurMin() const;

    /**
     * Finds the maximal height of the Terrain
     * @return the maximal height of the Terrain
     */
    virtual double getHauteurMax() const;

    /**
     * Finds the greatest difference of height between two points
     * @return the greatest difference of height between two points
     */
    virtual double getPenteMax() const;
};

    inline double TerrainNoise::getHauteurMin() const{
        return altitudeMinimun;
    }

    inline double TerrainNoise::getHauteurMax() const{
        return altitudeMinimun+amplitude;
    }

#endif // TERRAINNOISE_H
