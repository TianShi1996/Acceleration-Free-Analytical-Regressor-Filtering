clear
close all
clc

load sim_sd1.mat
load sim_sd2.mat
%%
sd_ind=0:0.002:0.03;
len=length(sd_ind);
clc
size_fig=[1000,400,560,200];
close all

sim_ind=1:length(sd_ind);

lab_acc.name="Baseline";lab_acc.name2="Baseline";
% lab_acc.col1=[135 206 250]/255;lab_acc.col2=[72 61 139]/255;
lab_acc.col1=[255,215,0]/255;lab_acc.col2=[165,42,42]/255;
compfig(data_acc(sim_ind),lab_acc,1);
set(gcf,'paperpositionmode','auto');
print('-depsc','ACC.eps');

lab_accf_1.name="LD-CLRC";lab_accf_1.name2="DDF-CLRC ($\lambda=100$)";
% lab_accf_1.col1=[135 206 250]/255;lab_accf_1.col2=[72 61 139]/255;
lab_accf_1.col1=[0,206,209]/255;lab_accf_1.col2=[153,50,204]/255;
compfig(data_accf_1(sim_ind),lab_accf_1,2)
set(gcf,'paperpositionmode','auto');
print('-depsc','DDF-L.eps');

lab_accf_2.name="HD-CLRC";lab_accf_2.name2="DDF-CLRC ($\lambda=20$)";
% lab_accf_2.col1=[65 105 225]/255;lab_accf_2.col2=[205 155 29]/255;
lab_accf_2.col1=[72,209,204]/255;lab_accf_2.col2=[34,139,34]/255;
compfig(data_accf_2(sim_ind),lab_accf_2,3)
set(gcf,'paperpositionmode','auto');
print('-depsc','DDF-H.eps');

lab_reg.name="AF-CLRC";lab_reg.name2="AF-CLRC";
lab_reg.col1=[255 165 0]/255;lab_reg.col2=[205 16 118]/255;
% lab_reg.col1=[255 192 203]/255;lab_reg.col2=[148 0 211]/255;
compfig(data_reg(sim_ind),lab_reg,4)
set(gcf,'paperpositionmode','auto');
print('-depsc','AF-CLRC.eps');


%%
clc
close all
size_fig=[1000,400,560,170];
qerr_acc=RMSE(data_acc(1:len),3);
qerr_accf_1=RMSE(data_accf_1(1:len),3);
qerr_accf_2=RMSE(data_accf_2(1:len),3);
qerr_reg=RMSE(data_reg(1:len),3);
% qerr_hg=RMSE(data_hg);
ind=sd_ind;
col_len=1/ind(end);
% lab_acc.col=lab_acc.col2;%+ind(floor(end))*col_len*(lab_acc.col2-lab_acc.col1);
% lab_accf_2.col=lab_accf_2.col2;%+ind(floor(end))*col_len*(lab_accf_2.col2-lab_accf_2.col1);
% lab_accf_1.col=lab_accf_1.col2;%+ind(floor(end/3))*col_len*(lab_accf_1.col2-lab_accf_1.col1);
% lab_reg.col=lab_reg.col2;%+ind(floor(1))*col_len*(lab_reg.col2-lab_reg.col1);

lab_acc.col=lab_acc.col1+ind(floor(end/4*3))*col_len*(lab_acc.col2-lab_acc.col1);
lab_accf_2.col=lab_accf_2.col1+ind(floor(end))*col_len*(lab_accf_2.col2-lab_accf_2.col1);
lab_accf_1.col=lab_accf_1.col1+ind(floor(end/2))*col_len*(lab_accf_1.col2-lab_accf_1.col1);
lab_reg.col=lab_reg.col1+ind(floor(end/3))*col_len*(lab_reg.col2-lab_reg.col1);

