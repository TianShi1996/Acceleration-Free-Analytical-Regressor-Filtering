function tau=norm_tau(u)
[~,len]=size(u);
tau=zeros(2,len);
tau(1,:)=u(1,:);
for k=1:len
    tau(2,k)=norm(u(2:end,k));
end