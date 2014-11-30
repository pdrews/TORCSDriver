manager = 2; % Disable experimental distributed computing stuff that never worked

settings = Common.IASParameters();
%REPS & Distribution settings
settings.setParameter('epsilonAction', 0.8);
settings.setParameter('initSigma', 0.2);
settings.setParameter('initSigmaMu', 0.1); 
settings.setParameter('initSigmaMuStates', 1); 
settings.setParameter('initSigmaStates', 0.5); 
settings.setParameter('minCovAction', 10^-6);
settings.setParameter('minCorrAction', 1);

%Iterations & Sampling
settings.setParameter('maxSamples', 4000);
settings.setParameter('numVirtualSamples', 0);
settings.setParameter('initialSamples', 400);
settings.setParameter('useOnlyVirtualSamples', 0);
settings.setParameter('numIterations',200);
settings.setParameter('newSamples', 40);
settings.setParameter('numInitialVirtual', 100);

%Local REPS settings (No Local REPS so far, but we might try it (remember to set actionModel to learner...))
settings.setParameter('localREPSBandwidth', 0.5);

dimState = 1; %TODO: set this for TORCS
dimAction = 2;

resultsPath = '/tmp/'; %Filling up your disk space
environment = TORCS.ZMQEnvironment(settings, dimState, dimAction);
featureFunction = Features.SquaredFeatures(settings, 1:dimState);
actionModel = ActionModels.GaussianActionDistribution(settings);
learner = Learner.EpisodicREPS(settings, actionModel, featureFunction);
director = TORCS.ZMQDirector();
deletionStrategy = GoalLearning.StandardDeletionStrategy(settings);

learningScenario = GoalLearning.DirectedEpisodicLearningScenario(settings, director, deletionStrategy, environment, learner, actionModel, {});
learningScenario.storeModels = true; %can take up a lot of space!

numTrials = 5;
evalFunc = @(evalParameters, evalValues)TrialManagement.evalParallel('TORCS',numTrials,learningScenario, settings, evalParameters, evalValues, [], resultsPath);
[resultsCellCell, trialsCellCell, propertiesCell] = evalFunc({'epsilonAction'}, {0.8});


