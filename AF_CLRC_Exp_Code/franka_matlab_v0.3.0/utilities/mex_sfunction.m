%  Copyright (c) 2021 Franka Emika GmbH - All Rights Reserved
%  This file is subject to the terms and conditions defined in the file
%  'LICENSE' , which is part of this package

function mex_sfunction(src)

src_full_path = which(src);
src_full_home_path = fileparts(src_full_path);

warnStruct = warning('on', 'MATLAB:mex:GccVersion_link');

disp([newline,'<=== Mexing ',src,' ===>',newline]);
                              
mex_string = strjoin({'mex', fullfile(src_full_home_path,src),'-outdir ',fullfile(src_full_home_path)},' ');
               
evalin('base',mex_string);
warning(warnStruct);
end