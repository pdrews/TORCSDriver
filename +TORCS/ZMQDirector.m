classdef ZMQDirector
    properties
        communicator
    end
    
    methods
        function obj = ZMQDirector()
        end
        
        function state = nextState(~, ~)
            state = TORCS.ZMQCommunicator('state');
        end
    end
    
end

