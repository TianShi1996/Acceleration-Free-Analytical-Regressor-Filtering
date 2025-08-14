%  Copyright (c) 2021 Franka Emika GmbH - All Rights Reserved
%  This file is subject to the terms and conditions defined in the file
%  'LICENSE' , which is part of this package

function eigen_install_path = get_eigen_install_path_linux()
project_root = fileparts(which('init_franka_matlab'));
[~,eigen3Path] = system(['cd ',project_root, '&& cmake --find-package -DNAME=Eigen3 -DCOMPILER_ID=GNU -DLANGUAGE=C -DMODE=COMPILE']);
eigen_install_path = strip(strrep(eigen3Path,'-I',''));
if exist(fullfile(project_root,'CMakeFiles'),'dir')
    rmdir(fullfile(project_root,'CMakeFiles'),'s');
end

end