/*
 * MPC0.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "MPC0".
 *
 * Model version              : 1.0
 * Simulink Coder version : 9.9 (R2023a) 19-Nov-2022
 * C source code generated on : Fri Mar 22 01:13:37 2024
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "MPC0.h"
#include "rtwtypes.h"
#include <string.h>
#include <emmintrin.h>
#include "MPC0_private.h"
#include "rt_nonfinite.h"

/* Named constants for MATLAB Function: '<S22>/optimizer' */
#define MPC0_ny                        (3)

/* Block states (default storage) */
DW_MPC0_T MPC0_DW;

/* External inputs (root inport signals with default storage) */
ExtU_MPC0_T MPC0_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_MPC0_T MPC0_Y;

/* Real-time model */
static RT_MODEL_MPC0_T MPC0_M_;
RT_MODEL_MPC0_T *const MPC0_M = &MPC0_M_;

/* Model step function */
void MPC0_step(void)
{
  real_T rseq[30];
  real_T xk[9];
  real_T f[6];
  real_T zopt[6];
  real_T y_innov[3];
  int32_T i;
  int32_T j;
  static const real_T b_a[27] = { -0.30105723538620377, 0.77592735456212392,
    0.64658115558398421, 0.21843989546152032, -0.079083599337918892,
    0.86785051744545072, 0.010346665976060709, -0.016365429389411046,
    0.091176967762607086, -0.22109646835659436, -0.26310749636617548,
    0.16960957290829684, -0.37950478667122783, 0.23003620707755262,
    0.17057286057899457, 0.02968877196062536, 0.05608576448152669,
    0.0028970833352188752, 0.48167887156276884, 0.20605143212526345,
    0.3232383584266002, -0.059263697378463563, -0.14519138338719706,
    -0.087547747819810867, -0.048328915331327618, 0.018920968685444177,
    -0.01453947311953261 };

  static const real_T b_Hinv[36] = { 0.085349954307617548, 0.012251667469306558,
    -0.008925831191176483, -0.0996921252930366, -0.0026133852469418422,
    0.011389785949436803, 0.012251667469306558, 0.14732779261196915,
    0.015000260100825511, -0.058947785477547053, -0.13408623585351334,
    -0.00202244311132838, -0.008925831191176483, 0.015000260100825511,
    0.035554180476886244, 0.0029443292312839684, -0.0073472309294645918,
    -0.037308835530110225, -0.0996921252930366, -0.058947785477547053,
    0.0029443292312839684, 0.15534217784460544, 0.031840890646794989,
    -0.017788164277365244, -0.0026133852469418422, -0.13408623585351334,
    -0.0073472309294645918, 0.031840890646794989, 0.14129321150182361,
    0.0010545351260107696, 0.011389785949436803, -0.00202244311132838,
    -0.037308835530110225, -0.017788164277365244, 0.0010545351260107696,
    0.0440515948745242 };

  __m128d tmp;
  real_T rtb_xest[9];
  real_T ref;
  real_T rtb_u_idx_0;
  real_T rtb_u_idx_1;
  real_T y_innov_0;
  real_T y_innov_1;
  real_T y_innov_2;
  static const real_T a[27] = { -0.21379254437729364, -0.38984328363563669,
    1.2864502907995208, 0.030257047970682269, -0.36658932788445564,
    0.026005332937507789, 0.24134303448917802, 0.56129189637837917,
    0.90983688562155873, -0.076322801034655482, -1.4916652753124793,
    -0.47471716733609542, -1.0419553921380891, 0.022599709490588663,
    -0.020987956113323394, 0.62340787931866681, 0.17710116118905725,
    -0.20296161276763486, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 };

  static const real_T b_a_0[27] = { -0.30105723538620377, 0.77592735456212392,
    0.64658115558398421, 0.21843989546152032, -0.079083599337918892,
    0.86785051744545072, 0.010346665976060709, -0.016365429389411046,
    0.091176967762607086, -0.22109646835659436, -0.26310749636617548,
    0.16960957290829684, -0.37950478667122783, 0.23003620707755262,
    0.17057286057899457, 0.02968877196062536, 0.05608576448152669,
    0.0028970833352188752, 0.48167887156276884, 0.20605143212526345,
    0.3232383584266002, -0.059263697378463563, -0.14519138338719706,
    -0.087547747819810867, -0.048328915331327618, 0.018920968685444177,
    -0.01453947311953261 };

  static const real_T b_Kx[54] = { 26.464733560764248, 2.4831201715854792,
    21.483523600445835, -9.4572089687208951, 5.9084580047396331,
    12.951626097574451, 9.6774552182799454, -3.5750059978350652,
    26.501995118236287, -24.91786378269553, 0.38881576831595854,
    -19.324355405503514, 15.084276892273516, 3.9351074671866022,
    -6.5671483027920932, 19.144756986444033, 2.4296646097342651,
    -18.799433393335562, 121.12287786558369, 4.7523362685837753,
    82.008424097689371, -39.545608623641243, -2.4830219778949658,
    41.854972015309876, -9.0320366378935137, 15.673044292238229,
    99.9348181463511, 22.414025561148627, 2.3856818257431578, 14.787228262667774,
    -2.8046436811407549, 3.9887656829089417, 9.99425580787972, 8.31545565192167,
    -2.6213446747141478, 20.902302887199486, -20.532419123608328,
    -0.41803254656109712, -18.283706465139844, 11.280300433802523,
    -0.494017363235917, -4.214882138070621, 16.152013087604271,
    2.3009548137479947, -16.33246322017704, 99.851901023921471,
    3.9838750156230596, 64.961334027639481, -32.10983441720925,
    -3.4057761180104689, 38.2685401784532, -6.6074772241130146,
    12.989836947640132, 82.171116770277592 };

  static const real_T b_Ku1[18] = { 300.28841410888384, -103.39185068533003,
    868.55699140974116, -103.39185068533004, 220.38633279385743,
    -619.94713344381466, 868.55699140974116, -619.94713344381466,
    3419.3755154473706, 245.71104066884931, -70.597446273732345,
    712.811361971219, -108.40550662795741, 194.82090449588443,
    -577.06333650962767, 755.03040114491739, -521.37425386079281,
    2944.6276944539022 };

  static const real_T b_Kr[180] = { -0.38454467491269545, -0.71292625144590061,
    -0.26329453405801978, -1.0006190513221997, -0.60319052203856516,
    -0.61346455286688473, -1.1996140544738221, 0.34270755576296835,
    -1.1327254253882781, -0.94403971837966993, 1.1054771695141572,
    -1.7001662724904192, -0.63251392114183469, 1.2899740404821263,
    -2.2696176563974118, -0.56335649491991, 0.70496863756478578,
    -2.7945143124340022, -0.8660969382164434, 0.13504889287413294,
    -3.3589611674316178, -1.2531913026119745, -0.054049630603544813,
    -4.0007851805846411, -1.471479495943119, 0.41333478260398759,
    -4.7687737855482082, -1.3619995663582751, 0.95366132312091734,
    -5.5996922310368031, -0.53699541038855558, -0.19816593399106588,
    0.59647553857612945, -0.85760544458220134, -0.95983200116295042,
    1.1108303766789023, -1.5263826719142768, -1.2116278086218544,
    1.5305606251860158, -2.0361649423375181, -0.86521284133048659,
    1.8282392179513389, -2.2221393253968156, -0.025560239761729445,
    1.997592003827557, -2.1137421877490987, 0.49638868745445325,
    2.1346906445046883, -2.0500475764029331, 0.54419885537771906,
    2.2614353118295507, -2.204474303944258, 0.10133241989114428,
    2.3988381297957431, -2.6044612248886154, -0.18247595160322475,
    2.4738013718271139, -2.9927438988397603, -0.12870979598627028,
    2.4669701731585238, -0.69186122202260747, -0.26590041901847994,
    -1.7800805595336817, -0.22946155251062594, -1.1096668555144866,
    -3.6635949715664462, -0.11908895061974378, -1.4139844105304316,
    -5.5415947548333158, 0.15106101206575326, -1.5376831834770961,
    -7.39547045793195, 0.55418525953818165, -1.2463645972523967,
    -9.27133637446787, 1.138213875141467, -1.3240439601582448,
    -11.068726874684328, 1.621854103134398, -1.52798584306304,
    -12.822880887283272, 1.9950445298426944, -2.1192951713967836,
    -14.485760343252656, 2.1875301695434972, -2.4449125072291715,
    -16.141671546724076, 2.4245594137804991, -2.6832073445980988,
    -17.763701376073513, -0.0, -0.0, -0.0, -0.38454467491269545,
    -0.71292625144590061, -0.26329453405801978, -1.0006190513221997,
    -0.60319052203856516, -0.61346455286688473, -1.1996140544738221,
    0.34270755576296835, -1.1327254253882781, -0.94403971837966993,
    1.1054771695141572, -1.7001662724904192, -0.63251392114183469,
    1.2899740404821263, -2.2696176563974118, -0.56335649491991,
    0.70496863756478578, -2.7945143124340022, -0.8660969382164434,
    0.13504889287413294, -3.3589611674316178, -1.2531913026119745,
    -0.054049630603544813, -4.0007851805846411, -1.471479495943119,
    0.41333478260398759, -4.7687737855482082, -0.0, -0.0, -0.0,
    -0.53699541038855558, -0.19816593399106588, 0.59647553857612945,
    -0.85760544458220134, -0.95983200116295042, 1.1108303766789023,
    -1.5263826719142768, -1.2116278086218544, 1.5305606251860158,
    -2.0361649423375181, -0.86521284133048659, 1.8282392179513389,
    -2.2221393253968156, -0.025560239761729445, 1.997592003827557,
    -2.1137421877490987, 0.49638868745445325, 2.1346906445046883,
    -2.0500475764029331, 0.54419885537771906, 2.2614353118295507,
    -2.204474303944258, 0.10133241989114428, 2.3988381297957431,
    -2.6044612248886154, -0.18247595160322475, 2.4738013718271139, -0.0, -0.0,
    -0.0, -0.69186122202260747, -0.26590041901847994, -1.7800805595336817,
    -0.22946155251062594, -1.1096668555144866, -3.6635949715664462,
    -0.11908895061974378, -1.4139844105304316, -5.5415947548333158,
    0.15106101206575326, -1.5376831834770961, -7.39547045793195,
    0.55418525953818165, -1.2463645972523967, -9.27133637446787,
    1.138213875141467, -1.3240439601582448, -11.068726874684328,
    1.621854103134398, -1.52798584306304, -12.822880887283272,
    1.9950445298426944, -2.1192951713967836, -14.485760343252656,
    2.1875301695434972, -2.4449125072291715, -16.141671546724076 };

  static const real_T d_a[27] = { 0.30313337907629279, 0.0053056382406190521,
    0.20177975071411519, -1.0322789804079706, 0.19313798108881716,
    1.8330177287654366, 0.0, 0.0, 0.0, -1.8548219849827694, 1.8161220045135542,
    1.5410946611339871, 0.49786538202697594, 0.51029926024718064,
    1.8426884546663991, 0.0, 0.0, 0.0, 1.3069965578262865, 2.6725292874635591,
    3.1464383686463568, -0.23734290701756106, -0.89537570949852585,
    0.47331384232793172, 0.0, 0.0, 0.0 };

  static const real_T e_a[27] = { 0.066596839424293744, -0.52587061026068971,
    0.29291322247556728, 0.17476920430103207, 0.24336081491187675,
    0.779325316522347, 0.010346665976058121, -0.016365429389410685,
    0.091176967762613387, -0.11398815557628893, -0.070066215557237924,
    0.0336371421851255, -0.32135282762749673, -0.22706649626252678,
    0.14581149640342977, 0.029688771960626911, 0.056085764481526246,
    0.0028970833352125469, 0.60427118246499434, -0.33102064499282247,
    0.15452249552692301, -0.10067442304387733, 0.11775570091043003,
    -0.13543193367994377, -0.048328915331326917, 0.018920968685444281,
    -0.014539473119530216 };

  static const real_T c_a[81] = { 0.90092317405655387, -0.2493033974195708,
    0.25724719866611839, 0.23214203966170766, 0.21043290296091566,
    0.03314859720343704, 0.0, 0.0, 0.0, -0.06752954734497639,
    -0.8330310193952738, 0.20285265658709023, 0.13159710004303363,
    0.26290465375024358, 0.1558419752892051, 0.0, 0.0, 0.0, 0.35103799863479168,
    -0.071215697871225864, 0.16540964447895812, -0.71961988601501548,
    0.18375711990836563, -0.16102105986679391, 0.0, 0.0, 0.0,
    -0.23990990384681521, 0.74991526031256706, -0.017591814024124814,
    0.30225792761872794, 0.61763342331723969, 0.033619099393111168, 0.0, 0.0,
    0.0, -0.51118799980308516, -0.13630527689337496, 0.35655747346530459,
    -0.42809652046569618, 0.49491154968842388, 0.34133566565373274, 0.0, 0.0,
    0.0, 0.20191156373981778, -0.095751330200402343, 0.15907148554639322,
    0.58530760624092837, -0.1289070317789745, 0.9127682215326175, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 };

  /* MATLAB Function: '<S22>/optimizer' incorporates:
   *  Inport: '<Root>/mo or x'
   *  Inport: '<Root>/ref'
   *  Memory: '<S2>/last_x'
   *  UnitDelay: '<S2>/last_mv'
   */
  ref = MPC0_U.ref[0];
  rtb_u_idx_0 = MPC0_U.ref[1];
  rtb_u_idx_1 = MPC0_U.ref[2];
  for (i = 0; i < 10; i++) {
    rseq[i * MPC0_ny] = ref;
    rseq[i * MPC0_ny + 1] = rtb_u_idx_0;
    rseq[i * MPC0_ny + 2] = rtb_u_idx_1;
  }

  ref = MPC0_DW.last_mv_DSTATE[0];
  rtb_u_idx_0 = MPC0_DW.last_mv_DSTATE[1];
  rtb_u_idx_1 = MPC0_DW.last_mv_DSTATE[2];
  memcpy(&xk[0], &MPC0_DW.last_x_PreviousInput[0], 9U * sizeof(real_T));
  for (j = 0; j < 3; j++) {
    y_innov_0 = 0.0;
    for (i = 0; i < 9; i++) {
      y_innov_0 += a[3 * i + j] * xk[i];
    }

    y_innov[j] = MPC0_U.moorx[j] - y_innov_0;
  }

  y_innov_0 = y_innov[1];
  y_innov_1 = y_innov[0];
  y_innov_2 = y_innov[2];
  for (j = 0; j <= 6; j += 2) {
    /* MATLAB Function: '<S22>/optimizer' */
    tmp = _mm_loadu_pd(&xk[j]);
    _mm_storeu_pd(&rtb_xest[j], _mm_add_pd(_mm_add_pd(_mm_add_pd(_mm_mul_pd
      (_mm_loadu_pd(&b_a[j + 9]), _mm_set1_pd(y_innov_0)), _mm_mul_pd
      (_mm_loadu_pd(&b_a[j]), _mm_set1_pd(y_innov_1))), _mm_mul_pd(_mm_loadu_pd(
      &b_a[j + 18]), _mm_set1_pd(y_innov_2))), tmp));
  }

  /* MATLAB Function: '<S22>/optimizer' incorporates:
   *  UnitDelay: '<S2>/last_mv'
   */
  for (j = 8; j < 9; j++) {
    rtb_xest[j] = ((b_a_0[j + 9] * y_innov_0 + b_a_0[j] * y_innov_1) + b_a_0[j +
                   18] * y_innov_2) + xk[j];
  }

  for (i = 0; i < 6; i++) {
    y_innov_0 = 0.0;
    for (j = 0; j < 9; j++) {
      y_innov_0 += b_Kx[9 * i + j] * rtb_xest[j];
    }

    y_innov_1 = 0.0;
    for (j = 0; j < 30; j++) {
      y_innov_1 += b_Kr[30 * i + j] * rseq[j];
    }

    f[i] = ((b_Ku1[3 * i + 1] * rtb_u_idx_0 + b_Ku1[3 * i] * ref) + b_Ku1[3 * i
            + 2] * rtb_u_idx_1) + (y_innov_0 + y_innov_1);
    zopt[i] = 0.0;
  }

  for (j = 0; j < 6; j++) {
    for (i = 0; i <= 4; i += 2) {
      tmp = _mm_loadu_pd(&zopt[i]);
      _mm_storeu_pd(&zopt[i], _mm_sub_pd(tmp, _mm_mul_pd(_mm_loadu_pd(&b_Hinv[6 *
        j + i]), _mm_set1_pd(f[j]))));
    }
  }

  ref = MPC0_DW.last_mv_DSTATE[0] + zopt[0];
  rtb_u_idx_0 = ref;

  /* Outport: '<Root>/mv' incorporates:
   *  Gain: '<S2>/umin_scale1'
   */
  MPC0_Y.mv[0] = MPC0_P.umin_scale1_Gain[0] * ref;

  /* MATLAB Function: '<S22>/optimizer' incorporates:
   *  UnitDelay: '<S2>/last_mv'
   */
  ref = MPC0_DW.last_mv_DSTATE[1] + zopt[1];
  rtb_u_idx_1 = ref;

  /* Outport: '<Root>/mv' incorporates:
   *  Gain: '<S2>/umin_scale1'
   */
  MPC0_Y.mv[1] = MPC0_P.umin_scale1_Gain[1] * ref;

  /* MATLAB Function: '<S22>/optimizer' incorporates:
   *  UnitDelay: '<S2>/last_mv'
   */
  ref = MPC0_DW.last_mv_DSTATE[2] + zopt[2];

  /* Outport: '<Root>/mv' incorporates:
   *  Gain: '<S2>/umin_scale1'
   */
  MPC0_Y.mv[2] = MPC0_P.umin_scale1_Gain[2] * ref;
  for (j = 0; j < 9; j++) {
    /* MATLAB Function: '<S22>/optimizer' */
    y_innov_0 = 0.0;
    for (i = 0; i < 9; i++) {
      y_innov_0 += c_a[9 * i + j] * xk[i];
    }

    /* Update for Memory: '<S2>/last_x' incorporates:
     *  MATLAB Function: '<S22>/optimizer'
     */
    MPC0_DW.last_x_PreviousInput[j] = (((d_a[j + 9] * rtb_u_idx_1 + d_a[j] *
      rtb_u_idx_0) + d_a[j + 18] * ref) + y_innov_0) + ((e_a[j + 9] * y_innov[1]
      + e_a[j] * y_innov[0]) + e_a[j + 18] * y_innov[2]);
  }

  /* Update for UnitDelay: '<S2>/last_mv' incorporates:
   *  MATLAB Function: '<S22>/optimizer'
   */
  MPC0_DW.last_mv_DSTATE[0] = rtb_u_idx_0;
  MPC0_DW.last_mv_DSTATE[1] = rtb_u_idx_1;
  MPC0_DW.last_mv_DSTATE[2] = ref;

  /* Matfile logging */
  rt_UpdateTXYLogVars(MPC0_M->rtwLogInfo, (&MPC0_M->Timing.taskTime0));

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.25s, 0.0s] */
    if ((rtmGetTFinal(MPC0_M)!=-1) &&
        !((rtmGetTFinal(MPC0_M)-MPC0_M->Timing.taskTime0) >
          MPC0_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(MPC0_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++MPC0_M->Timing.clockTick0)) {
    ++MPC0_M->Timing.clockTickH0;
  }

  MPC0_M->Timing.taskTime0 = MPC0_M->Timing.clockTick0 *
    MPC0_M->Timing.stepSize0 + MPC0_M->Timing.clockTickH0 *
    MPC0_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void MPC0_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)MPC0_M, 0,
                sizeof(RT_MODEL_MPC0_T));
  rtmSetTFinal(MPC0_M, 10.0);
  MPC0_M->Timing.stepSize0 = 0.25;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = (NULL);
    MPC0_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(MPC0_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(MPC0_M->rtwLogInfo, (NULL));
    rtliSetLogT(MPC0_M->rtwLogInfo, "tout");
    rtliSetLogX(MPC0_M->rtwLogInfo, "");
    rtliSetLogXFinal(MPC0_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(MPC0_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(MPC0_M->rtwLogInfo, 4);
    rtliSetLogMaxRows(MPC0_M->rtwLogInfo, 0);
    rtliSetLogDecimation(MPC0_M->rtwLogInfo, 1);
    rtliSetLogY(MPC0_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(MPC0_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(MPC0_M->rtwLogInfo, (NULL));
  }

  /* states (dwork) */
  (void) memset((void *)&MPC0_DW, 0,
                sizeof(DW_MPC0_T));

  /* external inputs */
  (void)memset(&MPC0_U, 0, sizeof(ExtU_MPC0_T));

  /* external outputs */
  (void)memset(&MPC0_Y, 0, sizeof(ExtY_MPC0_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(MPC0_M->rtwLogInfo, 0.0, rtmGetTFinal(MPC0_M),
    MPC0_M->Timing.stepSize0, (&rtmGetErrorStatus(MPC0_M)));

  /* InitializeConditions for Memory: '<S2>/last_x' */
  memcpy(&MPC0_DW.last_x_PreviousInput[0], &MPC0_P.last_x_InitialCondition[0],
         9U * sizeof(real_T));

  /* InitializeConditions for UnitDelay: '<S2>/last_mv' */
  MPC0_DW.last_mv_DSTATE[0] = MPC0_P.last_mv_InitialCondition[0];
  MPC0_DW.last_mv_DSTATE[1] = MPC0_P.last_mv_InitialCondition[1];
  MPC0_DW.last_mv_DSTATE[2] = MPC0_P.last_mv_InitialCondition[2];
}

/* Model terminate function */
void MPC0_terminate(void)
{
  /* (no terminate code required) */
}
