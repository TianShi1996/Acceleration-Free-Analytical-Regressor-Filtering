function slotine=Base_Slotine_Panda(q,dq,v,dv)

Y_qr_q_dot=Base_Regressor_Panda(q,dq+v,dv)';
Y_qr_dot=Base_Regressor_Panda(q,v,dv)';
Y_q_dot=Base_Regressor_Panda(q,dq,dv)';
Y_0=Base_Regressor_Panda(q,zeros(size(q)),dv)';
slotine=0.5*(Y_qr_q_dot-Y_qr_dot-Y_q_dot+3*Y_0);

% slotine(1,2)=Y_q_dot(1,2);
% slotine(1,3)=Y_q_dot(1,3);
% slotine(1,4)=Y_q_dot(1,4);
% slotine(2,12)=Y_q_dot(2,12);
% slotine(2,13)=Y_q_dot(2,13);
% slotine(2,14)=Y_q_dot(2,14);
% slotine(3,22)=Y_q_dot(3,22);
% slotine(3,23)=Y_q_dot(3,23);
% slotine(3,24)=Y_q_dot(3,24);
% slotine(4,32)=Y_q_dot(4,32);
% slotine(4,33)=Y_q_dot(4,33);
% slotine(4,34)=Y_q_dot(4,34);
% slotine(5,42)=Y_q_dot(5,42);
% slotine(5,43)=Y_q_dot(5,43);
% slotine(5,44)=Y_q_dot(5,44);
% slotine(6,52)=Y_q_dot(6,52);
% slotine(6,53)=Y_q_dot(6,53);
% slotine(6,54)=Y_q_dot(6,54);
% slotine(7,62)=Y_q_dot(7,62);
% slotine(7,63)=Y_q_dot(7,63);
% slotine(7,64)=Y_q_dot(7,64);
slotine=slotine';

