function err=RMSE(data,p)
Ts=0.0002;
ind=130/Ts:145/Ts;
len=length(data);
if p==3
    for k=1:len
        err(k)=sqrt(sum(data{k}(ind,p).^2)*Ts/15);
    end
else
    for k=1:len
        err(k)=sqrt(sum(data{k}(ind,p).^2)*Ts/15);
        % err(k)=max(data{k}(ind,p));
    end
end





