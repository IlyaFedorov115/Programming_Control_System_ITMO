A = [0 1 0; -0.25 0 0; 0 0 -0.5];

B = [0; 0; 0];

C = [1 0 1];

dt1 = 0.2;
dt2 = 0.033;
dt3 = 0.01;

% part for left 

A1 = expm(A*dt1);
A2 = expm(A*dt2);
A3 = expm(A*dt3);

B1 = inv(A) * (A1 - eye(size(A))) * B;
B2 = inv(A) * (A2 - eye(size(A))) * B;
B3 = inv(A) * (A3 - eye(size(A))) * B;

% part for right



