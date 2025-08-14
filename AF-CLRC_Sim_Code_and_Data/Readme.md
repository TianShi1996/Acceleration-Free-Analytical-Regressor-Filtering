#  Folder Description
The data in this folder is based on the implementation of the paper
Title: Acceleration-Free Analytical Regressor Filtering for Robot Online Identification and Control


Noting: MATLAB version: R2024a 
Simulation procedures: Adding all files and file folders to path, then 
1) running RegComp_main.m  can generate results of Figs. 2-3
2) running DDF_Test_main.m can generate results of Fig. 4
Note that all results must be moved into sim_fig or simg_fig_DDF folder


# |Directory/File|              	|Description|
|-- Readme.txt		// readme file
|-- AF-CLRC_Sim_Code		// simulation folder
|-- |-- dynamic_model          //  dynamics model
|-- |-- FrictionModel_Matlab    // friction model
|-- |-- regressor_Panda    // regressor package
|-- |-- RNE_Package        // recursive  Newton-Euler package
|-- |-- sim_fig
|-- |-- sim_fig_DDF
|-- |-- trajectory         // Desired trajectory                         
|-- |-- CLRC_acc.mdl                
|-- |-- CLRC_acc_f1.mdl         
|-- |-- CLRC_acc_f2.mdl                
|-- |-- CLRC_filter_reg.mdl  // The proposed method
|-- |-- CLRC_RNE.mdl
|-- |-- Panda_run.m      // Parameters Initialization      
|-- |-- RegComp_main.m   // Main program to generate results of Figs. 2-3
|-- |-- DDF_Test_main.m  // Main program to generate results of Fig. 4


