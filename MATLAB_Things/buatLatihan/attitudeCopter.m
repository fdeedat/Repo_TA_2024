%% Nonlinear State Space Quadcopter
function [dx,y] = attitudeCopter(t,x,u,Ixx,Iyy,Izz,Krx,Kry,Krz,Brx,Bry,varargin)
    y = [x(4);x(5);x(6)];
    dx = [x(4);
        x(5);
        x(6);
        ((Iyy-Izz)/Ixx)*x(5)*x(6)+u(1)/Ixx-Krx*x(4)/Ixx-Brx*x(1)/Ixx;
        ((Izz-Ixx)/Iyy)*x(4)*x(6)+u(2)/Iyy-Kry*x(5)/Iyy-Bry*x(2)/Iyy;
        ((Ixx-Iyy)/Izz)*x(4)*x(5)+u(3)/Izz-Krz*x(6)/Izz;
        % ((Iyy-Izz)/Ixx)*x(5)*x(6)+u(1)/Ixx-Krx*x(4)/Ixx;
        % ((Izz-Ixx)/Iyy)*x(4)*x(6)+u(2)/Iyy-Kry*x(5)/Iyy;
        % ((Ixx-Iyy)/Izz)*x(4)*x(5)+u(3)/Izz-Krz*x(6)/Izz;
        ]; 
    % Nambahin damping Kx
end