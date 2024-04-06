//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: cobaJoystick.cpp
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
#include "cobaJoystick_types.h"
#include "rtwtypes.h"
#include <math.h>
#include "cobaJoystick_private.h"

extern "C"
{

#include "rt_nonfinite.h"

}

#include "rt_defines.h"

// Block signals (default storage)
B_cobaJoystick_T cobaJoystick_B;

// Block states (default storage)
DW_cobaJoystick_T cobaJoystick_DW;

// Real-time model
RT_MODEL_cobaJoystick_T cobaJoystick_M_ = RT_MODEL_cobaJoystick_T();
RT_MODEL_cobaJoystick_T *const cobaJoystick_M = &cobaJoystick_M_;

// Forward declaration for local functions
static void cobaJoystick_SystemCore_setup(px4_internal_block_PWM_cobaJo_T *obj,
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

static void cobaJoystick_SystemCore_setup(px4_internal_block_PWM_cobaJo_T *obj,
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
void cobaJoystick_step(void)
{
  real_T rtb_FilterCoefficient;
  real_T rtb_fcn3;
  real_T tmp;
  real_T tmp_0;
  int32_T i;
  real32_T tmp_1;
  uint16_T rtb_Gain1_p[4];
  uint16_T status;
  boolean_T b_varargout_1;
  boolean_T b_varargout_1_0;
  boolean_T b_varargout_1_1;

  // Reset subsysRan breadcrumbs
  srClearBC(cobaJoystick_DW.EnabledSubsystem_SubsysRanBC_gz);

  // Reset subsysRan breadcrumbs
  srClearBC(cobaJoystick_DW.EnabledSubsystem_SubsysRanBC_g);

  // Reset subsysRan breadcrumbs
  srClearBC(cobaJoystick_DW.IfActionSubsystem_SubsysRanBC);

  // Reset subsysRan breadcrumbs
  srClearBC(cobaJoystick_DW.IfActionSubsystem1_SubsysRanBC);

  // Reset subsysRan breadcrumbs
  srClearBC(cobaJoystick_DW.IfActionSubsystem2_SubsysRanBC);

  // Reset subsysRan breadcrumbs
  srClearBC(cobaJoystick_DW.EnabledSubsystem_SubsysRanBC);

  // MATLABSystem: '<S3>/SourceBlock'
  b_varargout_1 = uORB_read_step(cobaJoystick_DW.obj_o.orbMetadataObj,
    &cobaJoystick_DW.obj_o.eventStructObj, &cobaJoystick_B.b_varargout_2_m,
    false, 1.0);

  // Outputs for Enabled SubSystem: '<S3>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S156>/Enable'

  if (b_varargout_1) {
    // SignalConversion generated from: '<S156>/In1'
    cobaJoystick_B.In1_p = cobaJoystick_B.b_varargout_2_m;
    srUpdateBC(cobaJoystick_DW.EnabledSubsystem_SubsysRanBC_g);
  }

  // End of Outputs for SubSystem: '<S3>/Enabled Subsystem'

  // SignalConversion generated from: '<Root>/Bus Selector'
  cobaJoystick_B.z = cobaJoystick_B.In1_p.z;

  // MATLABSystem: '<S2>/SourceBlock'
  b_varargout_1_0 = uORB_read_step(cobaJoystick_DW.obj_d.orbMetadataObj,
    &cobaJoystick_DW.obj_d.eventStructObj, &cobaJoystick_B.b_varargout_2, false,
    1.0);

  // Outputs for Enabled SubSystem: '<S2>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S155>/Enable'

  if (b_varargout_1_0) {
    // SignalConversion generated from: '<S155>/In1'
    cobaJoystick_B.In1 = cobaJoystick_B.b_varargout_2;
    srUpdateBC(cobaJoystick_DW.EnabledSubsystem_SubsysRanBC_gz);
  }

  // End of Outputs for SubSystem: '<S2>/Enabled Subsystem'

  // Sqrt: '<S163>/sqrt' incorporates:
  //   DataTypeConversion: '<Root>/Data Type Conversion1'
  //   Product: '<S164>/Product'
  //   Product: '<S164>/Product1'
  //   Product: '<S164>/Product2'
  //   Product: '<S164>/Product3'
  //   Sum: '<S164>/Sum'

  cobaJoystick_B.Saturation_l = sqrt(((static_cast<real_T>(cobaJoystick_B.In1.q
    [0]) * cobaJoystick_B.In1.q[0] + static_cast<real_T>(cobaJoystick_B.In1.q[1])
    * cobaJoystick_B.In1.q[1]) + static_cast<real_T>(cobaJoystick_B.In1.q[2]) *
    cobaJoystick_B.In1.q[2]) + static_cast<real_T>(cobaJoystick_B.In1.q[3]) *
    cobaJoystick_B.In1.q[3]);

  // Product: '<S158>/Product' incorporates:
  //   DataTypeConversion: '<Root>/Data Type Conversion1'

  cobaJoystick_B.Filter_o = cobaJoystick_B.In1.q[0] /
    cobaJoystick_B.Saturation_l;

  // Product: '<S158>/Product1' incorporates:
  //   DataTypeConversion: '<Root>/Data Type Conversion1'

  cobaJoystick_B.Saturation_f = cobaJoystick_B.In1.q[1] /
    cobaJoystick_B.Saturation_l;

  // Product: '<S158>/Product2' incorporates:
  //   DataTypeConversion: '<Root>/Data Type Conversion1'

  cobaJoystick_B.Filter = cobaJoystick_B.In1.q[2] / cobaJoystick_B.Saturation_l;

  // Product: '<S158>/Product3' incorporates:
  //   DataTypeConversion: '<Root>/Data Type Conversion1'

  cobaJoystick_B.Saturation_l = cobaJoystick_B.In1.q[3] /
    cobaJoystick_B.Saturation_l;

  // Fcn: '<S4>/fcn3'
  rtb_fcn3 = (cobaJoystick_B.Saturation_f * cobaJoystick_B.Saturation_l -
              cobaJoystick_B.Filter_o * cobaJoystick_B.Filter) * -2.0;

  // If: '<S159>/If' incorporates:
  //   Constant: '<S160>/Constant'
  //   Constant: '<S161>/Constant'

  if (rtb_fcn3 > 1.0) {
    // Outputs for IfAction SubSystem: '<S159>/If Action Subsystem' incorporates:
    //   ActionPort: '<S160>/Action Port'

    rtb_fcn3 = cobaJoystick_P.Constant_Value_l;

    // End of Outputs for SubSystem: '<S159>/If Action Subsystem'

    // Update for IfAction SubSystem: '<S159>/If Action Subsystem' incorporates:
    //   ActionPort: '<S160>/Action Port'

    // Update for If: '<S159>/If' incorporates:
    //   Constant: '<S160>/Constant'

    srUpdateBC(cobaJoystick_DW.IfActionSubsystem_SubsysRanBC);

    // End of Update for SubSystem: '<S159>/If Action Subsystem'
  } else if (rtb_fcn3 < -1.0) {
    // Outputs for IfAction SubSystem: '<S159>/If Action Subsystem1' incorporates:
    //   ActionPort: '<S161>/Action Port'

    rtb_fcn3 = cobaJoystick_P.Constant_Value_i;

    // End of Outputs for SubSystem: '<S159>/If Action Subsystem1'

    // Update for IfAction SubSystem: '<S159>/If Action Subsystem1' incorporates:
    //   ActionPort: '<S161>/Action Port'

    // Update for If: '<S159>/If' incorporates:
    //   Constant: '<S161>/Constant'

    srUpdateBC(cobaJoystick_DW.IfActionSubsystem1_SubsysRanBC);

    // End of Update for SubSystem: '<S159>/If Action Subsystem1'
  } else {
    // Update for IfAction SubSystem: '<S159>/If Action Subsystem2' incorporates:
    //   ActionPort: '<S162>/Action Port'

    // Update for If: '<S159>/If'
    srUpdateBC(cobaJoystick_DW.IfActionSubsystem2_SubsysRanBC);

    // End of Update for SubSystem: '<S159>/If Action Subsystem2'
  }

  // End of If: '<S159>/If'

  // SignalConversion generated from: '<Root>/Bus Selector'
  cobaJoystick_B.x = cobaJoystick_B.In1_p.x;

  // Trigonometry: '<S157>/trigFcn'
  if (rtb_fcn3 > 1.0) {
    rtb_fcn3 = 1.0;
  } else if (rtb_fcn3 < -1.0) {
    rtb_fcn3 = -1.0;
  }

  // DeadZone: '<Root>/Deadband'
  if (cobaJoystick_B.x > cobaJoystick_P.Deadband_End) {
    tmp_1 = cobaJoystick_B.x - cobaJoystick_P.Deadband_End;
  } else if (cobaJoystick_B.x >= cobaJoystick_P.Deadband_Start) {
    tmp_1 = 0.0F;
  } else {
    tmp_1 = cobaJoystick_B.x - cobaJoystick_P.Deadband_Start;
  }

  // Sum: '<S1>/Add2' incorporates:
  //   DeadZone: '<Root>/Deadband'
  //   Gain: '<S1>/Gain'
  //   Gain: '<S6>/Gain1'
  //   Trigonometry: '<S157>/trigFcn'

  rtb_fcn3 = asin(rtb_fcn3) - cobaJoystick_P.Gain_Gain * tmp_1 *
    cobaJoystick_P.Gain1_Gain_n;

  // DiscreteIntegrator: '<S42>/Integrator' incorporates:
  //   Gain: '<S39>/Integral Gain'

  cobaJoystick_DW.Integrator_DSTATE += cobaJoystick_P.PID_pitch_I * rtb_fcn3 *
    cobaJoystick_P.Integrator_gainval;

  // Gain: '<S45>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S37>/Filter'
  //   Gain: '<S36>/Derivative Gain'
  //   Sum: '<S37>/SumD'

  rtb_FilterCoefficient = (cobaJoystick_P.PID_pitch_D * rtb_fcn3 -
    cobaJoystick_DW.Filter_DSTATE) * cobaJoystick_P.PID_pitch_N;

  // SignalConversion generated from: '<Root>/Bus Selector'
  cobaJoystick_B.y = cobaJoystick_B.In1_p.y;

  // DeadZone: '<Root>/Deadband1'
  if (cobaJoystick_B.y > cobaJoystick_P.Deadband1_End) {
    tmp_1 = cobaJoystick_B.y - cobaJoystick_P.Deadband1_End;
  } else if (cobaJoystick_B.y >= cobaJoystick_P.Deadband1_Start) {
    tmp_1 = 0.0F;
  } else {
    tmp_1 = cobaJoystick_B.y - cobaJoystick_P.Deadband1_Start;
  }

  // Sum: '<S1>/Add3' incorporates:
  //   DeadZone: '<Root>/Deadband1'
  //   Fcn: '<S4>/fcn4'
  //   Fcn: '<S4>/fcn5'
  //   Gain: '<S1>/Gain1'
  //   Gain: '<S7>/Gain1'
  //   Trigonometry: '<S157>/Trigonometric Function3'

  cobaJoystick_B.Filter_o = rt_atan2d_snf((cobaJoystick_B.Filter *
    cobaJoystick_B.Saturation_l + cobaJoystick_B.Filter_o *
    cobaJoystick_B.Saturation_f) * 2.0, ((cobaJoystick_B.Filter_o *
    cobaJoystick_B.Filter_o - cobaJoystick_B.Saturation_f *
    cobaJoystick_B.Saturation_f) - cobaJoystick_B.Filter * cobaJoystick_B.Filter)
    + cobaJoystick_B.Saturation_l * cobaJoystick_B.Saturation_l) -
    cobaJoystick_P.Gain1_Gain_g * tmp_1 * cobaJoystick_P.Gain1_Gain_c;

  // DiscreteIntegrator: '<S90>/Integrator' incorporates:
  //   Gain: '<S87>/Integral Gain'

  cobaJoystick_DW.Integrator_DSTATE_m += cobaJoystick_P.PID_roll_I *
    cobaJoystick_B.Filter_o * cobaJoystick_P.Integrator_gainval_e;

  // Gain: '<S93>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S85>/Filter'
  //   Gain: '<S84>/Derivative Gain'
  //   Sum: '<S85>/SumD'

  cobaJoystick_B.Saturation_f = (cobaJoystick_P.PID_roll_D *
    cobaJoystick_B.Filter_o - cobaJoystick_DW.Filter_DSTATE_d) *
    cobaJoystick_P.PID_roll_N;

  // SignalConversion generated from: '<Root>/Bus Selector'
  cobaJoystick_B.r = cobaJoystick_B.In1_p.r;

  // DeadZone: '<Root>/Deadband2'
  if (cobaJoystick_B.r > cobaJoystick_P.Deadband2_End) {
    tmp_1 = cobaJoystick_B.r - cobaJoystick_P.Deadband2_End;
  } else if (cobaJoystick_B.r >= cobaJoystick_P.Deadband2_Start) {
    tmp_1 = 0.0F;
  } else {
    tmp_1 = cobaJoystick_B.r - cobaJoystick_P.Deadband2_Start;
  }

  // Sum: '<S1>/Add1' incorporates:
  //   DataTypeConversion: '<S1>/Data Type Conversion2'
  //   DeadZone: '<Root>/Deadband2'

  cobaJoystick_B.Saturation_l = static_cast<real_T>(tmp_1) -
    cobaJoystick_B.In1.yawspeed;

  // DiscreteIntegrator: '<S138>/Integrator' incorporates:
  //   Gain: '<S135>/Integral Gain'

  cobaJoystick_DW.Integrator_DSTATE_i += cobaJoystick_P.PID_yaw_rate_I *
    cobaJoystick_B.Saturation_l * cobaJoystick_P.Integrator_gainval_b;

  // Gain: '<S141>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S133>/Filter'
  //   Gain: '<S132>/Derivative Gain'
  //   Sum: '<S133>/SumD'

  cobaJoystick_B.Filter = (cobaJoystick_P.PID_yaw_rate_D *
    cobaJoystick_B.Saturation_l - cobaJoystick_DW.Filter_DSTATE_k) *
    cobaJoystick_P.PID_yaw_rate_N;

  // Sum: '<S51>/Sum' incorporates:
  //   Gain: '<S47>/Proportional Gain'

  rtb_fcn3 = (cobaJoystick_P.PID_pitch_P * rtb_fcn3 +
              cobaJoystick_DW.Integrator_DSTATE) + rtb_FilterCoefficient;

  // Saturate: '<S49>/Saturation'
  if (rtb_fcn3 > cobaJoystick_P.PID_pitch_UpperSaturationLimit) {
    rtb_fcn3 = cobaJoystick_P.PID_pitch_UpperSaturationLimit;
  } else if (rtb_fcn3 < cobaJoystick_P.PID_pitch_LowerSaturationLimit) {
    rtb_fcn3 = cobaJoystick_P.PID_pitch_LowerSaturationLimit;
  }

  // Sum: '<S99>/Sum' incorporates:
  //   Gain: '<S95>/Proportional Gain'

  cobaJoystick_B.Filter_o = (cobaJoystick_P.PID_roll_P * cobaJoystick_B.Filter_o
    + cobaJoystick_DW.Integrator_DSTATE_m) + cobaJoystick_B.Saturation_f;

  // Saturate: '<S97>/Saturation'
  if (cobaJoystick_B.Filter_o > cobaJoystick_P.PID_roll_UpperSaturationLimit) {
    cobaJoystick_B.Filter_o = cobaJoystick_P.PID_roll_UpperSaturationLimit;
  } else if (cobaJoystick_B.Filter_o <
             cobaJoystick_P.PID_roll_LowerSaturationLimit) {
    cobaJoystick_B.Filter_o = cobaJoystick_P.PID_roll_LowerSaturationLimit;
  }

  // Sum: '<S147>/Sum' incorporates:
  //   Gain: '<S143>/Proportional Gain'

  cobaJoystick_B.Saturation_l = (cobaJoystick_P.PID_yaw_rate_P *
    cobaJoystick_B.Saturation_l + cobaJoystick_DW.Integrator_DSTATE_i) +
    cobaJoystick_B.Filter;

  // Saturate: '<S145>/Saturation'
  if (cobaJoystick_B.Saturation_l >
      cobaJoystick_P.PID_yaw_rate_UpperSaturationLim) {
    cobaJoystick_B.Saturation_l = cobaJoystick_P.PID_yaw_rate_UpperSaturationLim;
  } else if (cobaJoystick_B.Saturation_l <
             cobaJoystick_P.PID_yaw_rate_LowerSaturationLim) {
    cobaJoystick_B.Saturation_l = cobaJoystick_P.PID_yaw_rate_LowerSaturationLim;
  }

  // SignalConversion generated from: '<S5>/Product1' incorporates:
  //   Constant: '<S5>/Constant'
  //   Sum: '<S5>/Add'

  tmp = cobaJoystick_P.Constant_Value_cv + cobaJoystick_B.z;
  for (i = 0; i < 4; i++) {
    // Gain: '<S5>/Gain1' incorporates:
    //   Constant: '<S5>/Mixer matrix'
    //   Product: '<S5>/Product1'
    //   Saturate: '<S145>/Saturation'
    //   Saturate: '<S49>/Saturation'
    //   Saturate: '<S97>/Saturation'

    tmp_0 = floor((((cobaJoystick_P.Mixermatrix_Value[i + 4] * rtb_fcn3 +
                     cobaJoystick_P.Mixermatrix_Value[i] * tmp) +
                    cobaJoystick_P.Mixermatrix_Value[i + 8] *
                    cobaJoystick_B.Filter_o) +
                   cobaJoystick_P.Mixermatrix_Value[i + 12] *
                   cobaJoystick_B.Saturation_l) * cobaJoystick_P.Gain1_Gain);
    if (rtIsNaN(tmp_0) || rtIsInf(tmp_0)) {
      tmp_0 = 0.0;
    } else {
      tmp_0 = fmod(tmp_0, 65536.0);
    }

    rtb_Gain1_p[i] = static_cast<uint16_T>(tmp_0 < 0.0 ? static_cast<int32_T>(
      static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>(-tmp_0))))
      : static_cast<int32_T>(static_cast<uint16_T>(tmp_0)));

    // End of Gain: '<S5>/Gain1'
  }

  // MATLABSystem: '<S165>/SourceBlock'
  b_varargout_1_1 = uORB_read_step(cobaJoystick_DW.obj.orbMetadataObj,
    &cobaJoystick_DW.obj.eventStructObj, &cobaJoystick_B.b_varargout_2_c, false,
    1.0);

  // Outputs for Enabled SubSystem: '<S165>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S166>/Enable'

  if (b_varargout_1_1) {
    // SignalConversion generated from: '<S166>/In1'
    cobaJoystick_B.In1_f = cobaJoystick_B.b_varargout_2_c;
    srUpdateBC(cobaJoystick_DW.EnabledSubsystem_SubsysRanBC);
  }

  // End of MATLABSystem: '<S165>/SourceBlock'
  // End of Outputs for SubSystem: '<S165>/Enabled Subsystem'

  // SignalConversion generated from: '<S5>/Bus Selector'
  cobaJoystick_B.armed = cobaJoystick_B.In1_f.armed;

  // MATLABSystem: '<S5>/PX4 PWM Output' incorporates:
  //   Constant: '<S5>/Reset'

  for (i = 0; i < 8; i++) {
    cobaJoystick_B.pwmValue[i] = 0U;
  }

  cobaJoystick_B.pwmValue[0] = rtb_Gain1_p[0];
  cobaJoystick_B.pwmValue[1] = rtb_Gain1_p[1];
  cobaJoystick_B.pwmValue[2] = rtb_Gain1_p[2];
  cobaJoystick_B.pwmValue[3] = rtb_Gain1_p[3];
  if (cobaJoystick_B.armed) {
    if (!cobaJoystick_DW.obj_l.isArmed) {
      cobaJoystick_DW.obj_l.isArmed = true;
      status = pwm_arm(&cobaJoystick_DW.obj_l.pwmDevHandler,
                       &cobaJoystick_DW.obj_l.armAdvertiseObj);
      cobaJoystick_DW.obj_l.errorStatus = static_cast<uint16_T>
        (cobaJoystick_DW.obj_l.errorStatus | status);
    }

    status = pwm_setServo(&cobaJoystick_DW.obj_l.pwmDevHandler,
                          cobaJoystick_DW.obj_l.servoCount,
                          cobaJoystick_DW.obj_l.channelMask,
                          &cobaJoystick_B.pwmValue[0],
                          cobaJoystick_DW.obj_l.isMain,
                          &cobaJoystick_DW.obj_l.actuatorAdvertiseObj);
    cobaJoystick_DW.obj_l.errorStatus = static_cast<uint16_T>
      (cobaJoystick_DW.obj_l.errorStatus | status);
  } else {
    status = pwm_disarm(&cobaJoystick_DW.obj_l.pwmDevHandler,
                        &cobaJoystick_DW.obj_l.armAdvertiseObj);
    cobaJoystick_DW.obj_l.errorStatus = static_cast<uint16_T>
      (cobaJoystick_DW.obj_l.errorStatus | status);
    cobaJoystick_DW.obj_l.isArmed = false;
    status = pwm_resetServo(&cobaJoystick_DW.obj_l.pwmDevHandler,
      cobaJoystick_DW.obj_l.servoCount, cobaJoystick_DW.obj_l.channelMask,
      cobaJoystick_DW.obj_l.isMain, &cobaJoystick_DW.obj_l.actuatorAdvertiseObj);
    cobaJoystick_DW.obj_l.errorStatus = static_cast<uint16_T>
      (cobaJoystick_DW.obj_l.errorStatus | status);
  }

  if (cobaJoystick_DW.obj_l.isMain) {
    status = pwm_forceFailsafe(&cobaJoystick_DW.obj_l.pwmDevHandler,
      static_cast<int32_T>(cobaJoystick_P.Reset_Value));
    cobaJoystick_DW.obj_l.errorStatus = static_cast<uint16_T>
      (cobaJoystick_DW.obj_l.errorStatus | status);
  }

  // End of MATLABSystem: '<S5>/PX4 PWM Output'
  // Logic: '<S2>/NOT' incorporates:
  //   MATLABSystem: '<S2>/SourceBlock'

  cobaJoystick_B.NOT = !b_varargout_1_0;

  // Logic: '<S3>/NOT' incorporates:
  //   MATLABSystem: '<S3>/SourceBlock'

  cobaJoystick_B.NOT_b = !b_varargout_1;

  // Update for DiscreteIntegrator: '<S37>/Filter'
  cobaJoystick_DW.Filter_DSTATE += cobaJoystick_P.Filter_gainval *
    rtb_FilterCoefficient;

  // Update for DiscreteIntegrator: '<S85>/Filter'
  cobaJoystick_DW.Filter_DSTATE_d += cobaJoystick_P.Filter_gainval_j *
    cobaJoystick_B.Saturation_f;

  // Update for DiscreteIntegrator: '<S133>/Filter'
  cobaJoystick_DW.Filter_DSTATE_k += cobaJoystick_P.Filter_gainval_i *
    cobaJoystick_B.Filter;

  {                                    // Sample time: [0.2s, 0.0s]
  }

  // Update absolute time for base rate
  // The "clockTick0" counts the number of times the code of this task has
  //  been executed. The absolute time is the multiplication of "clockTick0"
  //  and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
  //  overflow during the application lifespan selected.

  cobaJoystick_M->Timing.taskTime0 =
    ((time_T)(++cobaJoystick_M->Timing.clockTick0)) *
    cobaJoystick_M->Timing.stepSize0;
}

