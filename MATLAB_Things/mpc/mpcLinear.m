%% State Space buat MPC yang super duper linear white box
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
% C = [1 0 0 0 0 0;
%     0 1 0 0 0 0;
%     0 0 1 0 0 0;
%     0 0 0 1 0 0;
%     0 0 0 0 1 0;
%     0 0 0 0 0 1];
C = [0 0 0 1 0 0;
    0 0 0 0 1 0;
    0 0 0 0 0 1];

D = 0;

sys = ss(A,B,C,D);
sysD = c2d(sys,0.01)
%% mpc things
mpcobj = mpc(sys,0.01,5,2);
setEstimator(mpcobj,'custom');
xsys = [0;0;0;0;0;0];
xmpc = mpcstate(mpcobj)