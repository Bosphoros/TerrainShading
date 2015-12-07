#ifndef TERRAINNOISESMULTIPLES_H
#define TERRAINNOISESMULTIPLES_H
#include "terrain.h"
#include <vector>

/**
 * @brief The TerrainNoisesMultiples class, using series of additionnal heights and frequences
 */
class TerrainNoisesMultiples : public Terrain
{
private:
    double altitudeMinimum; /**< The minimal height of the TerrainNoisesMultiples */
    std::vector<double> amplitudes; /**< Vector of additionnal heights to apply */
    std::vector<double> frequences; /**< Vector of frequecies to apply */
public:
    /**
     * Constructor of TerrainNoisesMultiples
     * @param[in] am the minimal height of the TerrainNoisesMultiples
     * @param[in] lFreqs vector of frequencies to apply, will be passed to 1/lFreqs[i]
     * @param[in] lAmpl vector of heights to add
     * @param[in] aa the first point of definition of the Terrain on the plane
     * @param[in] bb the second point of definition of the Terrain on the plane
     */
    TerrainNoisesMultiples(double am,const std::vector<double>& lFreqs,const std::vector<double>& lAmpl, const Vector2D &aa, const Vector2D &bb);

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

inline double TerrainNoisesMultiples::getHauteurMin() const {
    return altitudeMinimum;
}

#endif // TERRAINNOISESMULTIPLES_H
