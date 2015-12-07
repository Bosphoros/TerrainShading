#ifndef MATHUTILS_H
#define MATHUTILS_H

/**
 * @brief The MathUtils class
 * This class concentrates functions not present in cmath
 */
class MathUtils
{
public:
    MathUtils();
    /**
     * Finds the value corresponding to x scaled between min and max with a smoothed scale
     * @param[in] min the minimal value of the new scale
     * @param[in] max the maximal value of the new scale
     * @param[in] x the value to process
     * @return the new value of x, between min and max
     */
    static double fonctionQuadratique(double min, double max, double x);

    /**
     * Find the value corresponding to x scaled between min and max, from max to min
     * @param[in] min the minimal value of the scale
     * @param[in] max the maximal value of the scale
     * @param[in] x the value to process
     * @see fonctionQuadratique()
     * @return the new value of x, between max and min
     */
    static double fonctionQuadratiqueInv(double min, double max, double x);

    /**
     * Cubic interpolation of a value, t, contained between p0 and p1
     * @param[in] before_p0 the value before p0
     * @param[in] p0 the value before t
     * @param[in] p1 the value after t
     * @param[in] after_p1 the value after p1
     * @param[in] t the place of the value to find, between p0 and p1
     * @return the cubic interpolation of t
     */
    static double interpolate(double before_p0, double p0, double p1, double after_p1, double t);

    /**
     * Reverses the value after a certain threshold
     * @param[in] n the value before the ridge
     * @param[in] s the threshold to apply
     * @return 2*s-n if n > s, n else
     */
    static double ridge(double n, double s);

    /**
     * Takes two doubles and returns the rest of a - X*b as long as a > X*b
     * @param[in] a the divided
     * @param[in] b the divisor
     * @return minimal positive value of a - X*b with a > X*b
     */
    static double mod(double a, double b);

    /**
     * The absolute value of a double
     * @param[in] d the double we want the absolute value
     * @return the absolute value of d
     */
    static double dabs(double d);
};

#endif // MATHUTILS_H
