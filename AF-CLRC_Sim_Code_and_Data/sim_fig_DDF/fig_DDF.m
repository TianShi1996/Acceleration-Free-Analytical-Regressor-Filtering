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

for i=1:len_lm
    for k=1:len_sd
        data=data_accf{i,k};
        W_ss(i,k)=max(data(:,2));
        RMSE_q(i,k)=sqrt(sum(data(:,3).^2)*Ts/15);
        RMSE_pre(i,k)=sqrt(sum(data(:,4).^2)*Ts/15);

        data_AF=data_reg{k};
        W_ss_AF(i,k)=max(data_AF(ind,2));
        RMSE_q_AF(i,k)=sqrt(sum(data_AF(ind,3).^2)*Ts/15);
        RMSE_pre_AF(i,k)=sqrt(sum(data_AF(ind,4).^2)*Ts/15);
    end
    % figure(1)
    % plot3(DDF_alpha(i)*ones(len_sd,1),sd_ind,W_ss(i,:),'o');hold on;
end
[X,Y]=meshgrid(sd_ind,DDF_alpha);

%% color
color_aff=zeros(len_lm,len_sd,3);
color_reg=zeros(len_lm,len_sd,3);
for i=1:len_lm
    for j=1:len_sd
        % color2=[0,206,209]/255;color1=[153,50,204]/255;
        c11=[0,206,209]/255;c12=[153,50,204]/255;c21=[72,209,204]/255;c22=[34,139,34]/255;
        color2=(0.3*c11+0.7*c12);color1=(0.7*c21+0.3*c22);
        % color2=[0.6350 0.0780 0.1840];color1=[1 1 0];
        color_aff(len_lm-i+1,j,[1,2,3])=color2+(color1-color2)*(i-1)/(len_lm-1);
        color2=[255 165 0]/255;color1=[205 16 118]/255;
        %color2=[0 0.4470 0.7410];color1=[0 1 1];
        color_reg(len_lm-i+1,j,[1,2,3])=color2+(color1-color2)*(j-1)/(len_sd-1);
    end
end

%
close all
clc
Pos=zeros(3,4);
for k=3:-1:1
    Pos2(k,:)=[0.57,1.04-k*0.32,0.39,0.25];
    % Pos2(k,:)=[0.98-(4-k)*0.3,0.10,0.24,0.38];
end
for k=3:-1:1
    Pos(k,:)=[0.1,1.04-k*0.32,0.39,0.27];
    % Pos(k,:)=[0.98-(4-k)*0.3,0.58,0.24,0.38];
end


h=figure(1);set(h,"position",[1000,260,680,240*3]);
h1=subplot(321);set(h1,'Position',Pos(1,:))
sh=surf(X,Y,W_ss_AF,color_reg,'FaceAlpha',1,'EdgeColor','flat');hold on;
surf(X,Y,W_ss,color_aff,'FaceAlpha',0.75,'EdgeColor','flat');%,'EdgeColor','interp','FaceColor','interp'
legend('AF-CLRC','DDF-CLRC','Location','northeast','NumColumns',2,"FontSize",ftsize-3);
xlabel("$\sigma$ (rad/s)",'Interpreter','latex');ylabel("$\lambda$",'Interpreter','latex');zlabel("$w_{\rm{ss}}$",'Interpreter','latex');
text(0.043,145,1,"(a)","FontSize",ftsize,"FontName","Times New Roman");
set(gca,"FontSize",ftsize,"FontName","Times New Roman");view(-135,10);
% set(gcf,'paperpositionmode','auto');
% print('-depsc','fig_DDF_w.eps');

% h=figure(2);set(h,"position",[1000,560,560,300])
h1=subplot(323);set(h1,'Position',Pos(2,:))
surf(X,Y,RMSE_q_AF,color_reg,'FaceAlpha',1,'EdgeColor','flat');hold on;
surf(X,Y,RMSE_q,color_aff,'FaceAlpha',0.75,'EdgeColor','flat');
legend('AF-CLRC','DDF-CLRC','Location','northeast','NumColumns',2,"FontSize",ftsize-3);
xlabel("$\sigma$ (rad/s)",'Interpreter','latex');ylabel("$\lambda$",'Interpreter','latex');zlabel("$e_{\rm{RMSE}}$ (rad)",'Interpreter','latex');
zlim([0,0.4]);
text(0.043,150,0.4,"(b)","FontSize",ftsize,"FontName","Times New Roman");
set(gca,"FontSize",ftsize,"FontName","Times New Roman");view(-135,10);
% print('-depsc','fig_DDF_e.eps');

