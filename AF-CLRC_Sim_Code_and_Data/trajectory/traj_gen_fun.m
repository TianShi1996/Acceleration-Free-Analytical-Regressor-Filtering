function [y,dy,ddy]=traj_gen_fun(t,T,P)

% T_len=length(T);
[~,n]=size(P);
minT=min(T);maxT=max(T);

if t>=minT && t<=maxT
    ts=t-minT;
    td1=T-t;
    ind0=max(find(td1<=0));
    ind1=min(find(td1>=0));
    t0=T(ind0)-minT;
    t1=T(ind1)-minT;

    AT=[1,  t0,  t0^2,  t0^3,   t0^4,    t0^5;
        0,  1,   2*t0,  3*t0^2, 4*t0^3,  5*t0^4;
        0,  0,   2,     6*t0,   12*t0^2, 20*t0^3;
        1,  t1,  t1^2,  t1^3,   t1^4,    t1^5;
        0,  1,   2*t1,  3*t1^2, 4*t1^3,  5*t1^4;
        0,  0,   2,     6*t1,   12*t1^2, 20*t1^3];

    b=zeros(6,n);
    b(1,:)=P(ind0,:);b(4,:)=P(ind1,:);

    tp=[1,  ts,  ts^2,  ts^3,   ts^4,    ts^5]';
    dtp=[0,  1,   2*ts,  3*ts^2, 4*ts^3,  5*ts^4]';
    ddtp=[0,  0,   2,     6*ts,   12*ts^2, 20*ts^3]';

    c=pinv(AT)*b;
    y=c'*tp;
    dy=c'*dtp;
    ddy=c'*ddtp;
else
    if t<minT
        y=P(1,:)';
    else
        y=P(end,:)';
    end
    dy=zeros(7,1);
    ddy=zeros(7,1);
end