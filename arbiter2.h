#pragma once

#include <tr1/memory>
#include "policy.h"
#include "controller.h"
#include "Spline.h"
#include "wrap.h"

class Arbiter {
public:
    Arbiter(double segment_length, int context_dim, int action_dim);
    void drive();
    void setTrack(tTrack* track);
    void newRace(tCarElt* car, tSituation* s);
private:
    double m_segment_start_distance;
    double m_segment_start_time;
    double m_segment_length;

    int m_context_dim;
    int m_action_dim;
    double m_action_segment_length;
    double m_context_segment_length;

    Driver m_controller;
    std::tr1::shared_ptr<Spline> m_current_spline;
    std::tr1::shared_ptr<Policy> m_policy;
};

