clear all
close all


%% Test 1
% Equation:
% y'(t) = 5*y(t) - 3   in [ 0, 1 ]
%  y(0) = 0
% Discretization:
% h = 0.001
% Nh = 1000

fileID = fopen( 'solution_1.txt', 'r' );
u_n = fscanf( fileID, '%f' );
u_ex = @(t) -3/5 * exp(5*t) + 3/5;
t = linspace( 0, 1, length(u_n) );
plot( t, u_n )
hold on
plot( t, u_ex(t) )


%% Test 2
% Equation:
% y'(t) = 5cos(2y(t))   in [ 0, 10 ]
%  y(0) = 0
% Discretization:
% h = 0.001
% Nh = 1000

fileID = fopen( 'solution_2.txt', 'r' );
u_n = fscanf( fileID, '%f' );
u_ex = @(t) 0.5*asin((exp(20.*t)-1)./(exp(20.*t)+1));
t = linspace( 0, 10, length(u_n) );
plot( t, u_n )
hold on
plot( t, u_ex(t) )