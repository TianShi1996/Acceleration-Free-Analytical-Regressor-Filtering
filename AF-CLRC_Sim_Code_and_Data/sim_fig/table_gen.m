clear
close all
clc

load sim_sd1.mat
load sim_sd2.mat

sd_ind=0:0.002:0.03;
len=length(sd_ind);

qerr_acc=RMSE(data_acc(1:len),3);
qerr_accf_1=RMSE(data_accf_1(1:len),3);
qerr_accf_2=RMSE(data_accf_2(1:len),3);
qerr_reg=RMSE(data_reg(1:len),3);

perr_acc=RMSE(data_acc(1:len),4);
perr_accf_1=RMSE(data_accf_1(1:len),4);
perr_accf_2=RMSE(data_accf_2(1:len),4);
perr_reg=RMSE(data_reg(1:len),4);

max_e_acc=max(qerr_acc);min_e_acc=min(qerr_acc);avg_e_acc=mean(qerr_acc);
max_e_accf_1=max(qerr_accf_1);min_e_accf_1=min(qerr_accf_1);avg_e_accf_1=mean(qerr_accf_1);
max_e_accf_2=max(qerr_accf_2);min_e_accf_2=min(qerr_accf_2);avg_e_accf_2=mean(qerr_accf_2);
max_e_reg=max(qerr_reg);min_e_reg=min(qerr_reg);avg_e_reg=mean(qerr_reg);

max_pre_acc=max(perr_acc);min_pre_acc=min(perr_acc);avg_pre_acc=mean(perr_acc);
max_pre_accf_1=max(perr_accf_1);min_pre_accf_1=min(perr_accf_1);avg_pre_accf_1=mean(perr_accf_1);
max_pre_accf_2=max(perr_accf_2);min_pre_accf_2=min(perr_accf_2);avg_pre_accf_2=mean(perr_accf_2);
max_pre_reg=max(perr_reg);min_pre_reg=min(perr_reg);avg_pre_reg=mean(perr_reg);

[max_e_acc, max_pre_acc, min_e_acc, min_pre_acc, avg_e_acc, avg_pre_acc;
    max_e_accf_1,max_pre_accf_1, min_e_accf_1,min_pre_accf_1, avg_e_accf_1,avg_pre_accf_1;
    max_e_accf_2,max_pre_accf_2, min_e_accf_2,min_pre_accf_2, avg_e_accf_2,avg_pre_accf_2;
  max_e_reg,max_pre_reg, min_e_reg,min_pre_reg, avg_e_reg,avg_pre_reg]

