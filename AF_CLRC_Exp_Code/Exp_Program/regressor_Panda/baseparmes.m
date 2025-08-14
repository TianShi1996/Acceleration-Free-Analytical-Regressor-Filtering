function par=baseparmes()

% m=[panda_par(1);panda_par(2);panda_par(3);panda_par(4);panda_par(5);panda_par(6);panda_par(7)];
% l_1x=panda_par(8);l_1y=panda_par(9);l_1z=panda_par(10);
% l_2x=panda_par(11);l_2y=panda_par(12);l_2z=panda_par(13);
% l_3x=panda_par(14);l_3y=panda_par(15);l_3z=panda_par(16);
% l_4x=panda_par(17);l_4y=panda_par(18);l_4z=panda_par(19);
% l_5x=panda_par(20);l_5y=panda_par(21);l_5z=panda_par(22);
% l_6x=panda_par(23);l_6y=panda_par(24);l_6z=panda_par(25);
% l_7x=panda_par(26);l_7y=panda_par(27);l_7z=panda_par(28);
% l_x=[l_1x,l_2x,l_3x,l_4x,l_5x,l_6x,l_7x];l_y=[l_1y,l_2y,l_3y,l_4y,l_5y,l_6y,l_7y];l_z=[l_1z,l_2z,l_3z,l_4z,l_5z,l_6z,l_7z];
% L_1xx=panda_par(29);L_1xy=panda_par(30);L_1xz=panda_par(31);L_1yy=panda_par(32);L_1yz=panda_par(33);L_1zz=panda_par(34);
% L_2xx=panda_par(35);L_2xy=panda_par(36);L_2xz=panda_par(37);L_2yy=panda_par(38);L_2yz=panda_par(39);L_2zz=panda_par(40);
% L_3xx=panda_par(41);L_3xy=panda_par(42);L_3xz=panda_par(43);L_3yy=panda_par(44);L_3yz=panda_par(45);L_3zz=panda_par(46);
% L_4xx=panda_par(47);L_4xy=panda_par(48);L_4xz=panda_par(49);L_4yy=panda_par(50);L_4yz=panda_par(51);L_4zz=panda_par(52);
% L_5xx=panda_par(53);L_5xy=panda_par(54);L_5xz=panda_par(55);L_5yy=panda_par(56);L_5yz=panda_par(57);L_5zz=panda_par(58);
% L_6xx=panda_par(59);L_6xy=panda_par(60);L_6xz=panda_par(61);L_6yy=panda_par(62);L_6yz=panda_par(63);L_6zz=panda_par(64);
% L_7xx=panda_par(65);L_7xy=panda_par(66);L_7xz=panda_par(67);L_7yy=panda_par(68);L_7yz=panda_par(69);L_7zz=panda_par(70);
% L_xx=[L_1xx,L_2xx,L_3xx,L_4xx,L_5xx,L_6xx,L_7xx];L_xy=[L_1xy,L_2xy,L_3xy,L_4xy,L_5xy,L_6xy,L_7xy];
% L_xz=[L_1xz,L_2xz,L_3xz,L_4xz,L_5xz,L_6xz,L_7xz];
% L_yy=[L_1yy,L_2yy,L_3yy,L_4yy,L_5yy,L_6yy,L_7yy];L_yz=[L_1yz,L_2yz,L_3yz,L_4yz,L_5yz,L_6yz,L_7yz];
% L_zz=[L_1zz,L_2zz,L_3zz,L_4zz,L_5zz,L_6zz,L_7zz];
% fc_1=panda_par(71);fc_2=panda_par(72);fc_3=panda_par(73);fc_4=panda_par(74);fc_5=panda_par(75);fc_6=panda_par(76);fc_7=panda_par(77);
% fv_1=panda_par(78);fv_2=panda_par(79);fv_3=panda_par(80);fv_4=panda_par(81);fv_5=panda_par(82);fv_6=panda_par(83);fv_7=panda_par(83);
% fo_1 = panda_par(85);fo_2 = panda_par(86);fo_3 = panda_par(87);fo_4 = panda_par(88);fo_5 = panda_par(89);fo_6 = panda_par(90);fo_7 = panda_par(91);
% f_c=[fc_1,fc_2,fc_3,fc_4,fc_5,fc_6,fc_7];
% f_v=[fv_1,fv_2,fv_3,fv_4,fv_5,fv_6,fv_7];
% f_o=[fo_1,fo_2,fo_3,fo_4,fo_5,fo_6,fo_7];


