function fric_par = FrictionPar()


f_v =[0.0665, 0.1987, 0.0399, 0.2257,  0.1023, -0.0132, 0.0638]';
f_c =[0.245, 0.1523, 0.1827, 0.3591, 0.2669, 0.1658, 0.2109 ]';
f_o =[-0.1073,-0.1566,-0.0686,-0.2522,0.0045,0.0910,-0.0127]';


%% Stribeck effect
vs=1; %  Stribeck velocity


f_s0=f_o;
f_s1=-f_o/vs;
% f_s2=f_o/2/vs^2;
% f_s3=f_o/6/vs^3;
% fric_par=[f_c;f_v;f_s0;f_s1;f_s2];
fric_par=[f_v;f_c;f_s0;f_s1];
% fric_par=[f_v;f_c;f_s0];

