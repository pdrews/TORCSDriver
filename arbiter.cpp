#include "arbiter.h"

Arbiter::Arbiter(int nb_segments, int nb_intervals_per_segment, Controller* controller, Policy* policy, Wrapper* wrapper)
{
	Arbiter(nb_segments, nb_intervals_per_segment);
	this->setController(controller);
	this->setPolicy(policy);
	this->setWrapper(wrapper);
}
void Arbiter::drive()
{
	float length_from_start = m_wrapper->getDistanceFromStart();
	tCarElt car_state = m_wrapper->getCarState();
	//get the segment id which we are on
	int segment_position_idx = (int)floor(length_from_start/m_segment_length);
	//get position in meters of the start of segment we are on
	float segment_position_met = fmod(segment_position_idx * m_segment_length, m_track_length);
	//if we do not have splitted the two consecutives segments into intervals, do it	
	if (m_positions.count(segment_position_met) <= 0) 
	{
		float end_two_segments_met = fmod(segment_position_met + 2*m_segment_length,m_track_length);
		this->collectIntervalPositions(segment_position_met,end_two_segments_met);
	}
	//feed the positions in the policy to collect data points
	vector<double> data_points_y;
	data_points_y = m_policy->search(m_positions[segment_position_met]);
	Spline* spline = new Spline(m_positions_x[segment_position_met], data_points_y);
	m_controller->getCarControls(spline, car_state);
}
void Arbiter::setController(Controller* controller) {m_controller = controller;}
void Arbiter::setPolicy(Policy* policy) {m_policy = policy;}
void Arbiter::setWrapper(Wrapper* w)
{
	m_wrapper = w;
	m_track_length = m_wrapper->getTrackLength();
	m_segment_length = m_track_length/m_nb_segments;
	m_interval_length = m_segment_length/m_nb_intervals_per_segment;
}
void Arbiter::collectIntervalPositions(float beg_measure, float end_measure)
{
	m_positions_x[beg_measure].clear();
	for (float i_meas= beg_measure; i_meas < end_measure; i_meas = i_meas+ m_interval_length)
	{
		WorldState world_state_i = m_wrapper->getWorldState(i_meas);
		m_positions_x[beg_measure].push_back(world_state_i.position_x);
		m_positions[beg_measure]=world_state_i;
	}
}
