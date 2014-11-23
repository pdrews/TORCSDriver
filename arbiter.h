#ifndef __ARBITER_H__
#define __ARBITER_H__
#include <iostream>
#include <map>
#include <math.h>
#include <vector>  
class Arbiter
{
public:
	Arbiter(int nb_segments, int nb_intervals_per_segment):m_nb_segments(nb_segments),m_nb_intervals_per_segment(nb_intervals_per_segment){};
	void  Arbiter::Arbiter(int nb_segments, int nb_intervals_per_segment, 
		Controller* controller, Policy* policy, Wrapper* wrapper);
	void drive();
	void setController(Controller* controller);
	void setWrapper(Wrapper* w);
	void setPolicy(Policy* policy);
private:
	Controller* m_controller;
	Policy* m_policy;
	Wrapper* m_wrapper;
	float m_track_length;
	int m_nb_segments;
	float m_segment_length;
	float m_interval_length;
	int m_nb_intervals_per_segment;
	map<float, WorldState> m_positions;
	map<float,vector<float> > m_positions_x;
	void collectIntervalPositions();
}
#endif
