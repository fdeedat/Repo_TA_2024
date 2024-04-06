//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: cobaJoystick_types.h
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
#ifndef RTW_HEADER_cobaJoystick_types_h_
#define RTW_HEADER_cobaJoystick_types_h_
#include "rtwtypes.h"
#include <uORB/topics/vehicle_odometry.h>
#include <uORB/topics/manual_control_setpoint.h>
#include <uORB/topics/actuator_armed.h>
#ifndef struct_e_px4_internal_block_SampleTi_T
#define struct_e_px4_internal_block_SampleTi_T

struct e_px4_internal_block_SampleTi_T
{
  int32_T __dummy;
};

#endif                                // struct_e_px4_internal_block_SampleTi_T

#ifndef struct_px4_internal_block_Subscriber_T
#define struct_px4_internal_block_Subscriber_T

struct px4_internal_block_Subscriber_T
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  e_px4_internal_block_SampleTi_T SampleTimeHandler;
  pollfd_t eventStructObj;
  orb_metadata_t * orbMetadataObj;
};

#endif                                // struct_px4_internal_block_Subscriber_T

#ifndef struct_px4_internal_block_PWM_cobaJo_T
#define struct_px4_internal_block_PWM_cobaJo_T

struct px4_internal_block_PWM_cobaJo_T
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  int pwmDevHandler;
  const char * pwmDevObj;
  unsigned int servoCount;
  int channelMask;
  boolean_T isMain;
  uint16_T errorStatus;
  orb_advert_t armAdvertiseObj;
  orb_advert_t actuatorAdvertiseObj;
  boolean_T isArmed;
};

#endif                                // struct_px4_internal_block_PWM_cobaJo_T

// Parameters (default storage)
typedef struct P_cobaJoystick_T_ P_cobaJoystick_T;

// Forward declaration for rtModel
typedef struct tag_RTM_cobaJoystick_T RT_MODEL_cobaJoystick_T;

#endif                                 // RTW_HEADER_cobaJoystick_types_h_

//
// File trailer for generated code.
//
// [EOF]
//
