//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: cobaJoystick.h
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
#ifndef RTW_HEADER_cobaJoystick_h_
#define RTW_HEADER_cobaJoystick_h_
#include <poll.h>
#include <uORB/uORB.h>
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "MW_uORB_Read.h"
#include "MW_PX4_PWM.h"
#include "cobaJoystick_types.h"
#include <uORB/topics/vehicle_odometry.h>
#include <uORB/topics/manual_control_setpoint.h>
#include <uORB/topics/actuator_armed.h>

extern "C"
{

#include "rtGetNaN.h"

}

extern "C"
{

#include "rt_nonfinite.h"

}

#include <stddef.h>

// Macros for accessing real-time model data structure
#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWExtModeInfo
#define rtmGetRTWExtModeInfo(rtm)      ((rtm)->extModeInfo)
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   ((rtm)->Timing.taskTime0)
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                (&(rtm)->Timing.taskTime0)
#endif

// Block signals (default storage)
struct B_cobaJoystick_T {
  px4_Bus_vehicle_odometry In1;        // '<S155>/In1'
  px4_Bus_vehicle_odometry b_varargout_2;
  px4_Bus_manual_control_setpoint In1_p;// '<S156>/In1'
  px4_Bus_manual_control_setpoint b_varargout_2_m;
  uint16_T pwmValue[8];
  px4_Bus_actuator_armed In1_f;        // '<S166>/In1'
  px4_Bus_actuator_armed b_varargout_2_c;
  real_T Saturation_l;                 // '<S145>/Saturation'
  real_T Filter;                       // '<S133>/Filter'
  real_T Saturation_f;                 // '<S97>/Saturation'
  real_T Filter_o;                     // '<S85>/Filter'
  real32_T z;   // '<Root>/SigConversion_InsertedFor_Bus Selector_at_outport_0'
  real32_T x;   // '<Root>/SigConversion_InsertedFor_Bus Selector_at_outport_1'
  real32_T y;   // '<Root>/SigConversion_InsertedFor_Bus Selector_at_outport_2'
  real32_T r;   // '<Root>/SigConversion_InsertedFor_Bus Selector_at_outport_3'
  boolean_T armed;// '<S5>/SigConversion_InsertedFor_Bus Selector_at_outport_0'
  boolean_T NOT;                       // '<S2>/NOT'
  boolean_T NOT_b;                     // '<S3>/NOT'
};

// Block states (default storage) for system '<Root>'
struct DW_cobaJoystick_T {
  px4_internal_block_Subscriber_T obj; // '<S165>/SourceBlock'
  px4_internal_block_Subscriber_T obj_o;// '<S3>/SourceBlock'
  px4_internal_block_Subscriber_T obj_d;// '<S2>/SourceBlock'
  px4_internal_block_PWM_cobaJo_T obj_l;// '<S5>/PX4 PWM Output'
  real_T Integrator_DSTATE;            // '<S42>/Integrator'
  real_T Filter_DSTATE;                // '<S37>/Filter'
  real_T Integrator_DSTATE_m;          // '<S90>/Integrator'
  real_T Filter_DSTATE_d;              // '<S85>/Filter'
  real_T Integrator_DSTATE_i;          // '<S138>/Integrator'
  real_T Filter_DSTATE_k;              // '<S133>/Filter'
  int8_T EnabledSubsystem_SubsysRanBC; // '<S165>/Enabled Subsystem'
  int8_T IfActionSubsystem2_SubsysRanBC;// '<S159>/If Action Subsystem2'
  int8_T IfActionSubsystem1_SubsysRanBC;// '<S159>/If Action Subsystem1'
  int8_T IfActionSubsystem_SubsysRanBC;// '<S159>/If Action Subsystem'
  int8_T EnabledSubsystem_SubsysRanBC_g;// '<S3>/Enabled Subsystem'
  int8_T EnabledSubsystem_SubsysRanBC_gz;// '<S2>/Enabled Subsystem'
};

// Parameters (default storage)
struct P_cobaJoystick_T_ {
  real_T PID_pitch_D;                  // Mask Parameter: PID_pitch_D
                                          //  Referenced by: '<S36>/Derivative Gain'

  real_T PID_roll_D;                   // Mask Parameter: PID_roll_D
                                          //  Referenced by: '<S84>/Derivative Gain'

