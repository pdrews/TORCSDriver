#ifndef __ARBITER_H__
#define __ARBITER_H__
#include <iostream>
#include <map>
#include <math.h>
#include <vector>  
#include <utility>
#include "DataStructures.h"
#include "wrapper.hpp"
#include "Spline.h"
#include "policy.h"
#include "controller.h"
using namespace std;

class Arbiter
{
public:
	Arbiter(int nb_segments, int nb_intervals_per_segment):m_nb_segments(nb_segments),m_nb_intervals_per_segment(nb_intervals_per_segment){};
	Arbiter(int nb_segments, int nb_intervals_per_segment, 
		Driver* controller, ZeroPolicy* policy, Wrapper* wrapper);
	void drive();
	void setController(Driver* controller);
	void setWrapper(Wrapper* w);
	void setPolicy(ZeroPolicy* policy);
private:
	Driver* m_controller;
	ZeroPolicy* m_policy;
	Wrapper* m_wrapper;
	float m_track_length;
	int m_nb_segments;
	float m_segment_length;
	float m_interval_length;
	int m_nb_intervals_per_segment;
	map<int, vector<double> > m_curvatures;
	map<int,vector<double> > m_positions_x;
	void collectIntervalPositions(int, double, double);
	pair<vector<double>, vector<double> > getSubCurvatures(int, float);
};
#endif