h=figure(5);set(h,"Position",size_fig);
plot(sd_ind,qerr_acc,'-^','color',lab_acc.col,'linewidth',1.8);hold on;
plot(sd_ind,qerr_accf_2,'-+','color',lab_accf_2.col,'linewidth',1.2);hold on;
plot(sd_ind,qerr_accf_1,'-o','color',lab_accf_1.col,'linewidth',1.8);hold on;
plot(sd_ind,qerr_reg,'->','color',lab_reg.col,'linewidth',1.8);hold on;
% plot(sd_ind,qerr_acc,'-^','color',"#0072BD",'linewidth',1.8);hold on;
% plot(sd_ind,qerr_accf_2,'-+','color',"#77AC30",'linewidth',1.2);hold on;
% plot(sd_ind,qerr_accf_1,'-o','color',"#D95319",'linewidth',1.2);hold on;
% plot(sd_ind,qerr_reg,'->','color',"#7E2F8E",'linewidth',1.8);hold on;
% plot(sd_ind,qerr_hg,'-^','color',"#0072BD",'linewidth',1.2);hold on;

legend('Baseline','DDF-CLRC ($\lambda=20$)','DDF-CLRC ($\lambda=100$)','AF-CLRC','interpreter','latex','NumColumns',2,'FontSize',10,'color','none','box','off');
text(-3.5/25*0.03,0.15,"(a)",'FontName','Times New Roman','FontSize',12);
xlabel('');%xticks([])
% ylabel('\boldmath{$\|e_1\|$} (rad)','Interpreter','latex');
ylabel('$e_{\rm{RMSE}}$ (rad)','Interpreter','latex');
set(gca,"FontName","Times New Roman","FontSize",12);
set(gcf,'paperpositionmode','auto');
print('-depsc','RMSE.eps');


%%
clc
close all
size_fig=[1000,400,560,190];
perr_acc=RMSE(data_acc(1:len),4);
perr_accf_1=RMSE(data_accf_1(1:len),4);
perr_accf_2=RMSE(data_accf_2(1:len),4);
perr_reg=RMSE(data_reg(1:len),4);
% qerr_hg=RMSE(data_hg);

h=figure(6);set(h,"Position",size_fig);
plot(sd_ind,perr_acc,'-^','color',lab_acc.col,'linewidth',1.8);hold on;
plot(sd_ind,perr_accf_2,'-+','color',lab_accf_2.col,'linewidth',1.2);hold on;
plot(sd_ind,perr_accf_1,'-o','color',lab_accf_1.col,'linewidth',1.2);hold on;
plot(sd_ind,perr_reg,'->','color',lab_reg.col,'linewidth',1.8);hold on;
% plot(sd_ind,perr_acc,'-^','color',"#0072BD",'linewidth',1.8);hold on;
% plot(sd_ind,perr_accf_2,'-+','color',"#77AC30",'linewidth',1.2);hold on;
% plot(sd_ind,perr_accf_1,'-o','color',"#D95319",'linewidth',1.2);hold on;
% plot(sd_ind,perr_reg,'->','color',"#7E2F8E",'linewidth',1.8);hold on;
% plot(sd_ind,qerr_hg,'-^','color',"#0072BD",'linewidth',1.2);hold on;

legend('Baseline','DDF-CLRC ($\lambda=20$)','DDF-CLRC ($\lambda=100$)','AF-CLRC','interpreter','latex','NumColumns',2,'FontSize',10,'color','none','box','off');
text(-3.5/25*0.03,5,"(b)",'FontName','Times New Roman','FontSize',12);
xlabel('$\sigma$ (rad/s)','Interpreter','latex');
% ylabel('\boldmath{$\|\epsilon\|$} (N.m)','Interpreter','latex');
ylabel('$\varepsilon_{\rm{RMSE}}$ (N.m)','Interpreter','latex','Position',[-0.0025,2]);
axis([0,0.03,0,5]);
set(gca,"FontName","Times New Roman","FontSize",12);
set(gcf,'paperpositionmode','auto');
print('-depsc','pre_RMSE.eps');














