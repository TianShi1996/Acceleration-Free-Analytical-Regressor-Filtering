function Cv=Coriolis_Reg(q,dq,G)
vec0=zeros(7,1);I=eye(7);

% Y_q_dot=Base_Regressor_Panda(q,dq,vec0);

% GY=G-Base_Regressor_Panda_43(q,dq,vec0);

GY=G-Regressor_Panda_full(q,dq,vec0);

% Cv=zeros(43,7);
% for k=1:7
%     Cv(:,k)=(Base_Slotine(q,dq,I(:,k))+G-Y_q_dot)/2*dq;
% end
Cv=[(Base_Slotine(q,dq,I(:,1))+GY)*dq,(Base_Slotine(q,dq,I(:,2))+GY)*dq,(Base_Slotine(q,dq,I(:,3))+GY)*dq,(Base_Slotine(q,dq,I(:,4))+GY)*dq,...
    (Base_Slotine(q,dq,I(:,5))+GY)*dq,(Base_Slotine(q,dq,I(:,6))+GY)*dq,(Base_Slotine(q,dq,I(:,7))+GY)*dq]/2;


end


function slotine=Base_Slotine(q,dq,v)
vec0=zeros(7,1);
% Y_qr_q_dot=Base_Regressor_Panda_43(q,dq+v,vec0);
% Y_qr_dot=Base_Regressor_Panda_43(q,v,vec0);


Y_qr_q_dot=Regressor_Panda_full(q,dq+v,vec0);
Y_qr_dot=Regressor_Panda_full(q,v,vec0);
slotine=Y_qr_q_dot-Y_qr_dot;
end