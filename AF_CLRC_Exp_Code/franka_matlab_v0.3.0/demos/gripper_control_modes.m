%  Copyright (c) 2020 Franka Emika GmbH - All Rights Reserved
%  This file is subject to the terms and conditions defined in the file
%  'LICENSE' , which is part of this package

classdef gripper_control_modes < Simulink.IntEnumType

    enumeration
        idle (0)
        read_state (1)
        homing (2)
        grasp (3)
        move (4)
        stop (5)
    end
    methods (Static)
        function retVal = getDefaultValue()
            retVal = gripper_control_modes.idle;
        end
    end
end