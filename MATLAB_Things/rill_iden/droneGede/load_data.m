clear
clc

% load data2.mat
load droneGede.mat

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
pwm_n1 = (pwm.Data(:,1)-900)/1100;
pwm_n2 = (pwm.Data(:,2)-900)/1100;
pwm_n3 = (pwm.Data(:,3)-900)/1100;
pwm_n4 = (pwm.Data(:,4)-900)/1100;

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
% y = 494.98*x + 304.12
% try implementing low pass filter

% Filtered PWM to rad/s
mReg= 670.227060933052;
cReg= -150.938615927672;

for i = 1:length(newPWM1)
    if newPWM1(i) <= 0.12
        w1(i) = 0;
    else  
        w1(i) = mReg*newPWM1(i) + cReg;
    end
end

for i = 1:length(newPWM2)
    if newPWM2(i) <= 0.12
        w2(i) = 0;
    else
        w2(i) = mReg*newPWM2(i) + cReg;
    end
end

for i = 1:length(newPWM3)
    if newPWM3(i) <= 0.12
        w3(i) = 0;
    else
        w3(i) = mReg*newPWM3(i) + cReg;
    end
end

for i = 1:length(newPWM4)
    if newPWM4(i) <= 0.12
        w4(i) = 0;
    else
        w4(i) = mReg*newPWM4(i) + cReg;
    end
end
%% Filtering
tc = 0.05;
tf1 = tf(1,[tc 1]);

% Filter the pwm value
filtered1 = lsim(tf1,w1',0.1*(1:length(w1))');
filtered2 = lsim(tf1,w2',0.1*(1:length(w2))');
filtered3 = lsim(tf1,w3',0.1*(1:length(w3))');
filtered4 = lsim(tf1,w4',0.1*(1:length(w4))');

% mixer shit
w1_new = filtered1;
w2_new = filtered2;
w3_new = filtered3;
w4_new = filtered4;

w = timeseries([w1_new,w2_new,w3_new,w4_new],timeIMU);
%% 
newAtt = resample(attitude,timeIMU);
%% Buat object data
% flightData = iddata([p,q,r],[w1_new,w2_new,w3_new,w4_new],0.04);
% flightData.OutputName = {"RollSpeed","PitchSpeed","YawSpeed"};
% flightData.InputName = {"Motor 1","Motor 2","Motor 3","Motor 4"};

%% Buat object data PWM -> pqr
flightData = iddata([p,q,r],[newPWM1,newPWM2,newPWM3,newPWM4],0.04);
flightData.OutputName = {"RollSpeed","PitchSpeed","YawSpeed"};
flightData.InputName = {"PWM 1","PWM 2","PWM 3","PWM 4"};

%% rad/s to Thrust 
% motor1 = ch2
% motor2 = ch3
% motor3 = ch4
% motor4 = ch1
mass = 1.371;
Ixx = 0.016887157; % Fixed 
Iyy = 0.016218129; % Fixed
Izz = 0.022727832; % Fixed
Krx = 0.01; % 0.0558 / 0.05
Kry = 0.01; % 0.0248 / 0.05
Krz = 0.01; % 0.0679 / 0.01
d = 0.215; % Fixed
ct = 9e-06; 
cm = 2.8856e-07; % iden: 5.3777e-08 / dari paper: 8e-8 % Fixed
Jr = 0.0032; % 0.0033

tau_thrust = ct*(w1_new.^2+w2_new.^2+w3_new.^2+w4_new.^2);
tau_roll = (sin(pi/4))*d*ct*(-w1_new.^2+w2_new.^2+w3_new.^2-w4_new.^2);
tau_pitch = (sin(pi/4))*d*ct*(w1_new.^2-w2_new.^2+w3_new.^2-w4_new.^2);
tau_yaw = cm*(w1_new.^2+w2_new.^2-w3_new.^2-w4_new.^2);

plot(tau_thrust)

% flightData_tau = iddata([p,q,r],[tau_roll,tau_pitch,tau_yaw],0.04);
% flightData_tau.OutputName = {"RollSpeed","PitchSpeed","YawSpeed"};
% flightData_tau.InputName = {"tau_roll","tau_pitch","tau_yaw"};

% newData = flightData_tau(145*25:358*25);
% vData = newData(1:100*25);
% eData = newData(101*25:end);
% %% Plotting 
% figure(1);
% plot(tau_roll); % corrcoef = -0.1879
% title('TauRoll vs RollSpeed');
% hold on
% plot(p)
% 
% hold off
% 
% figure(2);
% plot(tau_pitch); % corrcoef = -0.2247
% title('TauPitch vs PitchSpeed');
% hold on
% plot(q);
% hold off
% 
% figure(3);
% plot(tau_yaw); % corrcoef = 0.3218
% title('TauYaw vs YawSpeed');
% hold on
% plot(r);
% hold off;
% %%
% corrRoll = corrcoef(tau_roll, p, 'rows', 'complete')
% corrPitch = corrcoef(tau_pitch, q, 'rows', 'complete')
% corrYaw= corrcoef(tau_yaw, r, 'rows', 'complete')
% 
% %% Data Object buat Black Box 
% % Input: tau_roll, tau_pitch, tau_yaw
% % Output: p,q,r
% flightDatabb = iddata([p,q,r],[tau_thrust,tau_roll,tau_pitch,tau_yaw],0.04);
% flightDatabb.OutputName = {"RollSpeed","PitchSpeed","YawSpeed"};
% flightDatabb.InputName = {"tau_thrust","tau_roll","tau_pitch","tau_yaw"};
% 
% newDatabb = flightDatabb(145*25:358*25);
% vDatabb = newDatabb(1:100*25);
% eDatabb = newDatabb(101*25:end);
% figure(1);
% plot(eDatabb); 
% figure(2);
% tempw=[w1_new,w2_new,w3_new,w4_new]; 
% timew = 1:length(w1_new);
% plot(timew(260*25:264*25),tempw(260*25:264*25,:))