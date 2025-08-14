clc
close all

color_f='#D95319';

color_m='#006400';

color_a1="#0072BD";



% lab_accf_2.col1=[72,209,204]/255;lab_accf_2.col2=[34,139,34]/255;
% lab_accf_2.col=lab_accf_2.col1+ind(floor(end))*col_len*(lab_accf_2.col2-lab_accf_2.col1);
% color_a2=lab_accf_2.col;
% 
% lab_accf_1.col1=[0,206,209]/255;lab_accf_1.col2=[153,50,204]/255;
% lab_accf_1.col=lab_accf_1.col1+ind(floor(end/2))*col_len*(lab_accf_1.col2-lab_accf_1.col1);
% color_a1=lab_accf_1.col;
% 
% lab_reg.col1=[255 165 0]/255;lab_reg.col2=[205 16 118]/255;
% lab_reg.col=lab_reg.col1+ind(floor(end/3))*col_len*(lab_reg.col2-lab_reg.col1);
% color_f=lab_reg.col;

linwid=2;
ftsize=12;

Ts=1e-3;
T1=1:25/Ts;
T2=130/Ts:150/Ts;

t=0:Ts:150;ind_t=1:length(t);

load("MC.mat");
err_norm_mc=MC(ind_t,1);
tau_a_mc=MC(ind_t,2);

load("DDF_CLRC.mat");
err_norm_ddf1=DDF_CLRC(ind_t,1);
tau_a_ddf1=DDF_CLRC(ind_t,2);
W_norm_ddf1=DDF_CLRC(ind_t,3);
predict_err_ddf1=DDF_CLRC(ind_t,4);

load("AF_CLRC.mat");
err_norm_f=AF_CLRC(ind_t,1);
tau_a_f=AF_CLRC(ind_t,2);
W_norm_f=AF_CLRC(ind_t,3);
predict_err_f=AF_CLRC(ind_t,4);

h=figure(5);set(h,"Position",[1000,500,560,170]);
plot(t,W_norm_ddf1,'-.', 'color', color_a1,'linewidth',linwid-0.5);hold on;
plot(t,W_norm_f,'-', 'color', color_f,'linewidth',linwid);hold on;
axis([0,150,0,6]);
legend('DDF-CLRC','AF-CLRC','NumColumns',3,'FontSize',10,'box','off');
text(-3.5/25*150,6,"(a)",'FontName','Times New Roman','FontSize',ftsize);
% xlabel('Time (s)');
ylabel('$\|\hat W\|$','Interpreter','latex','Position',[-12,3]);
set(gca,'FontName','Times New Roman','FontSize',ftsize);

% annotation("arrow",[0.61,0.75],[0.55,0.72]);
axes('Position',[0.46,0.4,0.3,0.25]);
plot(t,W_norm_ddf1,'-.', 'color', color_a1,'linewidth',linwid-0.5);hold on;
plot(t,W_norm_f,'-', 'color', color_f,'linewidth',linwid);hold on;
axis([100,150,4.2,4.35]);
set(gca,'FontName','Times New Roman','FontSize',ftsize-2);
print('-depsc','Estimate.eps');

T1=1:10:25/Ts;
h=figure(6);set(h,"Position",[1000,500,560,170]);
plot(t(T1),tau_a_mc(T1),':', 'color', color_m,'linewidth',linwid);hold on;
plot(t(T1),tau_a_ddf1(T1),'-.', 'color', color_a1,'linewidth',linwid-0.5);hold on;
plot(t(T1),tau_a_f(T1),'-', 'color', color_f,'linewidth',linwid);hold on;

axis([0,25,0,80]);
legend('Baseline','DDF-CLRC','AF-CLRC','NumColumns',3,'FontSize',10,'box','off');
text(-3.5,80,"(b)",'FontName','Times New Roman','FontSize',ftsize);
% xlabel('Time (s)');
ylabel('\boldmath{$\|\tau_{\rm{J}}\|$} (N.m)','Interpreter','latex','Position',[-2,40]);
set(gca,'FontName','Times New Roman','FontSize',ftsize);

