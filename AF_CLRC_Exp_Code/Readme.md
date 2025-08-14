/**************************************************************************
****************************  Folder Description *************************************
****The data in this folder is based on the implementation of the paper
****Title: Acceleration-Free Analytical Regressor Filtering for Robot Online Identification and Control
***********************************************************************************/

/***Noting：Before running the experiment, you need to configure libfranka and Franka MATLAB ***/
/***Dependency package download URL: https://frankaemika.github.io/docs/  ***/
/***Experimental procedures: Adding all files and file folders to path, then  
/***running Main.m and opening the simulink file exp_CLRC_AF.mdl ***/


|Directory/File|              	|Description|
|-- Readme.txt		// readme file
|-- AF_CLRC_Exp_Code		// 
|-- |-- franka_matlab_v0.3.0   //  A library of dependencies necessary to run the experiment
|-- |-- Exp_Program                      //  Experiments program
|-- |-- |-- dynamic_model          //  dynamics model
|-- |-- |-- FrictionModel_Matlab    // friction model
|-- |-- |-- regressor_Panda    // regressor package
|-- |-- |-- trajectory         // Desired trajectory      
|-- |-- |-- exp_CLRC_DDF.mdl  // DDF-CLRC
|-- |-- |-- exp_MC.mdl        // MSLC
|-- |-- |-- exp_CLRC_AF.mdl  // The proposed method
|-- |-- |-- Panda_run.m      // Parameters Initialization 
|-- |-- |-- Main.m           // Environment Initialization


