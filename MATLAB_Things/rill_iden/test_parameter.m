%% For thrid Data (indoor pemberani)
newData = flightData_tau;
% vData = newData(1:100*25);
eData = newData;
% %% For second Data
% newData = flightData(145*25:358*25);
% vData = newData(1:100*25);
% eData = newData(101*25:end);
%% 
Ixx = 0.04642687; % Fixed 
Iyy = 0.03385234; % Fixed
Izz = 0.006060711; % Fixed
Krx = 0.005; % 0.0558 / 0.05
Kry = 0.005; % 0.0248 / 0.05
Krz = 0.01; % 0.0679 / 0.01
d = 0.11; % Fixed
ct = 0.8E-06; 
cm = 6.3777e-08; % iden: 5.3777e-08 / dari pape: 8e-8 % Fixed
Jr = 6e-9; % 0.0033

FileName = 'model_agile_tau';
Order = [3 3 6];
Parameters = [Ixx;Iyy;Izz;Krx;Kry;Krz;d;ct;cm;Jr];
InitialStates = [0;0;0;0;0;0];
m = idnlgrey(FileName,Order,Parameters,InitialStates,0)
% m.Algorithm.SimulationOptions.Solver = 'ode23s'; 

figure(1)
compare(m,eData)
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
    % 'OutputName',{'RollSpeed','PitchSpeed','YawSpeed'})

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
% subplot(4,1,4)
% title('Motor 4')
% plot(eData.InputData(:,4))

figure(3)
plot(eData)


%%
% m.SimulationOptions.AbsTol = 1e-5;
% m.SimulationOptions.RelTol = 1e-4;
% %compare(drone,m)
% m = setinit(m,'Fixed',{false,false,false,false,false,false});
% 
% m.Parameters(1).Fixed = true;
% m.Parameters(2).Fixed = true;
% m.Parameters(3).Fixed = true;
% m.Parameters(7).Fixed = true;
% m.Parameters(9).Fixed = true;
% % m.Parameters(11).Fixed = true;
% 
% opt = nlgreyestOptions('Display','on');
% opt.SearchOptions.MaxIterations = 50;
% opt.SearchMethod = 'lsqnonlin';
% 
% m = nlgreyest(rpData,m,opt);