% h=figure(3);set(h,"position",[1000,560,560,300])
h1=subplot(325);set(h1,'Position',Pos(3,:))
surf(X,Y,RMSE_pre_AF,color_reg,'FaceAlpha',1,'EdgeColor','flat');hold on;
surf(X,Y,RMSE_pre,color_aff,'FaceAlpha',0.75,'EdgeColor','flat');
legend('AF-CLRC','DDF-CLRC','Location','northeast','NumColumns',2,"FontSize",ftsize-3);
xlabel("$\sigma$ (rad/s)",'Interpreter','latex');ylabel("$\lambda$",'Interpreter','latex');zlabel("$\varepsilon_{\rm{RMSE}}$ (N.m)",'Interpreter','latex');
zlim([0,5.5]);
text(0.043,150,5.5,"(c)","FontSize",ftsize,"FontName","Times New Roman");
set(gca,"FontSize",ftsize,"FontName","Times New Roman");view(-135,10);
set(gcf,'paperpositionmode','auto');



% print('-depsc','fig_surf.eps');


% h=figure(2);set(h,"position",[1000,260,1160,240]);
h1=subplot(322);set(h1,'Position',Pos2(1,:))
surf(X,Y,W_ss_AF,color_reg,'FaceAlpha',1,'EdgeColor','flat');hold on;
surf(X,Y,W_ss,color_aff,'FaceAlpha',0.75,'EdgeColor','flat');%,'EdgeColor','interp','FaceColor','interp'
surf(X,Y,W_ss_AF,color_reg,'FaceAlpha',1,'LineWidth',1.5,'EdgeColor','interp','FaceColor','interp');
legend('AF-CLRC','DDF-CLRC','Location','northeast','NumColumns',2,"FontSize",ftsize-3);
xlabel("$\sigma$ (rad/s)",'Interpreter','latex');ylabel("$\lambda$",'Interpreter','latex');zlabel("$w_{\rm{ss}}$",'Interpreter','latex');
% text(-0.005,0,1,"(d)","FontSize",ftsize,"FontName","Times New Roman");
set(gca,"FontSize",ftsize,"FontName","Times New Roman");view(0,0);
% set(gcf,'paperpositionmode','auto');
% print('-depsc','fig_DDF_w.eps');

% h=figure(2);set(h,"position",[1000,560,560,300])
h1=subplot(324);set(h1,'Position',Pos2(2,:))
surf(X,Y,RMSE_q_AF,color_reg,'FaceAlpha',1,'EdgeColor','flat');hold on;
surf(X,Y,RMSE_q,color_aff,'FaceAlpha',0.75,'EdgeColor','flat');
surf(X,Y,RMSE_q_AF,color_reg,'FaceAlpha',1,'LineWidth',1.5,'EdgeColor','interp','FaceColor','interp');
legend('AF-CLRC','DDF-CLRC','Location','northeast','NumColumns',2,"FontSize",ftsize-3);
xlabel("$\sigma$ (rad/s)",'Interpreter','latex');ylabel("$\lambda$",'Interpreter','latex');zlabel("$e_{\rm{RMSE}}$ (rad)",'Interpreter','latex');
zlim([0,0.4]);
% text(-0.005,0,0.4,"(e)","FontSize",ftsize,"FontName","Times New Roman");
set(gca,"FontSize",ftsize,"FontName","Times New Roman");view(0,0);
% print('-depsc','fig_DDF_e.eps');

% h=figure(3);set(h,"position",[1000,560,560,300])
h1=subplot(326);set(h1,'Position',Pos2(3,:))
surf(X,Y,RMSE_pre_AF,color_reg,'FaceAlpha',1,'EdgeColor','flat');hold on;
surf(X,Y,RMSE_pre,color_aff,'FaceAlpha',0.75,'EdgeColor','flat');
surf(X,Y,RMSE_pre_AF,color_reg,'FaceAlpha',1,'LineWidth',1.5,'EdgeColor','interp','FaceColor','interp');
legend('AF-CLRC','DDF-CLRC','Location','northeast','NumColumns',2,"FontSize",ftsize-3);
xlabel("$\sigma$ (rad/s)",'Interpreter','latex');ylabel("$\lambda$",'Interpreter','latex');zlabel("$\varepsilon_{\rm{RMSE}}$ (N.m)",'Interpreter','latex');
zlim([0,5.5]);
% text(-0.005,0,5.5,"(f)","FontSize",ftsize,"FontName","Times New Roman");
set(gca,"FontSize",ftsize,"FontName","Times New Roman");view(0,0);
set(gcf,'paperpositionmode','auto');

print('-depsc','fig_surf.eps');