%  Copyright (c) 2020 Franka Emika GmbH - All Rights Reserved
%  This file is subject to the terms and conditions defined in the file
%  'LICENSE' , which is part of this package

function mex_franka_matlab_library()

franka_matlab_library_components = {'franka_automatic_error_recovery.cpp',...
                                    'franka_robot_state.cpp',...
                                    'franka_communication_test.cpp',...
                                    'franka_joint_poses.cpp',...
                                    'franka_joint_point_to_point_motion.cpp'};

cellfun(@mex_mxfunction,franka_matlab_library_components);

end