axes('Position',[0.3,0.58,0.20,0.17]);
plot(t(T1),tau_a_mc(T1),':', 'color', color_m,'linewidth',linwid);hold on;
plot(t(T1),tau_a_ddf1(T1),'-.', 'color', color_a1,'linewidth',linwid-0.5);hold on;
plot(t(T1),tau_a_f(T1),'-', 'color', color_f,'linewidth',linwid);hold on;
axis([12.8,13.2,46,48]);
set(gca,'FontName','Times New Roman','FontSize',ftsize-2);
set(gcf,'paperpositionmode','auto');
print('-depsc','torque.eps');









h=figure(1);set(h,"Position",[1000,500,560,170]);
plot(t(T1),err_norm_mc(T1),':', 'color', color_m,'linewidth',linwid);hold on;
plot(t(T1),err_norm_ddf1(T1),'-.', 'color', color_a1,'linewidth',linwid-0.5);hold on;
plot(t(T1),err_norm_f(T1),'-', 'color', color_f,'linewidth',linwid);hold on;

axis([0,25,0,0.08]);
legend('Baseline','DDF-CLRC','AF-CLRC','NumColumns',3,'FontSize',10,'box','off');
text(-3.5,0.08,"(c)",'FontName','Times New Roman','FontSize',ftsize);
ylabel('\boldmath{$\|e_1\|$} (rad)','Interpreter','latex');
set(gca,'FontName','Times New Roman','FontSize',ftsize);
print('-depsc','err1.eps');

h=figure(2);set(h,"Position",[1000,500,560,170]);
plot(t(T2),err_norm_mc(T2),':', 'color', color_m,'linewidth',linwid);hold on;
RMSE(err_norm_mc(T2))

plot(t(T2),err_norm_ddf1(T2),'-.', 'color', color_a1,'linewidth',linwid-0.5);hold on;
RMSE(err_norm_ddf1(T2))

plot(t(T2),err_norm_f(T2),'-', 'color', color_f,'linewidth',linwid);hold on;
RMSE(err_norm_f(T2))

axis([130,145,0,0.15]);yticks(0:0.05:0.15);
legend('Baseline','DDF-CLRC','AF-CLRC','NumColumns',3,'FontSize',10,'box','off');
text(-3.5/25*15+130,0.15,"(d)",'FontName','Times New Roman','FontSize',ftsize);
% xlabel('Time (s)');
ylabel('\boldmath{$\|e_1\|$} (rad)','Interpreter','latex','Position',[130-1.25,0.075]);
set(gca,'FontName','Times New Roman','FontSize',ftsize);
print('-depsc','err2.eps');


h=figure(3);set(h,"Position",[1000,500,560,190]);
plot(t(T1),predict_err_ddf1(T1),'-.', 'color', color_a1,'linewidth',linwid-0.5);hold on;
plot(t(T1),predict_err_f(T1),'-', 'color', color_f,'linewidth',linwid);hold on;

axis([0,25,0,18]);
legend('DDF-CLRC','AF-CLRC','NumColumns',3,'FontSize',10,'box','off');
text(-3.5,18,"(e)",'FontName','Times New Roman','FontSize',ftsize);
xlabel('Time (s)');
ylabel('\boldmath{$\|\varepsilon\|$} (N.m)','Interpreter','latex','Position',[-2.25,9]);
set(gca,'FontName','Times New Roman','FontSize',ftsize);
print('-depsc','pre_err1.eps');


h=figure(4);set(h,"Position",[1000,500,560,190]);
plot(t(T2),predict_err_ddf1(T2),'-.', 'color', color_a1,'linewidth',linwid-0.5);hold on;
plot(t(T2),predict_err_f(T2),'-', 'color', color_f,'linewidth',linwid);hold on;

axis([130,145,0,8]);
legend('DDF-CLRC','AF-CLRC','NumColumns',3,'FontSize',10,'box','off');
text(-3.5/25*15+130,8,"(f)",'FontName','Times New Roman','FontSize',ftsize);
xlabel('Time (s)');
ylabel('\boldmath{$\|\varepsilon\|$} (N.m)','Interpreter','latex','Position',[130-1.25,4]);
set(gca,'FontName','Times New Roman','FontSize',ftsize);
print('-depsc','pre_err2.eps');


%%
% h=figure(6);set(h,"Position",[1000,500,560,200]);
% load("AF/O_T_EE");
% time=O_T_EE(1,T2);
% pose_x=O_T_EE(14,T2);pose_y=O_T_EE(15,T2);pose_z=O_T_EE(16,T2);
% plot3(pose_x,pose_y,pose_z,'-','color',color_f,'linewidth',linwid);hold on;




