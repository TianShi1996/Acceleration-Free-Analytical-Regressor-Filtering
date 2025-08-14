//  Copyright (c) 2020 Franka Emika GmbH - All Rights Reserved
//  This file is subject to the terms and conditions defined in the file
//  'LICENSE' , which is part of this package

#define S_FUNCTION_LEVEL 2
#define S_FUNCTION_NAME apply_control

// Need to include simstruc.h for the definition of the SimStruct and
// its associated macro definitions.
#include "simstruc.h"

#include "sizes.h"

// Abstract:
//    The sizes information is used by Simulink to determine the S-function
//    block's characteristics (number of inputs, outputs, states, etc.).
static void mdlInitializeSizes(SimStruct* S) {
    
    /* Number of continuous and discrete states */
    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);

    ssSetNumSFcnParams(S, 12);

    ssSetSFcnParamTunable(S, 4, SS_PRM_TUNABLE);
    ssSetSFcnParamTunable(S, 5, SS_PRM_TUNABLE);
    ssSetSFcnParamTunable(S, 6, SS_PRM_TUNABLE);
    ssSetSFcnParamTunable(S, 7, SS_PRM_TUNABLE);
    ssSetSFcnParamTunable(S, 8, SS_PRM_TUNABLE);
    ssSetSFcnParamTunable(S, 10, SS_PRM_TUNABLE);

    ssSetSFcnParamTunable(S, 0, SS_PRM_NOT_TUNABLE);
    ssSetSFcnParamTunable(S, 1, SS_PRM_NOT_TUNABLE);
    ssSetSFcnParamTunable(S, 2, SS_PRM_NOT_TUNABLE);
    ssSetSFcnParamTunable(S, 3, SS_PRM_NOT_TUNABLE);
    ssSetSFcnParamTunable(S, 9, SS_PRM_NOT_TUNABLE);
    ssSetSFcnParamTunable(S, 11, SS_PRM_NOT_TUNABLE);

    // Parse the sfunction parameters(total 16)

    // 2. gripper_attached
    int gripperAttached = static_cast<int>(mxGetPr(ssGetSFcnParam(S, 1))[0]);

    // 3. control mode
    int controlMode = static_cast<int>(mxGetPr(ssGetSFcnParam(S, 2))[0]) - 1;

    // 16. elbow control requested in case of cartesian pose or velocity is commanded.
    int elbowControl = static_cast<int>(mxGetPr(ssGetSFcnParam(S, 11))[0]);

    // --> in case of elbow control assign the proper control mode...
    if ((bool)elbowControl) {
        switch (controlMode) {
            
        case torqueControlCartesianPose:
            controlMode = torqueControlCartesianPoseWithElbow;
            break;

        case torqueControlCartesianVelocities:
            controlMode = torqueControlCartesianVelocitiesWithElbow;
            break;

        case cartesianPoseControllerMode:
            controlMode = cartesianPoseControllerModeWithElbow;
            break;

        case cartesianVelocitiesControllerMode:
            controlMode = cartesianVelocitiesControllerModeWithElbow;
            break;
        }
    }

    if (!ssSetNumInputPorts(S, controlModeSizes[controlMode].numInputs + gripperAttached))
        return;

    if ((bool)gripperAttached) {
        ssSetInputPortWidth(S, 0, 9);
        ssSetInputPortDataType(S, 0, SS_DOUBLE);
    }

    /* Direct input signal access and direct input feedthrough */
    for (int ii = gripperAttached;
       ii < controlModeSizes[controlMode].numInputs + gripperAttached; ii++) {
        ssSetInputPortWidth(S, ii, controlModeSizes[controlMode].width[ii - gripperAttached]);
        ssSetInputPortDataType(S, ii, SS_DOUBLE);
    }

    if ((bool)gripperAttached) {
        ssSetInputPortRequiredContiguous(S, 0, true); /*direct input signal access*/
        /*
         * Set direct feedthrough flag (1=yes, 0=no).
         * A port has direct feedthrough if the input is used in either
         * the mdlOutputs or mdlGetTimeOfNextVarHit functions.
         */
        ssSetInputPortDirectFeedThrough(S, 0, 1);
    }

    /* Direct input signal access and direct input feedthrough */
    for (int ii = gripperAttached;
       ii < controlModeSizes[controlMode].numInputs + gripperAttached; ii++) {
        ssSetInputPortRequiredContiguous(S, ii, true); /*direct input signal access*/
        /*
         * Set direct feedthrough flag (1=yes, 0=no).
         * A port has direct feedthrough if the input is used in either
         * the mdlOutputs or mdlGetTimeOfNextVarHit functions.
         */
        ssSetInputPortDirectFeedThrough(S, ii, 1);
    }

    /* Output ports, their sizes and datatypes */
    if (!ssSetNumOutputPorts(S, 0))
        return;
        for (int i = 0; i < 0; i++) {
        ssSetOutputPortWidth(S, i, 0);
        ssSetOutputPortDataType(S, i, SS_DOUBLE);
    }

    /* Data-related */
    ssSetNumRWork(S, 0); /* number of real work vector elements   */
    ssSetNumIWork(S, 0); /* number of integer work vector elements*/
    ssSetNumPWork(S, 0); /* number of pointer work vector elements*/
    ssSetNumDWork(S, 2);
    ssSetDWorkWidth(S, 0, 1);
    ssSetDWorkWidth(S, 1, 1);
    ssSetDWorkDataType(S, 0, SS_DOUBLE);
    ssSetDWorkDataType(S, 1, SS_DOUBLE);

    /* Misc. */
    ssSetNumSampleTimes(S, 1);   /* number of sample times */
    ssSetNumModes(S, 0);         /* size of mode vector */
    ssSetNumNonsampledZCs(S, 0); /* number of states for which a block detects zero crossings */
    ssSetSimStateCompliance(S, USE_DEFAULT_SIM_STATE); /* sim state compliance */
    ssSetOptions(S, 0);                                /* s-function options */
}

