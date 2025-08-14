%  Copyright (c) 2021 Franka Emika GmbH - All Rights Reserved
%  This file is subject to the terms and conditions defined in the file
%  'LICENSE' , which is part of this package

function franka_emika_select_callback_handler(varargin)
  % The following parameters enable toolchain compliance.
  hDlg = varargin{1};
  hSrc = varargin{2};
  
  slConfigUISetVal(hDlg, hSrc, 'HardwareBoard', 'None');   % Hardware board
  
  % Solver
  slConfigUISetVal(hDlg, hSrc, 'StartTime', '0.0');   % Start time
  slConfigUISetEnabled(hDlg, hSrc, 'StartTime', 'off');
  
  slConfigUISetVal(hDlg, hSrc, 'StopTime', 'inf');   % Stop time
  
  slConfigUISetVal(hDlg, hSrc, 'SolverType', 'Fixed-step');   % Type
  slConfigUISetEnabled(hDlg, hSrc, 'SolverType', 'off');
  
  slConfigUISetVal(hDlg, hSrc, 'SolverName', 'FixedStepDiscrete');   % Solver
  slConfigUISetEnabled(hDlg, hSrc, 'SolverName', 'off');
  
  slConfigUISetVal(hDlg, hSrc, 'FixedStep', '0.001');   % Fixed-step size (fundamental sample time)
  slConfigUISetEnabled(hDlg, hSrc, 'FixedStep', 'off');
  
  slConfigUISetVal(hDlg, hSrc, 'ExtModeTransport', 1); % Transport layer
  
  slConfigUISetVal(hDlg, hSrc, 'TargetLang', 'C++');
  slConfigUISetEnabled(hDlg, hSrc, 'TargetLang', 'off');
  slConfigUISetEnabled(hDlg, hSrc, 'ExtModeStaticAlloc', 'off');
  
  RTMain=fullfile(fileparts(which('init_franka_matlab')),'franka_simulink_library','rtw','franka_emika_panda_target','src','rt_main.cpp');
  if ispc()
      RTMain = strrep(RTMain, '\','\\');
  end
  slConfigUISetVal(hDlg, hSrc, 'RTMain', RTMain);
  
  slConfigUISetVal(hDlg, hSrc, 'CombineOutputUpdateFcns', 'on');
  slConfigUISetEnabled(hDlg, hSrc, 'CombineOutputUpdateFcns', 'off');
  
  slConfigUISetVal(hDlg, hSrc, 'GRTInterface', 'off');
  slConfigUISetEnabled(hDlg, hSrc, 'GRTInterface', 'off');
  
  if ispc()
    slConfigUISetVal(hDlg, hSrc, 'ProdHWDeviceType', 'Intel->x86-64 (Windows64)');
    slConfigUISetVal(hDlg, hSrc, 'Toolchain', 'Franka Simulink | nmake (64-bit windows)');   % Toolchain
  elseif isunix()
    slConfigUISetVal(hDlg, hSrc, 'ProdHWDeviceType', 'Intel->x86-64 (Linux 64)');
    slConfigUISetVal(hDlg, hSrc, 'Toolchain', 'Franka Simulink | gmake (64-bit linux)');   % Toolchain
  end
  slConfigUISetVal(hDlg, hSrc, 'BuildConfiguration', 'Faster Runs');   % Build configuration
  slConfigUISetVal(hDlg, hSrc, 'ObjectivePriorities', 'Execution efficiency');
  
  slConfigUISetVal(hDlg, hSrc, 'UseToolchainInfoCompliant', 'on');
  slConfigUISetVal(hDlg, hSrc, 'GenerateMakefile','on');
  
  
  