  real_T PID_yaw_rate_D;               // Mask Parameter: PID_yaw_rate_D
                                          //  Referenced by: '<S132>/Derivative Gain'

  real_T PID_pitch_I;                  // Mask Parameter: PID_pitch_I
                                          //  Referenced by: '<S39>/Integral Gain'

  real_T PID_roll_I;                   // Mask Parameter: PID_roll_I
                                          //  Referenced by: '<S87>/Integral Gain'

  real_T PID_yaw_rate_I;               // Mask Parameter: PID_yaw_rate_I
                                          //  Referenced by: '<S135>/Integral Gain'

  real_T PID_pitch_InitialConditionForFi;
                              // Mask Parameter: PID_pitch_InitialConditionForFi
                                 //  Referenced by: '<S37>/Filter'

  real_T PID_roll_InitialConditionForFil;
                              // Mask Parameter: PID_roll_InitialConditionForFil
                                 //  Referenced by: '<S85>/Filter'

  real_T PID_yaw_rate_InitialConditionFo;
                              // Mask Parameter: PID_yaw_rate_InitialConditionFo
                                 //  Referenced by: '<S133>/Filter'

  real_T PID_pitch_InitialConditionForIn;
                              // Mask Parameter: PID_pitch_InitialConditionForIn
                                 //  Referenced by: '<S42>/Integrator'

  real_T PID_roll_InitialConditionForInt;
                              // Mask Parameter: PID_roll_InitialConditionForInt
                                 //  Referenced by: '<S90>/Integrator'

  real_T PID_yaw_rate_InitialCondition_l;
                              // Mask Parameter: PID_yaw_rate_InitialCondition_l
                                 //  Referenced by: '<S138>/Integrator'

  real_T PID_pitch_LowerSaturationLimit;
                               // Mask Parameter: PID_pitch_LowerSaturationLimit
                                  //  Referenced by: '<S49>/Saturation'

  real_T PID_roll_LowerSaturationLimit;
                                // Mask Parameter: PID_roll_LowerSaturationLimit
                                   //  Referenced by: '<S97>/Saturation'

  real_T PID_yaw_rate_LowerSaturationLim;
                              // Mask Parameter: PID_yaw_rate_LowerSaturationLim
                                 //  Referenced by: '<S145>/Saturation'

  real_T PID_pitch_N;                  // Mask Parameter: PID_pitch_N
                                          //  Referenced by: '<S45>/Filter Coefficient'

  real_T PID_roll_N;                   // Mask Parameter: PID_roll_N
                                          //  Referenced by: '<S93>/Filter Coefficient'

  real_T PID_yaw_rate_N;               // Mask Parameter: PID_yaw_rate_N
                                          //  Referenced by: '<S141>/Filter Coefficient'

  real_T PID_pitch_P;                  // Mask Parameter: PID_pitch_P
                                          //  Referenced by: '<S47>/Proportional Gain'

  real_T PID_roll_P;                   // Mask Parameter: PID_roll_P
                                          //  Referenced by: '<S95>/Proportional Gain'

  real_T PID_yaw_rate_P;               // Mask Parameter: PID_yaw_rate_P
                                          //  Referenced by: '<S143>/Proportional Gain'

  real_T PID_pitch_UpperSaturationLimit;
                               // Mask Parameter: PID_pitch_UpperSaturationLimit
                                  //  Referenced by: '<S49>/Saturation'

  real_T PID_roll_UpperSaturationLimit;
                                // Mask Parameter: PID_roll_UpperSaturationLimit
                                   //  Referenced by: '<S97>/Saturation'

  real_T PID_yaw_rate_UpperSaturationLim;
                              // Mask Parameter: PID_yaw_rate_UpperSaturationLim
                                 //  Referenced by: '<S145>/Saturation'

  px4_Bus_vehicle_odometry Out1_Y0;    // Computed Parameter: Out1_Y0
                                          //  Referenced by: '<S155>/Out1'

  px4_Bus_vehicle_odometry Constant_Value;// Computed Parameter: Constant_Value
                                             //  Referenced by: '<S2>/Constant'

  px4_Bus_manual_control_setpoint Out1_Y0_p;// Computed Parameter: Out1_Y0_p
                                               //  Referenced by: '<S156>/Out1'

