#ifndef __ARBITER_H__
#define __ARBITER_H__
#include <iostream>
#include <map>
#include <math.h>
#include <vector>  
#include <utility>
#include "DataStructures.h"
#include "wrap.h"
#include "Spline.h"
#include "policy.h"
#include "controller.h"
using namespace std;

class Arbiter
{
public:
	Arbiter(double segment_length, int nb_intervals_per_segment);
	//Arbiter(double segment_length, int nb_intervals_per_segment, 
	//	Driver* controller, ZeroPolicy* policy, wrapper* wrapper);
	void drive();
	void setController(Driver* controller);
	void setWrapper(wrapper* w);
	void setPolicy(ZeroPolicy* policy);
	void setTrack(tTrack* track);
	void newRace(tCarElt* car, tSituation *s);
private:
	Driver* m_controller;
	ZeroPolicy* m_policy;
	wrapper* m_wrapper;
	float m_track_length;
	Spline * m_prev_spline;
	int m_nb_segments;
	float m_segment_length;
	float m_interval_length;
	int m_nb_intervals_per_segment;
    float m_segment_start_time;
	map<int, vector<double> > m_curvatures;
	map<int,vector<double> > m_positions_x;
	void collectIntervalPositions(int, double, double);
	pair<vector<double>, vector<double> > getSubCurvatures(int, float);
};
#endif
