//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: px4demo_AttitudeControllerJoystick.cpp
//
// Code generated for Simulink model 'px4demo_AttitudeControllerJoystick'.
//
// Model version                  : 6.0
// Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
// C/C++ source code generated on : Thu Mar 21 17:12:37 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "px4demo_AttitudeControllerJoystick.h"
#include "px4demo_AttitudeControllerJoystick_types.h"
#include "rtwtypes.h"
#include <math.h>
#include "px4demo_AttitudeControllerJoystick_private.h"

extern "C"
{

#include "rt_nonfinite.h"

}

#include <uORB/topics/actuator_armed.h>
#include "rt_defines.h"

// Block signals (default storage)
B_px4demo_AttitudeControllerJ_T px4demo_AttitudeControllerJoy_B;

// Block states (default storage)
DW_px4demo_AttitudeController_T px4demo_AttitudeControllerJo_DW;

// Real-time model
RT_MODEL_px4demo_AttitudeCont_T px4demo_AttitudeControllerJo_M_ =
  RT_MODEL_px4demo_AttitudeCont_T();
RT_MODEL_px4demo_AttitudeCont_T *const px4demo_AttitudeControllerJo_M =
  &px4demo_AttitudeControllerJo_M_;

// Forward declaration for local functions
static void px4demo_Attitu_SystemCore_setup(px4_internal_block_PWM_px4dem_T *obj,
  boolean_T varargin_1, boolean_T varargin_2);
real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    int32_T tmp;
    int32_T tmp_0;
    if (u0 > 0.0) {
      tmp = 1;
    } else {
      tmp = -1;
    }

    if (u1 > 0.0) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    y = atan2(static_cast<real_T>(tmp), static_cast<real_T>(tmp_0));
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

static void px4demo_Attitu_SystemCore_setup(px4_internal_block_PWM_px4dem_T *obj,
  boolean_T varargin_1, boolean_T varargin_2)
{
  uint16_T status;
  obj->isSetupComplete = false;
  obj->isInitialized = 1;
  obj->isMain = true;
  obj->pwmDevObj = MW_PWM_OUTPUT_MAIN_DEVICE_PATH;
  status = pwm_open(&obj->pwmDevHandler, obj->pwmDevObj,
                    &obj->actuatorAdvertiseObj, &obj->armAdvertiseObj);
  obj->errorStatus = static_cast<uint16_T>(obj->errorStatus | status);
  obj->servoCount = 0;
  status = pwm_getServoCount(&obj->pwmDevHandler, &obj->servoCount);
  obj->errorStatus = static_cast<uint16_T>(obj->errorStatus | status);
  if (varargin_1) {
    status = pwm_arm(&obj->pwmDevHandler, &obj->armAdvertiseObj);
    obj->isArmed = true;
  } else {
    status = pwm_disarm(&obj->pwmDevHandler, &obj->armAdvertiseObj);
    obj->isArmed = false;
  }

  obj->errorStatus = static_cast<uint16_T>(obj->errorStatus | status);
  status = pwm_setPWMRate(&obj->pwmDevHandler, obj->isMain);
  obj->errorStatus = static_cast<uint16_T>(obj->errorStatus | status);
  obj->channelMask = 15;
  status = pwm_setChannelMask(&obj->pwmDevHandler, obj->channelMask);
  obj->errorStatus = static_cast<uint16_T>(obj->errorStatus | status);
  status = pwm_setFailsafePWM(&obj->pwmDevHandler, obj->servoCount,
    obj->channelMask, obj->isMain);
  obj->errorStatus = static_cast<uint16_T>(obj->errorStatus | status);
  status = pwm_setDisarmedPWM(&obj->pwmDevHandler, obj->servoCount,
    obj->channelMask, obj->isMain, &obj->actuatorAdvertiseObj);
  obj->errorStatus = static_cast<uint16_T>(obj->errorStatus | status);
  if (obj->isMain) {
    status = pwm_forceFailsafe(&obj->pwmDevHandler, static_cast<int32_T>
      (varargin_2));
    obj->errorStatus = static_cast<uint16_T>(obj->errorStatus | status);
    status = pwm_forceTerminateFailsafe(&obj->pwmDevHandler, 0);
    obj->errorStatus = static_cast<uint16_T>(obj->errorStatus | status);
  }

  obj->isSetupComplete = true;
}

