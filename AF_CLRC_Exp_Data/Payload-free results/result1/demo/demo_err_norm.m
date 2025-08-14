function demo_err_norm(Ctrl,color,task)
linwid=[1.5,1.5,2]+0.5;
ModName={'DDF-CLRC','AF-CLRC'};
ss={'-.','-'};Ts=1e-3;
if task==1
    t=0:Ts:25;filename='err_norm_1.gif';
    xind=[0,25];yind=[0,0.08];ind0=0;ticks=0:0.04:0.08;y_pose=[-2.5,0.04];
else
    t=130:Ts:145;filename='err_norm_2.gif';
    xind=[130,145];yind=[0,0.2];ind0=130/Ts;ticks=0:0.1:0.2;y_pose=[130-2.5/25*15,0.1];
end

h0=figure(2);set(h0,'Position',[1000,400,560,240]);
ftsize=18;
dur=100;
for i=1:length(t)/dur
    figure(2)
    ind=(dur*(i-1)+1):dur*i+ind0;
    for k=1:2
        plot(Ctrl(k).tout(ind),Ctrl(k).q_err_norm(2,ind),ss{k},'color',color{k},'linewidth',linwid(k));hold on
    end
    legend(ModName{1},ModName{2},'NumColumns',2,'FontSize',14);
    xlabel('Time (s)','Interpreter','latex','FontSize',ftsize);
    ylabel('{\boldmath$\|e_1\|$} (rad)','Interpreter','latex','FontSize',ftsize,'Position',y_pose);
    title('The tracking error norms','Interpreter','latex','FontSize',ftsize);
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