m=[4.970684,0.646926,3.228604,3.587895,1.225946,1.666555,7.35522e-01];
L_xx=[7.0337e-01,7.9620e-03,3.7242e-02,2.5853e-02,3.5549e-02,1.9640e-03,1.2516e-02];
L_yy=[7.0661e-01,2.8110e-02,3.6155e-02,1.9552e-02,2.9474e-02,4.3540e-03,1.0027e-02];
L_zz=[9.1170e-03,2.5995e-02,1.0830e-02,2.8323e-02,8.6270e-03,5.4330e-03,4.8150e-03];
L_xy=[-1.3900e-04,-3.9250e-03,-4.7610e-03,7.7960e-03,-2.1170e-03,1.0900e-04,-4.2800e-04];
L_xz=[6.7720e-03,1.0254e-02,-1.1396e-02,-1.3320e-03,-4.0370e-03,-1.1580e-03,-1.1960e-03];
L_yz=[1.9169e-02,7.0400e-04,-1.2805e-02,8.6410e-03,2.2900e-04,3.4100e-04,-7.4100e-04];
c_x=[3.875e-03,-3.141e-03,2.7518e-02,-5.317e-02,-1.1953e-02,6.0149e-02,1.0517e-02];
c_y=[2.081e-03,-2.872e-02,3.9252e-02,1.04419e-01,4.1065e-02,-1.4117e-02,-4.252e-03];
c_z=[-0.175,3.495e-03,-6.6502e-02,2.7454e-02,-3.8437e-02,-1.0517e-02,6.1597e-02];
l_x=[c_x(1)*m(1),c_x(2)*m(2),c_x(3)*m(3),c_x(4)*m(4),c_x(5)*m(5),c_x(6)*m(6),c_x(7)*m(7)];
l_y=[c_y(1)*m(1),c_y(2)*m(2),c_y(3)*m(3),c_y(4)*m(4),c_y(5)*m(5),c_y(6)*m(6),c_y(7)*m(7)];
l_z=[c_z(1)*m(1),c_z(2)*m(2),c_z(3)*m(3),c_z(4)*m(4),c_z(5)*m(5),c_z(6)*m(6),c_z(7)*m(7)];
f_v=[0.0665,0.1987,0.0399,0.2257,0.1023,-0.0132,0.0638];
f_c=[0.245,0.1523,0.1827,0.3591,0.2669,0.1658,0.2109];
f_o=[-0.1073,-0.1566,-0.0686,-0.2522,0.0045,0.0910,-0.0127];

par=zeros(64,1);

par(1)=L_zz(1)+L_yy(2);
par(2)=f_v(1);
par(3)=f_c(1);
par(4)=f_o(1);
par(5)=L_xx(2)-L_yy(2)+L_yy(3)+79*l_z(3)/125+6241*m(3)/62500+426649*m(4)/4000000+426649*m(5)/4000000+426649*m(6)/4000000+426649*m(7)/4000000;
par(6)=L_xy(2);
par(7)=L_xz(2);
par(8)=L_yz(2);
par(9)=L_zz(2)+L_yy(3)+79*l_z(3)/125+6241*m(3)/62500+426649*m(4)/4000000+426649*m(5)/4000000+426649*m(6)/4000000+426649*m(7)/4000000;
par(10)=l_x(2);
par(11)=l_y(2)-l_z(3)-79*m(3)/250-79*m(4)/250-79*m(5)/250-79*m(6)/250-79*m(7)/250;
par(12)=f_v(2);
par(13)=f_c(2);
par(14)=f_o(2);
par(15)=L_xx(3)-L_yy(3)+L_yy(4)-1089*m(4)/160000;
par(16)=L_xy(3)+33*l_z(4)/400;
par(17)=L_xz(3);
par(18)=L_yz(3);
par(19)=L_zz(3)+L_yy(4)+1089*m(4)/160000+1089*m(5)/80000+1089*m(6)/80000+1089*m(7)/80000;
par(20)=l_x(3)+33*m(4)/400+33*m(5)/400+33*m(6)/400+33*m(7)/400;
par(21)=l_y(3)-l_z(4);
par(22)=f_v(3);
par(23)=f_c(3);
par(24)=f_o(3);
par(25)=L_xx(4)-L_yy(4)+L_yy(5)+96*l_z(5)/125+562599*m(5)/4000000+562599*m(6)/4000000+562599*m(7)/4000000;
par(26)=L_xy(4)+33*l_z(5)/400+99*m(5)/3125+99*m(6)/3125+99*m(7)/3125;
par(27)=L_xz(4);
par(28)=L_yz(4);
par(29)=L_zz(4)+L_yy(5)+96*l_z(5)/125+617049*m(5)/4000000+617049*m(6)/4000000+617049*m(7)/4000000;
par(30)=l_x(4)-33*m(5)/400-33*m(6)/400-33*m(7)/400;
par(31)=l_y(4)+l_z(5)+48*m(5)/125+48*m(6)/125+48*m(7)/125;
par(32)=f_v(4);
par(33)=f_c(4);
par(34)=f_o(4);
par(35)=L_xx(5)-L_yy(5)+L_yy(6)+121*m(7)/15625;
par(36)=L_xy(5);
par(37)=L_xz(5);
par(38)=L_yz(5);
par(39)=L_zz(5)+L_yy(6)+121*m(7)/15625;
par(40)=l_x(5);
par(41)=l_y(5)-l_z(6);
par(42)=f_v(5);
par(43)=f_c(5);
par(44)=f_o(5);
par(45)=L_xx(6)-L_yy(6)+L_yy(7)+107*l_z(7)/500+741*m(7)/200000;
par(46)=L_xy(6)+11*l_z(7)/125+1177*m(7)/125000;
par(47)=L_xz(6);
par(48)=L_yz(6);
par(49)=L_zz(6)+L_yy(7)+107*l_z(7)/500+19193*m(7)/1000000;
par(50)=l_x(6)+11*m(7)/125;
par(51)=l_y(6)-l_z(7)-107*m(7)/1000;
par(52)=f_v(6);
par(53)=f_c(6);
par(54)=f_o(6);
par(55)=L_xx(7)-L_yy(7);
par(56)=L_xy(7);
par(57)=L_xz(7);
par(58)=L_yz(7);
par(59)=L_zz(7);
par(60)=l_x(7);
par(61)=l_y(7);
par(62)=f_v(7);
par(63)=f_c(7);
par(64)=f_o(7);


% 
par([2:4,12:14,22:24,32:34,42:44,52:54,62:64])=[];
% 
% par=[par;f_v';f_c';f_o'];









