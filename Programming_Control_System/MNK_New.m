
% plot V and a graph
% find parameters

dir = '/home/ilya/Matlab_Folder/Programming_Control_System/win10/';
filename = 'process_log_13_03_2023_11_19_37.csv';
data = readmatrix(strcat(dir, filename));

% Extract the columns into separate arrays
colT = data(:, 1) / 1000;
colY = data(:, 2);
colU = data(:, 3);

V = diff(colY)./mean(diff(colT));%diff(colT);            % velocity
dV = diff(V)./mean(diff(colT));%diff(colT(1:end-1));   % dV/dt

Q = [colU(1:end-2) V(1:end-1) colY(1:end-2)];

Qt = pinv(Q);

% Plot Velocity and dV/dt

figure;
subplot(2,1,1);
plot(colT(1:end-1), V);
title('V');
subplot(2,1,2);
plot(colT(1:end-2), dV);
title('A');
%hold on;
grid on;



boolExecute = 0;

% Filting data before diff

if boolExecute == 1
    freq = 20;
    w = 2 * pi * freq;
    alpha = 1 / w;
    tf_obj = tf([1], [alpha 1]);
    
    figure;
    bode(tf_obj);
    yfilt = lsim(tf_obj, colY);
    ufilt = lsim(tf_obj, colU);
    figure;
    subplot(2,1,1);
    plot(colT(1:end), yfilt);
    title('Y');
    subplot(2,1,2);
    plot(colT(1:end), ufilt);
    title('U');
end
%вход не фильтровать он сами задаем

%tf_obj = tf(num, den);
%y = lsim(tf_obj, u);
%y = a * y;



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
