function poles = findRoots (poly)
    %find the degree of the polynom

    degree = polynomialDegree(poly);

    %create random numbers for a and b, i took the interval [0,1] here, but
    %it does not really matter

    %a = (1)*rand(1);
    %b = (1)*rand(1);
    a = 0.4;
    b = 0.9;
    %1i represents the complex number i
    %create the initialize vector

    init = [];
    new_init = [];
    iter = 0;
    for k = 0:degree-1
       init(k+1) = (a+b*1i)^k;
    end

    diff = [];

   
    while true
        for i = 1:degree
            counter = 1;
            for j = 1:degree
                if i ~= j
                    diff(counter) = init(i) - init(j);
                    counter = counter +1;
                end
            end
            %diff
            product_diff = prod(diff);
            
            %i checked that because i realised that if product_diff is 0,
            %the program crashes. this is why i corrected it with a
            %tolerance of 10^-3
            
            if product_diff == 0
                product_diff = 0.001;
            end

            x = init(i);
            new_init(i) = init(i) - subs(poly)/product_diff;
        end

        err = max(abs(new_init-init));
        init = new_init;

        if err < 1e-3
            break;
        end

        if iter > 100
            break;
        end
        
        iter = iter + 1;
        
    end
    poles = init;    
end
