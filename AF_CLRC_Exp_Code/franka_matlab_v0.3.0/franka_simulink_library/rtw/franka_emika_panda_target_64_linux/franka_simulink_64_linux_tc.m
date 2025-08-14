%  Copyright (c) 2020 Franka Emika GmbH - All Rights Reserved
%  This file is subject to the terms and conditions defined in the file
%  'LICENSE' , which is part of this package

function tc = franka_simulink_64_linux_tc

%gather resources
franka_matlab_configs = load('franka_matlab_configs');
project_root = fileparts(which('init_franka_matlab'));
[~,eigen3Path] = system(['cd ',project_root, '&& cmake --find-package -DNAME=Eigen3 -DCOMPILER_ID=GNU -DLANGUAGE=C -DMODE=COMPILE']);
eigen3Path = strip(strrep(eigen3Path,'-I',''));
if exist(fullfile(project_root,'CMakeFiles'),'dir')
    rmdir(fullfile(project_root,'CMakeFiles'),'s');
end

custom_include = strjoin( {  ['-I',fullfile(franka_matlab_configs.libfranka_path,'include')],...
                             fullfile(franka_matlab_configs.libfranka_path,'examples'),...
                             fullfile(franka_matlab_configs.libfranka_path,'common','include'),...
                             fullfile(franka_matlab_configs.libfranka_path,'src'),...
                             fullfile(franka_matlab_configs.libfranka_path,'build'),...
                             fullfile(project_root,'franka_simulink_library','src'),...
                             fullfile(project_root,'franka_simulink_library','blocks'),...
                             fullfile(matlabroot,'toolbox','coder','rtiostream','src'),...
                             fullfile(matlabroot,'toolbox','coder','rtiostream','src','utils'),...
                             eigen3Path}, ' -I');   % Include directories 
                         
custom_library = strjoin({fullfile(franka_matlab_configs.libfranka_path,'build','examples','libexamples_common.a'),...
       fullfile(franka_matlab_configs.libfranka_path,'build','libfranka.so')},' ');

%franka_simulink_64_linux_tc Creates an Franka Emika 64 bit linux ToolchainInfo object.
% Get the already existing default toolchain for Linux
tc = coder.make.getToolchainInfoFromRegistry('GNU gcc/g++ | gmake (64-bit Linux)');

% tc = coder.make.ToolchainInfo('BuildArtifact', 'gmake makefile');
tc.Name             = 'Franka Simulink | gmake (64-bit linux)';
tc.Platform         = 'glnxa64';
tc.SupportedVersion = '4.4.x';

% tc.addAttribute('TransformPathsWithSpaces');

% ------------------------------
% Macros
% ------------------------------
tc.addMacro('MW_BIN_DIR', ['$(MATLAB_ROOT)/bin/' tc.Platform]);
tc.addMacro('CPP_17_OPTS', '-std=c++17');
tc.addMacro('FRANKA_INCLUDE_DIRECTORIES',custom_include)
tc.addIntrinsicMacros({'ANSI_OPTS', 'CPP_ANSI_OPTS'});


% ------------------------------
% C Compiler
% ------------------------------
 
tool = tc.getBuildTool('C Compiler');

tool.setName(           'GNU C Compiler');
tool.setCommand(        'gcc');
tool.setPath(           '');

tool.setDirective(      'IncludeSearchPath',    '-I');
tool.setDirective(      'PreprocessorDefine',   '-D');
tool.setDirective(      'OutputFlag',           '-o');
tool.setDirective(      'Debug',                '-g');

tool.setFileExtension(  'Source',               '.c');
tool.setFileExtension(  'Header',               '.h');
tool.setFileExtension(  'Object',               '.o');

tool.setCommandPattern('|>TOOL<| |>TOOL_OPTIONS<| |>OUTPUT_FLAG<||>OUTPUT<|');

% ------------------------------
% C++ Compiler
% ------------------------------

tool = tc.getBuildTool('C++ Compiler');

tool.setName(           'GNU C++ Compiler');
tool.setCommand(        'g++');
tool.setPath(           '');

tool.setDirective(      'IncludeSearchPath',  	'-I');
tool.setDirective(      'PreprocessorDefine', 	'-D');
tool.setDirective(      'OutputFlag',           '-o');
tool.setDirective(      'Debug',                '-g');

tool.setFileExtension(  'Source',               '.cpp');
tool.setFileExtension(  'Header',               '.hpp');
tool.setFileExtension(  'Object',               '.o');

% ------------------------------
% Linker
% ------------------------------

