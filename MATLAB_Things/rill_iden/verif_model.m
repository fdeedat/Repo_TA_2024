%% 
% clear; clc;
Ixx = 0.004642687; % Fixed 
Iyy = 0.003385234; % Fixed
Izz = 0.006060711; % Fixed
Krx = 0.05;  
Kry = 0.05;
Krz = 0.01;
Jr = 6e-9;
%%
FileName = 'model_agile_tau';
Order = [3 3 6];
Parameters = [Ixx;Iyy;Izz;Krx;Kry;Krz;Jr];
InitialStates = [0;0;0;0;0;0];
m = idnlgrey(FileName,Order,Parameters,InitialStates,0)
% m.Algorithm.SimulationOptions.Solver = 'ode23s'; 
% 
compare(m,eData)
%%
m.SimulationOptions.AbsTol = 1e-5;
m.SimulationOptions.RelTol = 1e-4;
%compare(drone,m)
m = setinit(m,'Fixed',{false,false,false,false,false,false});

m.Parameters(1).Fixed = true;
m.Parameters(2).Fixed = true;
m.Parameters(3).Fixed = true;

opt = nlgreyestOptions('Display','on');
opt.SearchOptions.MaxIterations = 50;
opt.SearchMethod = 'lsqnonlin';

m = nlgreyest(eData,m,opt);