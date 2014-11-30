/*Spline Class*/

#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <math.h>
#include <vector>
#include "spline_library.h"

class Spline{
	public:
		Spline(std::vector<double> xPoints, std::vector<double> yPoints, double initCurvature); //Constructor
		double computeSplineValue(double evalPoint); 
		double getCurvature(double evalPoint);
	private:
		tk::spline mySpline;
};