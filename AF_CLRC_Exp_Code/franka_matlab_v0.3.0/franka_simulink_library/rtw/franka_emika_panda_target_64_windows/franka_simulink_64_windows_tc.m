%  Copyright (c) 2021 Franka Emika GmbH - All Rights Reserved
%  This file is subject to the terms and conditions defined in the file
%  'LICENSE' , which is part of this package

function tc = franka_simulink_64_windows_tc

% Get the already existing default toolchain for windows with MV C++ 2017
tc = coder.make.getToolchainInfoFromRegistry('Microsoft Visual C++ 2017 v15.0 | nmake (64-bit Windows)');

% We start by renaming
tc.Name = 'Franka Simulink | nmake (64-bit windows)';

% Gradually adding dependencies to libfranka
project_root = fileparts(which('init_franka_matlab'));
franka_matlab_configs = load('franka_matlab_configs');

custom_include = strjoin( {  ['-I',fullfile(franka_matlab_configs.libfranka_path,'include')],...
                             fullfile(franka_matlab_configs.libfranka_path,'examples'),...
                             fullfile(franka_matlab_configs.libfranka_path,'common','include'),...
                             fullfile(franka_matlab_configs.poco_dir,'../../include'),...
                             fullfile(franka_matlab_configs.eigen_dir,'../../include'),...
                             fullfile(project_root,'franka_simulink_library','blocks'),...
                             fullfile(project_root,'franka_simulink_library','src')}, ' -I');   % Include directories

tc_libraries = strjoin({fullfile(franka_matlab_configs.poco_dir,'../../lib','PocoFoundation.lib'),...
       fullfile(franka_matlab_configs.libfranka_path,'build','Franka.lib'),...
       fullfile(franka_matlab_configs.libfranka_path,'build','examples','examples_common.lib')},' ');

tc.addMacro('FRANKA_INCLUDE_DIRECTORIES', custom_include)

cfg = tc.getBuildConfiguration('Faster Builds');

vsCCompilerOpts = cfg.getOption('C Compiler').getValue;
vsCCompilerOpts{1} = [vsCCompilerOpts{1}, ' /MD', ' $(FRANKA_INCLUDE_DIRECTORIES)'];
cfg.setOption( 'C Compiler',                vsCCompilerOpts);

vsCPPCompilerOpts = cfg.getOption('C++ Compiler').getValue;
vsCPPCompilerOpts{1} = [vsCPPCompilerOpts{1}, ' /MD', ' $(FRANKA_INCLUDE_DIRECTORIES)'];
cfg.setOption( 'C++ Compiler',              vsCPPCompilerOpts);

cfg = tc.getBuildConfiguration('Faster Runs');

vsCCompilerOpts = cfg.getOption('C Compiler').getValue;
vsCCompilerOpts{1} = [vsCCompilerOpts{1}, ' /MD', ' $(FRANKA_INCLUDE_DIRECTORIES)'];
cfg.setOption( 'C Compiler',                vsCCompilerOpts);

vsCPPCompilerOpts = cfg.getOption('C++ Compiler').getValue;
vsCPPCompilerOpts{1} = [vsCPPCompilerOpts{1}, ' /MD', ' $(FRANKA_INCLUDE_DIRECTORIES)'];
cfg.setOption( 'C++ Compiler',              vsCPPCompilerOpts);

% ------------------------------
% Linker
% ------------------------------
tool = tc.getBuildTool('Linker');
tool.Libraries = {tc_libraries};

end