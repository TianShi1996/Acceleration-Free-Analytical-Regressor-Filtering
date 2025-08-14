function sim_data=CLRC_parsim(model,sd_ind)
in=repmat(Simulink.SimulationInput,[1 length(sd_ind)]); %自动并行运行
for i = 1:1:length(sd_ind)
    in(i) = Simulink.SimulationInput(model);  %模型名称
    in(i) = in(i).setVariable('SD',sd_ind(i));  %运行变量名称
    in(i) = in(i).setVariable('vari',sd_ind(i)^2); 
end
par_sim = parsim(in, 'ShowProgress', 'off','ShowSimulationManager','off','TransferBaseWorkspaceVariables','on');

for k=1:length(sd_ind)
    % par_sim(k).tout=0:0.0002:100;
    sim_data{k}=[par_sim(k).tout,par_sim(k).err_norm.Data,par_sim(k).q_err_norm.Data,par_sim(k).predict_err.Data];
end

