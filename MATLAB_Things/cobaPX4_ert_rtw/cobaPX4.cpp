//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: cobaPX4.cpp
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
#include "cobaPX4.h"
#include "cobaPX4_types.h"
#include "rtwtypes.h"
#include <math.h>

extern "C"
{

#include "rt_nonfinite.h"

}

#include <uORB/topics/actuator_armed.h>
#include "cobaPX4_private.h"

// Block signals (default storage)
B_cobaPX4_T cobaPX4_B;

// Block states (default storage)
DW_cobaPX4_T cobaPX4_DW;

// Real-time model
RT_MODEL_cobaPX4_T cobaPX4_M_ = RT_MODEL_cobaPX4_T();
RT_MODEL_cobaPX4_T *const cobaPX4_M = &cobaPX4_M_;

// Forward declaration for local functions
static void cobaPX4_SystemCore_setup(px4_internal_block_PWM_cobaPX_T *obj,
  boolean_T varargin_1, boolean_T varargin_2);
static void cobaPX4_SystemCore_setup(px4_internal_block_PWM_cobaPX_T *obj,
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
void cobaPX4_step(void)
{
  px4_Bus_actuator_armed b_varargout_2;
  real_T rtb_Filter;
  real_T rtb_FilterCoefficient;
  int32_T i;
  uint16_T pwmValue[8];
  uint16_T rtb_Gain;
  boolean_T b_varargout_1;

  // Reset subsysRan breadcrumbs
  srClearBC(cobaPX4_DW.EnabledSubsystem_SubsysRanBC_p);

  // Reset subsysRan breadcrumbs
  srClearBC(cobaPX4_DW.EnabledSubsystem_SubsysRanBC);

  // MATLABSystem: '<S2>/SourceBlock'
  b_varargout_1 = uORB_read_step(cobaPX4_DW.obj_n.orbMetadataObj,
    &cobaPX4_DW.obj_n.eventStructObj, &b_varargout_2, false, 1.0);

  // Outputs for Enabled SubSystem: '<S2>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S52>/Enable'

  if (b_varargout_1) {
    // SignalConversion generated from: '<S52>/In1'
    cobaPX4_B.In1_n = b_varargout_2;
    srUpdateBC(cobaPX4_DW.EnabledSubsystem_SubsysRanBC_p);
  }

  // End of MATLABSystem: '<S2>/SourceBlock'
  // End of Outputs for SubSystem: '<S2>/Enabled Subsystem'

  // SignalConversion generated from: '<Root>/Bus Selector3'
  cobaPX4_B.armed = cobaPX4_B.In1_n.armed;

  // Constant: '<Root>/Constant1'
  cobaPX4_B.Constant1 = cobaPX4_P.Constant1_Value;

  // MATLABSystem: '<S3>/SourceBlock'
  b_varargout_1 = uORB_read_step(cobaPX4_DW.obj_d.orbMetadataObj,
    &cobaPX4_DW.obj_d.eventStructObj, &cobaPX4_B.b_varargout_2, false, 1.0);

  // Outputs for Enabled SubSystem: '<S3>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S53>/Enable'

  if (b_varargout_1) {
    // SignalConversion generated from: '<S53>/In1'
    cobaPX4_B.In1 = cobaPX4_B.b_varargout_2;
    srUpdateBC(cobaPX4_DW.EnabledSubsystem_SubsysRanBC);
  }

  // End of MATLABSystem: '<S3>/SourceBlock'
  // End of Outputs for SubSystem: '<S3>/Enabled Subsystem'

  // SignalConversion generated from: '<Root>/Bus Selector1'
  cobaPX4_B.z = cobaPX4_B.In1.z;

  // Gain: '<Root>/Gain1'
  cobaPX4_B.Gain1 = cobaPX4_P.Gain1_Gain * cobaPX4_B.z;

  // Sum: '<Root>/Sum'
  rtb_Filter = cobaPX4_B.Constant1 - cobaPX4_B.Gain1;

  // Gain: '<S38>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S30>/Filter'
  //   Gain: '<S29>/Derivative Gain'
  //   Sum: '<S30>/SumD'

  rtb_FilterCoefficient = (cobaPX4_P.PIDController1_D * rtb_Filter -
    cobaPX4_DW.Filter_DSTATE) * cobaPX4_P.PIDController1_N;

  // Gain: '<Root>/Gain' incorporates:
  //   Gain: '<S40>/Proportional Gain'
  //   Sum: '<S44>/Sum'

  rtb_Filter = floor((cobaPX4_P.PIDController1_P * rtb_Filter +
                      rtb_FilterCoefficient) * cobaPX4_P.Gain_Gain);
  if (rtIsNaN(rtb_Filter) || rtIsInf(rtb_Filter)) {
    rtb_Filter = 0.0;
  } else {
    rtb_Filter = fmod(rtb_Filter, 65536.0);
  }

  rtb_Gain = static_cast<uint16_T>(rtb_Filter < 0.0 ? static_cast<int32_T>(
    static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
    (-rtb_Filter)))) : static_cast<int32_T>(static_cast<uint16_T>(rtb_Filter)));

  // End of Gain: '<Root>/Gain'

  // MATLABSystem: '<Root>/PX4 PWM Output' incorporates:
  //   Logic: '<Root>/NOT'

  for (i = 0; i < 8; i++) {
    pwmValue[i] = 0U;
  }

  pwmValue[0] = rtb_Gain;
  pwmValue[1] = rtb_Gain;
  pwmValue[2] = rtb_Gain;
  pwmValue[3] = rtb_Gain;
  if (cobaPX4_B.armed) {
    if (!cobaPX4_DW.obj.isArmed) {
      cobaPX4_DW.obj.isArmed = true;
      rtb_Gain = pwm_arm(&cobaPX4_DW.obj.pwmDevHandler,
                         &cobaPX4_DW.obj.armAdvertiseObj);
      cobaPX4_DW.obj.errorStatus = static_cast<uint16_T>
        (cobaPX4_DW.obj.errorStatus | rtb_Gain);
    }

    rtb_Gain = pwm_setServo(&cobaPX4_DW.obj.pwmDevHandler,
      cobaPX4_DW.obj.servoCount, cobaPX4_DW.obj.channelMask, &pwmValue[0],
      cobaPX4_DW.obj.isMain, &cobaPX4_DW.obj.actuatorAdvertiseObj);
    cobaPX4_DW.obj.errorStatus = static_cast<uint16_T>
      (cobaPX4_DW.obj.errorStatus | rtb_Gain);
  } else {
    rtb_Gain = pwm_disarm(&cobaPX4_DW.obj.pwmDevHandler,
                          &cobaPX4_DW.obj.armAdvertiseObj);
    cobaPX4_DW.obj.errorStatus = static_cast<uint16_T>
      (cobaPX4_DW.obj.errorStatus | rtb_Gain);
    cobaPX4_DW.obj.isArmed = false;
    rtb_Gain = pwm_resetServo(&cobaPX4_DW.obj.pwmDevHandler,
      cobaPX4_DW.obj.servoCount, cobaPX4_DW.obj.channelMask,
      cobaPX4_DW.obj.isMain, &cobaPX4_DW.obj.actuatorAdvertiseObj);
    cobaPX4_DW.obj.errorStatus = static_cast<uint16_T>
      (cobaPX4_DW.obj.errorStatus | rtb_Gain);
  }

  if (cobaPX4_DW.obj.isMain) {
    rtb_Gain = pwm_forceFailsafe(&cobaPX4_DW.obj.pwmDevHandler, !cobaPX4_B.armed);
    cobaPX4_DW.obj.errorStatus = static_cast<uint16_T>
      (cobaPX4_DW.obj.errorStatus | rtb_Gain);
  }

  // End of MATLABSystem: '<Root>/PX4 PWM Output'
  // SignalConversion generated from: '<Root>/Bus Selector1'
  cobaPX4_B.vx = cobaPX4_B.In1.vx;

  // SignalConversion generated from: '<Root>/Bus Selector1'
  cobaPX4_B.vy = cobaPX4_B.In1.vy;

  // SignalConversion generated from: '<Root>/Bus Selector1'
  cobaPX4_B.vz = cobaPX4_B.In1.vz;

  // SignalConversion generated from: '<Root>/Bus Selector1'
  cobaPX4_B.heading = cobaPX4_B.In1.heading;

  // SignalConversion generated from: '<Root>/Bus Selector1'
  cobaPX4_B.x = cobaPX4_B.In1.x;

  // SignalConversion generated from: '<Root>/Bus Selector1'
  cobaPX4_B.y = cobaPX4_B.In1.y;

  // Update for DiscreteIntegrator: '<S30>/Filter'
  cobaPX4_DW.Filter_DSTATE += cobaPX4_P.Filter_gainval * rtb_FilterCoefficient;

  {                                    // Sample time: [0.2s, 0.0s]
  }

  // Update absolute time for base rate
  // The "clockTick0" counts the number of times the code of this task has
  //  been executed. The absolute time is the multiplication of "clockTick0"
  //  and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
  //  overflow during the application lifespan selected.

  cobaPX4_M->Timing.taskTime0 =
    ((time_T)(++cobaPX4_M->Timing.clockTick0)) * cobaPX4_M->Timing.stepSize0;
}

