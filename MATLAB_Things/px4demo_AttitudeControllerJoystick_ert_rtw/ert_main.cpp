//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: ert_main.cpp
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
#include <stdio.h>
#include <stdlib.h>
#include "px4demo_AttitudeControllerJoystick.h"
#include "px4demo_AttitudeControllerJoystick_private.h"
#include "rtwtypes.h"
#include "limits.h"
#include "rt_nonfinite.h"
#include "ext_mode.h"
#include "MW_PX4_TaskControl.h"
#include "nuttxinitialize.h"
#define UNUSED(x)                      x = x
#define NAMELEN                        16

// Function prototype declaration
void exitFcn(int sig);
void *terminateTask(void *arg);
void *baseRateTask(void *arg);
void *subrateTask(void *arg);
volatile boolean_T stopRequested = false;
volatile boolean_T runModel = true;
extmodeErrorCode_T errorCode;
px4_sem_t stopSem;
px4_sem_t baserateTaskSem;
pthread_t schedulerThread;
pthread_t baseRateThread;
pthread_t backgroundThread;
void *threadJoinStatus;
int terminatingmodel = 0;
void *baseRateTask(void *arg)
{
  runModel = (rtmGetErrorStatus(px4demo_AttitudeControllerJo_M) == (NULL));
  while (runModel) {
    px4_sem_wait(&baserateTaskSem);
    extmodeSimulationTime_T currentTime = (extmodeSimulationTime_T)
      px4demo_AttitudeControllerJo_M->Timing.taskTime0;
    px4demo_AttitudeControllerJoystick_step();

    // Get model outputs here

    // Trigger External Mode event
    extmodeEvent(0, currentTime);
    stopRequested = !((rtmGetErrorStatus(px4demo_AttitudeControllerJo_M) ==
                       (NULL)));
    runModel = !stopRequested && !extmodeSimulationComplete() &&
      !extmodeStopRequested();
  }

  runModel = 0;
  terminateTask(arg);
  pthread_exit((void *)0);
  return NULL;
}

void exitFcn(int sig)
{
  UNUSED(sig);
  rtmSetErrorStatus(px4demo_AttitudeControllerJo_M, "stopping the model");
  runModel = 0;
}

void *terminateTask(void *arg)
{
  UNUSED(arg);
  terminatingmodel = 1;

  {
    runModel = 0;

    // Wait for background task to complete
    CHECK_STATUS(pthread_join(backgroundThread, &threadJoinStatus), 0,
                 "pthread_join");
  }

  MW_PX4_Terminate();

  // Terminate model
  px4demo_AttitudeControllerJoystick_terminate();
  extmodeReset();
  px4_sem_post(&stopSem);
  return NULL;
}

void *backgroundTask(void *arg)
{
  while (runModel) {
    // Run External Mode background activities
    errorCode = extmodeBackgroundRun();
    if (errorCode != EXTMODE_SUCCESS) {
      // Code to handle External Mode background task errors
      // may be added here
    }
  }

  pthread_exit((void *)0);
  return NULL;
}

int px4_simulink_app_task_main (int argc, char *argv[])
{
  rtmSetErrorStatus(px4demo_AttitudeControllerJo_M, 0);

  // Parse External Mode command line arguments
  errorCode = extmodeParseArgs(argc, (const char_T **)argv);
  if (errorCode != EXTMODE_SUCCESS) {
    return (errorCode);
  }

  // Initialize model
  px4demo_AttitudeControllerJoystick_initialize();

  // External Mode initialization
  errorCode = extmodeInit(px4demo_AttitudeControllerJo_M->extModeInfo,
    &rtmGetTFinal(px4demo_AttitudeControllerJo_M));
  if (errorCode != EXTMODE_SUCCESS) {
    // Code to handle External Mode initialization errors
    // may be added here
  }

  if (errorCode == EXTMODE_SUCCESS) {
    // Wait until a Start or Stop Request has been received from the Host
    extmodeWaitForHostRequest(EXTMODE_WAIT_FOREVER);
    if (extmodeStopRequested()) {
      rtmSetStopRequested(px4demo_AttitudeControllerJo_M, true);
    }
  }

  // Call RTOS Initialization function
  nuttxRTOSInit(0.01, 0);

  // Wait for stop semaphore
  px4_sem_wait(&stopSem);

#if (MW_NUMBER_TIMER_DRIVEN_TASKS > 0)

  {
    int i;
    for (i=0; i < MW_NUMBER_TIMER_DRIVEN_TASKS; i++) {
      CHECK_STATUS(px4_sem_destroy(&timerTaskSem[i]), 0, "px4_sem_destroy");
    }
  }

#endif

  return 0;
}

//
// File trailer for generated code.
//
// [EOF]
//