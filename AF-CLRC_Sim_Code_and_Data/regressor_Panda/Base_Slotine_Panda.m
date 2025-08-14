function slotine=Base_Slotine_Panda(q,dq,v,dv)

% Y_qr_q_dot=Base_Regressor_Panda_43(q,dq+v,dv);
% Y_qr_dot=Base_Regressor_Panda_43(q,v,dv);
% Y_q_dot=Base_Regressor_Panda_43(q,dq,dv);
% Y_0=Base_Regressor_Panda_43(q,zeros(size(q)),dv);
% slotine=0.5*(Y_qr_q_dot-Y_qr_dot-Y_q_dot+3*Y_0);


Y_qr_q_dot=Regressor_Panda_full(q,dq+v,dv);
Y_qr_dot=Regressor_Panda_full(q,v,dv);
Y_q_dot=Regressor_Panda_full(q,dq,dv);
Y_0=Regressor_Panda_full(q,zeros(size(q)),dv);
slotine=0.5*(Y_qr_q_dot-Y_qr_dot-Y_q_dot+3*Y_0);