// Model initialize function
void cobaJoystick_initialize(void)
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));
  rtmSetTFinal(cobaJoystick_M, -1);
  cobaJoystick_M->Timing.stepSize0 = 0.2;

  // External mode info
  cobaJoystick_M->Sizes.checksums[0] = (2249833342U);
  cobaJoystick_M->Sizes.checksums[1] = (3106580552U);
  cobaJoystick_M->Sizes.checksums[2] = (3845480400U);
  cobaJoystick_M->Sizes.checksums[3] = (3032345513U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[11];
    cobaJoystick_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = (sysRanDType *)
      &cobaJoystick_DW.EnabledSubsystem_SubsysRanBC_gz;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = (sysRanDType *)
      &cobaJoystick_DW.EnabledSubsystem_SubsysRanBC_g;
    systemRan[4] = &rtAlwaysEnabled;
    systemRan[5] = (sysRanDType *)&cobaJoystick_DW.IfActionSubsystem_SubsysRanBC;
    systemRan[6] = (sysRanDType *)
      &cobaJoystick_DW.IfActionSubsystem1_SubsysRanBC;
    systemRan[7] = (sysRanDType *)
      &cobaJoystick_DW.IfActionSubsystem2_SubsysRanBC;
    systemRan[8] = &rtAlwaysEnabled;
    systemRan[9] = (sysRanDType *)&cobaJoystick_DW.EnabledSubsystem_SubsysRanBC;
    systemRan[10] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(cobaJoystick_M->extModeInfo,
      &cobaJoystick_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(cobaJoystick_M->extModeInfo,
                        cobaJoystick_M->Sizes.checksums);
    rteiSetTPtr(cobaJoystick_M->extModeInfo, rtmGetTPtr(cobaJoystick_M));
  }

  // InitializeConditions for DiscreteIntegrator: '<S42>/Integrator'
  cobaJoystick_DW.Integrator_DSTATE =
    cobaJoystick_P.PID_pitch_InitialConditionForIn;

  // InitializeConditions for DiscreteIntegrator: '<S37>/Filter'
  cobaJoystick_DW.Filter_DSTATE = cobaJoystick_P.PID_pitch_InitialConditionForFi;

  // InitializeConditions for DiscreteIntegrator: '<S90>/Integrator'
  cobaJoystick_DW.Integrator_DSTATE_m =
    cobaJoystick_P.PID_roll_InitialConditionForInt;

  // InitializeConditions for DiscreteIntegrator: '<S85>/Filter'
  cobaJoystick_DW.Filter_DSTATE_d =
    cobaJoystick_P.PID_roll_InitialConditionForFil;

  // InitializeConditions for DiscreteIntegrator: '<S138>/Integrator'
  cobaJoystick_DW.Integrator_DSTATE_i =
    cobaJoystick_P.PID_yaw_rate_InitialCondition_l;

  // InitializeConditions for DiscreteIntegrator: '<S133>/Filter'
  cobaJoystick_DW.Filter_DSTATE_k =
    cobaJoystick_P.PID_yaw_rate_InitialConditionFo;

  // SystemInitialize for Enabled SubSystem: '<S3>/Enabled Subsystem'
  // SystemInitialize for SignalConversion generated from: '<S156>/In1' incorporates:
  //   Outport: '<S156>/Out1'

  cobaJoystick_B.In1_p = cobaJoystick_P.Out1_Y0_p;

  // End of SystemInitialize for SubSystem: '<S3>/Enabled Subsystem'

  // SystemInitialize for Enabled SubSystem: '<S2>/Enabled Subsystem'
  // SystemInitialize for SignalConversion generated from: '<S155>/In1' incorporates:
  //   Outport: '<S155>/Out1'

  cobaJoystick_B.In1 = cobaJoystick_P.Out1_Y0;

  // End of SystemInitialize for SubSystem: '<S2>/Enabled Subsystem'

  // SystemInitialize for Enabled SubSystem: '<S165>/Enabled Subsystem'
  // SystemInitialize for SignalConversion generated from: '<S166>/In1' incorporates:
  //   Outport: '<S166>/Out1'

  cobaJoystick_B.In1_f = cobaJoystick_P.Out1_Y0_k;

  // End of SystemInitialize for SubSystem: '<S165>/Enabled Subsystem'

  // Start for MATLABSystem: '<S3>/SourceBlock'
  cobaJoystick_DW.obj_o.matlabCodegenIsDeleted = false;
  cobaJoystick_DW.obj_o.isInitialized = 1;
  cobaJoystick_DW.obj_o.orbMetadataObj = ORB_ID(manual_control_setpoint);
  uORB_read_initialize(cobaJoystick_DW.obj_o.orbMetadataObj,
                       &cobaJoystick_DW.obj_o.eventStructObj);
  cobaJoystick_DW.obj_o.isSetupComplete = true;

  // Start for MATLABSystem: '<S2>/SourceBlock'
  cobaJoystick_DW.obj_d.matlabCodegenIsDeleted = false;
  cobaJoystick_DW.obj_d.isInitialized = 1;
  cobaJoystick_DW.obj_d.orbMetadataObj = ORB_ID(vehicle_odometry);
  uORB_read_initialize(cobaJoystick_DW.obj_d.orbMetadataObj,
                       &cobaJoystick_DW.obj_d.eventStructObj);
  cobaJoystick_DW.obj_d.isSetupComplete = true;

  // Start for MATLABSystem: '<S165>/SourceBlock'
  cobaJoystick_DW.obj.matlabCodegenIsDeleted = false;
  cobaJoystick_DW.obj.isInitialized = 1;
  cobaJoystick_DW.obj.orbMetadataObj = ORB_ID(actuator_armed);
  uORB_read_initialize(cobaJoystick_DW.obj.orbMetadataObj,
                       &cobaJoystick_DW.obj.eventStructObj);
  cobaJoystick_DW.obj.isSetupComplete = true;

  // Start for MATLABSystem: '<S5>/PX4 PWM Output' incorporates:
  //   Constant: '<S5>/Reset'

  cobaJoystick_DW.obj_l.errorStatus = 0U;
  cobaJoystick_DW.obj_l.isInitialized = 0;
  cobaJoystick_DW.obj_l.matlabCodegenIsDeleted = false;
  cobaJoystick_SystemCore_setup(&cobaJoystick_DW.obj_l, cobaJoystick_B.armed,
    cobaJoystick_P.Reset_Value);
}

