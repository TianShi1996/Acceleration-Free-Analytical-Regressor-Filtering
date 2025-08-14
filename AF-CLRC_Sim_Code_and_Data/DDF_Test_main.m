clear
close all
clc
warning off;

Panda_run;

sd_ind=0:0.002:0.03;
DDF_alpha=10:5:150;len_lm=length(DDF_alpha);
ind=130/Ts:5:145/Ts;

for i=1:len_lm
    k=0;
    for SD=sd_ind
        % SD
        diff_alpha1=DDF_alpha(i);
        vari = SD^2;k=k+1;
        try
            sim_accf_1=sim("CLRC_acc_f1.mdl",150);
            data_accf{i,k}=[sim_accf_1.tout(ind),sim_accf_1.err_norm.Data(ind),sim_accf_1.q_err_norm.Data(ind),sim_accf_1.predict_err.Data(ind)];
            memory=whos("data_accf");
            fprintf("SD=%f, Time=%f s, Memory=%f mb\n",SD,sim_accf_1.SimulationMetadata.TimingInfo.ExecutionElapsedWallTime,memory.bytes/1024/1024);
        catch
            data_accf{i,k}="error";
            fprintf("Error\n");
        end
        
    end
end

save("sim_DDF_Test.mat","data_accf");


