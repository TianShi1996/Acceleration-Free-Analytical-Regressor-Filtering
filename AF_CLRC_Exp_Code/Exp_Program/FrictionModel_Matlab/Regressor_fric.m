function Reg_fric = Regressor_fric(dq)

reg_fc=diag(sign(dq));
reg_fv=diag(dq);
% vs=0.1;
% reg_s0=diag(exp(-dq.^2/vs^2));

reg_s0=eye(length(dq));
% reg_s1=diag(abs(dq));
% reg_s2=diag(dq.^2);
% reg_s3=diag(abs(dq).^3);

% Reg_fric=[reg_fc,reg_fv,reg_s0,reg_s1,reg_s2]';
% Reg_fric=[reg_fv,reg_fc,reg_s0,reg_s1]';
Reg_fric=[reg_fv,reg_fc,reg_s0]';



