clear
close all
clc

Ts=1e-3;
color_f='#D95319';

color_a2='#006400';

color_a1="#0072BD";


color={color_a1,color_f};



load("DDF/W_norm.mat");W_norm_ddf1=W_norm;
load("AF/W_norm.mat");W_norm_f=W_norm;

load("DDF/tau_a.mat");tau_a_ddf1=norm_tau(tau_a);
load("AF/tau_a.mat");tau_a_f=norm_tau(tau_a);

load("DDF/err_norm.mat");err_norm_ddf1=err_norm;
load("AF/err_norm.mat");err_norm_f=err_norm;

load("DDF/predict_err.mat");predict_err_ddf1=predict_err;
load("AF/predict_err.mat");predict_err_f=predict_err;


Ctrl(1).tout=0:Ts:155;
Ctrl(1).W_hat=W_norm_ddf1;
Ctrl(1).tau_a=tau_a_ddf1;
Ctrl(1).q_err_norm=err_norm_ddf1;
Ctrl(1).pre_err=predict_err_ddf1;

Ctrl(2).tout=0:Ts:155;
Ctrl(2).W_hat=W_norm_f;
Ctrl(2).tau_a=tau_a_f;
Ctrl(2).q_err_norm=err_norm_f;
Ctrl(2).pre_err=predict_err_f;


%%
close all;clc
% task=1,2 which represents task 1 and 2.
task=2;
% demo_taua(Ctrl,color,task);
% demo_err_norm(Ctrl,color,task);
demo_pre_err(Ctrl,color,task);

% demo_W_hat(Ctrl,color)