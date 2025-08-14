function Phic=Gravity_RNE_Regressor_panda(q,g0)

q1=q(1);q2=q(2);q3=q(3);q4=q(4);q5=q(5);q6=q(6);q7=q(7);
s1=sin(q1);c1=cos(q1);s2=sin(q2);c2=cos(q2);s3=sin(q3);c3=cos(q3);
s4=sin(q4);c4=cos(q4);s5=sin(q5);c5=cos(q5);s6=sin(q6);c6=cos(q6);
s7=sin(q7);c7=cos(q7);
sin_q=[s1,s2,s3,s4,s5,s6,s7];
cos_q=[c1,c2,c3,c4,c5,c6,c7];

sin_q=sym('s',[7,1]);cos_q=sym('c',[7,1]);

Xn=matrix_Xn(sin_q,cos_q);
XXnSI=matrix_XXnSI(sin_q,cos_q);
XXnSI_sym=sym(zeros(size(XXnSI)));
n=7;
du0=zeros(7,1);
du0=-g0;

Phi=sym(zeros(7,70));
for i=1:n
    ind=(6*i-5):(6*i);Xi=Xn(ind,:);

    du0=Xi*du0;
    % for j=1:6
    % fprintf('%s%s%s%s%s%s%s',['du0',num2str(i),num2str(j),'=',string(du0(j)),';']);
    % fprintf("\n");
    % end
    du0=sym(['du0',num2str(i)],[6,1]);

    fi_vec=fun_Ru(du0);
    for k=1:i
        for p=(6*i-5):(6*i)
            if XXnSI(k,p)~=0
                fprintf('%s%s%s%s%s%s%s',['XXnSI_',num2str(k),num2str(p),'=',string(XXnSI(k,p)),';']);
                fprintf("\n");XXnSI_sym(k,p)=sym(['XXnSI_',num2str(k),num2str(p)]);
            % else
            %     XXnSI_sym(k,p)=0;
            end
        end
    end
    Phi(1:i,10*(i-1)+1:10*i)=XXnSI_sym(1:i,ind)*fi_vec;
    % for k=1:i
    %     for p=10*(i-1)+1:10*i
    %         if Phi(k,p)~=0
    %             fprintf('%s%s%s%s%s%s%s',['Phi(',num2str(k),',',num2str(p),')=',string(Phi(k,p)),';']);
    %             fprintf("\n");
    %         end
    %     end
    % end
end

for i=1:n
    for k=1:i
        for p=10*(i-1)+1:10*i
            if Phi(k,p)~=0
                fprintf('%s%s%s%s%s%s%s',['Phi(',num2str(k),',',num2str(p),')=',string(Phi(k,p)),';']);
                fprintf("\n");
            end
        end
    end
end

Phic=reshape(Phi,490,1);
end

function fi_vec=fun_Ru(du)

du1=du(1);du2=du(2);du3=du(3);du4=du(4);du5=du(5);du6=du(6);

fi_vec=[0,    0,  du6, -du5, du1,   0,   0,   0, du3, du2
    0, -du6,    0,  du4,   0, du2,   0, du3,   0, du1
    0,  du5, -du4,    0,   0,   0, du3, du2, du1,   0
    du4,    0, -du3,  du2,   0,   0,   0,   0,   0,   0
    du5,  du3,    0, -du1,   0,   0,   0,   0,   0,   0
    du6, -du2,  du1,    0,   0,   0,   0,   0,   0,   0];

end