// Function: mdlInitializeSampleTimes =========================================
// Abstract:
//   This function is used to specify the sample time(s) for your
//   S-function. You must register the same number of sample times as
//   specified in ssSetNumSampleTimes.
static void mdlInitializeSampleTimes(SimStruct* S) {
  ssSetSampleTime(S, 0, 0.001);
  ssSetOffsetTime(S, 0, 0.0);
  ssSetModelReferenceSampleTimeDefaultInheritance(S);
}

// Function: mdlStart =======================================================
// Abstract:
//   This function is called once at start of model execution. If you
//   have states that should be initialized once, this is the place
//   to do it.
#define MDL_START
static void mdlStart(SimStruct* S) {}

// Function: mdlOutputs =======================================================
// Abstract:
//   In this function, you compute the outputs of your S-function
//   block.
static void mdlOutputs(SimStruct* S, int_T tid) {}

#define MDL_UPDATE /* Change to #undef to remove function */
#if defined(MDL_UPDATE)
/* Function: mdlUpdate ======================================================
 * Abstract:
 *    This function is called once for every major integration time step.
 *    Discrete states are typically updated here, but this function is useful
 *    for performing any tasks that should only take place once per
 *    integration step.
 */
static void mdlUpdate(SimStruct* S, int_T tid) {}
#endif /* MDL_UPDATE */

#define MDL_DERIVATIVES /* Change to #undef to remove function */
#if defined(MDL_DERIVATIVES)
/* Function: mdlDerivatives =================================================
 * Abstract:
 *    In this function, you compute the S-function block's derivatives.
 *    The derivatives are placed in the derivative vector, ssGetdX(S).
 */
static void mdlDerivatives(SimStruct* S) {}
#endif /* MDL_DERIVATIVES */

/* Function: mdlTerminate =====================================================
 * Abstract:
 *    In this function, you should perform any actions that are necessary
 *    at the termination of a simulation.  For example, if memory was
 *    allocated in mdlStart, this is the place to free it.
 */
static void mdlTerminate(SimStruct* S) {}

#if defined(MATLAB_MEX_FILE)
#define MDL_RTW
/* Function: mdlRTW ===========================================================
 * Abstract:
 */
