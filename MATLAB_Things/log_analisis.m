%% Getting PWM Data
% ts = 0.1 s
timePWM = RCOU(:,2);
pwm1 = RCOU(:,3);
pwm2 = RCOU(:,4);
pwm3 = RCOU(:,5);
pwm4 = RCOU(:,6);

%% Getting Euler Angle
% ts = 0.1 s
timeATT = ATT(:,2);
roll = ATT(:,4);
pitch = ATT(:,6);
yaw = ATT(:,8);

%% Getting Angular Rate
% ts = 0.04 s
timeIMU = IMU_0(:,2);
rollSpeed = IMU_0(:,4);
pitchSpeed = IMU_0(:,5); 
yawSpeed = IMU_0(:,6);

%% Making to Timeseries
angRate = timeseries([rollSpeed,pitchSpeed,yawSpeed],timeIMU);
attitude = timeseries([roll,pitch,yaw],timeATT);
pwm = timeseries([pwm1,pwm2,pwm3,pwm4],timePWM);

%% Sampling Angular Rate data to PWM Data
% Input : PWM
% Output : Angular Rate
% newRate = resample(angRate,timePWM);
p = angRate.Data(:,1);
q = angRate.Data(:,2);
r = angRate.Data(:,3);

%% Normalise PWM
% normalised pwm 
pwm_n1 = (pwm.Data(:,1)-1000)/1000;
pwm_n2 = (pwm.Data(:,2)-1000)/1000;
pwm_n3 = (pwm.Data(:,3)-1000)/1000;
pwm_n4 = (pwm.Data(:,4)-1000)/1000;

npwm = [pwm_n1,pwm_n2,pwm_n3,pwm_n4];
npwm_ts = timeseries([pwm_n1,pwm_n2,pwm_n3,pwm_n4],timePWM);

%% Resample PWM -> angular rate (faster)
newPWM = resample(npwm_ts,timeIMU)
newPWM1 = newPWM.Data(:,1);    
newPWM1(isnan(newPWM1))=0;

newPWM2 = newPWM.Data(:,2);
newPWM2(isnan(newPWM2))=0;

newPWM3 = newPWM.Data(:,3);
newPWM3(isnan(newPWM3))=0;

newPWM4 = newPWM.Data(:,4);
newPWM4(isnan(newPWM4))=0;
%% PWM to Rad/s (with transfer function)
% Hasil Regresi dari datasheet throttle to rad/s
% y = 1128.7x + 914.57
% try implementing low pass filter

% Filtered PWM to rad/s
for i = 1:length(newPWM1)
    if newPWM1(i) <= 0.05
        w1(i) = 0;
    else  
        w1(i) = 1128.7*newPWM1(i) + 914.57;
    end
end

for i = 1:length(newPWM2)
    if newPWM2(i) <= 0.05
        w2(i) = 0;
    else
        w2(i) = 1128.7*newPWM2(i) + 914.57;
    end
end

for i = 1:length(newPWM3)
    if newPWM3(i) <= 0.05
        w3(i) = 0;
    else
        w3(i) = 1128.7*newPWM3(i) + 914.57;
    end
end

for i = 1:length(newPWM4)
    if newPWM4(i) <= 0.05
        w4(i) = 0;
    else
        w4(i) = 1128.7*newPWM4(i) + 914.57;
    end
end
%% Filtering
tc = 5;
tf1 = tf(1,[tc 1]);

% Filter the pwm value
filtered1 = lsim(tf1,w1',0.1*(1:length(w1))');
filtered2 = lsim(tf1,w2',0.1*(1:length(w2))');
filtered3 = lsim(tf1,w3',0.1*(1:length(w3))');
filtered4 = lsim(tf1,w4',0.1*(1:length(w4))');

% mixer shit
w4_new = filtered1;
w1_new = filtered2;
w2_new = filtered3;
w3_new = filtered4;

w = timeseries([w1_new,w2_new,w3_new,w4_new],timeIMU);
%% 
newAtt = resample(attitude,timeIMU);
%% Buat object data
flightData = iddata([p,q,r],[w1_new,w2_new,w3_new,w4_new],0.04);
flightData.OutputName = {"RollSpeed","PitchSpeed","YawSpeed"};
flightData.InputName = {"Motor 1","Motor 2","Motor 3","Motor 4"};

%% Thrust & Moment Constants
d = 0.11;
ct = 1.3E-06;
cm = 8.00E-08;
Ixx = 0.004642687; % Fixed 
Iyy = 0.003385234; % Fixed
Izz = 0.006060711; % Fixed

%% rad/s to Thrust 
% motor1 = ch2
% motor2 = ch3
% motor3 = ch4
% motor4 = ch1
%
%tau_thrust = ct*(newPWM2.^2+newPWM3.^2+newPWM4.^2+newPWM1.^2);
%tau_roll = (sin(pi/4))*d*ct*(-newPWM2.^2+newPWM3.^2+newPWM4.^2-newPWM1.^2);
%tau_pitch = (sin(pi/4))*d*ct*(newPWM2.^2-newPWM3.^2+newPWM4.^2-newPWM1.^2);
%tau_yaw = cm*(newPWM2.^2+newPWM3.^2-newPWM4.^2-newPWM1.^2);
%
tau_thrust = ct*(w1_new.^2+w2_new.^2+w3_new.^2+w4_new.^2);
tau_roll = (sin(pi/4))*d*ct*(-w1_new.^2+w2_new.^2+w3_new.^2-w4_new.^2)/Ixx;
tau_pitch = (sin(pi/4))*d*ct*(w1_new.^2-w2_new.^2+w3_new.^2-w4_new.^2)/Iyy;
tau_yaw = cm*(w1_new.^2+w2_new.^2-w3_new.^2-w4_new.^2)/Izz;

%% Plotting 
figure(1);
plot(tau_roll); % corrcoef = -0.1879
title('TauRoll vs RollSpeed');
hold on
plot(p)

hold off

figure(2);
plot(tau_pitch); % corrcoef = -0.2247
title('TauPitch vs PitchSpeed');
hold on
plot(q);
hold off

figure(3);
plot(tau_yaw); % corrcoef = 0.3218
title('TauYaw vs YawSpeed');
hold on
plot(r);
hold off;
%%
corrRoll = corrcoef(tau_roll, p, 'rows', 'complete')
corrPitch = corrcoef(tau_pitch, q, 'rows', 'complete')
corrYaw= corrcoef(tau_yaw, r, 'rows', 'complete')

%% Data Object buat Black Box 
% Input: tau_roll, tau_pitch, tau_yaw
% Output: p,q,r
flightDatabb = iddata([p,q,r],[tau_thrust,tau_roll,tau_pitch,tau_yaw],0.04);
flightDatabb.OutputName = {"RollSpeed","PitchSpeed","YawSpeed"};
flightDatabb.InputName = {"tau_thrust","tau_roll","tau_pitch","tau_yaw"};

newDatabb = flightDatabb(145*25:358*25);
vDatabb = newDatabb(1:100*25);
eDatabb = newDatabb(101*25:end);
figure(1);
plot(eDatabb); 
figure(2);
tempw=[w1_new,w2_new,w3_new,w4_new]; 
timew = 1:length(w1_new);
plot(timew(260*25:264*25),tempw(260*25:264*25,:))