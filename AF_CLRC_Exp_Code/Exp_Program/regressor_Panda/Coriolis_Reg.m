function Cv=Coriolis_Reg(q,dq,Fdq)
vec0=zeros(7,1);I=eye(7);
% Fdq=Base_Slotine_Panda(q,dq,vec0,vec0);
% Cv=Base_Slotine_Panda(q,dq,v,vec0)-Fdq;
[Y_q_dot,Y_0]=reg_init(q,dq);
Cv=zeros(43,7);
for k=1:7
    Cv(:,k)=(Base_Slotine(q,dq,I(:,k),Y_q_dot,Y_0)-Fdq)*dq;
end
% Cv=[Cvs{1},Cvs{2},Cvs{3},Cvs{4},Cvs{5},Cvs{6},Cvs{7}];
% Cv1=(Base_Slotine(q,dq,I(:,1),Y_q_dot,Y_0)-Fdq)*dq;
% Cv2=(Base_Slotine(q,dq,I(:,2),Y_q_dot,Y_0)-Fdq)*dq;
% Cv3=(Base_Slotine(q,dq,I(:,3),Y_q_dot,Y_0)-Fdq)*dq;
% Cv4=(Base_Slotine(q,dq,I(:,4),Y_q_dot,Y_0)-Fdq)*dq;
% Cv5=(Base_Slotine(q,dq,I(:,5),Y_q_dot,Y_0)-Fdq)*dq;
% Cv6=(Base_Slotine(q,dq,I(:,6),Y_q_dot,Y_0)-Fdq)*dq;
% Cv7=(Base_Slotine(q,dq,I(:,7),Y_q_dot,Y_0)-Fdq)*dq;
% Cv=[Cv1,Cv2,Cv3,Cv4,Cv5,Cv6,Cv7];
end



function [Y_q_dot,Y_0]=reg_init(q,dq)
vec0=zeros(7,1);
Y_q_dot=Base_Regressor_Panda(q,dq,vec0)';
Y_0=Base_Regressor_Panda(q,vec0,vec0)';
end

function slotine=Base_Slotine(q,dq,v,Y_q_dot,Y_0)
vec0=zeros(7,1);
Y_qr_q_dot=Base_Regressor_Panda(q,dq+v,vec0)';
Y_qr_dot=Base_Regressor_Panda(q,v,vec0)';
slotine=0.5*(Y_qr_q_dot-Y_qr_dot-Y_q_dot+3*Y_0);


slotine=slotine';
end