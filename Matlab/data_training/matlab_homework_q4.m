function final = matlab_homework_q4(start_p1, sl_infra, start_p2, sl_braking) 

    M1 = containers.Map(start_p1,sl_infra);
    M2 = containers.Map(start_p2,sl_braking);
    set1 = union(start_p1, start_p2);
    final_array = [];

    for k = 1:length(set1)
        if(isKey(M1,set1(k)) && isKey(M2, set1(k)))
            final_array(k) = min(M1(set1(k)),M2(set1(k)));     
        elseif(isKey(M1,set1(k)))
            closestSmallerKey = max(find(cell2mat(keys(M2)) < set1(k)));
            final_array(k) = min(M1(set1(k)),sl_braking(closestSmallerKey));
        elseif(isKey(M2,set1(k)))
            closestSmallerKey = max(find(cell2mat(keys(M1)) < set1(k)));
            final_array(k) = min(M2(set1(k)),sl_infra(closestSmallerKey));
        end
    end

    final_array_x = [set1 transpose(final_array)];
    k = 2;

    while k <= size(final_array_x, 1)
        if final_array_x(k, 2) == final_array_x(k-1, 2)
            final_array_x(k, :) = [];
        else
            k = k + 1;
        end
    end
    
    final = final_array_x;
end

