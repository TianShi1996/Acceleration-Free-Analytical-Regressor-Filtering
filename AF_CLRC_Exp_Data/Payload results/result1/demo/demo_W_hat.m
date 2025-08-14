function demo_W_hat(Ctrl,color)
linwid=[1.5,1.5,2]+0.5;
ModName={'DDF-CLRC','AF-CLRC'};
ss={'-.','-'};
Ts=1e-3;t=0:Ts:150;

filename='W_hat.gif';
xind=[0,150];yind=[0,9];ind0=0;

h0=figure(4);set(h0,'Position',[1000,400,560,240]);
ftsize=18;
dur=250;
for i=1:length(t)/dur
    figure(4)
    ind=(dur*(i-1)+1):dur*i+ind0;
    for k=1:2
        plot(Ctrl(k).tout(ind),Ctrl(k).W_hat(2,ind),ss{k},'color',color{k},'linewidth',linwid(k));hold on
    end
    legend(ModName{1},ModName{2},'NumColumns',2,'FontSize',14);
    xlabel('Time (s)','Interpreter','latex','FontSize',ftsize);

    ylabel('$\|\hat{W}\|$','Interpreter','latex','FontSize',ftsize,'Position',[-2.2/25*150,4.5]);
    title('Parameter estimate norms','Interpreter','latex','FontSize',ftsize);
    axis([0,150,0,9]);xticks(0:30:150);yticks(0:3:9);
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