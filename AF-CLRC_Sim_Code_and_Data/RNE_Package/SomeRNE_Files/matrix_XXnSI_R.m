function XXnSI=matrix_XXnSI_R(q,Xn)
n=7;
q1=q(1);q2=q(2);q3=q(3);q4=q(4);q5=q(5);q6=q(6);q7=q(7);



% Xn1=Xn(1:6,:);
Xn1=Xn(7:12,:)';
Xn2=Xn(13:18,:)';
Xn3=Xn(19:24,:)';
Xn4=Xn(25:30,:)';
Xn5=Xn(31:36,:)';
Xn6=Xn(37:42,:)';
% Xn7=Xn(43:48,:)';






XXn_12=Xn1;
XXn_23=Xn2;
XXn_34=Xn3;
XXn_45=Xn4;
XXn_56=Xn5;
XXn_67=Xn6;
XXn_13=XXn_12*Xn2;
XXn_14=XXn_13*Xn3;
XXn_15=XXn_14*Xn4;
XXn_16=XXn_15*Xn5;
XXn_17=XXn_16*Xn6;
XXn_24=XXn_23*Xn3;
XXn_25=XXn_24*Xn4;
XXn_26=XXn_25*Xn5;
XXn_27=XXn_26*Xn6;
XXn_35=XXn_34*Xn4;
XXn_36=XXn_35*Xn5;
XXn_37=XXn_36*Xn6;
XXn_46=XXn_45*Xn5;
XXn_47=XXn_46*Xn6;
XXn_57=XXn_56*Xn6;

XXnSI=zeros(7,6*n);XXnSI([15,58,101,144,187,230,273])=1;


XXnSI(1,7:42)=[XXn_12(3,:),XXn_13(3,:),XXn_14(3,:),XXn_15(3,:),XXn_16(3,:),XXn_17(3,:)];
XXnSI(2,13:42)=[XXn_23(3,:),XXn_24(3,:),XXn_25(3,:),XXn_26(3,:),XXn_27(3,:)];
XXnSI(3,19:42)=[XXn_34(3,:),XXn_35(3,:),XXn_36(3,:),XXn_37(3,:)];
XXnSI(4,25:42)=[XXn_45(3,:),XXn_46(3,:),XXn_47(3,:)];
XXnSI(5,31:42)=[XXn_56(3,:),XXn_57(3,:)];
XXnSI(6,37:42)=XXn_67(3,:);


