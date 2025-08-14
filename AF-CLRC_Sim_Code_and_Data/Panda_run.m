clear;
close all;
clc;
load trajectory\traj1_delay3.mat;
traj_c=traj1_delay3;


load P.mat;
invP=inv(P*P')*P;

load P_RNE.mat;
invP_RNE=inv(P_RNE*P_RNE')*P_RNE;


%%
SD = 0.0; % standard derivation
vari = SD^2; % noise variance



%% for controller

dyn_par=opt_par();
basepar=baseparmes(P);

fricpar=FrictionPar();

robot_par=[basepar;fricpar];

N=length(robot_par);
% basepar=[basepar;fricpar];

Ts = 0.0005; Umax = 500;

taud = 25; % integral duration
Lambda=3*eye(7);
Kc =diag([10,10,10,10,4,4,2.5]);%*0.02; % control gains

P0=0.04;
P1=1;

GammaW = 0.4*eye(N);
alpha=15;
alpha2=10;
diff_alpha1=100;
diff_alpha2=20;
kapa1=1;kapa2=0;



% taud = 25; % integral duration
% Lambda=10*eye(7);
% Kc =diag([20,20,20,20,8,8,5]);%*0.02; % control gains
% 
% P0=0.05;
% P1=0.1;
% 
% GammaW = 0.4*eye(N);
% alpha=4;
% alpha2=8;
% diff_alpha1=100;
% diff_alpha2=20;
% kapa1=1;kapa2=0;


q0=[0, -0.60, 0, -2.25, 0, 1.5, 0.8]';
q02=[0,0,0,-pi/2,0,pi,pi/4]';


I=eye(7);



f=30;


a=10;

g0=[0,0,0,0,0,-9.81]';
si=[0,0,1,0,0,0]';