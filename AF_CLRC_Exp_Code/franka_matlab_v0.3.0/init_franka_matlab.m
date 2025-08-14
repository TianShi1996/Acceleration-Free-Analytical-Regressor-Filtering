%  Copyright (c) 2022 Franka Emika GmbH - All Rights Reserved
%  This file is subject to the terms and conditions defined in the file
%  'LICENSE' , which is part of this package

function init_franka_matlab(libfranka_version)

fprintf('--Initializing Franka Matlab\n');

%% Project Root Path
project_root = fileparts(which('init_franka_matlab'));

%% Add subfolders
addpath(fullfile(project_root, 'demos'));
addpath(genpath(fullfile(project_root, 'franka_matlab_library')));
addpath(fullfile(project_root, 'franka_simulink_library'));
addpath(fullfile(project_root, 'franka_simulink_library','blocks'));
addpath(fullfile(project_root, 'franka_simulink_library','src'));
addpath(fullfile(project_root, 'franka_simulink_library','rtw'));
addpath(fullfile(project_root, 'franka_simulink_library','rtw','franka_emika_panda_target'));
if isunix()
    addpath(fullfile(project_root, 'franka_simulink_library','rtw','franka_emika_panda_target_64_linux'));
elseif ispc()
    addpath(fullfile(project_root, 'franka_simulink_library','rtw','franka_emika_panda_target_64_windows'));
end
addpath(fullfile(project_root, 'utilities'));

%% In case of windows machine the full dir paths for poco, eigen, vcpkg are needed
if ispc()
    if ~exist('franka_matlab_configs.mat','file')
        [~,vcpkg_path] = system('where vcpkg');
        vcpkg = fileparts(vcpkg_path);
        poco_dir = fullfile(vcpkg,'packages\poco_x64-windows\share\poco');
        eigen_dir = fullfile(vcpkg,'packages\eigen3_x64-windows\share\eigen3');
        vcpkg_cmake_path = fullfile(vcpkg,'scripts\buildsystems\vcpkg.cmake');
    else
        franka_matlab_configs = load('franka_matlab_configs');
        poco_dir = franka_matlab_configs.poco_dir;
        eigen_dir = franka_matlab_configs.eigen_dir;
        vcpkg_cmake_path = franka_matlab_configs.vcpkg_cmake_path;
    end
end

%% Save configs to mat file
if nargin == 0
    libfranka_version = '0.10.0';
end

libfranka_path = fullfile(project_root,'libfranka');

if ~exist('franka_matlab_configs.mat','file')
    save(fullfile(project_root, 'franka_matlab_configs'), 'libfranka_path');
else
    save(fullfile(project_root, 'franka_matlab_configs'), 'libfranka_path', '-append');
end

if ispc
    save(fullfile(project_root, 'franka_matlab_configs'), 'poco_dir',...
                                                          'eigen_dir',...
                                                          'vcpkg_cmake_path',...
                                                          '-append');
end
    
%% set up local environment, point to local machine standard gcc g++ libs
if isunix
    set_up_local_environment_linux();
elseif ispc
    set_up_local_environment_windows();
end

%% Init Toolchain
if ispc
    init_franka_simulink_64_windows_tc();
elseif isunix
    init_franka_simulink_64_linux_tc();
end

%% Refresh customizations
sl_refresh_customizations();

%% Quick evaluation of the situation of libfranka path provided
if isunix 
    libfranka_shared_lib = 'libfranka.so';
    libfranka_examples_common_lib = 'libexamples_common.a';
elseif ispc
    libfranka_shared_lib = 'franka.dll';
    libfranka_examples_common_lib = 'examples_common.lib';
end

if ~exist(fullfile(libfranka_path,'build',libfranka_shared_lib),'file') ||...
     ~exist(fullfile(libfranka_path,'build','examples',libfranka_examples_common_lib),'file')
     prompt = [newline, 'libfranka installation seems invalid, either install manually (see https://frankaemika.github.io/docs/)',newline,...
               'and hit init_franka_matlab(libfranka path) again',newline,...
               'or try installing automatically(Y):',newline,newline,...
               '!! Important !! ==================================================================== !! Important !!',newline,...
               '!! Important !! Make sure you managed dependencies in a terminal BEFORE installation !! Important !!',newline,...
               '!! Important !! ==================================================================== !! Important !!',newline,...
               '!! Important !! ==================================================================== !! Important !!',newline,newline,...
               'install libfranka now(Y)||skip installation(n):',newline,newline];
 
    str = input(prompt,'s');
    
    if (strcmp(str,'Y') || strcmp(str,'y'))
        
        install_libfranka(libfranka_version);
        
    else
        
        error('libfranka not properly installed, please manage installation (see https://frankaemika.github.io/docs/) and run init_franka_matlab_again(libfranka_local_installation_path) again');
        
    end
    
end

end