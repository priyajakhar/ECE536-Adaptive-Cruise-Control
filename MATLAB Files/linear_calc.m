clear all
clc
V = 2.22; %V NOMINAL VOLTAGE
Ke = 0.3174; %N.m/A
Kb = 0.4684; %V.sec/rad
J = 5e-2; %kg.m^2
B = 5.24e-5; %N.M.s
Ra = 7.5; %Ohm
La = 0.5e-3; %H

M = 0.3; %kg
rw = 0.07005/2; %m, radius of the wheel
G = 120;  %Gear ratio
A = 1e-3; %m^2, front area of the car
rho = 1.18; %kg/m^3
Cd = 0.3;
mu = 0.01;
rhouv = rho*Cd*A;
alpha = pi/20;
Ff2 = 0;
Tb = 0;
FD = 0;
g = 9.8; %m/s^2
Juv = J+M*(rw/G)^2;
Ftotal = rw/Juv/G*(M*g*sin(alpha)+M*g*mu*cos(alpha)+FD);
vw = 0; %wind velocity
Drag = rw/Juv/G/2*rhouv*(rw/G)^2;

vn=0.3; %NOMINAL VELOCITY, m/s

%calculate the parameters of A matrix
x22=-B/Juv-rhouv*rw^(2)/Juv/G^(2)*(vn+vw);
x23=Ke/Juv;
x32=-Kb/La;
x33=-Ra/La;

syms h;
A=[0 1 0 ;
    0 x22 x23;
    0 x32 x33]; %real A matrix
I=[1 0 0 ; 0 1 0 ; 0 0 1];
A=A-I*h;
double(solve(det(A)==0,h)); %calculate the eigenvalues

A=[0 1 0 ;
    0 x22 x23;
    0 x32 x33]; %again real A matrix
B=[ 0 0 0;
    0 0 0;
    1/La 0 0];
C=[0 0 0;
    0 1 0;
    0 0 0];
D=0*B;
[b,a]=ss2tf(A,B,C,D,1);
sys=tf(b(2,:),a) %system transfer function G(s)
%step(sys)
rlocus(sys)
%sys1=feedback(sys,1)
pidtool(sys,'PID')
C=pid(2.8446,7.8712,0.02208); %pid controller constants obtained from pidtool
T=feedback(C*sys,1); %the system with PID controller and unity feedback
step(T)

