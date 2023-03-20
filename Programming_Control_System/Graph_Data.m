% Read the CSV file
% Plot graph like in QT


dir = '/home/ilya/Matlab_Folder/Programming_Control_System/win10/';

filename = 'process_log_10_03_2023_09_46_42.csv';
filename = 'process_log_13_03_2023_11_19_37.csv';

data = readmatrix(strcat(dir, filename));

% Extract the columns into separate arrays
colT = data(:, 1) / 1000;
col1 = data(:, 2);
col2 = data(:, 3);

% Define two arrays with constant values
const1 = ones(size(col1))*10;
const2 = ones(size(col2))*20;

% Plot the data
figure;
plot(colT, col1);
hold on;
plot(colT, col2);

grid on;
xlabel('Time');
ylabel('Value');
title('Multiple lines on one graph');
legend('Curr h', 'Goal state');