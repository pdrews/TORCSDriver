#include "policy.h"
#include <cassert>
#include <cstdlib>
#include <cmath>

#include <iostream>
#include "singleton.h"

using namespace std;
using namespace zmq;

Policy::~Policy() {}

ZeroPolicy::ZeroPolicy(int actionDim, bool log) : m_actionDim(actionDim), m_log(log) {}

vector<double> ZeroPolicy::search(vector<double> const& context) {
    if(m_log) {
        cout << "looking for policy at distance from start " << singleton::getInstance().wrap.getDistanceFromStart() << ", context : ";
        for(int i = 0; i < context.size(); i++) 
            cout << context[i] << ", ";
        cout << " ... oh.. it's 0" << endl;
    }
    //-3.3822, -2.29066, -2.23472, 0.713521, -0.787446, 2.23577
    vector<double> actions;
    actions.push_back(-3.3822);
    actions.push_back(-2.29066);
    actions.push_back(-2.23472);
    actions.push_back(-0.713521);
    actions.push_back(-0.787446);
    actions.push_back(-2.23577);
    //for(int i = 0; i < m_actionDim; ++i)
    //    actions.push_back(0);
    return actions;
}

void ZeroPolicy::reportReward(double reward) {
    if(m_log)
        cout << " Got reward at distance from start " << singleton::getInstance().wrap.getDistanceFromStart() <<  ", probably didn't like my zeros :/ " << reward << endl;
}

ZMQPolicy::ZMQPolicy(int actionDim, string address) : m_actionDim(actionDim), m_context(1), m_channel(m_context, ZMQ_REP), m_waitingForReward(false), m_spline_count(0) {
    m_channel.bind(address.c_str());
}

vector<double> ZMQPolicy::search(vector<double> const& state) {
    assert(!m_waitingForReward); //This means you called this in the wrong order
    m_spline_count++;
    if(m_spline_count % 40 == 0)
        cout << m_spline_count << endl;

    //wait until state is being asked for
    message_t empty_msg;
    m_channel.recv(&empty_msg);
    assert(empty_msg.size() == 0); //This means the matlab part did something wrong. This cannot handle multiple clients at this time (although multiple servers should be fine)

    //send state
    size_t size = state.size() * sizeof(double);
    message_t states_msg(size);
    memcpy(states_msg.data(), &state[0], size);
    m_channel.send(states_msg);

    //wait for action
    message_t actions_msg;
    m_channel.recv(&actions_msg);
    double* actions = static_cast<double*>(actions_msg.data());

    m_waitingForReward = true;
    vector<double> result(actions, actions + actions_msg.size()/sizeof(double));
    return result;
}

void ZMQPolicy::reportReward(double reward) {
    assert(m_waitingForReward); //This means you called this in the wrong order

    message_t reward_msg(sizeof(double));
    *static_cast<double*>(reward_msg.data()) = reward;
    m_channel.send(reward_msg);

    m_waitingForReward = false;
}

