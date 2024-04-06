%% Nonlinear State Space Quadcopter
function [dx,y] = attitudeCopter(t,x,u,Ixx,Iyy,Izz,a,b,c,varargin)
    y = [x(1);x(2);x(3);x(4);x(5);x(6)];
    dx = [x(4);
        x(5);
        x(6);
        a*x(5)*x(6)+u(1)/Ixx;
        b*x(4)*x(6)+u(2)/Iyy;
        c*x(4)*x(5)+u(3)/Izz;];
end