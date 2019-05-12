%% Test 1
% Equation:
% y'(t) = 5*y(t) - 3   in [ 0, 1 ]
%  y(0) = 0
% Discretization:
% h = 0.01
% Nh = 100

clear all
close all

FEFileID = fopen( 'solution_1.txt', 'r' );
u_n = fscanf( FEFileID, '%f' );
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

FEFileID = fopen( 'solution_2.txt', 'r' );
u_n = fscanf( FEFileID, '%f' );
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

% Read files
FEFileID = fopen( 'solution_3.txt', 'r' );
AdapFileID = fopen( 'solution_3_adap.txt', 'r' );
TimesAdapFileID = fopen( 'times_solution_3_adap.txt', 'r' );
RKFileID = fopen( 'solution_3_RK.txt', 'r' );

% Numerical and exact solutions
u_n_FE = fscanf( FEFileID, '%f' );
u_n_adap = fscanf( AdapFileID, '%f' );
u_n_RK = fscanf( RKFileID, '%f' );
u_ex = @(t) t - 1 + 3*exp(-(t+1));

% Time vectors
t_FE = linspace( -1, 5, length(u_n_FE) );
t_adap = fscanf ( TimesAdapFileID, '%f' );
t_RK = linspace( -1, 5, length(u_n_RK) );

% Plot solutions
plot( t_FE, u_ex(t_FE) )
hold on
plot( t_FE, u_n_FE )
plot( t_adap, u_n_adap )
plot( t_RK, u_n_RK )

legend( 'Exact', 'FE', 'Adaptive FE', 'RK' )
