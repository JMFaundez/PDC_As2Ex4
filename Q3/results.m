close all
clear all
clc

C1 = 0.00204018;
C1_std =  0.00009792;

C3 = dlmread('3.results');
C4 = dlmread('4.results');
C5 = dlmread('5.results');

C4 = C4(1:end-1,:);
C5 = C5(1:end-1,:);
% question 3
h1 = figure(1);
set(h1, 'Position', [0 0 800 400]);
set(h1, 'Color', 'w');
errorbar(C3(:,1),C1*ones(size(C3(:,1)))*10^3,C1_std*ones(size(C3(:,1)))*10^3)
hold on
errorbar(C3(:,1),C3(:,2)*10^3,C3(:,3)*10^3)
xlabel('Threads')
ylabel('Execution time [ms]')
legend('Serial','Parallel (critical)')
ylim([-1,150])
grid on
export_fig Q3.eps


h2 = figure(2);
set(h2, 'Position', [0 0 800 400]);
set(h2, 'Color', 'w');
errorbar(C3(:,1),C1*ones(size(C3(:,1)))*10^3,C1_std*ones(size(C3(:,1)))*10^3)
hold on
errorbar(C4(:,1),C4(:,2)*10^3,C4(:,3)*10^3)
errorbar(C5(:,1),C5(:,2)*10^3,C5(:,3)*10^3)
xlabel('Threads')
ylabel('Execution time [ms]')
legend('Serial','Parallel (no padding)','Parallel (padding)')
grid on
export_fig Q45.eps