  px4_Bus_manual_control_setpoint Constant_Value_h;// Computed Parameter: Constant_Value_h
                                                      //  Referenced by: '<S3>/Constant'

  px4_Bus_actuator_armed Out1_Y0_k;    // Computed Parameter: Out1_Y0_k
                                          //  Referenced by: '<S166>/Out1'

  px4_Bus_actuator_armed Constant_Value_c;// Computed Parameter: Constant_Value_c
                                             //  Referenced by: '<S165>/Constant'

  real_T Constant_Value_l;             // Expression: 1
                                          //  Referenced by: '<S160>/Constant'

  real_T Constant_Value_i;             // Expression: 1
                                          //  Referenced by: '<S161>/Constant'

  real_T Mixermatrix_Value[16];
                          // Expression: [1 -1 1 1;1 1 -1 1;1 -1 -1 -1;1 1 1 -1]
                             //  Referenced by: '<S5>/Mixer matrix'

  real_T Constant_Value_cv;            // Expression: 1
                                          //  Referenced by: '<S5>/Constant'

  real_T Integrator_gainval;           // Computed Parameter: Integrator_gainval
                                          //  Referenced by: '<S42>/Integrator'

  real_T Filter_gainval;               // Computed Parameter: Filter_gainval
                                          //  Referenced by: '<S37>/Filter'

  real_T Integrator_gainval_e;       // Computed Parameter: Integrator_gainval_e
                                        //  Referenced by: '<S90>/Integrator'

  real_T Filter_gainval_j;             // Computed Parameter: Filter_gainval_j
                                          //  Referenced by: '<S85>/Filter'

  real_T Integrator_gainval_b;       // Computed Parameter: Integrator_gainval_b
                                        //  Referenced by: '<S138>/Integrator'

  real_T Filter_gainval_i;             // Computed Parameter: Filter_gainval_i
                                          //  Referenced by: '<S133>/Filter'

  real_T Gain1_Gain;                   // Expression: 1000
                                          //  Referenced by: '<S5>/Gain1'

  real32_T Deadband_Start;             // Computed Parameter: Deadband_Start
                                          //  Referenced by: '<Root>/Deadband'

  real32_T Deadband_End;               // Computed Parameter: Deadband_End
                                          //  Referenced by: '<Root>/Deadband'

  real32_T Gain_Gain;                  // Computed Parameter: Gain_Gain
                                          //  Referenced by: '<S1>/Gain'

  real32_T Gain1_Gain_n;               // Computed Parameter: Gain1_Gain_n
                                          //  Referenced by: '<S6>/Gain1'

  real32_T Deadband1_Start;            // Computed Parameter: Deadband1_Start
                                          //  Referenced by: '<Root>/Deadband1'

  real32_T Deadband1_End;              // Computed Parameter: Deadband1_End
                                          //  Referenced by: '<Root>/Deadband1'

  real32_T Gain1_Gain_g;               // Computed Parameter: Gain1_Gain_g
                                          //  Referenced by: '<S1>/Gain1'

  real32_T Gain1_Gain_c;               // Computed Parameter: Gain1_Gain_c
                                          //  Referenced by: '<S7>/Gain1'

  real32_T Deadband2_Start;            // Computed Parameter: Deadband2_Start
                                          //  Referenced by: '<Root>/Deadband2'

  real32_T Deadband2_End;              // Computed Parameter: Deadband2_End
                                          //  Referenced by: '<Root>/Deadband2'

  boolean_T Reset_Value;               // Computed Parameter: Reset_Value
                                          //  Referenced by: '<S5>/Reset'

};

// Real-time Model Data Structure
struct tag_RTM_cobaJoystick_T {
  const char_T *errorStatus;
  RTWExtModeInfo *extModeInfo;

  //
  //  Sizes:
  //  The following substructure contains sizes information
  //  for many of the model attributes such as inputs, outputs,
  //  dwork, sample times, etc.

  struct {
    uint32_T checksums[4];
  } Sizes;

  //
  //  SpecialInfo:
  //  The following substructure contains special information
  //  related to other components that are dependent on RTW.

  struct {
    const void *mappingInfo;
  } SpecialInfo;

  //
  //  Timing:
  //  The following substructure contains information regarding
  //  the timing information for the model.

