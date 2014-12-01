#include "arbiter.h"
#include "singleton.h"

Arbiter::Arbiter(double segment_length, int nb_intervals_per_segment):m_segment_length(segment_length),m_nb_intervals_per_segment(nb_intervals_per_segment)
	{
		this->setPolicy(new ZeroPolicy(2*m_nb_intervals_per_segment, true));
		this->setController( new Driver());
		this->setWrapper( &singleton::getInstance().wrap);
		this->m_prev_spline = NULL;
		m_interval_length = m_segment_length/m_nb_intervals_per_segment;
	};
/*Arbiter::Arbiter(double segment_length, int nb_intervals_per_segment, Driver* controller, ZeroPolicy* policy, wrapper* wrapper)
{
	//this->m_nb_segments = nb_segments;
	this->m_prev_spline = NULL;
	this->m_segment_length = segment_length;
	this->m_nb_intervals_per_segment= nb_intervals_per_segment;
	m_interval_length = m_segment_length/m_nb_intervals_per_segment;
	this->setWrapper(wrapper);
	this->setController(controller);
	this->setPolicy(policy);
}*/
void Arbiter::drive()
{
	//Get position from start of race
	float length_from_start = m_wrapper->m_distFromStart;
	//Get position from start of track
	float length_from_start_mod = m_wrapper->getDistanceFromStart();
	tCarElt* car_state = m_wrapper->m_car;
	tSituation* situation = m_wrapper->m_situation;
	//Get the segment id which we are on from start of race
	int segment_position_idx = length_from_start/m_segment_length;
	//Get position in meters of the start of segment we are on
	float segment_position_met = segment_position_idx * m_segment_length;
	//If we do not have splitted the two consecutives segments into intervals, do it
	double prev_spline_value = 0;
	if (m_prev_spline != NULL)
	{
		prev_spline_value = m_prev_spline->getCurvature(length_from_start_mod);
	}
	bool cond = (m_curvatures.find(segment_position_idx) != m_curvatures.end());
	//int cond = m_curvatures.count(segment_position_idx);	
	if (!cond) 
	{
        float segment_time = m_wrapper->getCurrentTime() - m_segment_start_time;
        m_segment_start_time = m_wrapper->getCurrentTime();
		float end_two_segments_met = segment_position_met + 2*m_segment_length;
		this->collectIntervalPositions(segment_position_idx, segment_position_met, end_two_segments_met);
        m_policy->reportReward(segment_time);
		vector<double> data_points_y = m_policy->search(m_curvatures[segment_position_idx]);
		m_prev_spline = new Spline(m_positions_x[segment_position_idx], data_points_y, prev_spline_value);
		m_controller->setSpline(*m_prev_spline);
	}
	
	//Policy-Spline interaction
	//pair<vector<double>, vector<double> > future_arguments = this->getSubCurvatures(segment_position_idx, length_from_start_mod);	
	
	//Controller interaction	
	m_controller->drive(situation, car_state, length_from_start_mod - segment_position_met);	
}
void Arbiter::setController(Driver* controller) {m_controller = controller;}
void Arbiter::setPolicy(ZeroPolicy* policy) {m_policy = policy;}
void Arbiter::setWrapper(wrapper* w)
{
	m_wrapper = w;
	//m_track_length = m_wrapper->m_trackLength;
	m_nb_segments = (int)(m_wrapper->m_trackLength/m_segment_length);
	//m_segment_length = m_track_length/m_nb_segments;
	//m_interval_length = m_segment_length/m_nb_intervals_per_segment;
}
void Arbiter::collectIntervalPositions(int segment_id, double beg_measure, double end_measure)
{
	for (float i_meas= beg_measure; i_meas < end_measure; i_meas = i_meas+ m_interval_length)
	{
		double curvature_i = m_wrapper->getCurvature(fmod(i_meas,m_wrapper->m_trackLength));
		m_curvatures[segment_id].push_back(curvature_i);
		m_positions_x[segment_id].push_back(fmod(i_meas,m_wrapper->m_trackLength));
	}
}
pair<vector<double>,vector<double> > Arbiter::getSubCurvatures(int segment_id,float position)
{
	int k = 0;
	for (vector<double>::iterator it = m_positions_x[segment_id].begin(); it != m_positions_x[segment_id].end(); ++it)
	{
		if (*it == position)
			break;
		else
			k++;
	}
	vector<double> future_positions(m_positions_x[segment_id].begin()+1, m_positions_x[segment_id].end());
	vector<double> future_curvatures(m_curvatures[segment_id].begin()+1, m_curvatures[segment_id].end()); 
	pair<vector<double>,vector<double> > result(future_positions, future_curvatures);
	return result;
}
void Arbiter::setTrack(tTrack* track)
{
	this->m_controller->setTrack(track);
}
void Arbiter::newRace(tCarElt* car, tSituation *s)
{
	this->m_controller->newRace(car, s);
}
