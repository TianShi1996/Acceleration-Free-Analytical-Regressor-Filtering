function qerr=RMSE(data)
Ts=0.001;
% ind=[120/Ts:145/Ts];
% len=length(data);
% for k=1:len
%     qerr(k)=sqrt(sum(data{k}(ind,3).^2)*Ts/25);
% end

sqrt(sum(data.^2)*Ts/25)





