function Phic=SL_RNE_Regressor_panda(q,dq,dqr,ddqr,g0,si)

q1=q(1);q2=q(2);q3=q(3);q4=q(4);q5=q(5);q6=q(6);q7=q(7);
s1=sin(q1);c1=cos(q1);s2=sin(q2);c2=cos(q2);s3=sin(q3);c3=cos(q3);
s4=sin(q4);c4=cos(q4);s5=sin(q5);c5=cos(q5);s6=sin(q6);c6=cos(q6);
s7=sin(q7);c7=cos(q7);
sin_q=[s1,s2,s3,s4,s5,s6,s7];
cos_q=[c1,c2,c3,c4,c5,c6,c7];


Xn=matrix_Xn(sin_q,cos_q);
XXnSI=matrix_XXnSI(sin_q,cos_q);
% XXnSI=matrix_XXnSI_R(q,Xn);
n=7;

dqs=dq'.*si;
dqrs=dqr'.*si;
ddqrs=ddqr'.*si;

vec0=zeros(6,1);

v0=vec0;u0=vec0;
du0=-g0;

Phi=zeros(7,70);
% Phic=zeros(70,7);
% Q=zeros(6*n,10);


for i=1:n
    ind=(6*i-5):(6*i);Xi=Xn(ind,:);
    v0=Xi*v0+dqs(:,i);
    u0=Xi*u0+dqrs(:,i);
    omegax=[0,-v0(3),v0(2);
        v0(3),0,-v0(1);
        -v0(2),v0(1),0];
    vux=[0,-v0(6),v0(5);
        v0(6),0,-v0(4);
        -v0(5),v0(4),0];
    vix=[omegax,zeros(3);
        vux,omegax];
    du0=Xi*du0+ddqrs(:,i)+dqr(i)*vix(:,3);
    
    
    fi_vec=fun_Ru(u0,du0,v0);%Q(ind,:)=fi_vec;
    Phi(1:i,10*(i-1)+1:10*i)=XXnSI(1:i,ind)*fi_vec;
end

Phic=Phi';
end

function fi_vec=fun_Ru(u,du,v)
u1=u(1);u2=u(2);u3=u(3);u4=u(4);u5=u(5);u6=u(6);
du1=du(1);du2=du(2);du3=du(3);du4=du(4);du5=du(5);du6=du(6);
v1=v(1);v2=v(2);v3=v(3);v4=v(4);v5=v(5);v6=v(6);
fi_vec=zeros(6,10);
fi_vec(1,1)=u6*v5 - u5*v6;
fi_vec(1,2)=u5*v2 - u2*v5 - u3*v6 + u6*v3;
fi_vec(1,3)=du6 + u1*v5 - u4*v2;
fi_vec(1,4)=u1*v6 - du5 - u4*v3;
fi_vec(1,5)=du1;
fi_vec(1,6)=-u2*v3;
fi_vec(1,7)=u3*v2;
fi_vec(1,8)=u2*v2 - u3*v3;
fi_vec(1,9)=du3 + u1*v2;
fi_vec(1,10)=du2 - u1*v3;
fi_vec(2,1)=u4*v6 - u6*v4;
fi_vec(2,2)=u2*v4 - du6 - u5*v1;
fi_vec(2,3)=u4*v1 - u1*v4 - u3*v6 + u6*v3;
fi_vec(2,4)=du4 + u2*v6 - u5*v3;
fi_vec(2,5)=u1*v3;
fi_vec(2,6)=du2;
fi_vec(2,7)=-u3*v1;
fi_vec(2,8)=du3 - u2*v1;
fi_vec(2,9)=u3*v3 - u1*v1;
fi_vec(2,10)=du1 + u2*v3;
fi_vec(3,1)=u5*v4 - u4*v5;
fi_vec(3,2)=du5 + u3*v4 - u6*v1;
fi_vec(3,3)=u3*v5 - du4 - u6*v2;
fi_vec(3,4)=u4*v1 - u1*v4 - u2*v5 + u5*v2;
fi_vec(3,5)=-u1*v2;
fi_vec(3,6)=u2*v1;
fi_vec(3,7)=du3;
fi_vec(3,8)=du2 + u3*v1;
fi_vec(3,9)=du1 - u3*v2;
fi_vec(3,10)=u1*v1 - u2*v2;
fi_vec(4,1)=du4 - u5*v3 + u6*v2;
fi_vec(4,2)=- u2*v2 - u3*v3;
fi_vec(4,3)=u1*v2 - du3;
fi_vec(4,4)=du2 + u1*v3;
fi_vec(5,1)=du5 + u4*v3 - u6*v1;
fi_vec(5,2)=du3 + u2*v1;
fi_vec(5,3)=- u1*v1 - u3*v3;
fi_vec(5,4)=u2*v3 - du1;
fi_vec(6,1)=du6 - u4*v2 + u5*v1;
fi_vec(6,2)=u3*v1 - du2;
fi_vec(6,3)=du1 + u3*v2;
fi_vec(6,4)=- u1*v1 - u2*v2;
end





