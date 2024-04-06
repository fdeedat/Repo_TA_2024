%%
A = [0 0 0 1 0 0;
    0 0 0 0 1 0;
    0 0 0 0 0 1;
    0 0 0 0 0 0;
    0 0 0 0 0 0;
    0 0 0 0 0 0];
B = [0 0 0; 
    0 0 0;
    0 0 0;
    1/Ixx 0 0;
    0 1/Iyy 0;
    0 0 1/Izz];
C = [0 0 0 1 0 0;
    0 0 0 0 1 0;
    0 0 0 0 0 1];
D = 0;

sys = ss(A,B,C,D);

% set names
sys.InputName = {'tau_roll','tau_pitch','tau_yaw'};
sys.OutputName = {'RollSppeed','PitchSpeed','YawSpeed'};

%%
sys = setmpcsignals(sysdis2,'MV',[1,2,3],'MO',[1,2,3]);
damp(sys)
%%
Ts = 0.1;
mpcobj = mpc(sys,Ts,5,2)
for i = 1:3
    mpcobj.MV(i).Min = -1;
    mpcobj.MV(i).Max = 1;
    mpcobj.MV(i).RateMin = -0.1;
    mpcobj.MV(i).RateMax = 0.1;
    
    mpcobj.OV(i).Min = -0.5;
    mpcobj.OV(i).Max = 0.5;
    
end
% mpcobj.MV = struct('Min',-0.1,'Max',0.1,'RateMin',-1,'RateMax',1);
setEstimator(mpcobj,'custom');
%%
C = [1 0 0 0 0 0;
    0 1 0 0 0 0;
    0 0 1 0 0 0
    0 0 0 1 0 0;
    0 0 0 0 1 0;
    0 0 0 0 0 1];

