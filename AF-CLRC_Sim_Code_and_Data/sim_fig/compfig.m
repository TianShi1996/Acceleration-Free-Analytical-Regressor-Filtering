function compfig(data,lab,k)

sd_ind=0:0.002:0.03;
size_fig=[1000,400,560,150];
if lab.name=="AF-CLRC" %|| lab.name=="DDF-HD" 
    size_fig=[1000,400,560,170];
end

% ind=[0:0.002:0.01,0.02:0.01:0.03];
ind=sd_ind;
col_len=1/ind(end);
h=figure(k);set(h,"Position",size_fig);
i=1;colm=[];
for SD=ind
    col1=[135 206 250]/255;col2=[72 61 139]/255;
    color=lab.col1+SD*col_len*(lab.col2-lab.col1);
    colm=[colm;color];
    plot(data{i}(:,1),data{i}(:,2),'color',color,'linewidth',1.2);hold on
    i=i+1;
end
colormap(colm(1:end,:));c=colorbar("EastOutside",'Ticks',[0,1/3,2/3,1],'TickLabels',0:0.01:0.03,'FontSize',12);
% c.Label.String="SD";
axis([0,150,0,4.5])
text(10,3.5,lab.name2,'fontsize',10,"FontName","Times New Roman",'Interpreter','latex')
text(160,-0.3,"$\sigma$",'Interpreter','latex','fontsize',14,"FontName","Times New Roman")
% xlabel("Time (s)","Interpreter","latex");
if lab.name=="AF-CLRC" %|| lab.name=="DDF-HD" 
    xlabel("Time (s)","Interpreter","latex");
else
    xlabel('');
end

ylabel("$\|\tilde{W}\|$","Interpreter","latex")

set(gca,"FontName","Times New Roman","FontSize",12);


if lab.name=="Baseline"
    text(-15,4.5,'(a)',"FontName","Times New Roman","FontSize",12);
    axes('Position',[0.45,0.45,0.3,0.3]);
    i=1;colm=[];
    for SD=ind
        %col1=[135 206 250]/255;col2=[72 61 139]/255;
        color=lab.col1+SD*col_len*(lab.col2-lab.col1);
        colm=[colm;color];
        plot(data{i}(:,1),data{i}(:,2),'color',color,'linewidth',1.2);hold on
        i=i+1;
    end
    axis([0,150,0,0.8]);yticks(0:0.2:0.8);
    set(gca,"FontName","Times New Roman","FontSize",10);
end


if lab.name=="LD-CLRC"
    text(-15,4.5,'(c)',"FontName","Times New Roman","FontSize",12);
    axes('Position',[0.45,0.45,0.3,0.3]);
    i=1;colm=[];
    for SD=ind
        %col1=[135 206 250]/255;col2=[72 61 139]/255;
        color=lab.col1+SD*col_len*(lab.col2-lab.col1);
        colm=[colm;color];
        plot(data{i}(:,1),data{i}(:,2),'color',color,'linewidth',1.2);hold on
        i=i+1;
    end
    axis([0,150,0,0.8]);yticks(0:0.2:0.8);
    set(gca,"FontName","Times New Roman","FontSize",10);
end
if lab.name=="HD-CLRC"
    text(-15,4.5,'(b)',"FontName","Times New Roman","FontSize",12);
    axes('Position',[0.45,0.45,0.3,0.3]);
    i=1;colm=[];
    for SD=ind
        %col1=[135 206 250]/255;col2=[72 61 139]/255;
        color=lab.col1+SD*col_len*(lab.col2-lab.col1);
        colm=[colm;color];
        plot(data{i}(:,1),data{i}(:,2),'color',color,'linewidth',1.2);hold on
        i=i+1;
    end
    axis([0,150,0.3,0.5]);%yticks(0:0.2:0.8);
    set(gca,"FontName","Times New Roman","FontSize",10);
end

if lab.name=="AF-CLRC"
    text(-15,4.5,'(d)',"FontName","Times New Roman","FontSize",12);
    axes('Position',[0.45,0.45,0.3,0.3]);
    i=1;colm=[];
    for SD=ind
        %col1=[135 206 250]/255;col2=[72 61 139]/255;
        color=lab.col1+SD*col_len*(lab.col2-lab.col1);
        colm=[colm;color];
        plot(data{i}(:,1),data{i}(:,2),'color',color,'linewidth',1.2);hold on
        i=i+1;
    end
    axis([0,150,0,0.15]);
    set(gca,"FontName","Times New Roman","FontSize",10);
end

