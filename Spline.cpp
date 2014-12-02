#include "Spline.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "spline_library.h"
#include "singleton.h"
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
    unfilteredX = xPoints;
    filteredX = xPoints;
    trackLength = singleton::getInstance().wrap.m_trackLength;

    for (int i = 1; i < unfilteredX.size(); i++){
      if (unfilteredX[i] < unfilteredX[0]){
        filteredX[i] = trackLength + unfilteredX[i];
      }
    }
    mySpline.set_points(filteredX, yPoints, initCurvature);

}

Spline::Spline()
{}

//Returns the value of the spline and the curvature as a vector [value, curvature]
double Spline::computeSplineValue(double evalPoint){
  trackLength = singleton::getInstance().wrap.m_trackLength;
  if (evalPoint < unfilteredX[0]){
        evalPoint = trackLength + evalPoint;
  }
  return mySpline(evalPoint)[0];
}
double Spline::getCurvature(double evalPoint){
  if (evalPoint < unfilteredX[0]){
        evalPoint = trackLength + evalPoint;
  }  
  return mySpline(evalPoint)[1];
}
