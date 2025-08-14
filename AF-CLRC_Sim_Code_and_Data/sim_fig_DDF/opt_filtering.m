clear
close all
clc

Ts=1e-3;
col1=[0.4660 0.6740 0.1880];
col2=[0 0.4470 0.7410];
col3=[0.8500 0.3250 0.0980];
col4=[0.6350 0.0780 0.1840];

Ts0 = 0.0002;
ind=130/Ts0:5:145/Ts0;
ftsize=12;
sd_ind=0:0.002:0.03;len_sd=length(sd_ind);
DDF_alpha=10:5:150;len_lm=length(DDF_alpha);

load sim_DDF_Test.mat;
load sim_AF.mat;

%%
close all
sd_ind(8)
for i=1:len_lm
    k=8;
        data=data_accf{i,k};
        W_ss(i)=max(data(:,2));
        RMSE_q(i)=sqrt(sum(data(:,3).^2)*Ts/15);
        RMSE_pre(i)=sqrt(sum(data(:,4).^2)*Ts/15);

        data_AF=data_reg{k};
        W_ss_AF(i)=max(data_AF(ind,2));
        RMSE_q_AF(i)=sqrt(sum(data_AF(ind,3).^2)*Ts/15);
        RMSE_pre_AF(i)=sqrt(sum(data_AF(ind,4).^2)*Ts/15);
end
linwid=1.5;
for k=3:-1:1
    % Pos(k,:)=[0.1,1.04-k*0.32,0.39,0.27];
    Pos(k,:)=[1.06-(4-k)*0.32,0.25,0.22,0.7];
end

h=figure(1);set(h,"Position",[1000,560,560,180])
% h1=subplot(131);set(h1,'Position',Pos(1,:))
plot(DDF_alpha,W_ss,'-','LineWidth',linwid);grid on
xlabel("$\lambda$",'Interpreter','latex');ylabel("$w_{\rm{ss}}$",'Interpreter','latex');
% text(-60,0.8,"(a)","FontSize",ftsize,"FontName","Times New Roman");
set(gca,"FontSize",ftsize,"FontName","Times New Roman");

% h2=subplot(132);set(h2,'Position',Pos(2,:))
% plot(DDF_alpha,RMSE_q,'-','LineWidth',linwid);
% xlabel("$\lambda$",'Interpreter','latex');ylabel("$e_{\rm{RMSE}}$",'Interpreter','latex');
% text(-60,0.3,"(b)","FontSize",ftsize,"FontName","Times New Roman");
% set(gca,"FontSize",ftsize,"FontName","Times New Roman");
% 
% h3=subplot(133);set(h3,'Position',Pos(3,:))
% plot(DDF_alpha,RMSE_pre,'-','LineWidth',linwid);ylim([0,5]);yticks([0,2.5,5])
% xlabel("$\lambda$",'Interpreter','latex');ylabel("$\varepsilon_{\rm{RMSE}}$",'Interpreter','latex');
% text(-60,5,"(c)","FontSize",ftsize,"FontName","Times New Roman");
% set(gca,"FontSize",ftsize,"FontName","Times New Roman");

set(gcf,'paperpositionmode','auto');
print('-depsc','fig_opt.eps');
