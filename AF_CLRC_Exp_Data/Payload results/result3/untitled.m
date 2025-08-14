clear
close all
clc

load('AF/err_norm.mat');load('AF/predict_err.mat');
figure(1);plot(err_norm(1,:),err_norm(2,:),'r');hold on;figure(2);plot(predict_err(1,:),predict_err(2,:),'r');hold on;
load('DDF/err_norm.mat');load('DDF/predict_err.mat');
figure(1);plot(err_norm(1,:),err_norm(2,:),'b');hold on;figure(2);plot(predict_err(1,:),predict_err(2,:),'b');hold on;

