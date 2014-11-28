#include <vector>
#include <string>
#include <zmq.hpp>

class Policy {
    public:
        virtual std::vector<double> search(std::vector<double> const& state) = 0;
        virtual void reportReward(double reward) = 0;
        virtual ~Policy();
};

///This policy always returns 0 actions, use it to test policy integration with the controller
class ZeroPolicy : public Policy {
    public:
        explicit ZeroPolicy(int actionDim);
        std::vector<double> search(std::vector<double> const& state);
        void reportReward(double reward);
    private:
        int const m_actionDim;
};

///This is the actual policy that communicates with REPS
class ZMQPolicy : public Policy {
    public:
        explicit ZMQPolicy(int actionDim, std::string address = "tcp://127.0.0.1:21346");
        std::vector<double> search(std::vector<double> const& state);
        void reportReward(double reward);
    private:
        int const m_actionDim;
        zmq::context_t m_context;
        zmq::socket_t m_channel;
        bool m_waitingForReward;
};

