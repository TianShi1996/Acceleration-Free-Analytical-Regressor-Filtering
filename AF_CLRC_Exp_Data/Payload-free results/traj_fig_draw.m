clear
close all
clc
Ts=1e-3;
ind=5/Ts:15/Ts;
load result2\traj_Clover_delay.mat;
load result2\traj_Clover.mat;


pose=reshape(traj_Clover.pose.Data(1:3,1,ind),3,length(ind));
qd=traj_Clover_delay.qd;

h=figure(1);set(h,"position",[1000,260,680,240*1.5]);
subplot('Position',[0.1,0.58,0.37,0.37]);
plot(pose(2,:),pose(3,:),'LineWidth',1.5);
% xlabel('y (m)');
ylabel('z (m)');
axis([-0.3,0.3,0.35,0.9]);xticks(-0.3:0.1:0.3)
text(-0.42,0.9,'(a)','FontName',"Times New Roman",'Fontsize',12)
set(gca,'FontName',"Times New Roman",'Fontsize',12)
subplot('Position',[0.54,0.58,0.37,0.37]);
plot(qd,'LineWidth',1.5);title('');axis([130,150,-2.6,2.1])
xlabel('');
ylabel('\boldmath{$q_{\rm{d}}$} (rad)','Interpreter','latex');
legend('$q_1$','$q_2$','$q_3$','$q_4$','$q_5$','$q_6$','$q_7$','Interpreter','latex','location','northwest',...
    'NumColumns',3,'fontsize',8,'color','none','edgecolor','none')
set(gca,'FontName',"Times New Roman",'Fontsize',12)



load result3\traj_Rose3_delay.mat;
load result3\traj_Rose3.mat;

pose=reshape(traj_Rose3.pose.Data(1:3,1,ind),3,length(ind));
qd=traj_Rose3_delay.qd;

% h=figure(2);set(h,"position",[1000,260,680,240]);
subplot('Position',[0.1,0.13,0.37,0.37]);
plot(pose(2,:),pose(3,:),'LineWidth',1.5);
xlabel('y (m)');ylabel('z (m)');
%axis([-0.3,0.3,0.35,0.9])
axis([-0.4,0.4,0.6,1.1])
text(-0.55,1.1,'(b)','FontName',"Times New Roman",'Fontsize',12)
set(gca,'FontName',"Times New Roman",'Fontsize',12)
subplot('Position',[0.54,0.13,0.37,0.37]);
plot(qd,'LineWidth',1.5);title('');axis([130,155,-2.8,2.1])
xlabel('Time (s)');ylabel('\boldmath{$q_{\rm{d}}$} (rad)','Interpreter','latex');
legend('$q_1$','$q_2$','$q_3$','$q_4$','$q_5$','$q_6$','$q_7$','Interpreter','latex','location','northwest',...
    'NumColumns',3,'fontsize',8,'color','none','edgecolor','none')
set(gca,'FontName',"Times New Roman",'Fontsize',12)
