%%
FileName = 'model_c';
Order = [3 3 6];
Parameters = [Ixx;Iyy;Izz;Krx;Kry;Krz;0.01;0.01];
InitialStates = [0;0;0;0;0;0];
m = idnlgrey(FileName,Order,Parameters,InitialStates,0)
m.Algorithm.SimulationOptions.Solver = 'ode15s';
% 
% eData = newData(40*10:120*10);
% vData = newData(121*10:end);
%%
set(m,'InputName',{'tau_roll','tau_pitch','tau_yaw'}, ...
    'OutputName',{'RollSpeed','PitchSpeed','YawSpeed'})
%%
m.SimulationOptions.AbsTol = 1e-6;
m.SimulationOptions.RelTol = 1e-5;
%compare(drone,m)
m = setinit(m,'Fixed',{false,false,false,false,false,false});
opt = nlgreyestOptions('Display','on');

m = nlgreyest(eData,m,opt)

%% Parameter nampak jeeeeee
rotorCt = 4.27E-06;
rotorCm = 8.00E-08;
rotorD = 0.2275;
%%
M_rctcm = [-sin(pi/4)*rotorD*rotorCt, sin(pi/4)*rotorD*rotorCt, sin(pi/4)*rotorD*rotorCt, -sin(pi/4)*rotorD*rotorCt;
        sin(pi/4)*rotorD*rotorCt, -sin(pi/4)*rotorD*rotorCt, sin(pi/4)*rotorD*rotorCt, -sin(pi/4)*rotorD*rotorCt;
        rotorCm, rotorCm, -rotorCm, -rotorCm];
w1= 400;
w2= 400;
w3 = 200;
w4 = 200;
M_rctcm*([w1^2;w2^2;w3^2;w4^2])