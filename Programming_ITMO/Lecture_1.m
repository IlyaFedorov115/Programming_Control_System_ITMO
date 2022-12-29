num = [1 4 4 2];
den = [1 4 4 1];

Gp = tf(num, den);

% observable form
GpssObs = canon(Gp,'companion');
GpssObsA = GpssObs.A;
GpssObsB = GpssObs.B;
GpssObsC = GpssObs.C;
GpssObsD = GpssObs.D;

% controll form 
GpssConA = GpssObsA.';
GpssConB = GpssObsC.';
GpssConC = GpssObsB.';
GpssConD = GpssObsD;

% dicrete controll form
GpssConA1 = expm(GpssConA*dt1);
GpssConA2 = expm(GpssConA*dt2);
GpssConA3 = expm(GpssConA*dt3);

GpssConB1 = inv(GpssConA) * (GpssConA1 - eye(size(GpssConA))) * GpssConB;
GpssConB2 = inv(GpssConA) * (GpssConA2 - eye(size(GpssConA))) * GpssConB;
GpssConB3 = inv(GpssConA) * (GpssConA3 - eye(size(GpssConA))) * GpssConB;

