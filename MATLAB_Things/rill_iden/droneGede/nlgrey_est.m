%% For thrid Data (indoor pemberani)
% newData = flightData(228*25:525*25);
newData = flightData(339*25:360*25);
vData = flightData(441*25:461*25);
% eData = newData(46*25:end);
% %% For second Data
% newData = flightData(145*25:358*25);
% vData = newData(1:100*25);
% eData = newData(101*25:end);

% 0.0121788252894294
% 0.0101799984094420
% 0.0475555463444681
% 0.0541508433128678
% 0.0135801025041739
% 0.0568961617307131
% 0.215000000000000
% 9.00000000000000e-06
% 1.16669640754000e-06
% 0.00104045878953994
% 0.000387306063492652
% 0.0773311447875422
% 670.227060933052
% -150.938615927672

%% 
mass = 1.371;
Ixx = 0.0771162988505217; % Fixed 
Iyy = 0.0347107665529648; % Fixed
Izz = 0.117698160529904; % Fixed
Krx = 0.290969897703740; 
Kry = 0.0795680280421862; 
Krz = 0.203163720734318; % 1.6441
d = 0.215; % Fixed
ct = 9e-06; % 8.9917e-05 coba fixed 
cm = 1.42775461467086e-06; % iden: 1.1309e-05 / dari paper: 8e-8 % Fixed 1.1309e-05
Jr = 0.00912667102498166; % 0.0033
Brx = 0.00302617346840011;
Bry = 0.0383573707724321;
regM = 670.227060933052;
regC = -150.938615927672;

FileName = 'model_dji';
Order = [3 4 6];
Parameters = [Ixx;Iyy;Izz;Krx;Kry;Krz;d;ct;cm;Jr;Brx;Bry;regM;regC];
InitialStates = [0;0;0;0;0;0];
m = idnlgrey(FileName,Order,Parameters,InitialStates,0)
% m.Algorithm.SimulationOptions.Solver = 'ode23s'; 

figure(1)
compare(m,newData)
% %% For first Data
% newData = flightData(219*10:353*10);
% eData = newData(1:670);
% vData = newData(671:end);
% 
% %%
% rpData = flightData(258*25:288*25)
% %% For thrid Data (indoor pemberani)
% newData = flightData(507*25:521*25);
% % vData = newData(1:100*25);
% % eData = newData(101*25:end);
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
m.Parameters(7).Fixed = true;
m.Parameters(8).Fixed = true;
% m.Parameters(11).Fixed = true;

opt = nlgreyestOptions('Display','on');
opt.SearchOptions.MaxIterations = 50;
opt.SearchMethod = 'lsqnonlin';

m = nlgreyest(newData,m,opt);