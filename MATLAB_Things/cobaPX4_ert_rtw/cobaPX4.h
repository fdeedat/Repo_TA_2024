//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: cobaPX4.h
//
// Code generated for Simulink model 'cobaPX4'.
//
// Model version                  : 1.16
// Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
// C/C++ source code generated on : Fri Mar  1 16:46:32 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_cobaPX4_h_
#define RTW_HEADER_cobaPX4_h_
#include <poll.h>
#include <uORB/uORB.h>
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "MW_PX4_PWM.h"
#include "MW_uORB_Read.h"
#include "cobaPX4_types.h"
#include <uORB/topics/vehicle_local_position.h>
#include <uORB/topics/actuator_armed.h>

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
struct B_cobaPX4_T {
  px4_Bus_vehicle_local_position In1;  // '<S53>/In1'
  px4_Bus_vehicle_local_position b_varargout_2;
  px4_Bus_actuator_armed In1_n;        // '<S52>/In1'
  real_T Constant1;                    // '<Root>/Constant1'
  real32_T z;  // '<Root>/SigConversion_InsertedFor_Bus Selector1_at_outport_2'
  real32_T Gain1;                      // '<Root>/Gain1'
  real32_T vx; // '<Root>/SigConversion_InsertedFor_Bus Selector1_at_outport_3'
  real32_T vy; // '<Root>/SigConversion_InsertedFor_Bus Selector1_at_outport_4'
  real32_T vz; // '<Root>/SigConversion_InsertedFor_Bus Selector1_at_outport_5'
  real32_T heading;
               // '<Root>/SigConversion_InsertedFor_Bus Selector1_at_outport_6'
  real32_T x;  // '<Root>/SigConversion_InsertedFor_Bus Selector1_at_outport_0'
  real32_T y;  // '<Root>/SigConversion_InsertedFor_Bus Selector1_at_outport_1'
  boolean_T armed;
               // '<Root>/SigConversion_InsertedFor_Bus Selector3_at_outport_0'
};

// Block states (default storage) for system '<Root>'
struct DW_cobaPX4_T {
  px4_internal_block_PWM_cobaPX_T obj; // '<Root>/PX4 PWM Output'
  px4_internal_block_Subscriber_T obj_d;// '<S3>/SourceBlock'
  px4_internal_block_Subscriber_T obj_n;// '<S2>/SourceBlock'
  real_T Filter_DSTATE;                // '<S30>/Filter'
  struct {
    void *LoggedData[2];
  } Scope_PWORK;                       // '<Root>/Scope'

  int8_T EnabledSubsystem_SubsysRanBC; // '<S3>/Enabled Subsystem'
  int8_T EnabledSubsystem_SubsysRanBC_p;// '<S2>/Enabled Subsystem'
};

// Parameters (default storage)
struct P_cobaPX4_T_ {
  real_T PIDController1_D;             // Mask Parameter: PIDController1_D
                                          //  Referenced by: '<S29>/Derivative Gain'

  real_T PIDController1_InitialCondition;
                              // Mask Parameter: PIDController1_InitialCondition
                                 //  Referenced by: '<S30>/Filter'

  real_T PIDController1_N;             // Mask Parameter: PIDController1_N
                                          //  Referenced by: '<S38>/Filter Coefficient'

  real_T PIDController1_P;             // Mask Parameter: PIDController1_P
                                          //  Referenced by: '<S40>/Proportional Gain'

  px4_Bus_vehicle_local_position Out1_Y0;// Computed Parameter: Out1_Y0
                                            //  Referenced by: '<S53>/Out1'

  px4_Bus_vehicle_local_position Constant_Value;// Computed Parameter: Constant_Value
                                                   //  Referenced by: '<S3>/Constant'

  px4_Bus_actuator_armed Out1_Y0_d;    // Computed Parameter: Out1_Y0_d
                                          //  Referenced by: '<S52>/Out1'

  px4_Bus_actuator_armed Constant_Value_g;// Computed Parameter: Constant_Value_g
                                             //  Referenced by: '<S2>/Constant'

  real_T Constant1_Value;              // Expression: 50
                                          //  Referenced by: '<Root>/Constant1'

  real_T Filter_gainval;               // Computed Parameter: Filter_gainval
                                          //  Referenced by: '<S30>/Filter'

  real_T Gain_Gain;                    // Expression: 1
                                          //  Referenced by: '<Root>/Gain'

  real32_T Gain1_Gain;                 // Computed Parameter: Gain1_Gain
                                          //  Referenced by: '<Root>/Gain1'

};

// Real-time Model Data Structure
struct tag_RTM_cobaPX4_T {
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

  extern P_cobaPX4_T cobaPX4_P;

#ifdef __cplusplus

}

#endif

// Block signals (default storage)
#ifdef __cplusplus

extern "C"
{

#endif

  extern struct B_cobaPX4_T cobaPX4_B;

#ifdef __cplusplus

}

#endif

// Block states (default storage)
extern struct DW_cobaPX4_T cobaPX4_DW;

#ifdef __cplusplus

extern "C"
{

#endif

  // Model entry point functions
  extern void cobaPX4_initialize(void);
  extern void cobaPX4_step(void);
  extern void cobaPX4_terminate(void);

#ifdef __cplusplus

}

#endif

// Real-time Model object
#ifdef __cplusplus

