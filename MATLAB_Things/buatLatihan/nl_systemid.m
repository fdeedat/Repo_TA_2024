%%
FileName = 'attitudeCopter';
Order = [6 3 6];
% Parameters = [Ixx;Iyy;Izz;((Iyy-Izz)/Ixx);((Izz-Ixx)/Iyy);((Ixx-Iyy)/Izz)];
Parameters = [1;1;1;1;1;1];
InitialStates = [0;0;0;0;0;0];
m = idnlgrey(FileName,Order,Parameters,InitialStates,0.1)

%%
set(m,'InputName',{'tau_roll','tau_pitch','tau_yaw'}, ...
    'OutputName',{'Roll','Pitch','Yaw','RollSpeed','PitchSpeed','YawSpeed'})
%%
m.SimulationOptions.AbsTol = 1e-6;
m.SimulationOptions.RelTol = 1e-5;
%compare(drone,m)
m = setinit(m,'Fixed',{true,true,true,false,false,false});
opt = nlgreyestOptions('Display','on');
m = nlgreyest(newDataeTrain,m,opt)