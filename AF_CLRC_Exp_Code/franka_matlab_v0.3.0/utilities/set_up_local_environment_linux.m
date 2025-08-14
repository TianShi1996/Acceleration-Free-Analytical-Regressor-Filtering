%  Copyright (c) 2021 Franka Emika GmbH - All Rights Reserved
%  This file is subject to the terms and conditions defined in the file
%  'LICENSE' , which is part of this package

function set_up_local_environment_linux()

franka_matlab_configs = load('franka_matlab_configs');

%% set LD_LIBRARY_PATH

[~, ld_library_path ] = system('echo $LD_LIBRARY_PATH');
if ~contains(ld_library_path,[franka_matlab_configs.libfranka_path,'/build'])
    ld_library_path = [ld_library_path,':',franka_matlab_configs.libfranka_path,'/build'];
end

new_ld_library_path = strrep(ld_library_path,[matlabroot,'/bin/glnxa64:'],'');
new_ld_library_path = strrep(new_ld_library_path,[matlabroot,'/sys/os/glnxa64:'],'');

setenv('LD_LIBRARY_PATH',[new_ld_library_path,':',fullfile(franka_matlab_configs.libfranka_path,'build')]);

%% set LD_RUN_PATH

[~, ld_run_path ] = system('echo $LD_RUN_PATH');
if ~contains(ld_run_path,[franka_matlab_configs.libfranka_path,'/build'])
    ld_run_path = [ld_run_path,':',franka_matlab_configs.libfranka_path,'/build'];
end

setenv('LD_RUN_PATH',ld_run_path);

end