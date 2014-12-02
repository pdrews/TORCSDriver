#include "arbiter2.h"
#include "singleton.h"
#include <iostream>

using namespace std;
using namespace std::tr1;

Arbiter::Arbiter(double segment_length, int context_dim, int action_dim) : 
    m_segment_start_distance(0),
    m_segment_start_time(-3), //TODO: exact start time...
    m_segment_length(segment_length),
    m_context_dim(context_dim),
    m_action_dim(action_dim),
    m_action_segment_length((segment_length * 2) / action_dim),
    m_context_segment_length((segment_length * 2) / context_dim),
    m_policy(new ZeroPolicy(action_dim, true)) {
}

void Arbiter::drive() {
    wrapper& wrapper = singleton::getInstance().wrap;
    double current_position = wrapper.getDistanceFromStart();

    double position_on_spline = current_position - m_segment_start_distance; //position of next segment
    if(current_position < m_segment_start_distance) //wraparound
        position_on_spline += wrapper.m_trackLength;
    if(position_on_spline > m_segment_length) {
        //new segment, gather context information
        m_segment_start_distance = current_position;
        double segment_time = wrapper.getCurrentTime() - m_segment_start_time;
        m_segment_start_time = wrapper.getCurrentTime();
        vector<double> curvatures;
        for(int i = 0; i < m_context_dim; ++i) {
            curvatures.push_back(wrapper.getCurvature(fmod(current_position + i * m_context_segment_length, wrapper.m_trackLength)));
        }
        //TODO: fix context
        m_policy->reportReward(segment_time); //TODO: fix initial step
        vector<double> spline_y = m_policy->search(curvatures);
        vector<double> spline_x;
        cout << "Spline x ";
        for(int i = 0; i < m_action_dim; ++i) {
            spline_x.push_back(current_position + i * m_action_segment_length);
            cout << current_position + i * m_action_segment_length << " ";
        }
        cout << endl;
        if(m_current_spline)
            m_current_spline.reset(new Spline(spline_x, spline_y, m_current_spline->getCurvature(current_position)));
        else
            m_current_spline.reset(new Spline(spline_x, spline_y, 0));
        cout << "Spline y ";
        for (int i = 0; i < spline_y.size(); i++)
        {
          cout << spline_y[i] << " ";
        }
        cout << endl;
        m_controller.setSpline(*m_current_spline);
    }

    //call controller
    tCarElt* car_state = wrapper.m_car;
    tSituation* situation = wrapper.m_situation;
    m_controller.drive(situation, car_state, current_position);
}

void Arbiter::setTrack(tTrack* track)
{
    m_controller.setTrack(track);
}
void Arbiter::newRace(tCarElt* car, tSituation *s)
{
    m_controller.newRace(car, s);
}

