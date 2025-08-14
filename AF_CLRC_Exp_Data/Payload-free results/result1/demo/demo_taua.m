function demo_taua(Ctrl,color,task)
linwid=[1.5,1.5,2]+0.5;
ModName={'DDF-CLRC','AF-CLRC'};
ss={'-.','-'};Ts=1e-3;
if task==1
    t=0:Ts:25;filename='tau_a_1.gif';
    xind=[0,25];yind=[0,80];ind0=0;y_pose=[-2.5,40];
else
    t=130:Ts:145;filename='tau_a_2.gif';
    xind=[130,145];yind=[0,80];ind0=130/Ts;y_pose=[-2.5/25*15+130,40];
end

h0=figure(1);set(h0,'Position',[1000,400,560,240]);
ftsize=18;
dur=100;
for i=1:length(t)/dur
    figure(1)
    ind=(dur*(i-1)+1):dur*i+ind0;
    for k=1:2
        plot(Ctrl(k).tout(ind),Ctrl(k).tau_a(2,ind),ss{k},'color',color{k},'linewidth',linwid(k));hold on
    end
    legend(ModName{1},ModName{2},'NumColumns',2,'FontSize',14);
    xlabel('Time (s)','Interpreter','latex','FontSize',ftsize);
    ylabel('{\boldmath$\|\tau\|$} (N.m)','Interpreter','latex','FontSize',ftsize,'Position',y_pose);
    title('The joint toruqe norms','Interpreter','latex','FontSize',ftsize);
    xlim(xind);
    ylim(yind);yticks(0:40:80);
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
end