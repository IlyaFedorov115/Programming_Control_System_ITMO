% Pid parameters

P = 6.68519117883399;
I = 3.41356175675233;
D = 1.64826423496531;
N = 4.79339804476038;

tf_p = tf(P, [1])
tf_i = tf(I, [1 0])
tf_D = tf(N, [1]) / (1 + tf(N, [1 0]))

W_Pid = tf_p + tf_i + tf_D
W_Pid.Numerator


system = ss(W_Pid)
canon_sys = canon(system, 'modal')

can
fprintf('Get form for filter')

tf_lp
filter_ss = ss(tf_lp)
canon_filter_ss = canon(filter_ss)