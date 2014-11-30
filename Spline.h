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
		std::vector<double> getValues(double evalPoint); //Returns the value of the spline and the curvature as a vector [value, curvature]
	private:
		tk::spline mySpline;
};