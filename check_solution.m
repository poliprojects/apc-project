%% Plot exact and computed solution

clear all
close all

% Select the test number:
% Test 1:
% y'(t) = 5*y(t) - 3   in [ 0, 1 ]
%  y(0) = 0
%
% Test 2:
% y'(t) = -y(t)   in [ 0, 30 ]
%  y(0) = 1
%
% Test 3:
% y'(t) = t - y(t)   in [ -1, 5 ]
% y(-1) = 1
%
Test = 1;

% Read files
FEFileID = fopen( ['solution_',num2str(Test),'_FE.txt'], 'r' );
AdapFileID = fopen( ['solution_',num2str(Test),'_adapFE.txt'], 'r' );
TimesAdapFileID = fopen( ['times_solution_',num2str(Test),'_adapFE.txt'], 'r' );
RKFileID = fopen( ['solution_',num2str(Test),'_RK.txt'], 'r' );

% Numerical and exact solutions
u_n_FE = fscanf( FEFileID, '%f' );
u_n_adap = fscanf( AdapFileID, '%f' );
u_n_RK = fscanf( RKFileID, '%f' );
if( Test == 1 )
    u_ex = @(t) -3/5 * exp(5*t) + 3/5;
elseif( Test == 2 )
    u_ex = @(t) exp(-t);
elseif( Test == 3 )
    u_ex = @(t) t - 1 + 3*exp(-(t+1));
end

% Time vectors
if( Test == 1 )
    t_in = 0;
    t_fin = 1;
elseif( Test == 2 )
    t_in = 0;
    t_fin = 30;
elseif( Test == 3 )
    t_in = -1;
    t_fin = 5;
end
t_FE = linspace( t_in, t_fin, length(u_n_FE) );
t_RK = linspace( t_in, t_fin, length(u_n_RK) );
t_adap = fscanf ( TimesAdapFileID, '%f' ); % with adaptive methods time is read from file

% Plot solutions
plot( t_FE, u_ex(t_FE) )
hold on
plot( t_FE, u_n_FE )
plot( t_adap, u_n_adap )
plot( t_RK, u_n_RK )

legend( 'Exact', 'FE', 'Adaptive FE', 'RK' )
