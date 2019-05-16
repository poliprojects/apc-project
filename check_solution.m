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
Test = 3;

methods = [ "FE", "adapFE", "RK" ];

% Read computed solution and time instants from file
for i = 1 : length( methods )
    method = methods(i);
    FileID = fopen( ['solution_',num2str(Test),'_',char(method),'.txt'], 'r' );
    buff = fscanf( FileID, '%s', 1 ); % Solution: 
    un{i} = fscanf( FileID, '%f' );
    buff = fscanf( FileID, '%s', 2 ); % Time instants:
    tn{i} = fscanf( FileID, '%f' );
end

% Exact solution
if( Test == 1 )
    u_ex = @(t) -3/5 * exp(5*t) + 3/5;
elseif( Test == 2 )
    u_ex = @(t) exp(-t);
elseif( Test == 3 )
    u_ex = @(t) t - 1 + 3*exp(-(t+1));
end

% Plot
figure
hold on
plot( tn{1}, u_ex(tn{1}) )
for i = 1 : length( methods )
    plot( tn{i}, un{i} )
end
legend( 'Exact', char(methods(1)), char(methods(2)), char(methods(3)) )