// Model step function
void px4demo_AttitudeControllerJoystick_step(void)
{
  real_T VectorConcatenate_tmp;
  real_T VectorConcatenate_tmp_0;
  real_T VectorConcatenate_tmp_1;
  real_T VectorConcatenate_tmp_2;
  int32_T i;
  real32_T tmp;
  uint16_T rtb_Gain1_n[4];
  uint16_T status;
  boolean_T b_varargout_1;
  boolean_T b_varargout_1_0;

  // Reset subsysRan breadcrumbs
  srClearBC(px4demo_AttitudeControllerJo_DW.EnabledSubsystem_SubsysRanBC_c);

  // Reset subsysRan breadcrumbs
  srClearBC(px4demo_AttitudeControllerJo_DW.EnabledSubsystem_SubsysRanBC_g);

  // Reset subsysRan breadcrumbs
  srClearBC(px4demo_AttitudeControllerJo_DW.EnabledSubsystem_SubsysRanBC);

  // Reset subsysRan breadcrumbs
  srClearBC(px4demo_AttitudeControllerJo_DW.IfActionSubsystem_SubsysRanBC);

  // Reset subsysRan breadcrumbs
  srClearBC(px4demo_AttitudeControllerJo_DW.IfActionSubsystem1_SubsysRanBC);

  // Reset subsysRan breadcrumbs
  srClearBC(px4demo_AttitudeControllerJo_DW.IfActionSubsystem2_SubsysRanBC);

  // MATLABSystem: '<S4>/SourceBlock'
  b_varargout_1 = uORB_read_step
    (px4demo_AttitudeControllerJo_DW.obj.orbMetadataObj,
     &px4demo_AttitudeControllerJo_DW.obj.eventStructObj,
     &px4demo_AttitudeControllerJoy_B.b_varargout_2_m, false, 1.0);

  // Outputs for Enabled SubSystem: '<S4>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S160>/Enable'

  if (b_varargout_1) {
    // SignalConversion generated from: '<S160>/In1'
    px4demo_AttitudeControllerJoy_B.In1_p =
      px4demo_AttitudeControllerJoy_B.b_varargout_2_m;
    srUpdateBC(px4demo_AttitudeControllerJo_DW.EnabledSubsystem_SubsysRanBC);
  }

  // End of Outputs for SubSystem: '<S4>/Enabled Subsystem'

  // SignalConversion generated from: '<Root>/Bus Selector'
  px4demo_AttitudeControllerJoy_B.z = px4demo_AttitudeControllerJoy_B.In1_p.z;

  // MATLABSystem: '<S3>/SourceBlock'
  b_varargout_1_0 = uORB_read_step
    (px4demo_AttitudeControllerJo_DW.obj_d.orbMetadataObj,
     &px4demo_AttitudeControllerJo_DW.obj_d.eventStructObj,
     &px4demo_AttitudeControllerJoy_B.b_varargout_2, false, 1.0);

  // Outputs for Enabled SubSystem: '<S3>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S159>/Enable'

  if (b_varargout_1_0) {
    // SignalConversion generated from: '<S159>/In1'
    px4demo_AttitudeControllerJoy_B.In1 =
      px4demo_AttitudeControllerJoy_B.b_varargout_2;
    srUpdateBC(px4demo_AttitudeControllerJo_DW.EnabledSubsystem_SubsysRanBC_g);
  }

  // End of Outputs for SubSystem: '<S3>/Enabled Subsystem'

  // Sqrt: '<S167>/sqrt' incorporates:
  //   DataTypeConversion: '<Root>/Data Type Conversion1'
  //   Product: '<S168>/Product'
  //   Product: '<S168>/Product1'
  //   Product: '<S168>/Product2'
  //   Product: '<S168>/Product3'
  //   Sum: '<S168>/Sum'

  px4demo_AttitudeControllerJoy_B.Product3 = sqrt(((static_cast<real_T>
    (px4demo_AttitudeControllerJoy_B.In1.q[0]) *
    px4demo_AttitudeControllerJoy_B.In1.q[0] + static_cast<real_T>
    (px4demo_AttitudeControllerJoy_B.In1.q[1]) *
    px4demo_AttitudeControllerJoy_B.In1.q[1]) + static_cast<real_T>
    (px4demo_AttitudeControllerJoy_B.In1.q[2]) *
    px4demo_AttitudeControllerJoy_B.In1.q[2]) + static_cast<real_T>
    (px4demo_AttitudeControllerJoy_B.In1.q[3]) *
    px4demo_AttitudeControllerJoy_B.In1.q[3]);

  // Product: '<S162>/Product' incorporates:
  //   DataTypeConversion: '<Root>/Data Type Conversion1'

  px4demo_AttitudeControllerJoy_B.Filter_hl =
    px4demo_AttitudeControllerJoy_B.In1.q[0] /
    px4demo_AttitudeControllerJoy_B.Product3;

  // Product: '<S162>/Product1' incorporates:
  //   DataTypeConversion: '<Root>/Data Type Conversion1'

  px4demo_AttitudeControllerJoy_B.Sum = px4demo_AttitudeControllerJoy_B.In1.q[1]
    / px4demo_AttitudeControllerJoy_B.Product3;

  // Product: '<S162>/Product2' incorporates:
  //   DataTypeConversion: '<Root>/Data Type Conversion1'

  px4demo_AttitudeControllerJoy_B.Product2 =
    px4demo_AttitudeControllerJoy_B.In1.q[2] /
    px4demo_AttitudeControllerJoy_B.Product3;

  // Product: '<S162>/Product3' incorporates:
  //   DataTypeConversion: '<Root>/Data Type Conversion1'

  px4demo_AttitudeControllerJoy_B.Product3 =
    px4demo_AttitudeControllerJoy_B.In1.q[3] /
    px4demo_AttitudeControllerJoy_B.Product3;

  // Fcn: '<S5>/fcn2' incorporates:
  //   Fcn: '<S5>/fcn5'

  VectorConcatenate_tmp = px4demo_AttitudeControllerJoy_B.Filter_hl *
    px4demo_AttitudeControllerJoy_B.Filter_hl;
  VectorConcatenate_tmp_0 = px4demo_AttitudeControllerJoy_B.Sum *
    px4demo_AttitudeControllerJoy_B.Sum;
  VectorConcatenate_tmp_1 = px4demo_AttitudeControllerJoy_B.Product2 *
    px4demo_AttitudeControllerJoy_B.Product2;
  VectorConcatenate_tmp_2 = px4demo_AttitudeControllerJoy_B.Product3 *
    px4demo_AttitudeControllerJoy_B.Product3;

  // Trigonometry: '<S161>/Trigonometric Function1' incorporates:
  //   Concatenate: '<S161>/Vector Concatenate'
  //   Fcn: '<S5>/fcn1'
  //   Fcn: '<S5>/fcn2'

  px4demo_AttitudeControllerJoy_B.VectorConcatenate[0] = rt_atan2d_snf
    ((px4demo_AttitudeControllerJoy_B.Sum *
      px4demo_AttitudeControllerJoy_B.Product2 +
      px4demo_AttitudeControllerJoy_B.Filter_hl *
      px4demo_AttitudeControllerJoy_B.Product3) * 2.0, ((VectorConcatenate_tmp +
       VectorConcatenate_tmp_0) - VectorConcatenate_tmp_1) -
     VectorConcatenate_tmp_2);

  // Fcn: '<S5>/fcn3'
  px4demo_AttitudeControllerJoy_B.fcn3 = (px4demo_AttitudeControllerJoy_B.Sum *
    px4demo_AttitudeControllerJoy_B.Product3 -
    px4demo_AttitudeControllerJoy_B.Filter_hl *
    px4demo_AttitudeControllerJoy_B.Product2) * -2.0;

  // If: '<S163>/If' incorporates:
  //   Constant: '<S164>/Constant'
  //   Constant: '<S165>/Constant'

  if (px4demo_AttitudeControllerJoy_B.fcn3 > 1.0) {
    // Outputs for IfAction SubSystem: '<S163>/If Action Subsystem' incorporates:
    //   ActionPort: '<S164>/Action Port'

    px4demo_AttitudeControllerJoy_B.fcn3 =
      px4demo_AttitudeControllerJoy_P.Constant_Value_lz;

    // End of Outputs for SubSystem: '<S163>/If Action Subsystem'

    // Update for IfAction SubSystem: '<S163>/If Action Subsystem' incorporates:
    //   ActionPort: '<S164>/Action Port'

    // Update for If: '<S163>/If' incorporates:
    //   Constant: '<S164>/Constant'

    srUpdateBC(px4demo_AttitudeControllerJo_DW.IfActionSubsystem_SubsysRanBC);

    // End of Update for SubSystem: '<S163>/If Action Subsystem'
  } else if (px4demo_AttitudeControllerJoy_B.fcn3 < -1.0) {
    // Outputs for IfAction SubSystem: '<S163>/If Action Subsystem1' incorporates:
    //   ActionPort: '<S165>/Action Port'

    px4demo_AttitudeControllerJoy_B.fcn3 =
      px4demo_AttitudeControllerJoy_P.Constant_Value_i;

    // End of Outputs for SubSystem: '<S163>/If Action Subsystem1'

    // Update for IfAction SubSystem: '<S163>/If Action Subsystem1' incorporates:
    //   ActionPort: '<S165>/Action Port'

    // Update for If: '<S163>/If' incorporates:
    //   Constant: '<S165>/Constant'

    srUpdateBC(px4demo_AttitudeControllerJo_DW.IfActionSubsystem1_SubsysRanBC);

    // End of Update for SubSystem: '<S163>/If Action Subsystem1'
  } else {
    // Update for IfAction SubSystem: '<S163>/If Action Subsystem2' incorporates:
    //   ActionPort: '<S166>/Action Port'

    // Update for If: '<S163>/If'
    srUpdateBC(px4demo_AttitudeControllerJo_DW.IfActionSubsystem2_SubsysRanBC);

    // End of Update for SubSystem: '<S163>/If Action Subsystem2'
  }

  // End of If: '<S163>/If'

  // Trigonometry: '<S161>/trigFcn' incorporates:
  //   Concatenate: '<S161>/Vector Concatenate'

  if (px4demo_AttitudeControllerJoy_B.fcn3 > 1.0) {
    px4demo_AttitudeControllerJoy_B.fcn3 = 1.0;
  } else if (px4demo_AttitudeControllerJoy_B.fcn3 < -1.0) {
    px4demo_AttitudeControllerJoy_B.fcn3 = -1.0;
  }

  px4demo_AttitudeControllerJoy_B.VectorConcatenate[1] = asin
    (px4demo_AttitudeControllerJoy_B.fcn3);

  // End of Trigonometry: '<S161>/trigFcn'

  // Trigonometry: '<S161>/Trigonometric Function3' incorporates:
  //   Concatenate: '<S161>/Vector Concatenate'
  //   Fcn: '<S5>/fcn4'
  //   Fcn: '<S5>/fcn5'

  px4demo_AttitudeControllerJoy_B.VectorConcatenate[2] = rt_atan2d_snf
    ((px4demo_AttitudeControllerJoy_B.Product2 *
      px4demo_AttitudeControllerJoy_B.Product3 +
      px4demo_AttitudeControllerJoy_B.Filter_hl *
      px4demo_AttitudeControllerJoy_B.Sum) * 2.0, ((VectorConcatenate_tmp -
       VectorConcatenate_tmp_0) - VectorConcatenate_tmp_1) +
     VectorConcatenate_tmp_2);

  // SignalConversion generated from: '<Root>/Bus Selector'
  px4demo_AttitudeControllerJoy_B.x = px4demo_AttitudeControllerJoy_B.In1_p.x;

  // DeadZone: '<Root>/Deadband'
  if (px4demo_AttitudeControllerJoy_B.x >
      px4demo_AttitudeControllerJoy_P.Deadband_End) {
    tmp = px4demo_AttitudeControllerJoy_B.x -
      px4demo_AttitudeControllerJoy_P.Deadband_End;
  } else if (px4demo_AttitudeControllerJoy_B.x >=
             px4demo_AttitudeControllerJoy_P.Deadband_Start) {
    tmp = 0.0F;
  } else {
    tmp = px4demo_AttitudeControllerJoy_B.x -
      px4demo_AttitudeControllerJoy_P.Deadband_Start;
  }

  // Sum: '<S2>/Add2' incorporates:
  //   DeadZone: '<Root>/Deadband'
  //   Gain: '<S10>/Gain1'
  //   Gain: '<S2>/Gain'

  px4demo_AttitudeControllerJoy_B.fcn3 =
    px4demo_AttitudeControllerJoy_B.VectorConcatenate[1] -
    px4demo_AttitudeControllerJoy_P.Gain_Gain * tmp *
    px4demo_AttitudeControllerJoy_P.Gain1_Gain_n;

  // DiscreteIntegrator: '<S46>/Integrator' incorporates:
  //   Gain: '<S43>/Integral Gain'

  px4demo_AttitudeControllerJo_DW.Integrator_DSTATE +=
    px4demo_AttitudeControllerJoy_P.PID_pitch_I *
    px4demo_AttitudeControllerJoy_B.fcn3 *
    px4demo_AttitudeControllerJoy_P.Integrator_gainval;

  // Gain: '<S49>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S41>/Filter'
  //   Gain: '<S40>/Derivative Gain'
  //   Sum: '<S41>/SumD'

  px4demo_AttitudeControllerJoy_B.Product3 =
    (px4demo_AttitudeControllerJoy_P.PID_pitch_D *
     px4demo_AttitudeControllerJoy_B.fcn3 -
     px4demo_AttitudeControllerJo_DW.Filter_DSTATE) *
    px4demo_AttitudeControllerJoy_P.PID_pitch_N;

  // Sum: '<S55>/Sum' incorporates:
  //   Gain: '<S51>/Proportional Gain'

  px4demo_AttitudeControllerJoy_B.Saturation =
    (px4demo_AttitudeControllerJoy_P.PID_pitch_P *
     px4demo_AttitudeControllerJoy_B.fcn3 +
     px4demo_AttitudeControllerJo_DW.Integrator_DSTATE) +
    px4demo_AttitudeControllerJoy_B.Product3;

  // Saturate: '<S53>/Saturation'
  if (px4demo_AttitudeControllerJoy_B.Saturation >
      px4demo_AttitudeControllerJoy_P.PID_pitch_UpperSaturationLimit) {
    // Sum: '<S55>/Sum' incorporates:
    //   Saturate: '<S53>/Saturation'

    px4demo_AttitudeControllerJoy_B.Saturation =
      px4demo_AttitudeControllerJoy_P.PID_pitch_UpperSaturationLimit;
  } else if (px4demo_AttitudeControllerJoy_B.Saturation <
             px4demo_AttitudeControllerJoy_P.PID_pitch_LowerSaturationLimit) {
    // Sum: '<S55>/Sum' incorporates:
    //   Saturate: '<S53>/Saturation'

    px4demo_AttitudeControllerJoy_B.Saturation =
      px4demo_AttitudeControllerJoy_P.PID_pitch_LowerSaturationLimit;
  }

  // End of Saturate: '<S53>/Saturation'

  // SignalConversion generated from: '<Root>/Bus Selector'
  px4demo_AttitudeControllerJoy_B.y = px4demo_AttitudeControllerJoy_B.In1_p.y;

  // DeadZone: '<Root>/Deadband1'
  if (px4demo_AttitudeControllerJoy_B.y >
      px4demo_AttitudeControllerJoy_P.Deadband1_End) {
    tmp = px4demo_AttitudeControllerJoy_B.y -
      px4demo_AttitudeControllerJoy_P.Deadband1_End;
  } else if (px4demo_AttitudeControllerJoy_B.y >=
             px4demo_AttitudeControllerJoy_P.Deadband1_Start) {
    tmp = 0.0F;
  } else {
    tmp = px4demo_AttitudeControllerJoy_B.y -
      px4demo_AttitudeControllerJoy_P.Deadband1_Start;
  }

  // Sum: '<S2>/Add3' incorporates:
  //   DeadZone: '<Root>/Deadband1'
  //   Gain: '<S11>/Gain1'
  //   Gain: '<S2>/Gain1'

  px4demo_AttitudeControllerJoy_B.Sum =
    px4demo_AttitudeControllerJoy_B.VectorConcatenate[2] -
    px4demo_AttitudeControllerJoy_P.Gain1_Gain_g * tmp *
    px4demo_AttitudeControllerJoy_P.Gain1_Gain_c;

  // DiscreteIntegrator: '<S94>/Integrator' incorporates:
  //   Gain: '<S91>/Integral Gain'

  px4demo_AttitudeControllerJo_DW.Integrator_DSTATE_m +=
    px4demo_AttitudeControllerJoy_P.PID_roll_I *
    px4demo_AttitudeControllerJoy_B.Sum *
    px4demo_AttitudeControllerJoy_P.Integrator_gainval_e;

  // Gain: '<S97>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S89>/Filter'
  //   Gain: '<S88>/Derivative Gain'
  //   Sum: '<S89>/SumD'

  px4demo_AttitudeControllerJoy_B.fcn3 =
    (px4demo_AttitudeControllerJoy_P.PID_roll_D *
     px4demo_AttitudeControllerJoy_B.Sum -
     px4demo_AttitudeControllerJo_DW.Filter_DSTATE_d) *
    px4demo_AttitudeControllerJoy_P.PID_roll_N;

  // Sum: '<S103>/Sum' incorporates:
  //   Gain: '<S99>/Proportional Gain'

  px4demo_AttitudeControllerJoy_B.Saturation_f =
    (px4demo_AttitudeControllerJoy_P.PID_roll_P *
     px4demo_AttitudeControllerJoy_B.Sum +
     px4demo_AttitudeControllerJo_DW.Integrator_DSTATE_m) +
    px4demo_AttitudeControllerJoy_B.fcn3;

  // Saturate: '<S101>/Saturation'
  if (px4demo_AttitudeControllerJoy_B.Saturation_f >
      px4demo_AttitudeControllerJoy_P.PID_roll_UpperSaturationLimit) {
    // Sum: '<S103>/Sum' incorporates:
    //   Saturate: '<S101>/Saturation'

    px4demo_AttitudeControllerJoy_B.Saturation_f =
      px4demo_AttitudeControllerJoy_P.PID_roll_UpperSaturationLimit;
  } else if (px4demo_AttitudeControllerJoy_B.Saturation_f <
             px4demo_AttitudeControllerJoy_P.PID_roll_LowerSaturationLimit) {
    // Sum: '<S103>/Sum' incorporates:
    //   Saturate: '<S101>/Saturation'

    px4demo_AttitudeControllerJoy_B.Saturation_f =
      px4demo_AttitudeControllerJoy_P.PID_roll_LowerSaturationLimit;
  }

  // End of Saturate: '<S101>/Saturation'

  // SignalConversion generated from: '<Root>/Bus Selector'
  px4demo_AttitudeControllerJoy_B.r = px4demo_AttitudeControllerJoy_B.In1_p.r;

  // SignalConversion generated from: '<Root>/Bus Selector2'
  px4demo_AttitudeControllerJoy_B.yawspeed =
    px4demo_AttitudeControllerJoy_B.In1.yawspeed;

  // DeadZone: '<Root>/Deadband2'
  if (px4demo_AttitudeControllerJoy_B.r >
      px4demo_AttitudeControllerJoy_P.Deadband2_End) {
    tmp = px4demo_AttitudeControllerJoy_B.r -
      px4demo_AttitudeControllerJoy_P.Deadband2_End;
  } else if (px4demo_AttitudeControllerJoy_B.r >=
             px4demo_AttitudeControllerJoy_P.Deadband2_Start) {
    tmp = 0.0F;
  } else {
    tmp = px4demo_AttitudeControllerJoy_B.r -
      px4demo_AttitudeControllerJoy_P.Deadband2_Start;
  }

  // Sum: '<S2>/Add1' incorporates:
  //   DataTypeConversion: '<S2>/Data Type Conversion2'
  //   DeadZone: '<Root>/Deadband2'

  px4demo_AttitudeControllerJoy_B.Sum = static_cast<real_T>(tmp) -
    px4demo_AttitudeControllerJoy_B.yawspeed;

  // DiscreteIntegrator: '<S142>/Integrator' incorporates:
  //   Gain: '<S139>/Integral Gain'

  px4demo_AttitudeControllerJo_DW.Integrator_DSTATE_i +=
    px4demo_AttitudeControllerJoy_P.PID_yaw_rate_I *
    px4demo_AttitudeControllerJoy_B.Sum *
    px4demo_AttitudeControllerJoy_P.Integrator_gainval_b;

  // Gain: '<S145>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S137>/Filter'
  //   Gain: '<S136>/Derivative Gain'
  //   Sum: '<S137>/SumD'

  px4demo_AttitudeControllerJoy_B.Filter_hl =
    (px4demo_AttitudeControllerJoy_P.PID_yaw_rate_D *
     px4demo_AttitudeControllerJoy_B.Sum -
     px4demo_AttitudeControllerJo_DW.Filter_DSTATE_k) *
    px4demo_AttitudeControllerJoy_P.PID_yaw_rate_N;

  // Sum: '<S151>/Sum' incorporates:
  //   Gain: '<S147>/Proportional Gain'

  px4demo_AttitudeControllerJoy_B.Saturation_l =
    (px4demo_AttitudeControllerJoy_P.PID_yaw_rate_P *
     px4demo_AttitudeControllerJoy_B.Sum +
     px4demo_AttitudeControllerJo_DW.Integrator_DSTATE_i) +
    px4demo_AttitudeControllerJoy_B.Filter_hl;

  // Saturate: '<S149>/Saturation'
  if (px4demo_AttitudeControllerJoy_B.Saturation_l >
      px4demo_AttitudeControllerJoy_P.PID_yaw_rate_UpperSaturationLim) {
    // Sum: '<S151>/Sum' incorporates:
    //   Saturate: '<S149>/Saturation'

    px4demo_AttitudeControllerJoy_B.Saturation_l =
      px4demo_AttitudeControllerJoy_P.PID_yaw_rate_UpperSaturationLim;
  } else if (px4demo_AttitudeControllerJoy_B.Saturation_l <
             px4demo_AttitudeControllerJoy_P.PID_yaw_rate_LowerSaturationLim) {
    // Sum: '<S151>/Sum' incorporates:
    //   Saturate: '<S149>/Saturation'

    px4demo_AttitudeControllerJoy_B.Saturation_l =
      px4demo_AttitudeControllerJoy_P.PID_yaw_rate_LowerSaturationLim;
  }

  // End of Saturate: '<S149>/Saturation'

  // SignalConversion generated from: '<S6>/Product1' incorporates:
  //   Constant: '<S6>/Constant'
  //   Sum: '<S6>/Add'

  px4demo_AttitudeControllerJoy_B.Sum =
    px4demo_AttitudeControllerJoy_P.Constant_Value_m +
    px4demo_AttitudeControllerJoy_B.z;
  for (i = 0; i < 4; i++) {
    // Gain: '<S6>/Gain1' incorporates:
    //   Constant: '<S6>/Mixer matrix'
    //   Product: '<S6>/Product1'
    //   SignalConversion generated from: '<S6>/Product1'

    px4demo_AttitudeControllerJoy_B.Product2 = floor
      ((((px4demo_AttitudeControllerJoy_P.Mixermatrix_Value[i + 4] *
          px4demo_AttitudeControllerJoy_B.Saturation +
          px4demo_AttitudeControllerJoy_P.Mixermatrix_Value[i] *
          px4demo_AttitudeControllerJoy_B.Sum) +
         px4demo_AttitudeControllerJoy_P.Mixermatrix_Value[i + 8] *
         px4demo_AttitudeControllerJoy_B.Saturation_f) +
        px4demo_AttitudeControllerJoy_P.Mixermatrix_Value[i + 12] *
        px4demo_AttitudeControllerJoy_B.Saturation_l) *
       px4demo_AttitudeControllerJoy_P.Gain1_Gain);
    if (rtIsNaN(px4demo_AttitudeControllerJoy_B.Product2) || rtIsInf
        (px4demo_AttitudeControllerJoy_B.Product2)) {
      px4demo_AttitudeControllerJoy_B.Product2 = 0.0;
    } else {
      px4demo_AttitudeControllerJoy_B.Product2 = fmod
        (px4demo_AttitudeControllerJoy_B.Product2, 65536.0);
    }

    rtb_Gain1_n[i] = static_cast<uint16_T>
      (px4demo_AttitudeControllerJoy_B.Product2 < 0.0 ? static_cast<int32_T>(
        static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
          (-px4demo_AttitudeControllerJoy_B.Product2)))) : static_cast<int32_T>(
        static_cast<uint16_T>(px4demo_AttitudeControllerJoy_B.Product2)));

    // End of Gain: '<S6>/Gain1'
  }

  // MATLABSystem: '<S6>/PX4 PWM Output' incorporates:
  //   Constant: '<S6>/Reset'
  //   Logic: '<S6>/NOT'

  for (i = 0; i < 8; i++) {
    px4demo_AttitudeControllerJoy_B.pwmValue[i] = 0U;
  }

  px4demo_AttitudeControllerJoy_B.pwmValue[0] = rtb_Gain1_n[0];
  px4demo_AttitudeControllerJoy_B.pwmValue[1] = rtb_Gain1_n[1];
  px4demo_AttitudeControllerJoy_B.pwmValue[2] = rtb_Gain1_n[2];
  px4demo_AttitudeControllerJoy_B.pwmValue[3] = rtb_Gain1_n[3];
  if (!px4demo_AttitudeControllerJoy_P.Reset_Value) {
    if (!px4demo_AttitudeControllerJo_DW.obj_dx.isArmed) {
      px4demo_AttitudeControllerJo_DW.obj_dx.isArmed = true;
      status = pwm_arm(&px4demo_AttitudeControllerJo_DW.obj_dx.pwmDevHandler,
                       &px4demo_AttitudeControllerJo_DW.obj_dx.armAdvertiseObj);
      px4demo_AttitudeControllerJo_DW.obj_dx.errorStatus = static_cast<uint16_T>
        (px4demo_AttitudeControllerJo_DW.obj_dx.errorStatus | status);
    }

    status = pwm_setServo(&px4demo_AttitudeControllerJo_DW.obj_dx.pwmDevHandler,
                          px4demo_AttitudeControllerJo_DW.obj_dx.servoCount,
                          px4demo_AttitudeControllerJo_DW.obj_dx.channelMask,
                          &px4demo_AttitudeControllerJoy_B.pwmValue[0],
                          px4demo_AttitudeControllerJo_DW.obj_dx.isMain,
                          &px4demo_AttitudeControllerJo_DW.obj_dx.actuatorAdvertiseObj);
    px4demo_AttitudeControllerJo_DW.obj_dx.errorStatus = static_cast<uint16_T>
      (px4demo_AttitudeControllerJo_DW.obj_dx.errorStatus | status);
  } else {
    status = pwm_disarm(&px4demo_AttitudeControllerJo_DW.obj_dx.pwmDevHandler,
                        &px4demo_AttitudeControllerJo_DW.obj_dx.armAdvertiseObj);
    px4demo_AttitudeControllerJo_DW.obj_dx.errorStatus = static_cast<uint16_T>
      (px4demo_AttitudeControllerJo_DW.obj_dx.errorStatus | status);
    px4demo_AttitudeControllerJo_DW.obj_dx.isArmed = false;
    status = pwm_resetServo
      (&px4demo_AttitudeControllerJo_DW.obj_dx.pwmDevHandler,
       px4demo_AttitudeControllerJo_DW.obj_dx.servoCount,
       px4demo_AttitudeControllerJo_DW.obj_dx.channelMask,
       px4demo_AttitudeControllerJo_DW.obj_dx.isMain,
       &px4demo_AttitudeControllerJo_DW.obj_dx.actuatorAdvertiseObj);
    px4demo_AttitudeControllerJo_DW.obj_dx.errorStatus = static_cast<uint16_T>
      (px4demo_AttitudeControllerJo_DW.obj_dx.errorStatus | status);
  }

  if (px4demo_AttitudeControllerJo_DW.obj_dx.isMain) {
    status = pwm_forceFailsafe
      (&px4demo_AttitudeControllerJo_DW.obj_dx.pwmDevHandler,
       static_cast<int32_T>(px4demo_AttitudeControllerJoy_P.Reset_Value));
    px4demo_AttitudeControllerJo_DW.obj_dx.errorStatus = static_cast<uint16_T>
      (px4demo_AttitudeControllerJo_DW.obj_dx.errorStatus | status);
  }

  // End of MATLABSystem: '<S6>/PX4 PWM Output'
  // SignalConversion generated from: '<Root>/Bus Selector2'
  px4demo_AttitudeControllerJoy_B.rollspeed =
    px4demo_AttitudeControllerJoy_B.In1.rollspeed;

  // SignalConversion generated from: '<Root>/Bus Selector2'
  px4demo_AttitudeControllerJoy_B.pitchspeed =
    px4demo_AttitudeControllerJoy_B.In1.pitchspeed;

  // Logic: '<S3>/NOT' incorporates:
  //   MATLABSystem: '<S3>/SourceBlock'

  px4demo_AttitudeControllerJoy_B.NOT = !b_varargout_1_0;

  // Logic: '<S4>/NOT' incorporates:
  //   MATLABSystem: '<S4>/SourceBlock'

  px4demo_AttitudeControllerJoy_B.NOT_b = !b_varargout_1;

  // MATLABSystem: '<S7>/SourceBlock'
  b_varargout_1 = uORB_read_step
    (px4demo_AttitudeControllerJo_DW.obj_l.orbMetadataObj,
     &px4demo_AttitudeControllerJo_DW.obj_l.eventStructObj,
     &px4demo_AttitudeControllerJoy_B.BusAssignment, false, 1.0);

  // Logic: '<S7>/NOT' incorporates:
  //   MATLABSystem: '<S7>/SourceBlock'

  px4demo_AttitudeControllerJoy_B.NOT_m = !b_varargout_1;

  // Outputs for Enabled SubSystem: '<S7>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S9>/Enable'

  // MATLABSystem: '<S7>/SourceBlock'
  if (b_varargout_1) {
    // SignalConversion generated from: '<S9>/In1'
    px4demo_AttitudeControllerJoy_B.In1_a =
      px4demo_AttitudeControllerJoy_B.BusAssignment;
    srUpdateBC(px4demo_AttitudeControllerJo_DW.EnabledSubsystem_SubsysRanBC_c);
  }

  // End of Outputs for SubSystem: '<S7>/Enabled Subsystem'

  // BusAssignment: '<S1>/Bus Assignment' incorporates:
  //   Constant: '<S1>/Constant'
  //   SignalConversion generated from: '<S9>/In1'

  px4demo_AttitudeControllerJoy_B.BusAssignment =
    px4demo_AttitudeControllerJoy_B.In1_a;
  px4demo_AttitudeControllerJoy_B.BusAssignment.armed =
    px4demo_AttitudeControllerJoy_P.Constant_Value_a;

  // MATLABSystem: '<S8>/SinkBlock' incorporates:
  //   BusAssignment: '<S1>/Bus Assignment'

  uORB_write_step(px4demo_AttitudeControllerJo_DW.obj_e.orbMetadataObj,
                  &px4demo_AttitudeControllerJo_DW.obj_e.orbAdvertiseObj,
                  &px4demo_AttitudeControllerJoy_B.BusAssignment);

  // Update for DiscreteIntegrator: '<S41>/Filter'
  px4demo_AttitudeControllerJo_DW.Filter_DSTATE +=
    px4demo_AttitudeControllerJoy_P.Filter_gainval *
    px4demo_AttitudeControllerJoy_B.Product3;

  // Update for DiscreteIntegrator: '<S89>/Filter'
  px4demo_AttitudeControllerJo_DW.Filter_DSTATE_d +=
    px4demo_AttitudeControllerJoy_P.Filter_gainval_j *
    px4demo_AttitudeControllerJoy_B.fcn3;

  // Update for DiscreteIntegrator: '<S137>/Filter'
  px4demo_AttitudeControllerJo_DW.Filter_DSTATE_k +=
    px4demo_AttitudeControllerJoy_P.Filter_gainval_i *
    px4demo_AttitudeControllerJoy_B.Filter_hl;

  {                                    // Sample time: [0.01s, 0.0s]
  }

  // Update absolute time for base rate
  // The "clockTick0" counts the number of times the code of this task has
  //  been executed. The absolute time is the multiplication of "clockTick0"
  //  and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
  //  overflow during the application lifespan selected.

  px4demo_AttitudeControllerJo_M->Timing.taskTime0 =
    ((time_T)(++px4demo_AttitudeControllerJo_M->Timing.clockTick0)) *
    px4demo_AttitudeControllerJo_M->Timing.stepSize0;
}