// Model initialize function
void cobaPX4_initialize(void)
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));
  rtmSetTFinal(cobaPX4_M, -1);
  cobaPX4_M->Timing.stepSize0 = 0.2;

  // External mode info
  cobaPX4_M->Sizes.checksums[0] = (206393193U);
  cobaPX4_M->Sizes.checksums[1] = (1596279131U);
  cobaPX4_M->Sizes.checksums[2] = (2312408365U);
  cobaPX4_M->Sizes.checksums[3] = (1509457628U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[6];
    cobaPX4_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = (sysRanDType *)&cobaPX4_DW.EnabledSubsystem_SubsysRanBC_p;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = (sysRanDType *)&cobaPX4_DW.EnabledSubsystem_SubsysRanBC;
    systemRan[5] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(cobaPX4_M->extModeInfo,
      &cobaPX4_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(cobaPX4_M->extModeInfo, cobaPX4_M->Sizes.checksums);
    rteiSetTPtr(cobaPX4_M->extModeInfo, rtmGetTPtr(cobaPX4_M));
  }

  {
    boolean_T rtb_NOT;

    // InitializeConditions for DiscreteIntegrator: '<S30>/Filter'
    cobaPX4_DW.Filter_DSTATE = cobaPX4_P.PIDController1_InitialCondition;

    // SystemInitialize for Enabled SubSystem: '<S2>/Enabled Subsystem'
    // SystemInitialize for SignalConversion generated from: '<S52>/In1' incorporates:
    //   Outport: '<S52>/Out1'

    cobaPX4_B.In1_n = cobaPX4_P.Out1_Y0_d;

    // End of SystemInitialize for SubSystem: '<S2>/Enabled Subsystem'

    // SystemInitialize for Enabled SubSystem: '<S3>/Enabled Subsystem'
    // SystemInitialize for SignalConversion generated from: '<S53>/In1' incorporates:
    //   Outport: '<S53>/Out1'

    cobaPX4_B.In1 = cobaPX4_P.Out1_Y0;

    // End of SystemInitialize for SubSystem: '<S3>/Enabled Subsystem'

    // Start for MATLABSystem: '<S2>/SourceBlock'
    cobaPX4_DW.obj_n.matlabCodegenIsDeleted = false;
    cobaPX4_DW.obj_n.isInitialized = 1;
    cobaPX4_DW.obj_n.orbMetadataObj = ORB_ID(actuator_armed);
    uORB_read_initialize(cobaPX4_DW.obj_n.orbMetadataObj,
                         &cobaPX4_DW.obj_n.eventStructObj);
    cobaPX4_DW.obj_n.isSetupComplete = true;

    // Start for MATLABSystem: '<S3>/SourceBlock'
    cobaPX4_DW.obj_d.matlabCodegenIsDeleted = false;
    cobaPX4_DW.obj_d.isInitialized = 1;
    cobaPX4_DW.obj_d.orbMetadataObj = ORB_ID(vehicle_local_position);
    uORB_read_initialize(cobaPX4_DW.obj_d.orbMetadataObj,
                         &cobaPX4_DW.obj_d.eventStructObj);
    cobaPX4_DW.obj_d.isSetupComplete = true;

    // Start for MATLABSystem: '<Root>/PX4 PWM Output'
    cobaPX4_DW.obj.errorStatus = 0U;
    cobaPX4_DW.obj.isInitialized = 0;
    cobaPX4_DW.obj.matlabCodegenIsDeleted = false;
    cobaPX4_SystemCore_setup(&cobaPX4_DW.obj, cobaPX4_B.armed, rtb_NOT);
  }
}

