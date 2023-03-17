
dir = '/home/ilya/Matlab_Folder/Programming_Control_System/win10/';
filename = 'process_log_13_03_2023_11_19_37.csv';
data = readmatrix(strcat(dir, filename));

% Extract the columns into separate arrays
colT = data(:, 1) / 1000;
colY = data(:, 2);
colU = data(:, 3);

V = diff(colY)./mean(diff(colT));%diff(colT);            % velocity
Z = diff(V)./mean(diff(colT));%diff(colT(1:end-1));   % dV/dt

Q = [colU(1:end-2) V(1:end-1) colY(1:end-2)];

Qt = pinv(Q);

figure;
subplot(2,1,1);
plot(colT(1:end-1), V);
title('V');
subplot(2,1,2);
plot(colT(1:end-2), Z);
title('A');

%%
% |d| 



%hold on;

grid on;
%xlabel('Time');
%ylabel('Value');
%title('Multiple lines on one graph');
%legend('V', 'A');


% % Calculate the pseudo-inverse of Q
% Q1 = pinv(Q);
% 
% % Solve for the unknown parameters
% params = Q1 * z';
% 
% % Extract the individual parameters
% b = params(1);
% a1 = -params(2);
% a = params(3);