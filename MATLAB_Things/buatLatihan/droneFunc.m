%% State Space Function
function [A,B,C,D] = droneFunc(par,T)
A = [0 0 0 1 0 0;
    0 0 0 0 1 0;
    0 0 0 0 0 1;
    0 0 0 -par(4)/par(1) 0 0;
    0 0 0 0 -par(5)/par(2) 0;
    0 0 0 0 0 -par(6)/par(3)];
B = [0 0 0; 
    0 0 0;
    0 0 0;
    1/par(1) 0 0;
    0 1/par(2) 0;
    0 0 1/par(3)];
C = [0 0 0 1 0 0;
    0 0 0 0 1 0;
    0 0 0 0 0 1];
D = zeros(3);
end
