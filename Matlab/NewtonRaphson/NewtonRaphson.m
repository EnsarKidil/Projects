function root = NewtonRaphson(func, hi)
    
    %func is the function
    %hi is the initial value
    %this function has been created for the 10^-3 tolerance
    %this function uses newton raphson method to find the approximate value
    %and plots all the valeus that is found on the process
    
    f = func;
    epsilon = 1e-10;
    f_dot = @(h) (f(h+epsilon) - f(h)) / epsilon;
    fplot(f,'r','MarkerSize',10);
    hold on;
    err = hi;
    counter = 0;
    ylabel("f(h)");
    xlabel("h");
    hx = 0;
    lgd{1} = "f(h)";
        while abs(double(err)) > 1e-3
        hx = hi - f(hi) / f_dot(hi);
        err = abs(hx - hi) / abs(hx);
        plot(hi,f(hi),'.','MarkerSize',30);
        hi = hx;
        counter = counter + 1; 
        lgd{counter+1} = "h" + int2str(counter-1);
        end
    legend(lgd);
    disp("The approximate value of h is: " + hx);
    disp("Matlab found the solution in "+ counter + " steps");
    root = hi;
end