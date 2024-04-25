%% 
Ixx = 0.004642687; % Fixed 
Iyy = 0.003385234; % Fixed
Izz = 0.006060711; % Fixed
Krx = 0.05;  
Kry = 0.05;
Krz = 0.01;
Brx = 0.1;
Bry = 0.1;
d = 0.11; % Fixed
ct = 1.2E-06; 
cm = 8.00E-08;
Jr = 6e-9;

FileName = 'model_agile';
Order = [6 4 6];
Parameters = [Ixx;Iyy;Izz;Krx;Kry;Krz;Brx;Bry;d;ct;cm;Jr];
InitialStates = [0;0;0;0;0;0];
m = idnlgrey(FileName,Order,Parameters,InitialStates,0)
% m.Algorithm.SimulationOptions.Solver = 'ode23s'; 
% 
compare(m,eData)
%% For first Data
newData = flightData(219*10:353*10);
eData = newData(1:670);
vData = newData(671:end);

%% For second Data
newData = flightData(145*25:358*25);
vData = newData(1:100*25);
eData = newData(101*25:end);
%%
set(m,'InputName',{'Motor 1','Motor 2','Motor 3','Motor 4'}, ...
    'OutputName',{'RollSpeed','PitchSpeed','YawSpeed'})
compare(m,eData)
%%
m.SimulationOptions.AbsTol = 1e-6;
m.SimulationOptions.RelTol = 1e-5;
%compare(drone,m)
m = setinit(m,'Fixed',{false,false,false,false,false,false});

m.Parameters(1).Fixed = true;
m.Parameters(2).Fixed = true;
m.Parameters(3).Fixed = true;
m.Parameters(9).Fixed = true;
m.Parameters(10).Fixed = true;
m.Parameters(11).Fixed = true;

opt = nlgreyestOptions('Display','on');
opt.SearchOptions.MaxIterations = 10;

m = nlgreyest(eData,m,opt);