#include "Spline.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "spline_library.h"
using namespace std;

Spline::Spline(std::vector<double> xPoints, std::vector<double> yPoints, double initCurvature){
    /*Spline library usage example:     
    std::vector<double> X(5), Y(5);
    X[0]=0.1; X[1]=0.4; X[2]=1.2; X[3]=1.8; X[4]=2.0;
    Y[0]=0.1; Y[1]=0.7; Y[2]=0.6; Y[3]=1.1; Y[4]=0.9;
    tk::spline s;
    s.set_points(X,Y);    // currently it is required that X is already sorted
    double x=1.5;
    printf("spline at %f is %f\n", x, s(x));
    */
    mySpline = tk::spline();
    mySpline.set_points(xPoints, yPoints, initCurvature);

}

//Returns the value of the spline and the curvature as a vector [value, curvature]
std::vector<double> Spline::getValues(double evalPoint){
    return mySpline(evalPoint);
}
