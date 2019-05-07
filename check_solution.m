%% Test 1
% Equation:
% y'(t) = 5*y(t) - 3   in [ 0, 1 ]
%  y(0) = 0
% Discretization:
% h = 0.01
% Nh = 100

clear all
close all

fileID = fopen( 'solution_1.txt', 'r' );
u_n = fscanf( fileID, '%f' );
u_ex = @(t) -3/5 * exp(5*t) + 3/5;
t = linspace( 0, 1, length(u_n) );
plot( t, u_n )
hold on
plot( t, u_ex(t) )
legend( 'Computed', 'Exact' )

%% Test 2
% Equation:
% y'(t) = -y(t)   in [ 0, 30 ]
%  y(0) = 1
% Discretization:
% h = ?     
% Nh = ?
%
% NB:  if h<2     ==>   u->0 as t->inf
%      otherwise  ==>   u diverges

clear all
close all

fileID = fopen( 'solution_2.txt', 'r' );
u_n = fscanf( fileID, '%f' );
u_ex = @(t) exp(-t);
t = linspace( 0, 30, length(u_n) );
plot( t, u_n )
hold on
plot( t, u_ex(t) )
legend( 'Computed', 'Exact' )

%% Test 3
% Equation:
% y'(t) = t - y(t)   in [ -1, 5 ]
% y(-1) = 1
% Discretization:
% h = ?
% Nh = ?

clear all
close all

fileID = fopen( 'solution_3.txt', 'r' );
u_n = fscanf( fileID, '%f' );
u_ex = @(t) t - 1 + 3*exp(-(t+1));
t = linspace( -1, 5, length(u_n) );
plot( t, u_n )
hold on
plot( t, u_ex(t) )
legend( 'Computed', 'Exact' )
