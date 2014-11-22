#include "Spline.h"
#include <iostream>
//#include "EigenLibrary/Eigen/Dense"
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "spline_library.h"
using namespace std;
//using Eigen::MatrixXd;

Spline::Spline(std::vector<double> xPoints, std::vector<double> yPoints){
	cout << "Spline made brah \n";
	/*Matrix multiplication example
	MatrixXd m1(2,2);
 	m1(0,0) = 1;
  	m1(1,0) = 2;
  	m1(0,1) = 3;
  	m1(1,1) = 4;
  	MatrixXd m2(2,1);
  	m2(0,0) = 2;
  	m2(1,0) = 2;
  	MatrixXd m3(2,1);
  	m3 = m1*m2;
  	cout << m3 << endl;
  	*/

  	/*Spline usage example:  	
  	std::vector<double> X(5), Y(5);
    X[0]=0.1; X[1]=0.4; X[2]=1.2; X[3]=1.8; X[4]=2.0;
    Y[0]=0.1; Y[1]=0.7; Y[2]=0.6; Y[3]=1.1; Y[4]=0.9;
    tk::spline s;
    s.set_points(X,Y);    // currently it is required that X is already sorted
    double x=1.5;
    printf("spline at %f is %f\n", x, s(x));
	*/

    //tk::spline mySpline;
    mySpline.set_points(xPoints, yPoints);

}

double Spline::getTangentAngle(double evalPoint){
	return 0;
}

double Spline::getCurvature(double evalPoint){
	return 0;
}

double Spline::computeSplineValue(double evalPoint){
	return mySpline(evalPoint);
}