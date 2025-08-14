%  Copyright (c) 2020 Franka Emika GmbH - All Rights Reserved
%  This file is subject to the terms and conditions defined in the file
%  'LICENSE' , which is part of this package

function init_franka_simulink_64_linux_tc

target_file = fullfile(fileparts(mfilename('fullpath')),'franka_simulink_64_linux_tc.mat');

if exist(target_file, 'file')
    movefile(target_file, [target_file, '.bak']);
end

tc='';
save(target_file, 'tc');

tc = franka_simulink_64_linux_tc;

save(target_file, 'tc');
while (~exist(target_file, 'file'))
  sleep(0.5);
end

if (tc.validate)
    RTW.TargetRegistry.getInstance('reset');
else
    error('Problem with franka_simulink_64_linux_tc');
end

end
