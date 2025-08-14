%  Copyright (c) 2021 Franka Emika GmbH - All Rights Reserved
%  This file is subject to the terms and conditions defined in the file
%  'LICENSE' , which is part of this package

function init_franka_simulink_64_windows_tc

target_file = fullfile(fileparts(mfilename('fullpath')),'franka_simulink_64_windows_tc.mat');
tc='';
save(target_file, 'tc');
tc = franka_simulink_64_windows_tc;
save(target_file, 'tc');
RTW.TargetRegistry.getInstance('reset');

end

