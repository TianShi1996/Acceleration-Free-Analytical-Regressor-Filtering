clear
close all
clc

Ts=1e-3;
% ind_t=130/Ts+1:145/Ts;T=15;filename="result1\";
% ind_t=130/Ts+1:150/Ts;T=20;filename="result2\";
ind_t=130/Ts+1:155/Ts;T=25;filename="result3\";



load(filename+"MC.mat");
load(filename+"DDF_CLRC.mat");
load(filename+"AF_CLRC.mat");

err_norm_mc=MC(ind_t,1);
tau_a_mc=MC(ind_t,2);

err_norm_ddf1=DDF_CLRC(ind_t,1);
tau_a_ddf1=DDF_CLRC(ind_t,2);
W_norm_ddf1=DDF_CLRC(ind_t,3);
predict_err_ddf1=DDF_CLRC(ind_t,4);

err_norm_f=AF_CLRC(ind_t,1);
tau_a_f=AF_CLRC(ind_t,2);
W_norm_f=AF_CLRC(ind_t,3);
predict_err_f=AF_CLRC(ind_t,4);



af_clrc.t=ind_t*Ts;
af_clrc.err=err_norm_f;
af_clrc.pre_err=predict_err_f;
af_err=Table_RMSE(af_clrc.err,T);
af_pre=Table_RMSE(af_clrc.pre_err,T);

ddf_clrc.t=ind_t*Ts;
ddf_clrc.err=err_norm_ddf1;
ddf_clrc.pre_err=predict_err_ddf1;
ddf_err=Table_RMSE(ddf_clrc.err,T);
ddf_pre=Table_RMSE(ddf_clrc.pre_err,T);

mc_err=Table_RMSE(err_norm_mc,T);

[af_err,af_pre,ddf_err,ddf_pre,mc_err]

% figure(1)
% plot(af_clrc.t,af_clrc.err)

function e=Table_RMSE(u,T)
Ts=1e-3;
e=sqrt(sum(u.^2)*Ts/T);
end

function e=Table_ss(u)
e=max(u);
end

