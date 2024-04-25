%% Data prep
eData = newData(40*10:164*10);
vData = newData(165*10:end);

% Downsample datasets 10 times
eDataD = resample(eData,10); 
vDataD = resample(vData,10);
eDataD.Properties.TimeStep
%%
Inputs = ['tau_roll','tau_pitch','tau_yaw'];
Output = ['roll','pitch','yaw','p','q','r'];

nx = 6;
nssModel = idNeuralStateSpace(nx,NumInputs=3);
nssModel.InputName = Inputs;
nssModel.OutputName = Output;

nssModel.StateNetwork = createMLPNetwork(nssModel,"state", ...
    LayerSizes=[128 128], ...
    WeightsInitializer="glorot", ...
    BiasInitializer="zeros", ...
    Activations='tanh')
%%
predictionStep = 20; % length of each data segment
numExperiment = height(eDataD) - predictionStep;
Expts = cell(1, numExperiment); 

for i = 1:numExperiment
    Expts{i} = eDataD(i:i+predictionStep,:);
    if i>1
       % set the row time of each segment to be identical; this is a requirement for training a
       % neural state-space model with multiple data experiments
       Expts{i}.Properties.RowTimes = Expts{1}.Properties.RowTimes;
    end
end

StateOpt = nssTrainingOptions('adam');
StateOpt.MaxEpochs = 90;
StateOpt.InputInterSample = 'pchip';  
%% Train the neural state-space model
tic
nssModel = nlssest(Expts,nssModel,StateOpt)
toc