classdef ZMQEnvironment < Environments.EpisodicEnvironment
    properties
        file = fopen('~/rewards.txt', 'w+');
    end
    
    methods
        function obj = ZMQEnvironment(settings, dimState, dimAction)
            obj = obj@Environments.EpisodicEnvironment(settings, dimState, dimAction);
            
        end
        
        function [reward] = rewardFunction(obj, state, action)
            reward = TORCS.ZMQCommunicator('evaluate', action);
            
            fprintf(obj.file, [num2str(reward), '\n']);
            
        end
    end
    
end

