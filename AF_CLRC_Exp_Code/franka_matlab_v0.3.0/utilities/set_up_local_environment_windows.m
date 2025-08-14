%  Copyright (c) 2021 Franka Emika GmbH - All Rights Reserved
%  This file is subject to the terms and conditions defined in the file
%  'LICENSE' , which is part of this package

function set_up_local_environment_windows()

franka_matlab_configs = load('franka_matlab_configs');

%% set FRANKA LIB PATH
path = getenv('PATH');
if ~contains(path,fullfile(franka_matlab_configs.libfranka_path,'build'))
    setenv('PATH', [getenv('PATH') ';' fullfile(franka_matlab_configs.libfranka_path,'build')]);
end
end