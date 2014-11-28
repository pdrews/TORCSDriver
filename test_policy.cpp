#include "policy.h"
#include <iostream>
#include <random>

using namespace std;

//Very simple test task that tests matlab <-> C++ policy search interaction, not required for TORCS
int main() {
    ZMQPolicy policy(2);
    double state = 1;

    mt19937 generator;
    uniform_real_distribution<double> distribution(-5,5);
    for(;;) {
        state = distribution(generator);
        cout << "state: " << state << "; ";
        vector<double> actions = policy.search(vector<double>{state});
        cout << "action: " << actions[0] << "," << actions[1] << "; ";
        double reward = -(actions[0]-state)*(actions[0]-state) - (actions[1]-state)*(actions[1]-state);
        cout << "reward: " << reward << endl;
        policy.reportReward(reward);
    }
}

