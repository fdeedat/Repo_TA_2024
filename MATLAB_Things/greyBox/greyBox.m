%% Parameter Dinamik
a = sqrt(2)/2*13;
Ixx = 0.0168;
Iyy = 0.0162;
Izz = 0.0227;
m = 1.3578;
Cm = 0.00001;
%% SISO buat coba-coba
A = [0 1 0;
    0 0 1;
    -1 -2 -3];
B = [0;
    1;
    4];
C = [1 0 0;
    0 0 1];
D = [0;0];
siso_sys = ss(A,B,C,D)
%% State Space 1
A = [0 0 0 1 0 0;
    0 0 0 0 1 0;
    0 0 0 0 0 1;
    0 0 0 0 0 0;
    0 0 0 0 0 0;
    0 0 0 0 0 0];
B = [0 0 0 0;
    0 0 0 0;
    0 0 0 0;
    0 1/Ixx 0 0;
    0 0 1/Iyy 0;
    0 0 0 1/Izz];
C = [1 0 0 0 0 0;
    0 1 0 0 0 0;
    0 0 1 0 0 0];
D = 0;
Ts = 0.27;
m3 = idss(A,B,C,D,'Ts',Ts)
%% State space 2 indian revised
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
Ts = 0.25;

%sys2 = ss(A,B,C,D);
%sys2d = c2d(sys2,0.27,'tustin')
m4 = ss(A,B,C,D);
% m4d = c2d(m4,Ts,'zoh')
m4.InputName = {'tau_roll','tau_pitch','tau_yaw'};
m4.OutputName ={'RollSpeed','PitchSpeed','YawSpeed'};
m4.StateName = {'Roll','Pitch','Yaw','RollSpeed','PitchSpeed','YawSpeed'};
%% State Space Indian with z as state
A = [0 0 0 1 0 0;
    0 0 0 0 1 0;
    0 0 0 0 0 1;
    0 0 0 0 0 0;
    0 0 0 0 0 0;
    0 0 0 0 0 0];
B = [0 0 0;
    0 0 0;
    0 0 0;
    1/0.005 0 0;
    0 1/0.005 0;
    0 0 1/0.009];
C = [1 0 0 0 0 0;
    0 1 0 0 0 0;
    0 0 1 0 0 0;
    0 0 0 1 0 0;
    0 0 0 0 1 0;
    0 0 0 0 0 1];
D = 0;

Ts = 0.01;

sysZ = ss(A,B,C,D);
sysZd = c2d(sysZ,0.01,'zoh')

sysZd.InputName = {'tau_roll','tau_pitch','tau_yaw'};
sysZd.OutputName = {'RollSpeed','PitchSpeed','YawSpeed'};
sysZd.StateName = {'Roll','Pitch','Yaw','RollSpeed','PitchSpeed','YawSpeed'};
%% 
% sysdis2 = idss(m4d.A,m4d.B,m4d.C,m4d.D,'Ts',Ts)
sysdis2 = idss(m4.A,m4.B,m4.C,m4.D,'Ts',0.1)

%sysdis2 = idss(sysZd.A,sysZd.B,sysZd.C,sysZd.D,'Ts',Ts)
%%
sysdis2.Structure.A.Free = false;

sysdis2.Structure.A.Free(1,1) = true;
sysdis2.Structure.A.Free(1,4) = true;
sysdis2.Structure.A.Free(2,2) = true;
sysdis2.Structure.A.Free(2,5) = true;
sysdis2.Structure.A.Free(3,3) = true;
sysdis2.Structure.A.Free(3,6) = true;
%sysdis2.Structure.A.Free(4,8) = true;
sysdis2.Structure.A.Free(4,4) = true;
sysdis2.Structure.A.Free(5,5) = true;
sysdis2.Structure.A.Free(6,6) = true;
%sysdis2.Structure.A.Free(7,7) = true;
%sysdis2.Structure.A.Free(8,8) = true;

sysdis2.Structure.B.Free = true;

sysdis2.Structure.B.Free(1,1) = true;
sysdis2.Structure.B.Free(2,2) = true;
sysdis2.Structure.B.Free(3,3) = true;
sysdis2.Structure.B.Free(4,1) = true;
sysdis2.Structure.B.Free(5,2) = true;
sysdis2.Structure.B.Free(6,3) = true;

sysdis2.Structure.C.Free = false;

% sysdis2.Structure.C.Free(1,1) = true;
% sysdis2.Structure.C.Free(2,2) = true;
% sysdis2.Structure.C.Free(3,3) = true;
% sysdis2.Structure.C.Free(4,8) = true;
% sysdis2.Structure.C.Free(1,4) = true;
% sysdis2.Structure.C.Free(2,5) = true;
% sysdis2.Structure.C.Free(3,6) = true;
% sysdis2.Structure.C.Free(4,4) = true;
% sysdis2.Structure.C.Free(5,5) = true;
% sysdis2.Structure.C.Free(6,6) = true;

sysdis2.Structure.D.Free = false;
%%
opt = ssestOptions;
opt.InitialState = 'zero';
%%
sysdis2 = ssest(pqrDatae,sysdis2,opt)

%%
mA = [-0.0558,-0.9968,0.0802,0.0415;
    0.5980,-0.1150,-0.0318,0;
    -3.0500,0.3880,-0.4650,0;
    0,0.0805,1.0000,0];

mB = [0.0073,0;
    -0.4750,0.0077;
    0.1530,0.1430;
    0,0];

mC = [0,1,0,0;
    0,0,0,1];

mD = [0,0;
    0,0];

sysM = ss(mA,mB,mC,mD,0.01)

%%
mpcControl = setmpcsignals(sysdis2,'MV',[1;2;3],'MO',[1;2;3]);
old_stauts = mpcverbosity('off');
%%
mpcobj = mpc(mpcControl,0.25)