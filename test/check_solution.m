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
% Test 4:
% y1'(t) = -3*y1(t) -   y2(t) + sin(t)
% y2'(t) =    y1(t) - 5*y2(t) - 2		 in [0,10]
% y(0) = 1 1
%
% Test 5:
% y'(t) = -16.0*y(t)   in [ 0, 1 ]
%  y(0) = 1
%
% Test 6:
% y'(t) = 2^( -x/4 + 6 + 10*t )   in [ 0, 100 ]
%  y(0) = 1
%
% Test 7:
% y'(t) = atan( 5 * ( 1 - t ) ) * y   in [ 0, 3 ]
%  y(0) = 26^0.1
%
% Test 8:
% y'(t) = TODO   in [ 0, 3 ]
%  y(0) = 4 3 2 1


Test = 8;

available_methods = ...
    [ "FE","RK4","Heun","IserNor", ...                 % predefined RK
      "adapFE","adapRK4","adapHeun","adapIserNor", ... % predefined adapRK
      "adapRK","RK" ];                          % user defined in main.cpp

% Build the vector of methods that have been actually used
k = 1;
for i = 1 : length( available_methods )
    ID = fopen( ['../solution_',num2str(Test),'_', ...
            char(available_methods(i)),'.txt']);
    if( ID ~= -1 ) % if the corresponding file exists
        methods(k) = available_methods(i);
        k = k + 1;
    end
end

% Set colors for plot
colors = [ [      0    0.4470    0.7410 ]
           [ 0.8500    0.3250    0.0980 ];
           [ 0.9290    0.6940    0.1250 ];
           [ 0.4940    0.1840    0.5560 ]; 
           [ 0.4660    0.6740    0.1880 ];
           [ 0.3010    0.7450    0.9330 ];
           [ 0.6350    0.0780    0.1840 ];
           [      0         0         1 ];
           [      0         1         0 ];
           [      1         0         1 ]; ];

% Read computed solution and time instants from file
for i = 1 : length( methods )
    method = methods(i);
    FileID = fopen( ['../solution_',num2str(Test),'_',char(method), ...
        '.txt'], 'r' );
    buff = fscanf( FileID, '%s', 1 ); % Solution: 
    [ un_to_be_formatted, un_count ] = fscanf( FileID, '%f' );
    buff = fscanf( FileID, '%s', 2 ); % Time instants:
    [ tn{i}, tn_count ] = fscanf( FileID, '%f' );
    n = un_count / tn_count; % Dimension of the system
    for j = 1 : n
        un{i}(:,j) = un_to_be_formatted( j : n : end-n+j );
    end
    clear un_to_be_formatted    
end
    
% Exact solution
t = linspace( tn{1}(1), tn{1}(end) );
if( Test == 1 )
    u_ex = @(t) -3/5 * exp(5*t) + 3/5;
    u = u_ex( t );
elseif( Test == 2 )
    u_ex = @(t) exp(-t);
    u = u_ex( t );
elseif( Test == 3 )
    u_ex = @(t) t - 1 + 3*exp(-(t+1)); 
    u = u_ex( t );
elseif( Test == 4 )
    u_ex = @(t) deal( (2223*exp(-4*t))/2312 - (15*t.*exp(-4*t))/34 - ...
        (7514^(1/2)*cos(t + atan(83/25)))/289 + 1/8, ...
                       (3243*exp(-4*t))/2312 - cos(t + atan(15/8))/17 - ...
                       (15*t.*exp(-4*t))/34 - 3/8 );
    [ u(1,:), u(2,:) ] = u_ex( t );
elseif( Test == 5 )
    u_ex = @(t) exp(-(84*t)/5);
    u = u_ex( t );
elseif( Test == 6 )
    u_ex = @(t) (4*(log((20*2^(1/4) - 32)/(5*log(2)) + (32*2.^(10*t))/(...
        5*log(2))) - 2*log(2) + log(log(2))))/log(2);
    u = u_ex( t );
elseif( Test == 7 )
    u_ex = @(t) (3119084307157359*exp(log((5.*t - 5).^2 + 1)/10 - atan(...
        5*t - 5).*(t - 1))*exp(atan(5) - log(26)/10))/2251799813685248;
    u = u_ex( t );
elseif( Test == 8 )
    u_ex = @(t) 0.*t;
    u = u_ex( t );
end

% Plot
figure(1)
hold on
h = plot( t, u, 'color', [0,0,0] );
if( Test == 8 )
    xlim( [ 0, 16000 ] )
end
% set(get(get(h(1:0),'Annotation'),'LegendInformation'), ...
%     'IconDisplayStyle','off'); % To set legend properly
for i = 1 : length( methods )
    h = plot( tn{i}, un{i}, 'color', colors(i,:) );
    % Set legend properly
    if( length(h) > 1 )
        for i = 2 : n
            set(get(get(h(i),'Annotation'),'LegendInformation'), ...
                'IconDisplayStyle','off');
        end
    end
end

% Legend
Legend = cell(length(methods),1);
Legend{1} = 'Exact';
for k = 2 : length(methods)+1
    Legend{k} = char( methods(k-1) );
end
legend( Legend, 'location', 'bestoutside' )

% Title and labels
title( 'ODE solution' )
xlabel( 't' )
ylabel( 'y(t)' )

% Close all open files
fclose('all');

% xlim( [ 0, 0.05 ] )
% ylim( [ -0.2, 0 ] )


%% Compute and compare the relative Mean Square Error
MSE = zeros( 1, length( methods ) );

for i = 1 : length( methods )
    if n == 2
        [u_ex_eval_1,u_ex_eval_2] = u_ex( tn{i} );
        norm_ex = sqrt( u_ex_eval_1.^2 + u_ex_eval_2.^2 );
        err_1 = un{i}(:,1) - u_ex_eval_1;
        err_2 = un{i}(:,2) - u_ex_eval_2;
        err_norm = sqrt( err_1.^2 + err_2.^2 );
        errors = err_norm ./ norm_ex;
    elseif n == 1
        u_ex_eval = u_ex( tn{i} );
        errors = ( un{i} - u_ex_eval ) ./ u_ex_eval;
    end
    
    % Replace NaNs produced by division by u_ex=0 with absolute error
    errors( isnan( errors ) ) = un{i}( isnan( errors ) );
    
    % Compute MSE
    MSE(i) = mean( errors.^2 );
end


figure(2)
bar( categorical( methods ), MSE )
ylabel( 'Mean squared nodal error' )
set(gca,'YScale','log')
