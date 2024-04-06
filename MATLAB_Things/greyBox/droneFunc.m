%% State Space Function
function [A,B,C,D] = droneFunc(par,T)
A = [0 1 0 0 0 0;
    0 0 0 0 0 0;
    0 0 0 1 0 0;
    0 0 0 0 0 0;
    0 0 0 0 0 1;
    0 0 0 0 0 0];
B = [0 0 0 0;
    par(1)/par(2) -par(1)/par(2) -par(1)/par(2) par(1)/par(2);
    0 0 0 0;
    par(1)/par(3) par(1)/par(3) -par(1)/par(3) -par(1)/par(3);
    0 0 0 0;
    par(4) par(4) par(4) par(4)];
C = [0 1 0 0 0 0;
    0 0 0 1 0 0;
    0 0 0 0 0 1];
D = 0;
end