// Model terminate function
void cobaJoystick_terminate(void)
{
  uint16_T status;

  // Terminate for MATLABSystem: '<S3>/SourceBlock'
  if (!cobaJoystick_DW.obj_o.matlabCodegenIsDeleted) {
    cobaJoystick_DW.obj_o.matlabCodegenIsDeleted = true;
    if ((cobaJoystick_DW.obj_o.isInitialized == 1) &&
        cobaJoystick_DW.obj_o.isSetupComplete) {
      uORB_read_terminate(&cobaJoystick_DW.obj_o.eventStructObj);
    }
  }

  // End of Terminate for MATLABSystem: '<S3>/SourceBlock'

  // Terminate for MATLABSystem: '<S2>/SourceBlock'
  if (!cobaJoystick_DW.obj_d.matlabCodegenIsDeleted) {
    cobaJoystick_DW.obj_d.matlabCodegenIsDeleted = true;
    if ((cobaJoystick_DW.obj_d.isInitialized == 1) &&
        cobaJoystick_DW.obj_d.isSetupComplete) {
      uORB_read_terminate(&cobaJoystick_DW.obj_d.eventStructObj);
    }
  }

  // End of Terminate for MATLABSystem: '<S2>/SourceBlock'

  // Terminate for MATLABSystem: '<S165>/SourceBlock'
  if (!cobaJoystick_DW.obj.matlabCodegenIsDeleted) {
    cobaJoystick_DW.obj.matlabCodegenIsDeleted = true;
    if ((cobaJoystick_DW.obj.isInitialized == 1) &&
        cobaJoystick_DW.obj.isSetupComplete) {
      uORB_read_terminate(&cobaJoystick_DW.obj.eventStructObj);
    }
  }

  // End of Terminate for MATLABSystem: '<S165>/SourceBlock'

  // Terminate for MATLABSystem: '<S5>/PX4 PWM Output'
  if (!cobaJoystick_DW.obj_l.matlabCodegenIsDeleted) {
    cobaJoystick_DW.obj_l.matlabCodegenIsDeleted = true;
    if ((cobaJoystick_DW.obj_l.isInitialized == 1) &&
        cobaJoystick_DW.obj_l.isSetupComplete) {
      status = pwm_disarm(&cobaJoystick_DW.obj_l.pwmDevHandler,
                          &cobaJoystick_DW.obj_l.armAdvertiseObj);
      cobaJoystick_DW.obj_l.errorStatus = static_cast<uint16_T>
        (cobaJoystick_DW.obj_l.errorStatus | status);
      status = pwm_resetServo(&cobaJoystick_DW.obj_l.pwmDevHandler,
        cobaJoystick_DW.obj_l.servoCount, cobaJoystick_DW.obj_l.channelMask,
        cobaJoystick_DW.obj_l.isMain,
        &cobaJoystick_DW.obj_l.actuatorAdvertiseObj);
      cobaJoystick_DW.obj_l.errorStatus = static_cast<uint16_T>
        (cobaJoystick_DW.obj_l.errorStatus | status);
      status = pwm_close(&cobaJoystick_DW.obj_l.pwmDevHandler,
                         &cobaJoystick_DW.obj_l.actuatorAdvertiseObj,
                         &cobaJoystick_DW.obj_l.armAdvertiseObj);
      cobaJoystick_DW.obj_l.errorStatus = static_cast<uint16_T>
        (cobaJoystick_DW.obj_l.errorStatus | status);
    }
  }

  // End of Terminate for MATLABSystem: '<S5>/PX4 PWM Output'
}

//
// File trailer for generated code.
//
// [EOF]
//
