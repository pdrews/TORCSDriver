#include <math.h>
#include <matrix.h>
#include <mex.h>
#include <stdio.h>
#include <stdlib.h>
#include <zmq.h>
#include <string.h>

void* context = NULL;
void* channel = NULL;

void cleanup() {
    zmq_close(channel);
}

void mexFunction(int nlhs, mxArray** plhs, int nrhs, mxArray const** prhs) {
    if(!context) {
        context = zmq_init(1);
        channel = zmq_socket(context, ZMQ_REQ);
        zmq_connect(channel, "tcp://127.0.0.1:21346");
        mexAtExit(&cleanup);
    }

    char* cmd = mxArrayToString(prhs[0]);

    if(!strcmp(cmd, "state")) {
        zmq_msg_t empty_msg;
        zmq_msg_init(&empty_msg);
        zmq_send(channel, &empty_msg, 0);
        zmq_msg_close(&empty_msg);

        zmq_msg_t states_msg;
        zmq_msg_init(&states_msg);
        zmq_recv(channel, &states_msg, 0);
        double* states = zmq_msg_data(&states_msg);
        plhs[0] = mxCreateNumericMatrix(1,zmq_msg_size(&states_msg)/sizeof(double), mxDOUBLE_CLASS, 0);
        memcpy(mxGetPr(plhs[0]), states, zmq_msg_size(&states_msg));
        zmq_msg_close(&states_msg);
    }

    else if(!strcmp(cmd, "evaluate")) {
        double* actions = mxGetPr(prhs[1]);
        size_t size = mxGetN(prhs[1]) * sizeof(double);
        zmq_msg_t actions_msg;
        zmq_msg_init_size(&actions_msg, size);
        memcpy(zmq_msg_data(&actions_msg), actions, size);
        zmq_send(channel, &actions_msg, 0);
        zmq_msg_close(&actions_msg);

        zmq_msg_t reward_msg;
        zmq_msg_init(&reward_msg);
        zmq_recv(channel, &reward_msg, 0);

        double* reward = zmq_msg_data(&reward_msg);
        plhs[0] = mxCreateDoubleScalar(*reward);
        zmq_msg_close(&reward_msg);
    }
}