// Model initialize function
void px4demo_AttitudeControllerJoystick_initialize(void)
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));
  rtmSetTFinal(px4demo_AttitudeControllerJo_M, -1);
  px4demo_AttitudeControllerJo_M->Timing.stepSize0 = 0.01;

  // External mode info
  px4demo_AttitudeControllerJo_M->Sizes.checksums[0] = (2420574868U);
  px4demo_AttitudeControllerJo_M->Sizes.checksums[1] = (1898507106U);
  px4demo_AttitudeControllerJo_M->Sizes.checksums[2] = (388896334U);
  px4demo_AttitudeControllerJo_M->Sizes.checksums[3] = (2764514578U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[12];
    px4demo_AttitudeControllerJo_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = (sysRanDType *)
      &px4demo_AttitudeControllerJo_DW.EnabledSubsystem_SubsysRanBC_c;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = (sysRanDType *)
      &px4demo_AttitudeControllerJo_DW.EnabledSubsystem_SubsysRanBC_g;
    systemRan[5] = &rtAlwaysEnabled;
    systemRan[6] = (sysRanDType *)
      &px4demo_AttitudeControllerJo_DW.EnabledSubsystem_SubsysRanBC;
    systemRan[7] = &rtAlwaysEnabled;
    systemRan[8] = (sysRanDType *)
      &px4demo_AttitudeControllerJo_DW.IfActionSubsystem_SubsysRanBC;
    systemRan[9] = (sysRanDType *)
      &px4demo_AttitudeControllerJo_DW.IfActionSubsystem1_SubsysRanBC;
    systemRan[10] = (sysRanDType *)
      &px4demo_AttitudeControllerJo_DW.IfActionSubsystem2_SubsysRanBC;
    systemRan[11] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(px4demo_AttitudeControllerJo_M->extModeInfo,
      &px4demo_AttitudeControllerJo_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(px4demo_AttitudeControllerJo_M->extModeInfo,
                        px4demo_AttitudeControllerJo_M->Sizes.checksums);
    rteiSetTPtr(px4demo_AttitudeControllerJo_M->extModeInfo, rtmGetTPtr
                (px4demo_AttitudeControllerJo_M));
  }

  {
    px4_Bus_actuator_armed rtb_BusAssignment;
    boolean_T rtb_NOT;

    // InitializeConditions for DiscreteIntegrator: '<S46>/Integrator'
    px4demo_AttitudeControllerJo_DW.Integrator_DSTATE =
      px4demo_AttitudeControllerJoy_P.PID_pitch_InitialConditionForIn;

    // InitializeConditions for DiscreteIntegrator: '<S41>/Filter'
    px4demo_AttitudeControllerJo_DW.Filter_DSTATE =
      px4demo_AttitudeControllerJoy_P.PID_pitch_InitialConditionForFi;

    // InitializeConditions for DiscreteIntegrator: '<S94>/Integrator'
    px4demo_AttitudeControllerJo_DW.Integrator_DSTATE_m =
      px4demo_AttitudeControllerJoy_P.PID_roll_InitialConditionForInt;

    // InitializeConditions for DiscreteIntegrator: '<S89>/Filter'
    px4demo_AttitudeControllerJo_DW.Filter_DSTATE_d =
      px4demo_AttitudeControllerJoy_P.PID_roll_InitialConditionForFil;

    // InitializeConditions for DiscreteIntegrator: '<S142>/Integrator'
    px4demo_AttitudeControllerJo_DW.Integrator_DSTATE_i =
      px4demo_AttitudeControllerJoy_P.PID_yaw_rate_InitialCondition_l;

    // InitializeConditions for DiscreteIntegrator: '<S137>/Filter'
    px4demo_AttitudeControllerJo_DW.Filter_DSTATE_k =
      px4demo_AttitudeControllerJoy_P.PID_yaw_rate_InitialConditionFo;

    // SystemInitialize for Enabled SubSystem: '<S4>/Enabled Subsystem'
    // SystemInitialize for SignalConversion generated from: '<S160>/In1' incorporates:
    //   Outport: '<S160>/Out1'

    px4demo_AttitudeControllerJoy_B.In1_p =
      px4demo_AttitudeControllerJoy_P.Out1_Y0_p;

    // End of SystemInitialize for SubSystem: '<S4>/Enabled Subsystem'

    // SystemInitialize for Enabled SubSystem: '<S3>/Enabled Subsystem'
    // SystemInitialize for SignalConversion generated from: '<S159>/In1' incorporates:
    //   Outport: '<S159>/Out1'

    px4demo_AttitudeControllerJoy_B.In1 =
      px4demo_AttitudeControllerJoy_P.Out1_Y0;

    // End of SystemInitialize for SubSystem: '<S3>/Enabled Subsystem'

    // SystemInitialize for Enabled SubSystem: '<S7>/Enabled Subsystem'
    // SystemInitialize for SignalConversion generated from: '<S9>/In1' incorporates:
    //   Outport: '<S9>/Out1'

    px4demo_AttitudeControllerJoy_B.In1_a =
      px4demo_AttitudeControllerJoy_P.Out1_Y0_n;

    // End of SystemInitialize for SubSystem: '<S7>/Enabled Subsystem'

    // Start for MATLABSystem: '<S4>/SourceBlock'
    px4demo_AttitudeControllerJo_DW.obj.matlabCodegenIsDeleted = false;
    px4demo_AttitudeControllerJo_DW.obj.isInitialized = 1;
    px4demo_AttitudeControllerJo_DW.obj.orbMetadataObj = ORB_ID
      (manual_control_setpoint);
    uORB_read_initialize(px4demo_AttitudeControllerJo_DW.obj.orbMetadataObj,
                         &px4demo_AttitudeControllerJo_DW.obj.eventStructObj);
    px4demo_AttitudeControllerJo_DW.obj.isSetupComplete = true;

    // Start for MATLABSystem: '<S3>/SourceBlock'
    px4demo_AttitudeControllerJo_DW.obj_d.matlabCodegenIsDeleted = false;
    px4demo_AttitudeControllerJo_DW.obj_d.isInitialized = 1;
    px4demo_AttitudeControllerJo_DW.obj_d.orbMetadataObj = ORB_ID
      (vehicle_odometry);
    uORB_read_initialize(px4demo_AttitudeControllerJo_DW.obj_d.orbMetadataObj,
                         &px4demo_AttitudeControllerJo_DW.obj_d.eventStructObj);
    px4demo_AttitudeControllerJo_DW.obj_d.isSetupComplete = true;

    // Start for MATLABSystem: '<S6>/PX4 PWM Output' incorporates:
    //   Constant: '<S6>/Reset'

    px4demo_AttitudeControllerJo_DW.obj_dx.errorStatus = 0U;
    px4demo_AttitudeControllerJo_DW.obj_dx.isInitialized = 0;
    px4demo_AttitudeControllerJo_DW.obj_dx.matlabCodegenIsDeleted = false;
    px4demo_Attitu_SystemCore_setup(&px4demo_AttitudeControllerJo_DW.obj_dx,
      rtb_NOT, px4demo_AttitudeControllerJoy_P.Reset_Value);

    // Start for MATLABSystem: '<S7>/SourceBlock'
    px4demo_AttitudeControllerJo_DW.obj_l.matlabCodegenIsDeleted = false;
    px4demo_AttitudeControllerJo_DW.obj_l.isInitialized = 1;
    px4demo_AttitudeControllerJo_DW.obj_l.orbMetadataObj = ORB_ID(actuator_armed);
    uORB_read_initialize(px4demo_AttitudeControllerJo_DW.obj_l.orbMetadataObj,
                         &px4demo_AttitudeControllerJo_DW.obj_l.eventStructObj);
    px4demo_AttitudeControllerJo_DW.obj_l.isSetupComplete = true;

    // Start for MATLABSystem: '<S8>/SinkBlock' incorporates:
    //   BusAssignment: '<S1>/Bus Assignment'

    px4demo_AttitudeControllerJo_DW.obj_e.matlabCodegenIsDeleted = false;
    px4demo_AttitudeControllerJo_DW.obj_e.isInitialized = 1;
    px4demo_AttitudeControllerJo_DW.obj_e.orbMetadataObj = ORB_ID(actuator_armed);
    uORB_write_initialize(px4demo_AttitudeControllerJo_DW.obj_e.orbMetadataObj,
                          &px4demo_AttitudeControllerJo_DW.obj_e.orbAdvertiseObj,
                          &rtb_BusAssignment, 1);
    px4demo_AttitudeControllerJo_DW.obj_e.isSetupComplete = true;
  }
}

