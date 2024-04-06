%% Coba SISO banyak
yawResponse = iddata(YawSpeed,tau_yaw,0.27);
yawResponse.InputName = 'tau_yaw';
yawResponse.OutputName = 'YawSpeed';

rollResponse = iddata(Roll,tau_roll,0.27);
rollResponse.InputName = 'tau_roll';
rollResponse.OutputName = 'roll';
%% Setting up the data
drone = iddata([Roll,Pitch,Yaw,RollSpeed,PitchSpeed,YawSpeed],[tau_roll,tau_pitch,tau_yaw],0.25);
drone.InputName = {'tau_roll','tau_pitch','tau_yaw'};
drone.OutputName = {'Roll','Pitch','Yaw','RollSpeed','PitchSpeed','YawSpeed'};

%% Test Data
testDrone = iddata([testRollSpeed,testPitchSpeed,testYawSpeed], ...
    [testTau_roll,testTau_pitch,testTau_yaw],0.27);
testDrone.InputName = {'tau_roll','tau_pitch','tau_yaw'};
testDrone.OutputName = {'RollSpeed','PitchSpeed','YawSpeed'};

%% Setting up the data 3 output
drone = iddata([RollSpeed,PitchSpeed,YawSpeed],[Motor1,Motor2,Motor3,Motor4],0.25);
drone.InputName = {'Motor1','Motor2','Motor3','Motor4'};
drone.OutputName = {'RollSpeed','PitchSpeed','YawSpeed'};

%% Test Data set input step 
rollDrone = drone(565:636);
rollDrone.InputName = {'tau_roll','tau_pitch','tau_yaw'};
rollDrone.OutputName = {'RollSpeed','PitchSpeed','YawSpeed'};

%% Test Data set input step 3 output
rollDrone = drone(565:636);
rollDrone.InputName = {'Motor1','Motor2','Motor3','Motor4'};
rollDrone.OutputName = {'RollSpeed','PitchSpeed','YawSpeed'};

%% Test Data set input step 
pitchDrone = drone(828:1018);
pitchDrone.InputName = {'Motor1','Motor2','Motor3','Motor4'};
pitchDrone.OutputName = {'Roll','Pitch','Yaw','RollSpeed','PitchSpeed','YawSpeed'};

%% Test Data set input step 3 output
pitchDrone = drone(828:1018);
pitchDrone.InputName = {'tau_roll','tau_pitch','tau_yaw'};
pitchDrone.OutputName = {'RollSpeed','PitchSpeed','YawSpeed'};

%% Test Data set input step 3 output
yawDrone = drone(435*4:535*4);
yawDrone.InputName = {'tau_roll','tau_pitch','tau_yaw'};
yawDrone.OutputName = {'RollSpeed','PitchSpeed','YawSpeed'};

%% Plotting
plot(drone)
%% Segmentasi data hanya pada saat terbang 
drone = drone(546:1360)

%% Segmentasi data train
trainDrone = drone(20*4:90*4)
trainDrone.InputName = {'tau_pitch','tau_roll','tau_yaw'};
trainDrone.OutputName =  {'Roll','Pitch','Yaw','RollSpeed','PitchSpeed','YawSpeed'};

%% Segmentasi data train 3 output
trainDrone = drone(1:407)
trainDrone.InputName = {'Motor1','Motor2','Motor3','Motor4'};
trainDrone.OutputName = {'RollSpeed','PitchSpeed','YawSpeed'};

%% Segmentasi data validasi
testDrone= drone(90*4:end)
testDrone.InputName = {'tau_roll','tau_pitch','tau_yaw'};
testDrone.OutputName = {'Roll','Pitch','Yaw','RollSpeed','PitchSpeed','YawSpeed'};

%% Segmentasi data validasi
% testDrone= drone(408:end)
sysdis2.InputName = {'tau_roll','tau_pitch','tau_yaw'};
sysdis2.OutputName = {'RollSpeed','PitchSpeed','YawSpeed'};

%% convert dari pwm ke thrust
thrust2pwm = [1 -1 1 1;1 1 -1 1; 1 1 1 -1;1 -1 -1 -1];
pwm2thrust = inv(thrust2pwm);
motor = [motor1PWM';motor2PWM';motor3PWM';motor4PWM'];
thrust = pwm2thrust * motor;

tau_thrust = (thrust(1,:))';
tau_roll = (thrust(2,:))';
tau_pitch = (thrust(3,:))';
tau_yaw = (thrust(4,:))';

%% 💀🙏
motor1PWM = motor1PWM(:,2);
motor2PWM = motor2PWM(:,2);
motor3PWM = motor3PWM(:,2);
motor4PWM = motor4PWM(:,2);

%% Convert dari thrust ke pwm
thrust = [tau_thrust';tau_roll';tau_pitch';tau_yaw'];
thrust2pwm = [1 -1 1 1;1 1 -1 1; 1 1 1 -1;1 -1 -1 -1];

pwm = thrust2pwm * thrust;
pwm1 = (pwm(1,:))';
pwm2 = (pwm(2,:))';
pwm3 = (pwm(3,:))';
pwm4 = (pwm(4,:))'