// Model terminate function
void cobaPX4_terminate(void)
{
  uint16_T status;

  // Terminate for MATLABSystem: '<S2>/SourceBlock'
  if (!cobaPX4_DW.obj_n.matlabCodegenIsDeleted) {
    cobaPX4_DW.obj_n.matlabCodegenIsDeleted = true;
    if ((cobaPX4_DW.obj_n.isInitialized == 1) &&
        cobaPX4_DW.obj_n.isSetupComplete) {
      uORB_read_terminate(&cobaPX4_DW.obj_n.eventStructObj);
    }
  }

  // End of Terminate for MATLABSystem: '<S2>/SourceBlock'

  // Terminate for MATLABSystem: '<S3>/SourceBlock'
  if (!cobaPX4_DW.obj_d.matlabCodegenIsDeleted) {
    cobaPX4_DW.obj_d.matlabCodegenIsDeleted = true;
    if ((cobaPX4_DW.obj_d.isInitialized == 1) &&
        cobaPX4_DW.obj_d.isSetupComplete) {
      uORB_read_terminate(&cobaPX4_DW.obj_d.eventStructObj);
    }
  }

  // End of Terminate for MATLABSystem: '<S3>/SourceBlock'

  // Terminate for MATLABSystem: '<Root>/PX4 PWM Output'
  if (!cobaPX4_DW.obj.matlabCodegenIsDeleted) {
    cobaPX4_DW.obj.matlabCodegenIsDeleted = true;
    if ((cobaPX4_DW.obj.isInitialized == 1) && cobaPX4_DW.obj.isSetupComplete) {
      status = pwm_disarm(&cobaPX4_DW.obj.pwmDevHandler,
                          &cobaPX4_DW.obj.armAdvertiseObj);
      cobaPX4_DW.obj.errorStatus = static_cast<uint16_T>
        (cobaPX4_DW.obj.errorStatus | status);
      status = pwm_resetServo(&cobaPX4_DW.obj.pwmDevHandler,
        cobaPX4_DW.obj.servoCount, cobaPX4_DW.obj.channelMask,
        cobaPX4_DW.obj.isMain, &cobaPX4_DW.obj.actuatorAdvertiseObj);
      cobaPX4_DW.obj.errorStatus = static_cast<uint16_T>
        (cobaPX4_DW.obj.errorStatus | status);
      status = pwm_close(&cobaPX4_DW.obj.pwmDevHandler,
                         &cobaPX4_DW.obj.actuatorAdvertiseObj,
                         &cobaPX4_DW.obj.armAdvertiseObj);
      cobaPX4_DW.obj.errorStatus = static_cast<uint16_T>
        (cobaPX4_DW.obj.errorStatus | status);
    }
  }

  // End of Terminate for MATLABSystem: '<Root>/PX4 PWM Output'
}

//
// File trailer for generated code.
//
// [EOF]
//
