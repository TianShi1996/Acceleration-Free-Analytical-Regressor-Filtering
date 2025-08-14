%  Copyright (c) 2021 Franka Emika GmbH - All Rights Reserved
%  This file is subject to the terms and conditions defined in the file
%  'LICENSE' , which is part of this package

function blkStruct = slblocks
		Browser.Library = 'franka_simulink_library';
		Browser.Name = 'Franka Emika Simulink Support Package';
		blkStruct.Browser = Browser; 