static void mdlRTW(SimStruct *S)
{
    // 1.robot's ip
    size_t robot_ip_length = mxGetNumberOfElements(ssGetSFcnParam(S, 0)) + 1;
    static char robot_ip_[20];
    mxGetString(ssGetSFcnParam(S, 0), robot_ip_, robot_ip_length);

    // 2. gripper_attached
    int gripperAttached = static_cast<int>(mxGetPr(ssGetSFcnParam(S, 1))[0]);

    // 3. control mode
    int controlMode = static_cast<int>(mxGetPr(ssGetSFcnParam(S, 2))[0]) - 1;

    // 4 controller_choice
    int controller_choice_ = static_cast<int>(mxGetPr(ssGetSFcnParam(S, 3))[0]) - 1;
    
    // 14 init_joint_configuration_req
    int init_joint_configuration_req_ = static_cast<int>(mxGetPr(ssGetSFcnParam(S, 9))[0]);

    // 16. elbow control requested in case of cartesian pose or velocity is commanded.
    int elbowControl = static_cast<int>(mxGetPr(ssGetSFcnParam(S, 11))[0]);

    // define robot's unique id
    std::string robot_id_string(robot_ip_);
    replaceStringInPlace(robot_id_string,".","");
    
    static char robot_id_cstr[20];
    robot_id_string.copy(robot_id_cstr, robot_id_string.size() + 1);
    robot_id_cstr[robot_id_string.size()] = '\0';
    
    // --> in case of elbow control assign the proper control mode...
    if ((bool)elbowControl) {
        switch (controlMode) {
            
        case torqueControlCartesianPose:
            controlMode = torqueControlCartesianPoseWithElbow;
            break;

        case torqueControlCartesianVelocities:
            controlMode = torqueControlCartesianVelocitiesWithElbow;
            break;

        case cartesianPoseControllerMode:
            controlMode = cartesianPoseControllerModeWithElbow;
            break;

        case cartesianVelocitiesControllerMode:
            controlMode = cartesianVelocitiesControllerModeWithElbow;
            break;
        }
    }
    
    if ( !ssWriteRTWParameters(S, 6,
            SSWRITE_VALUE_VECT, "collision_thresholds", "", mxGetPr(ssGetSFcnParam(S, 4)), 52, 
            SSWRITE_VALUE_VECT, "joint_impedance", "", mxGetPr(ssGetSFcnParam(S, 5)), 7,
            SSWRITE_VALUE_VECT, "cartesian_impedance", "", mxGetPr(ssGetSFcnParam(S, 6)), 6,
            SSWRITE_VALUE_VECT, "load_inertia", "", mxGetPr(ssGetSFcnParam(S, 7)), 13,
            SSWRITE_VALUE_VECT, "EE_T_K", "", mxGetPr(ssGetSFcnParam(S, 8)), 16,
            SSWRITE_VALUE_VECT, "init_joint_configuration", "", mxGetPr(ssGetSFcnParam(S, 10)), 7
            )){
        ssSetErrorStatus(S,"Error writing parameter data to .rtw file");
        return;
    }
    
    if ( !ssWriteRTWParamSettings(S, 7,
            SSWRITE_VALUE_QSTR, "robot_ip", &robot_ip_,
            SSWRITE_VALUE_QSTR, "robot_id", &robot_id_cstr,
            SSWRITE_VALUE_DTYPE_NUM, "gripper_attached", &gripperAttached, DTINFO(SS_INT32, 0),
            SSWRITE_VALUE_DTYPE_NUM, "control_mode", &controlMode, DTINFO(SS_INT32, 0),
            SSWRITE_VALUE_DTYPE_NUM, "controller_choice", &controller_choice_, DTINFO(SS_INT32, 0),
            SSWRITE_VALUE_DTYPE_NUM, "elbow_control", &elbowControl, DTINFO(SS_INT32, 0),
            SSWRITE_VALUE_DTYPE_NUM, "init_joint_configuration_req", &init_joint_configuration_req_, DTINFO(SS_INT32, 0))) {
        ssSetErrorStatus(S,"Error writing parameter settings data to .rtw file");           
        return; /* An error occured, which will be reported by Simulink. */
    }
}
#endif /* MDL_RTW */

// Required S-function trailer
#ifdef MATLAB_MEX_FILE /* Is this file being compiled as a MEX-file? */
#include "simulink.c"  /* MEX-file interface mechanism */
#else
#include "cg_sfun.h" /* Code generation registration function */
#endif