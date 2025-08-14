clear
close all
clc
warning off;

Panda_run;
k=0;
sd_ind=0:0.002:0.03;
% sd_ind=0.005;


% model={'CLRC_acc','CLRC_acc_f','CLRC_filter_reg','CLRC_high_gain'};
% tic;data_acc=[data_acc,CLRC_parsim(model{1},sd_ind)];toc
% tic;data_accf=[data_accf,CLRC_parsim(model{2},sd_ind)];toc
% tic;data_reg=[data_reg,CLRC_parsim(model{3},sd_ind)];toc
% % data_hg=CLRC_parsim(model{4},sd_ind);
% data_hg=[];
% % toc
% save("sim_sd.mat","data_reg","data_accf","data_acc","data_hg");


% SD=sd_ind;
for SD=sd_ind
    SD
    vari = SD^2;k=k+1;
    tic;sim_accf_1=sim("CLRC_acc_f1.mdl",150);toc
    data_accf_1{k}=[sim_accf_1.tout,sim_accf_1.err_norm.Data,sim_accf_1.q_err_norm.Data,reshape(sim_accf_1.q.Data,7,length(sim_accf_1.tout))',sim_accf_1.predict_err.Data];
    tic;sim_accf_2=sim("CLRC_acc_f2.mdl",150);toc
    data_accf_2{k}=[sim_accf_2.tout,sim_accf_2.err_norm.Data,sim_accf_2.q_err_norm.Data,reshape(sim_accf_2.q.Data,7,length(sim_accf_2.tout))',sim_accf_2.predict_err.Data];
    tic;sim_reg=sim("CLRC_filter_reg.mdl",150);toc
    data_reg{k}=[sim_reg.tout,sim_reg.err_norm.Data,sim_reg.q_err_norm.Data,reshape(sim_reg.q.Data,7,length(sim_reg.tout))',sim_reg.predict_err.Data];
end

save("sim_sd.mat","data_accf_1","data_accf_2","data_reg");
