function Phic=Filter_CT_Regressor_panda(q,dq,si)

n=7;

dqs=dq'.*si;

Xn=matrix_Xn(sin(q),cos(q));
% v0=zeros(6,1);
v0=dqs(:,1);

Phi=zeros(7,70);
si_ct=zeros(6,n);

for i=2:n
    Xi=Xn(6*i-5:6*i,:);
    v0=Xi*v0+dqs(:,i);

    fi_vec_CT=fun_Ru_CT(v0);
    si_ct([1,2,4,5],i)= [v0(2),-v0(1),v0(5),-v0(4)]';
    XXn=zeros(i,6);

    for j=2:i
        Xs=eye(6);
        k=j;
        while k<i
            Xs=Xs*Xn(6*k+1:6*k+6,:)';k=k+1;
        end
        XXn(j,:)=si_ct(:,j)'*Xs;
    end
    % XXn=si_ct(:,1:i)'*Xs;
    Phi(1:i,10*(i-1)+1:10*i)=XXn*fi_vec_CT;
end

Phic=Phi';

end

function fi_vec_CT=fun_Ru_CT(v)

v1=v(1);v2=v(2);v3=v(3);v4=v(4);v5=v(5);v6=v(6);
fi_vec_CT=[ 0,   0,  v6, -v5, v1,  0,  0,  0, v3, v2
    0, -v6,   0,  v4,  0, v2,  0, v3,  0, v1
    0,  v5, -v4,   0,  0,  0, v3, v2, v1,  0
    v4,   0, -v3,  v2,  0,  0,  0,  0,  0,  0
    v5,  v3,   0, -v1,  0,  0,  0,  0,  0,  0
    v6, -v2,  v1,   0,  0,  0,  0,  0,  0,  0];
end
