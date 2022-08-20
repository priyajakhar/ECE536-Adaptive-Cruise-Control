%initalize the simulation
clear all
clc
Ke = 0.128; %N.m/A
Kb = 0.16; %V.sec/rad
J = 5e-2; %kg.m^2
B = 5.24e-5; %N.M.s
Ra = 0.12; %Ohm
La = 0.69e-3; %H
V = 56; %V
M = 168; %kg
rw = 0.2201; %m
G = 6; 
A = 1.5; %m^2
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
vw = 0;
Drag = rw/Juv/G/2*rhouv*(rw/G)^2;
vn=4; %nominal velocity
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
    0 -1/Juv rw/Juv/G;
    1/La 0 0];
C=[1 0 0;
    0 1 0;
    0 0 1];