extern "C"
{

#endif

  extern RT_MODEL_cobaPX4_T *const cobaPX4_M;

#ifdef __cplusplus

}

#endif

extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S2>/NOT' : Unused code path elimination
//  Block '<S3>/NOT' : Unused code path elimination


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
//  '<Root>' : 'cobaPX4'
//  '<S1>'   : 'cobaPX4/PID Controller1'
//  '<S2>'   : 'cobaPX4/PX4 uORB Read2'
//  '<S3>'   : 'cobaPX4/vehicle_local_pos'
//  '<S4>'   : 'cobaPX4/PID Controller1/Anti-windup'
//  '<S5>'   : 'cobaPX4/PID Controller1/D Gain'
//  '<S6>'   : 'cobaPX4/PID Controller1/Filter'
//  '<S7>'   : 'cobaPX4/PID Controller1/Filter ICs'
//  '<S8>'   : 'cobaPX4/PID Controller1/I Gain'
//  '<S9>'   : 'cobaPX4/PID Controller1/Ideal P Gain'
//  '<S10>'  : 'cobaPX4/PID Controller1/Ideal P Gain Fdbk'
//  '<S11>'  : 'cobaPX4/PID Controller1/Integrator'
//  '<S12>'  : 'cobaPX4/PID Controller1/Integrator ICs'
//  '<S13>'  : 'cobaPX4/PID Controller1/N Copy'
//  '<S14>'  : 'cobaPX4/PID Controller1/N Gain'
//  '<S15>'  : 'cobaPX4/PID Controller1/P Copy'
//  '<S16>'  : 'cobaPX4/PID Controller1/Parallel P Gain'
//  '<S17>'  : 'cobaPX4/PID Controller1/Reset Signal'
//  '<S18>'  : 'cobaPX4/PID Controller1/Saturation'
//  '<S19>'  : 'cobaPX4/PID Controller1/Saturation Fdbk'
//  '<S20>'  : 'cobaPX4/PID Controller1/Sum'
//  '<S21>'  : 'cobaPX4/PID Controller1/Sum Fdbk'
//  '<S22>'  : 'cobaPX4/PID Controller1/Tracking Mode'
//  '<S23>'  : 'cobaPX4/PID Controller1/Tracking Mode Sum'
//  '<S24>'  : 'cobaPX4/PID Controller1/Tsamp - Integral'
//  '<S25>'  : 'cobaPX4/PID Controller1/Tsamp - Ngain'
//  '<S26>'  : 'cobaPX4/PID Controller1/postSat Signal'
//  '<S27>'  : 'cobaPX4/PID Controller1/preSat Signal'
//  '<S28>'  : 'cobaPX4/PID Controller1/Anti-windup/Disabled'
//  '<S29>'  : 'cobaPX4/PID Controller1/D Gain/Internal Parameters'
//  '<S30>'  : 'cobaPX4/PID Controller1/Filter/Disc. Forward Euler Filter'
//  '<S31>'  : 'cobaPX4/PID Controller1/Filter ICs/Internal IC - Filter'
//  '<S32>'  : 'cobaPX4/PID Controller1/I Gain/Disabled'
//  '<S33>'  : 'cobaPX4/PID Controller1/Ideal P Gain/Passthrough'
//  '<S34>'  : 'cobaPX4/PID Controller1/Ideal P Gain Fdbk/Disabled'
//  '<S35>'  : 'cobaPX4/PID Controller1/Integrator/Disabled'
//  '<S36>'  : 'cobaPX4/PID Controller1/Integrator ICs/Disabled'
//  '<S37>'  : 'cobaPX4/PID Controller1/N Copy/Disabled'
//  '<S38>'  : 'cobaPX4/PID Controller1/N Gain/Internal Parameters'
//  '<S39>'  : 'cobaPX4/PID Controller1/P Copy/Disabled'
//  '<S40>'  : 'cobaPX4/PID Controller1/Parallel P Gain/Internal Parameters'
//  '<S41>'  : 'cobaPX4/PID Controller1/Reset Signal/Disabled'
//  '<S42>'  : 'cobaPX4/PID Controller1/Saturation/Passthrough'
//  '<S43>'  : 'cobaPX4/PID Controller1/Saturation Fdbk/Disabled'
//  '<S44>'  : 'cobaPX4/PID Controller1/Sum/Sum_PD'
//  '<S45>'  : 'cobaPX4/PID Controller1/Sum Fdbk/Disabled'
//  '<S46>'  : 'cobaPX4/PID Controller1/Tracking Mode/Disabled'
//  '<S47>'  : 'cobaPX4/PID Controller1/Tracking Mode Sum/Passthrough'
//  '<S48>'  : 'cobaPX4/PID Controller1/Tsamp - Integral/TsSignalSpecification'
//  '<S49>'  : 'cobaPX4/PID Controller1/Tsamp - Ngain/Passthrough'
//  '<S50>'  : 'cobaPX4/PID Controller1/postSat Signal/Forward_Path'
//  '<S51>'  : 'cobaPX4/PID Controller1/preSat Signal/Forward_Path'
//  '<S52>'  : 'cobaPX4/PX4 uORB Read2/Enabled Subsystem'
//  '<S53>'  : 'cobaPX4/vehicle_local_pos/Enabled Subsystem'

#endif                                 // RTW_HEADER_cobaPX4_h_

//
// File trailer for generated code.
//
// [EOF]
//
