function demo_pre_err(Ctrl,color,task)
linwid=[1.5,1.5,2]+0.5;
ModName={'DDF-CLRC','AF-CLRC'};
ss={'-.','-'};Ts=1e-3;
if task==1
    t=0:Ts:25;filename='traj2_pre_err_1.gif';
    xind=[0,25];yind=[0,8];ind0=0;ticks=0:2:6;y_pose=[-2.5,4];
else
    t=130:Ts:150;filename='traj2_pre_err_2.gif';
    xind=[130,150];yind=[0,8];ind0=130/Ts;ticks=0:4:8;y_pose=[-2.5/25*20+130,4];
end

h0=figure(3);set(h0,'Position',[1000,400,560,240]);
ftsize=18;
dur=100;
for i=1:length(t)/dur
    figure(3)
    ind=(dur*(i-1)+1):dur*i+ind0;
    for k=1:2
        plot(Ctrl(k).tout(ind),Ctrl(k).pre_err(2,ind),ss{k},'color',color{k},'linewidth',linwid(k));hold on
    end
    legend(ModName{1},ModName{2},'NumColumns',2,'FontSize',14);
    xlabel('Time (s)','Interpreter','latex','FontSize',ftsize);
    ylabel('{\boldmath$\|\varepsilon\|$} (N.m)','Interpreter','latex','FontSize',ftsize,'Position',y_pose);
    title('The prediction error norms','Interpreter','latex','FontSize',ftsize);
    xlim(xind);
    ylim(yind);yticks(ticks);
    set(gca,'FontName','Times New Roman','FontSize',ftsize);
%     pause(0.01);
    F=getframe(gcf);
    im=frame2im(F);
    [I,map]=rgb2ind(im,256);
    k=i-0;
    if k==1
        imwrite(I,map,filename,'gif','Loopcount',inf, 'DelayTime',1/60);
    else
        imwrite(I,map,filename,'gif','WriteMode','append', 'DelayTime',1/60);
    end
end