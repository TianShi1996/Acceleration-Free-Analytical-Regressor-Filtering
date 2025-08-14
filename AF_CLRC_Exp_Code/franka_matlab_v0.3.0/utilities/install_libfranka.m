%  Copyright (c) 2022 Franka Emika GmbH - All Rights Reserved
%  This file is subject to the terms and conditions defined in the file
%  'LICENSE' , which is part of this package

function install_libfranka(libfranka_version)

installation_path = fileparts(which('init_franka_matlab'));
franka_matlab_configs = load('franka_matlab_configs');

if ispc
    poco_dir = franka_matlab_configs.poco_dir;
    eigen_dir = franka_matlab_configs.eigen_dir;
    vcpkg_cmake_path = franka_matlab_configs.vcpkg_cmake_path;
end

system(cding(installation_path,'git clone --recursive https://github.com/frankaemika/libfranka'));
system(cding(fullfile(installation_path, 'libfranka'), ['git checkout ',libfranka_version]));
system(cding(fullfile(installation_path, 'libfranka'),'git submodule update'));
system(cding(fullfile(installation_path, 'libfranka'),'mkdir build'));

if ispc 
    system_msvs(cding(fullfile(installation_path, 'libfranka','build'),['cmake -DPoco_DIR=', poco_dir,...
                                                                            ' -DEigen3_DIR=', eigen_dir,...
                                                                            ' -DCMAKE_TOOLCHAIN_FILE=', vcpkg_cmake_path,...
                                                                            ' -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=OFF -DCMAKE_POSITION_INDEPENDENT_CODE=ON -G Ninja ..']));
    system_msvs(cding(fullfile(installation_path, 'libfranka','build'),'ninja'));
elseif isunix 
    system(cding(fullfile(installation_path, 'libfranka','build'),'cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=OFF -DCMAKE_POSITION_INDEPENDENT_CODE=ON ..'));
    system(cding(fullfile(installation_path, 'libfranka','build'),'cmake --build .'));
end

libfranka_path = fullfile(installation_path,'libfranka');
project_root = fileparts(which('init_franka_matlab'));
code_gen_target = 'franka_emika';

if ~exist('franka_matlab_configs.mat','file')
    save(fullfile(project_root, 'franka_matlab_configs'), 'libfranka_path',...
                                                      'code_gen_target');
end

save(fullfile(project_root, 'franka_matlab_configs'), 'libfranka_path','-append');

end

function cd_string = cding(path, cmd)

cd_string = ['pushd ',path,' && ',cmd, '&& popd'];

end

function system_msvs(cmd)

system(['"C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars64.bat" && ', cmd]);

end