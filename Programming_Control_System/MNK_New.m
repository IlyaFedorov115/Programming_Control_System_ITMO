
% plot V and a graph
% find parameters

% filt another variant + plot
bool_use_another_var = 0;

bool_plot_V_dv_before_filt = 0;



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

if bool_plot_V_dv_before_filt == 1
    figure;
    subplot(2,1,1);
    plot(colT(1:end-1), V);
    title('V');
    subplot(2,1,2);
    plot(colT(1:end-2), dV);
    title('A');
    %hold on;
    grid on;
end



% Filting data before diff
freq = 1000 / mean(diff(data(:, 1))); % Герц
freq = 5;
w_freq = 2 * pi * freq;
alpha_filt = 1/w_freq;
alpha_filt = 1 / freq;
tf_lp = tf(1, [alpha_filt 1]);
t_for_filt = 0:alpha_filt:((size(colY)-1)*alpha_filt);
Y_filt = lsim(tf_lp, colY', t_for_filt); 
%Y_filt = filter(1, [alpha_filt 1], colY);

figure;
plot(colY);
hold on
plot(Y_filt);
grid on;
title('Filtering Y');
legend('Output', 'Filter out');


% filt by windowsize
%
if bool_use_another_var == 1
    windowSize = 5;
    b_tmp = (1/windowSize)*ones(1, windowSize);
    a_tmp = 1;
    Y_filt = filter(b_tmp,a_tmp,colY);
    figure;
    plot(colY);
    hold on
    plot(Y_filt2);
    grid on;
    legend('Output', 'Filter out');
end


% Filt V and dV/dt 
%
% Filt and recalc V and dV/dt
V = diff(Y_filt)./mean(diff(colT));%diff(colT);            % velocity
%figure;
%plot(colT(1:end-1), V);
%title('V after filt Y');


% Filt V
alpha_filt = 0.02;
t_for_filt = 0:alpha_filt:((size(V)-1)*alpha_filt);
V_filt = lsim(tf_lp, V', t_for_filt); 
V = V_filt;
dV = diff(V)./mean(diff(colT));%diff(colT(1:end-1));   % dV/dt

t_for_filt = 0:alpha_filt:((size(dV)-1)*alpha_filt);
dV_filt = lsim(tf_lp, dV', t_for_filt);

figure;
subplot(3,1,1);
plot(colT(1:end-1), V);
title('V after filt');
grid on;
subplot(3,1,2);
plot(colT(1:end-2), dV);
title('dV/dt after V filt');
grid on;

subplot(3,1,3);
plot(colT(1:end-2), dV_filt);
title('dV/dt after filt');
grid on;



%
% Calc coefficients for W(s)
%
alpha_filt = 0.025;



Q = [colU(1:end-2) V_filt(1:end-1) Y_filt(1:end-2)];
Qt = pinv(Q);
params = Qt * dV_filt;

b = params(1)
a1 = -params(2)
a0 = -params(3)

b = 0.9827;
a1 = 2.9780;
a0 = 0.5452;

W_model = tf(b, [1 a1 a0]);
t_for_filt = 0:alpha_filt:((size(colU)-1)*alpha_filt);
Out_Model = lsim(W_model, colU, t_for_filt);
figure;
plot(t_for_filt, Out_Model);
hold on;
plot(colT, colY);
grid on;
legend('Simulation', 'Qt');
%X = [dV_filt, V_filt(1:end-1), Y_filt(1:end-2)];
%params = inv(X' * X) * X' * Y_filt(1:end-2)



%
% Using lowpass
%
cut_len = 20;
freq = 100;
w_freq = 2 * pi * freq;
w_freq = 3;
Y_filt = lowpass(colY, w_freq, freq);
Y_filt = Y_filt(1:end-cut_len);
%figure;
%plot(Y_filt);
V = diff(Y_filt)./mean(diff(colT));%diff(colT);            % velocity
V_filt = lowpass(V, w_freq, freq);

V_filt = V_filt(1:end);
dV = diff(V_filt)./mean(diff(colT));%diff(colT(1:end-1));   % dV/dt
dV_filt = lowpass(dV, w_freq, freq);
dV_filt = dV_filt(1:end);


figure;
subplot(4,1,1);
plot(colT(1:end-1-cut_len), V);
title('V after filt lowpass');
grid on;
subplot(4,1,2);
plot(colT(1:end-2-cut_len), dV);
title('dV/dt after V filt lowpass');
grid on;

subplot(4,1,3);
plot(colT(1:end-2-cut_len), dV_filt);
title('dV/dt after filt lowpass');
grid on;

subplot(4,1,4);
plot(colT(1:end-cut_len), Y_filt);
hold on;
plot(colT, colY);
title('Y filt lowpass');
legend('Y_filt', 'Y');
grid on;


Q = [colU(1:end-2-cut_len) V_filt(1:end-1) Y_filt(1:end-2)];
Qt = pinv(Q);
params = Qt * dV_filt;

b = params(1)
a1 = -params(2)
a0 = -params(3)
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
