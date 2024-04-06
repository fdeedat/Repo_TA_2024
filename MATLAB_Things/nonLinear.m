%% Parameter Matlab
a = 1/sqrt(2);
Ixx = 0.005;
Iyy = 0.005;
Izz = 0.009;
mass = 0.8;
l = 0.165;
dragCoeff = 0.01;
thrustCoeff = 0;

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
C = [0 0 0 1 0 0;
    0 0 0 0 1 0;
    0 0 0 0 0 1];
D = 0;

sys = ss(A,B,C,D);

%%
omega1= 0;
omega2= 0;
omega3= 0;
omega4= 0;

psidot = 0;
thetdot = 0;
phidot = 0;

%% Simulasi Dinamika Non Linear
tfin = 10;
u =[sin(t);0;0];
x0 = [0;0;0;0;0;0];
[t,x] = ode45(@att,[0 tfin],x0,[],u);
plot(t,x)
hold on
plot(t,sin(t))

%% udah ngerti 🙏
function dx = att(t,x,u)
    Ixx = 0.005;
    Iyy = 0.005;
    Izz = 0.009;

    x1 = x(1);
    x2 = x(2);
    x3 = x(3);
    x4 = x(4);
    x5 = x(5);
    x6 = x(6);

    tau_roll = u(1);
    tau_pitch = u(2);
    tau_yaw = u(3);

    dx1 = x4;
    dx2 = x5;
    dx3 = x6;
    dx4 = ((Iyy-Izz)*x5*x6/Ixx) + tau_roll/Ixx;
    dx5 = ((Izz-Ixx)*x4*x6/Iyy) + tau_pitch/Iyy;
    dx6 = ((Ixx-Iyy)*x5*x4/Izz) + tau_yaw/Izz;

    dx = [dx1;dx2;dx3;dx4;dx5;dx6];
end