  struct {
    time_T taskTime0;
    uint32_T clockTick0;
    time_T stepSize0;
    time_T tFinal;
    boolean_T stopRequestedFlag;
  } Timing;
};

// Block parameters (default storage)
#ifdef __cplusplus

extern "C"
{

#endif

  extern P_cobaJoystick_T cobaJoystick_P;

#ifdef __cplusplus

}

#endif

// Block signals (default storage)
#ifdef __cplusplus

extern "C"
{

#endif

  extern struct B_cobaJoystick_T cobaJoystick_B;

#ifdef __cplusplus

}

#endif

// Block states (default storage)
extern struct DW_cobaJoystick_T cobaJoystick_DW;

#ifdef __cplusplus

extern "C"
{

#endif

  // Model entry point functions
  extern void cobaJoystick_initialize(void);
  extern void cobaJoystick_step(void);
  extern void cobaJoystick_terminate(void);

#ifdef __cplusplus

}

#endif

// Real-time Model object
#ifdef __cplusplus

extern "C"
{

#endif

  extern RT_MODEL_cobaJoystick_T *const cobaJoystick_M;

#ifdef __cplusplus

}

#endif

extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S165>/NOT' : Unused code path elimination


//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'cobaJoystick'
//  '<S1>'   : 'cobaJoystick/Attitude controller'
//  '<S2>'   : 'cobaJoystick/PX4 uORB Read1'
//  '<S3>'   : 'cobaJoystick/PX4 uORB Read2'
//  '<S4>'   : 'cobaJoystick/Quaternions to Rotation Angles'
//  '<S5>'   : 'cobaJoystick/To Actuator'
//  '<S6>'   : 'cobaJoystick/Attitude controller/Degrees to Radians1'
//  '<S7>'   : 'cobaJoystick/Attitude controller/Degrees to Radians2'
//  '<S8>'   : 'cobaJoystick/Attitude controller/PID_pitch'
//  '<S9>'   : 'cobaJoystick/Attitude controller/PID_roll'
//  '<S10>'  : 'cobaJoystick/Attitude controller/PID_yaw_rate'
//  '<S11>'  : 'cobaJoystick/Attitude controller/PID_pitch/Anti-windup'
//  '<S12>'  : 'cobaJoystick/Attitude controller/PID_pitch/D Gain'
//  '<S13>'  : 'cobaJoystick/Attitude controller/PID_pitch/Filter'
//  '<S14>'  : 'cobaJoystick/Attitude controller/PID_pitch/Filter ICs'
//  '<S15>'  : 'cobaJoystick/Attitude controller/PID_pitch/I Gain'
//  '<S16>'  : 'cobaJoystick/Attitude controller/PID_pitch/Ideal P Gain'
//  '<S17>'  : 'cobaJoystick/Attitude controller/PID_pitch/Ideal P Gain Fdbk'
//  '<S18>'  : 'cobaJoystick/Attitude controller/PID_pitch/Integrator'
//  '<S19>'  : 'cobaJoystick/Attitude controller/PID_pitch/Integrator ICs'
//  '<S20>'  : 'cobaJoystick/Attitude controller/PID_pitch/N Copy'
//  '<S21>'  : 'cobaJoystick/Attitude controller/PID_pitch/N Gain'
//  '<S22>'  : 'cobaJoystick/Attitude controller/PID_pitch/P Copy'
//  '<S23>'  : 'cobaJoystick/Attitude controller/PID_pitch/Parallel P Gain'
//  '<S24>'  : 'cobaJoystick/Attitude controller/PID_pitch/Reset Signal'
//  '<S25>'  : 'cobaJoystick/Attitude controller/PID_pitch/Saturation'
//  '<S26>'  : 'cobaJoystick/Attitude controller/PID_pitch/Saturation Fdbk'
//  '<S27>'  : 'cobaJoystick/Attitude controller/PID_pitch/Sum'
//  '<S28>'  : 'cobaJoystick/Attitude controller/PID_pitch/Sum Fdbk'
//  '<S29>'  : 'cobaJoystick/Attitude controller/PID_pitch/Tracking Mode'
//  '<S30>'  : 'cobaJoystick/Attitude controller/PID_pitch/Tracking Mode Sum'
//  '<S31>'  : 'cobaJoystick/Attitude controller/PID_pitch/Tsamp - Integral'
//  '<S32>'  : 'cobaJoystick/Attitude controller/PID_pitch/Tsamp - Ngain'
//  '<S33>'  : 'cobaJoystick/Attitude controller/PID_pitch/postSat Signal'
//  '<S34>'  : 'cobaJoystick/Attitude controller/PID_pitch/preSat Signal'
//  '<S35>'  : 'cobaJoystick/Attitude controller/PID_pitch/Anti-windup/Passthrough'
//  '<S36>'  : 'cobaJoystick/Attitude controller/PID_pitch/D Gain/Internal Parameters'
//  '<S37>'  : 'cobaJoystick/Attitude controller/PID_pitch/Filter/Disc. Forward Euler Filter'
//  '<S38>'  : 'cobaJoystick/Attitude controller/PID_pitch/Filter ICs/Internal IC - Filter'
//  '<S39>'  : 'cobaJoystick/Attitude controller/PID_pitch/I Gain/Internal Parameters'
//  '<S40>'  : 'cobaJoystick/Attitude controller/PID_pitch/Ideal P Gain/Passthrough'
//  '<S41>'  : 'cobaJoystick/Attitude controller/PID_pitch/Ideal P Gain Fdbk/Disabled'
//  '<S42>'  : 'cobaJoystick/Attitude controller/PID_pitch/Integrator/Discrete'
//  '<S43>'  : 'cobaJoystick/Attitude controller/PID_pitch/Integrator ICs/Internal IC'
//  '<S44>'  : 'cobaJoystick/Attitude controller/PID_pitch/N Copy/Disabled'
//  '<S45>'  : 'cobaJoystick/Attitude controller/PID_pitch/N Gain/Internal Parameters'
//  '<S46>'  : 'cobaJoystick/Attitude controller/PID_pitch/P Copy/Disabled'
//  '<S47>'  : 'cobaJoystick/Attitude controller/PID_pitch/Parallel P Gain/Internal Parameters'
//  '<S48>'  : 'cobaJoystick/Attitude controller/PID_pitch/Reset Signal/Disabled'
//  '<S49>'  : 'cobaJoystick/Attitude controller/PID_pitch/Saturation/Enabled'
//  '<S50>'  : 'cobaJoystick/Attitude controller/PID_pitch/Saturation Fdbk/Disabled'
//  '<S51>'  : 'cobaJoystick/Attitude controller/PID_pitch/Sum/Sum_PID'
//  '<S52>'  : 'cobaJoystick/Attitude controller/PID_pitch/Sum Fdbk/Disabled'
//  '<S53>'  : 'cobaJoystick/Attitude controller/PID_pitch/Tracking Mode/Disabled'
//  '<S54>'  : 'cobaJoystick/Attitude controller/PID_pitch/Tracking Mode Sum/Passthrough'
//  '<S55>'  : 'cobaJoystick/Attitude controller/PID_pitch/Tsamp - Integral/TsSignalSpecification'
//  '<S56>'  : 'cobaJoystick/Attitude controller/PID_pitch/Tsamp - Ngain/Passthrough'
//  '<S57>'  : 'cobaJoystick/Attitude controller/PID_pitch/postSat Signal/Forward_Path'
//  '<S58>'  : 'cobaJoystick/Attitude controller/PID_pitch/preSat Signal/Forward_Path'
//  '<S59>'  : 'cobaJoystick/Attitude controller/PID_roll/Anti-windup'
//  '<S60>'  : 'cobaJoystick/Attitude controller/PID_roll/D Gain'
//  '<S61>'  : 'cobaJoystick/Attitude controller/PID_roll/Filter'
//  '<S62>'  : 'cobaJoystick/Attitude controller/PID_roll/Filter ICs'
//  '<S63>'  : 'cobaJoystick/Attitude controller/PID_roll/I Gain'
//  '<S64>'  : 'cobaJoystick/Attitude controller/PID_roll/Ideal P Gain'
//  '<S65>'  : 'cobaJoystick/Attitude controller/PID_roll/Ideal P Gain Fdbk'
//  '<S66>'  : 'cobaJoystick/Attitude controller/PID_roll/Integrator'
//  '<S67>'  : 'cobaJoystick/Attitude controller/PID_roll/Integrator ICs'
//  '<S68>'  : 'cobaJoystick/Attitude controller/PID_roll/N Copy'
//  '<S69>'  : 'cobaJoystick/Attitude controller/PID_roll/N Gain'
//  '<S70>'  : 'cobaJoystick/Attitude controller/PID_roll/P Copy'
//  '<S71>'  : 'cobaJoystick/Attitude controller/PID_roll/Parallel P Gain'
//  '<S72>'  : 'cobaJoystick/Attitude controller/PID_roll/Reset Signal'
//  '<S73>'  : 'cobaJoystick/Attitude controller/PID_roll/Saturation'
//  '<S74>'  : 'cobaJoystick/Attitude controller/PID_roll/Saturation Fdbk'
//  '<S75>'  : 'cobaJoystick/Attitude controller/PID_roll/Sum'
//  '<S76>'  : 'cobaJoystick/Attitude controller/PID_roll/Sum Fdbk'
//  '<S77>'  : 'cobaJoystick/Attitude controller/PID_roll/Tracking Mode'
//  '<S78>'  : 'cobaJoystick/Attitude controller/PID_roll/Tracking Mode Sum'
//  '<S79>'  : 'cobaJoystick/Attitude controller/PID_roll/Tsamp - Integral'
//  '<S80>'  : 'cobaJoystick/Attitude controller/PID_roll/Tsamp - Ngain'
//  '<S81>'  : 'cobaJoystick/Attitude controller/PID_roll/postSat Signal'
//  '<S82>'  : 'cobaJoystick/Attitude controller/PID_roll/preSat Signal'
//  '<S83>'  : 'cobaJoystick/Attitude controller/PID_roll/Anti-windup/Passthrough'
//  '<S84>'  : 'cobaJoystick/Attitude controller/PID_roll/D Gain/Internal Parameters'
//  '<S85>'  : 'cobaJoystick/Attitude controller/PID_roll/Filter/Disc. Forward Euler Filter'
//  '<S86>'  : 'cobaJoystick/Attitude controller/PID_roll/Filter ICs/Internal IC - Filter'
//  '<S87>'  : 'cobaJoystick/Attitude controller/PID_roll/I Gain/Internal Parameters'
//  '<S88>'  : 'cobaJoystick/Attitude controller/PID_roll/Ideal P Gain/Passthrough'
//  '<S89>'  : 'cobaJoystick/Attitude controller/PID_roll/Ideal P Gain Fdbk/Disabled'
//  '<S90>'  : 'cobaJoystick/Attitude controller/PID_roll/Integrator/Discrete'
//  '<S91>'  : 'cobaJoystick/Attitude controller/PID_roll/Integrator ICs/Internal IC'
//  '<S92>'  : 'cobaJoystick/Attitude controller/PID_roll/N Copy/Disabled'
//  '<S93>'  : 'cobaJoystick/Attitude controller/PID_roll/N Gain/Internal Parameters'
//  '<S94>'  : 'cobaJoystick/Attitude controller/PID_roll/P Copy/Disabled'
//  '<S95>'  : 'cobaJoystick/Attitude controller/PID_roll/Parallel P Gain/Internal Parameters'
//  '<S96>'  : 'cobaJoystick/Attitude controller/PID_roll/Reset Signal/Disabled'
//  '<S97>'  : 'cobaJoystick/Attitude controller/PID_roll/Saturation/Enabled'
//  '<S98>'  : 'cobaJoystick/Attitude controller/PID_roll/Saturation Fdbk/Disabled'
//  '<S99>'  : 'cobaJoystick/Attitude controller/PID_roll/Sum/Sum_PID'
//  '<S100>' : 'cobaJoystick/Attitude controller/PID_roll/Sum Fdbk/Disabled'
//  '<S101>' : 'cobaJoystick/Attitude controller/PID_roll/Tracking Mode/Disabled'
//  '<S102>' : 'cobaJoystick/Attitude controller/PID_roll/Tracking Mode Sum/Passthrough'
//  '<S103>' : 'cobaJoystick/Attitude controller/PID_roll/Tsamp - Integral/TsSignalSpecification'
//  '<S104>' : 'cobaJoystick/Attitude controller/PID_roll/Tsamp - Ngain/Passthrough'
//  '<S105>' : 'cobaJoystick/Attitude controller/PID_roll/postSat Signal/Forward_Path'
//  '<S106>' : 'cobaJoystick/Attitude controller/PID_roll/preSat Signal/Forward_Path'
//  '<S107>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/Anti-windup'
//  '<S108>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/D Gain'
//  '<S109>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/Filter'
//  '<S110>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/Filter ICs'
//  '<S111>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/I Gain'
//  '<S112>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/Ideal P Gain'
//  '<S113>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/Ideal P Gain Fdbk'
//  '<S114>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/Integrator'
//  '<S115>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/Integrator ICs'
//  '<S116>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/N Copy'
//  '<S117>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/N Gain'
//  '<S118>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/P Copy'
//  '<S119>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/Parallel P Gain'
//  '<S120>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/Reset Signal'
//  '<S121>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/Saturation'
//  '<S122>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/Saturation Fdbk'
//  '<S123>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/Sum'
//  '<S124>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/Sum Fdbk'
//  '<S125>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/Tracking Mode'
//  '<S126>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/Tracking Mode Sum'
//  '<S127>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/Tsamp - Integral'
//  '<S128>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/Tsamp - Ngain'
//  '<S129>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/postSat Signal'
//  '<S130>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/preSat Signal'
//  '<S131>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/Anti-windup/Passthrough'
//  '<S132>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/D Gain/Internal Parameters'
//  '<S133>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/Filter/Disc. Forward Euler Filter'
//  '<S134>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/Filter ICs/Internal IC - Filter'
//  '<S135>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/I Gain/Internal Parameters'
//  '<S136>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/Ideal P Gain/Passthrough'
//  '<S137>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/Ideal P Gain Fdbk/Disabled'
//  '<S138>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/Integrator/Discrete'
//  '<S139>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/Integrator ICs/Internal IC'
//  '<S140>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/N Copy/Disabled'
//  '<S141>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/N Gain/Internal Parameters'
//  '<S142>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/P Copy/Disabled'
//  '<S143>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/Parallel P Gain/Internal Parameters'
//  '<S144>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/Reset Signal/Disabled'
//  '<S145>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/Saturation/Enabled'
//  '<S146>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/Saturation Fdbk/Disabled'
//  '<S147>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/Sum/Sum_PID'
//  '<S148>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/Sum Fdbk/Disabled'
//  '<S149>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/Tracking Mode/Disabled'
//  '<S150>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/Tracking Mode Sum/Passthrough'
//  '<S151>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/Tsamp - Integral/TsSignalSpecification'
//  '<S152>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/Tsamp - Ngain/Passthrough'
//  '<S153>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/postSat Signal/Forward_Path'
//  '<S154>' : 'cobaJoystick/Attitude controller/PID_yaw_rate/preSat Signal/Forward_Path'
//  '<S155>' : 'cobaJoystick/PX4 uORB Read1/Enabled Subsystem'
//  '<S156>' : 'cobaJoystick/PX4 uORB Read2/Enabled Subsystem'
//  '<S157>' : 'cobaJoystick/Quaternions to Rotation Angles/Angle Calculation'
//  '<S158>' : 'cobaJoystick/Quaternions to Rotation Angles/Quaternion Normalize'
//  '<S159>' : 'cobaJoystick/Quaternions to Rotation Angles/Angle Calculation/Protect asincos input'
//  '<S160>' : 'cobaJoystick/Quaternions to Rotation Angles/Angle Calculation/Protect asincos input/If Action Subsystem'
//  '<S161>' : 'cobaJoystick/Quaternions to Rotation Angles/Angle Calculation/Protect asincos input/If Action Subsystem1'
//  '<S162>' : 'cobaJoystick/Quaternions to Rotation Angles/Angle Calculation/Protect asincos input/If Action Subsystem2'
//  '<S163>' : 'cobaJoystick/Quaternions to Rotation Angles/Quaternion Normalize/Quaternion Modulus'
//  '<S164>' : 'cobaJoystick/Quaternions to Rotation Angles/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
//  '<S165>' : 'cobaJoystick/To Actuator/PX4 uORB Read'
//  '<S166>' : 'cobaJoystick/To Actuator/PX4 uORB Read/Enabled Subsystem'

#endif                                 // RTW_HEADER_cobaJoystick_h_

//
// File trailer for generated code.
//
// [EOF]
//
