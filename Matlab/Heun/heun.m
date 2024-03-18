function [t, y] = heun(f, t0, tn, y0, h, tolerance, analytical_solution)
    
    %f is the function for y'(t)
    %t0 is the initial t
    %tn is the final t
    %h is the step
    %tolerance is the error
    %analytical solution is the y(t) itself
    
    t = t0:h:tn;
    y = zeros(size(t));
    y(1) = y0;

    for i = 1:length(t)-1
        k1 = f(t(i), y(i));
        y_pred = y(i) + h * k1;

        t_curr = t(i + 1);
        k2 = f(t_curr, y_pred);
        y_corr = y(i) + 0.5 * h * (k1 + k2);

        while true
            e = double(abs((y_corr - y_pred) / y_corr));

            if e < tolerance
                y(i + 1) = y_corr;
                break;
            else
                y_pred = y_corr;
                k2 = f(t_curr, y_corr);
                y_corr = y(i) + 0.5 * h * (k1 + k2);
            end
        end
    end
    t_analytical = linspace(t0, tn, 100);
    y_analytical = analytical_solution(t_analytical);
    figure;
    plot(t, y, 'o-', 'DisplayName', 'Numerical Solution (Heun)');
    hold on;
    plot(t_analytical, y_analytical, 'r-', 'DisplayName', 'Analytical Solution');
    xlabel('t');
    ylabel('y(t)');
    title('Numerical and Analytical Solutions');
    legend;
    grid on;
end