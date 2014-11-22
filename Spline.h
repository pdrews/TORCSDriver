/*Spline Class*/

#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <math.h>
#include <vector>
#include "spline_library.h"

class Spline{
	public:
		Spline(std::vector<double> xPoints, std::vector<double> yPoints); //Constructor
		double getTangentAngle(double evalPoint);
		double getCurvature(double evalPoint);
		double computeSplineValue(double evalPoint);
	private:
		tk::spline mySpline;
};