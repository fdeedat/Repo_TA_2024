%% 
% clear; clc;
Ixx = 0.004642687; % Fixed 
Iyy = 0.003385234; % Fixed
Izz = 0.006060711; % Fixed
Krx = 0.05;  
Kry = 0.05;
Krz = 0.01;
% Brx = 0.1;
% Bry = 0.1;
d = 0.11; % Fixed
ct = 1.2E-06;
% ct = 20;
cm = 8e-8;
Jr = 6e-9;

FileName = 'model_agile';
Order = [3 4 6];
Parameters = [Ixx;Iyy;Izz;Krx;Kry;Krz;d;ct;cm;Jr];
InitialStates = [0;0;0;0;0;0];
m = idnlgrey(FileName,Order,Parameters,InitialStates,0)
% m.Algorithm.SimulationOptions.Solver = 'ode23s'; 
% 
compare(m,eData)