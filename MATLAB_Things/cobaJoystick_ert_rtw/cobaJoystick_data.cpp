//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: cobaJoystick_data.cpp
//
// Code generated for Simulink model 'cobaJoystick'.
//
// Model version                  : 1.3
// Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
// C/C++ source code generated on : Thu Mar  7 11:25:05 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "cobaJoystick.h"

// Block parameters (default storage)
P_cobaJoystick_T cobaJoystick_P = {
  // Mask Parameter: PID_pitch_D
  //  Referenced by: '<S36>/Derivative Gain'

  0.0145948093220339,

  // Mask Parameter: PID_roll_D
  //  Referenced by: '<S84>/Derivative Gain'

  0.015,

  // Mask Parameter: PID_yaw_rate_D
  //  Referenced by: '<S132>/Derivative Gain'

  0.0,

  // Mask Parameter: PID_pitch_I
  //  Referenced by: '<S39>/Integral Gain'

  0.005,

  // Mask Parameter: PID_roll_I
  //  Referenced by: '<S87>/Integral Gain'

  0.005,

  // Mask Parameter: PID_yaw_rate_I
  //  Referenced by: '<S135>/Integral Gain'

  0.001,

  // Mask Parameter: PID_pitch_InitialConditionForFi
  //  Referenced by: '<S37>/Filter'

  0.0,

  // Mask Parameter: PID_roll_InitialConditionForFil
  //  Referenced by: '<S85>/Filter'

  0.0,

  // Mask Parameter: PID_yaw_rate_InitialConditionFo
  //  Referenced by: '<S133>/Filter'

  0.0,

  // Mask Parameter: PID_pitch_InitialConditionForIn
  //  Referenced by: '<S42>/Integrator'

  0.0,

  // Mask Parameter: PID_roll_InitialConditionForInt
  //  Referenced by: '<S90>/Integrator'

  0.0,

  // Mask Parameter: PID_yaw_rate_InitialCondition_l
  //  Referenced by: '<S138>/Integrator'

  0.0,

  // Mask Parameter: PID_pitch_LowerSaturationLimit
  //  Referenced by: '<S49>/Saturation'

  -0.05,

  // Mask Parameter: PID_roll_LowerSaturationLimit
  //  Referenced by: '<S97>/Saturation'

  -0.05,

  // Mask Parameter: PID_yaw_rate_LowerSaturationLim
  //  Referenced by: '<S145>/Saturation'

  -0.1,

  // Mask Parameter: PID_pitch_N
  //  Referenced by: '<S45>/Filter Coefficient'

  50.0,

  // Mask Parameter: PID_roll_N
  //  Referenced by: '<S93>/Filter Coefficient'

  50.0,

  // Mask Parameter: PID_yaw_rate_N
  //  Referenced by: '<S141>/Filter Coefficient'

  50.0,

  // Mask Parameter: PID_pitch_P
  //  Referenced by: '<S47>/Proportional Gain'

  0.027,

  // Mask Parameter: PID_roll_P
  //  Referenced by: '<S95>/Proportional Gain'

  0.03,

  // Mask Parameter: PID_yaw_rate_P
  //  Referenced by: '<S143>/Proportional Gain'

  0.2,

  // Mask Parameter: PID_pitch_UpperSaturationLimit
  //  Referenced by: '<S49>/Saturation'

  0.05,

  // Mask Parameter: PID_roll_UpperSaturationLimit
  //  Referenced by: '<S97>/Saturation'

  0.05,

  // Mask Parameter: PID_yaw_rate_UpperSaturationLim
  //  Referenced by: '<S145>/Saturation'

  0.1,

  // Computed Parameter: Out1_Y0
  //  Referenced by: '<S155>/Out1'

  {
    (0ULL),                            // timestamp
    (0ULL),                            // timestamp_sample
    0.0F,                              // x
    0.0F,                              // y
    0.0F,                              // z

    {
      0.0F, 0.0F, 0.0F, 0.0F }
    ,                                  // q

    {
      0.0F, 0.0F, 0.0F, 0.0F }
    ,                                  // q_offset

    {
      0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
      0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F }
    ,                                  // pose_covariance
    0.0F,                              // vx
    0.0F,                              // vy
    0.0F,                              // vz
    0.0F,                              // rollspeed
    0.0F,                              // pitchspeed
    0.0F,                              // yawspeed

    {
      0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
      0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F }
    ,                                  // velocity_covariance
    0U,                                // local_frame
    0U,                                // velocity_frame

    {
      0U, 0U }
    // _padding0
  },

  // Computed Parameter: Constant_Value
  //  Referenced by: '<S2>/Constant'

  {
    (0ULL),                            // timestamp
    (0ULL),                            // timestamp_sample
    0.0F,                              // x
    0.0F,                              // y
    0.0F,                              // z

    {
      0.0F, 0.0F, 0.0F, 0.0F }
    ,                                  // q

    {
      0.0F, 0.0F, 0.0F, 0.0F }
    ,                                  // q_offset

    {
      0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
      0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F }
    ,                                  // pose_covariance
    0.0F,                              // vx
    0.0F,                              // vy
    0.0F,                              // vz
    0.0F,                              // rollspeed
    0.0F,                              // pitchspeed
    0.0F,                              // yawspeed

    {
      0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
      0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F }
    ,                                  // velocity_covariance
    0U,                                // local_frame
    0U,                                // velocity_frame

    {
      0U, 0U }
    // _padding0
  },

  // Computed Parameter: Out1_Y0_p
  //  Referenced by: '<S156>/Out1'

  {
    (0ULL),                            // timestamp
    (0ULL),                            // timestamp_sample
    0.0F,                              // x
    0.0F,                              // y
    0.0F,                              // z
    0.0F,                              // r
    0.0F,                              // flaps
    0.0F,                              // aux1
    0.0F,                              // aux2
    0.0F,                              // aux3
    0.0F,                              // aux4
    0.0F,                              // aux5
    0.0F,                              // aux6
    0U,                                // data_source

    {
      0U, 0U, 0U }
    // _padding0
  },

  // Computed Parameter: Constant_Value_h
  //  Referenced by: '<S3>/Constant'

  {
    (0ULL),                            // timestamp
    (0ULL),                            // timestamp_sample
    0.0F,                              // x
    0.0F,                              // y
    0.0F,                              // z
    0.0F,                              // r
    0.0F,                              // flaps
    0.0F,                              // aux1
    0.0F,                              // aux2
    0.0F,                              // aux3
    0.0F,                              // aux4
    0.0F,                              // aux5
    0.0F,                              // aux6
    0U,                                // data_source

    {
      0U, 0U, 0U }
    // _padding0
  },

  // Computed Parameter: Out1_Y0_k
  //  Referenced by: '<S166>/Out1'

  {
    (0ULL),                            // timestamp
    false,                             // armed
    false,                             // prearmed
    false,                             // ready_to_arm
    false,                             // lockdown
    false,                             // manual_lockdown
    false,                             // force_failsafe
    false,                             // in_esc_calibration_mode
    false                              // soft_stop
  },

  // Computed Parameter: Constant_Value_c
  //  Referenced by: '<S165>/Constant'

  {
    (0ULL),                            // timestamp
    false,                             // armed
    false,                             // prearmed
    false,                             // ready_to_arm
    false,                             // lockdown
    false,                             // manual_lockdown
    false,                             // force_failsafe
    false,                             // in_esc_calibration_mode
    false                              // soft_stop
  },

  // Expression: 1
  //  Referenced by: '<S160>/Constant'

  1.0,

  // Expression: 1
  //  Referenced by: '<S161>/Constant'

  1.0,

  // Expression: [1 -1 1 1;1 1 -1 1;1 -1 -1 -1;1 1 1 -1]
  //  Referenced by: '<S5>/Mixer matrix'

  { 1.0, 1.0, 1.0, 1.0, -1.0, 1.0, -1.0, 1.0, 1.0, -1.0, -1.0, 1.0, 1.0, 1.0,
    -1.0, -1.0 },

  // Expression: 1
  //  Referenced by: '<S5>/Constant'

  1.0,

  // Computed Parameter: Integrator_gainval
  //  Referenced by: '<S42>/Integrator'

  0.2,

  // Computed Parameter: Filter_gainval
  //  Referenced by: '<S37>/Filter'

  0.2,

  // Computed Parameter: Integrator_gainval_e
  //  Referenced by: '<S90>/Integrator'

  0.2,

  // Computed Parameter: Filter_gainval_j
  //  Referenced by: '<S85>/Filter'

  0.2,

  // Computed Parameter: Integrator_gainval_b
  //  Referenced by: '<S138>/Integrator'

  0.2,

  // Computed Parameter: Filter_gainval_i
  //  Referenced by: '<S133>/Filter'

  0.2,

  // Expression: 1000
  //  Referenced by: '<S5>/Gain1'

  1000.0,

  // Computed Parameter: Deadband_Start
  //  Referenced by: '<Root>/Deadband'

  -0.05F,

  // Computed Parameter: Deadband_End
  //  Referenced by: '<Root>/Deadband'

  0.05F,

  // Computed Parameter: Gain_Gain
  //  Referenced by: '<S1>/Gain'

  50.0F,

  // Computed Parameter: Gain1_Gain_n
  //  Referenced by: '<S6>/Gain1'

  0.0174532924F,

  // Computed Parameter: Deadband1_Start
  //  Referenced by: '<Root>/Deadband1'

  -0.05F,

  // Computed Parameter: Deadband1_End
  //  Referenced by: '<Root>/Deadband1'

  0.05F,

  // Computed Parameter: Gain1_Gain_g
  //  Referenced by: '<S1>/Gain1'

  -50.0F,

  // Computed Parameter: Gain1_Gain_c
  //  Referenced by: '<S7>/Gain1'

  0.0174532924F,

  // Computed Parameter: Deadband2_Start
  //  Referenced by: '<Root>/Deadband2'

  -0.05F,

  // Computed Parameter: Deadband2_End
  //  Referenced by: '<Root>/Deadband2'

  0.05F,

  // Computed Parameter: Reset_Value
  //  Referenced by: '<S5>/Reset'

  false
};

//
// File trailer for generated code.
//
// [EOF]
//