// Model terminate function
void px4demo_AttitudeControllerJoystick_terminate(void)
{
  uint16_T status;

  // Terminate for MATLABSystem: '<S4>/SourceBlock'
  if (!px4demo_AttitudeControllerJo_DW.obj.matlabCodegenIsDeleted) {
    px4demo_AttitudeControllerJo_DW.obj.matlabCodegenIsDeleted = true;
    if ((px4demo_AttitudeControllerJo_DW.obj.isInitialized == 1) &&
        px4demo_AttitudeControllerJo_DW.obj.isSetupComplete) {
      uORB_read_terminate(&px4demo_AttitudeControllerJo_DW.obj.eventStructObj);
    }
  }

  // End of Terminate for MATLABSystem: '<S4>/SourceBlock'

  // Terminate for MATLABSystem: '<S3>/SourceBlock'
  if (!px4demo_AttitudeControllerJo_DW.obj_d.matlabCodegenIsDeleted) {
    px4demo_AttitudeControllerJo_DW.obj_d.matlabCodegenIsDeleted = true;
    if ((px4demo_AttitudeControllerJo_DW.obj_d.isInitialized == 1) &&
        px4demo_AttitudeControllerJo_DW.obj_d.isSetupComplete) {
      uORB_read_terminate(&px4demo_AttitudeControllerJo_DW.obj_d.eventStructObj);
    }
  }

  // End of Terminate for MATLABSystem: '<S3>/SourceBlock'

  // Terminate for MATLABSystem: '<S6>/PX4 PWM Output'
  if (!px4demo_AttitudeControllerJo_DW.obj_dx.matlabCodegenIsDeleted) {
    px4demo_AttitudeControllerJo_DW.obj_dx.matlabCodegenIsDeleted = true;
    if ((px4demo_AttitudeControllerJo_DW.obj_dx.isInitialized == 1) &&
        px4demo_AttitudeControllerJo_DW.obj_dx.isSetupComplete) {
      status = pwm_disarm(&px4demo_AttitudeControllerJo_DW.obj_dx.pwmDevHandler,
                          &px4demo_AttitudeControllerJo_DW.obj_dx.armAdvertiseObj);
      px4demo_AttitudeControllerJo_DW.obj_dx.errorStatus = static_cast<uint16_T>
        (px4demo_AttitudeControllerJo_DW.obj_dx.errorStatus | status);
      status = pwm_resetServo
        (&px4demo_AttitudeControllerJo_DW.obj_dx.pwmDevHandler,
         px4demo_AttitudeControllerJo_DW.obj_dx.servoCount,
         px4demo_AttitudeControllerJo_DW.obj_dx.channelMask,
         px4demo_AttitudeControllerJo_DW.obj_dx.isMain,
         &px4demo_AttitudeControllerJo_DW.obj_dx.actuatorAdvertiseObj);
      px4demo_AttitudeControllerJo_DW.obj_dx.errorStatus = static_cast<uint16_T>
        (px4demo_AttitudeControllerJo_DW.obj_dx.errorStatus | status);
      status = pwm_close(&px4demo_AttitudeControllerJo_DW.obj_dx.pwmDevHandler,
                         &px4demo_AttitudeControllerJo_DW.obj_dx.actuatorAdvertiseObj,
                         &px4demo_AttitudeControllerJo_DW.obj_dx.armAdvertiseObj);
      px4demo_AttitudeControllerJo_DW.obj_dx.errorStatus = static_cast<uint16_T>
        (px4demo_AttitudeControllerJo_DW.obj_dx.errorStatus | status);
    }
  }

  // End of Terminate for MATLABSystem: '<S6>/PX4 PWM Output'
  // Terminate for MATLABSystem: '<S7>/SourceBlock'
  if (!px4demo_AttitudeControllerJo_DW.obj_l.matlabCodegenIsDeleted) {
    px4demo_AttitudeControllerJo_DW.obj_l.matlabCodegenIsDeleted = true;
    if ((px4demo_AttitudeControllerJo_DW.obj_l.isInitialized == 1) &&
        px4demo_AttitudeControllerJo_DW.obj_l.isSetupComplete) {
      uORB_read_terminate(&px4demo_AttitudeControllerJo_DW.obj_l.eventStructObj);
    }
  }

  // End of Terminate for MATLABSystem: '<S7>/SourceBlock'
  // Terminate for MATLABSystem: '<S8>/SinkBlock'
  if (!px4demo_AttitudeControllerJo_DW.obj_e.matlabCodegenIsDeleted) {
    px4demo_AttitudeControllerJo_DW.obj_e.matlabCodegenIsDeleted = true;
    if ((px4demo_AttitudeControllerJo_DW.obj_e.isInitialized == 1) &&
        px4demo_AttitudeControllerJo_DW.obj_e.isSetupComplete) {
      uORB_write_terminate
        (&px4demo_AttitudeControllerJo_DW.obj_e.orbAdvertiseObj);
    }
  }

  // End of Terminate for MATLABSystem: '<S8>/SinkBlock'
}

//
// File trailer for generated code.
//
// [EOF]
//