tool = tc.getBuildTool('Linker');

tool.setName(           'GNU Linker');
tool.setCommand(        'gcc');
tool.setPath(           '');

tool.setDirective(      'Library',              '-l');
tool.setDirective(      'LibrarySearchPath',    '-L');
tool.setDirective(      'OutputFlag',           '-o');
tool.setDirective(      'Debug',                '-g');

tool.setFileExtension(  'Executable',           '');
tool.setFileExtension(  'Shared Library',       '.so');

% % project dependencies
tool.Libraries = {[custom_library,' -lPocoNet -lPocoFoundation -lPocoUtil -lmx -lmex -lmat -lm -lstdc++ -lpthread']};

% % ------------------------------
% % C++ Linker
% % ------------------------------

tool = tc.getBuildTool('C++ Linker');

tool.setName(           'GNU C++ Linker');
tool.setCommand(        'gcc');
tool.setPath(           '');

tool.setDirective(      'Library',              '-l');
tool.setDirective(      'LibrarySearchPath',    '-L');
tool.setDirective(      'OutputFlag',           '-o');
tool.setDirective(      'Debug',                '-g');

tool.setFileExtension(  'Executable',           '');
tool.setFileExtension(  'Shared Library',       '.so');

% ------------------------------
% Archiver
% ------------------------------

tool = tc.getBuildTool('Archiver');

tool.setName(           'GNU Archiver');
tool.setCommand(        'ar');
tool.setPath(           '');

tool.setDirective(      'OutputFlag',           '');

tool.setFileExtension(  'Static Library',       '.a');

% ------------------------------
% Builder
% ------------------------------

tc.setBuilderApplication(tc.Platform);

% ------------------------------
% Deployment
% ------------------------------

cfg = tc.getPostbuildTool('Download');
cfg.setName('Download');
cfg.setCommandPattern('|>TOOL<| |>TOOL_OPTIONS<|');

% ------------------------------
% Execution
% ------------------------------
cfg = tc.getPostbuildTool('Execute');
cfg.setName('Execute');
cfg.setCommandPattern('|>TOOL<| |>TOOL_OPTIONS<|');

% --------------------------------------------
% BUILD CONFIGURATIONS
% --------------------------------------------

optimsOffOpts = {'-O0'};
optimsOnOpts = {'-O3 -march=native -fno-loop-optimize'};

cCompilerOpts           = {'-c -fPIC $(ANSI_OPTS) $(FRANKA_INCLUDE_DIRECTORIES)'};
cppCompilerOpts         = {'-c -fPIC $(CPP_17_OPTS) $(FRANKA_INCLUDE_DIRECTORIES)'};
linkerOpts              = {'-Wl,-rpath,"$(MW_BIN_DIR)",-L"$(MW_BIN_DIR)"'};
sharedLinkerOpts        = {'-shared -Wl,-rpath,"$(MW_BIN_DIR)",-L"$(MW_BIN_DIR)"'};
archiverOpts            = {'ruvs'};

cfg = tc.getBuildConfiguration('Faster Builds');
cfg.setOption( 'C Compiler',                horzcat(cCompilerOpts,   optimsOffOpts));
cfg.setOption( 'Linker',                    linkerOpts);
cfg.setOption( 'Shared Library Linker',     sharedLinkerOpts);
cfg.setOption( 'C++ Compiler',              horzcat(cppCompilerOpts, optimsOffOpts));
cfg.setOption( 'C++ Linker',                linkerOpts);
cfg.setOption( 'C++ Shared Library Linker', sharedLinkerOpts);
cfg.setOption( 'Archiver',                  archiverOpts);

% Set the toolchain flags for 'Faster Runs' build configuration

cfg = tc.getBuildConfiguration('Faster Runs');
cfg.setOption( 'C Compiler',                horzcat(cCompilerOpts,   optimsOnOpts));
cfg.setOption( 'Linker',                    linkerOpts);
cfg.setOption( 'Shared Library Linker',     sharedLinkerOpts);
cfg.setOption( 'C++ Compiler',              horzcat(cppCompilerOpts, optimsOnOpts));
cfg.setOption( 'C++ Linker',                linkerOpts);
cfg.setOption( 'C++ Shared Library Linker', sharedLinkerOpts);
cfg.setOption( 'Archiver',                  archiverOpts);

tc.setBuildConfigurationOption('all', 'Execute',       '');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Helper Functions
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    function flag = getDebugFlag(toolkey)
        flag = tc.getBuildTool(toolkey).Directives.getValue('Debug').getRef();
    end
end