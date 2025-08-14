%  Copyright (c) 2020 Franka Emika GmbH - All Rights Reserved
%  This file is subject to the terms and conditions defined in the file
%  'LICENSE' , which is part of this package

function rtwTargetInfo(tr)

tr.registerTargetInfo(@loc_createToolchain);

end

% -------------------------------------------------------------------------
% Create the ToolchainInfoRegistry entries
% -------------------------------------------------------------------------
function config = loc_createToolchain

config = coder.make.ToolchainInfoRegistry; % initialize

config(1)                       = coder.make.ToolchainInfoRegistry;
config(end).Name                = 'Franka Simulink | nmake (64-bit windows)';
config(end).FileName            = fullfile(fileparts(mfilename('fullpath')),'franka_simulink_64_windows_tc.mat');
config(end).TargetHWDeviceType	= {};
config(end).Platform            = {computer('arch')};
end
