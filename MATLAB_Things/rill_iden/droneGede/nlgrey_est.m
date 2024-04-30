%% For thrid Data (indoor pemberani)
% newData = flightData(228*25:525*25);
newData = flightData_tau(339*25:360*25);
vData = flightData_tau(330*25:360*25);
% eData = newData(46*25:end);
% %% For second Data
% newData = flightData(145*25:358*25);
% vData = newData(1:100*25);
% eData = newData(101*25:end);

% 0.0210140091275141
% 0.0161622946933953
% 0.0817182415239415
% 0.0498181398702895
% 0.0311214873332469
% 0.0970626751115688
% 0.215000000000000
% 9.00000000000000e-06
% 1.11983505868590e-06
% 0.00148844465386550
% 0.199495144142079
% 0.145041195191806
% 494.980000000000
% 304.120000000000

%% 
mass = 1.371;
Ixx = 0.016887157; % Fixed 
Iyy = 0.016218129; % Fixed
Izz = 0.022727832; % Fixed
Krx = 0.290969897703740; 
Kry = 0.0795680280421862; 
Krz = 0.203163720734318; % 1.6441
d = 0.215; % Fixed
ct = 9e-06; % 8.9917e-05 coba fixed 
cm = 1.42775461467086e-06; % iden: 1.1309e-05 / dari paper: 8e-8 % Fixed 1.1309e-05
Jr = 0.00912667102498166; % 0.0033
Brx = 0.00302617346840011;
Bry = 0.0383573707724321;
regM = 494.98; 
regC = 304.12;

FileName = 'model_dji';
Order = [3 4 6];
Parameters = [Ixx;Iyy;Izz;Krx;Kry;Krz;d;ct;cm;Jr;regM;regC];
InitialStates = [0;0;0;0;0;0];
m = idnlgrey(FileName,Order,Parameters,InitialStates,0)
% m.Algorithm.SimulationOptions.Solver = 'ode23s'; 

figure(1)
compare(m,newData)

%% 
Ixx = 0.0210140091275141; % Fixed 
Iyy = 0.0161622946933953; % Fixed
Izz = 0.0817182415239415; % Fixed
Krx = 0.0695815406968292;
Kry = 0.0496228101190570;
Krz = 0.114623946115816; 
Brx = 0.290483157624344;
Bry = 0.168165350412933;

FileName = 'model_dji_tau';
Order = [3 3 6];
Parameters = [Ixx;Iyy;Izz;Krx;Kry;Krz];
InitialStates = [0;0;0;0;0;0];
m = idnlgrey(FileName,Order,Parameters,InitialStates,0)
% m.Algorithm.SimulationOptions.Solver = 'ode23s'; 

figure(1)
compare(m,newData)
%%
% set(m,'InputName',{'Motor 1','Motor 2','Motor 3','Motor 4'}, ...
%     'OutputName',{'RollSpeed','PitchSpeed','YawSpeed'})

set(m,'InputName',{'Tau Roll','Tau Pitch','tau Yaw'}, ...
    'OutputName',{'RollSpeed','PitchSpeed','YawSpeed'})

figure(2)
subplot(3,1,1)
plot(eData.InputData(:,1))
title('Motor 1')
subplot(3,1,2)
plot(eData.InputData(:,2))
title('Motor 2')
subplot(3,1,3)
plot(eData.InputData(:,3))
title('Motor 3')
subplot(4,1,4)
% title('Motor 4')
% plot(eData.InputData(:,4))

figure(3)
plot(eData)


%%
m.SimulationOptions.AbsTol = 1e-6;
m.SimulationOptions.RelTol = 1e-5;
%compare(drone,m)
m = setinit(m,'Fixed',{false,false,false,false,false,false});

% m.Parameters(1).Fixed = true;
% m.Parameters(2).Fixed = true;
% m.Parameters(3).Fixed = true;
% m.Parameters(7).Fixed = true;
% m.Parameters(8).Fixed = true;
% m.Parameters(11).Fixed = true;
% m.Parameters(12).Fixed = true;

opt = nlgreyestOptions('Display','on');
opt.SearchOptions.MaxIterations = 50;
opt.SearchMethod = 'lsqnonlin';

m = nlgreyest(newData,m,opt);