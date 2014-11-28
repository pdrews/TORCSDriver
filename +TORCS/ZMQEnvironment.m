classdef ZMQEnvironment < Environments.EpisodicEnvironment
    
    methods
        function obj = ZMQEnvironment(settings, dimState, dimAction)
            obj = obj@Environments.EpisodicEnvironment(settings, dimState, dimAction);
        end
        
        function [reward] = rewardFunction(obj, state, action)
            reward = TORCS.ZMQCommunicator('evaluate', action);
        end
    end
    
end

