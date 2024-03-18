% Girdiler
A = [8 -2 -2 0; -2 8 0 -2 ; -2 0 8 -2; 0 -2 -2 8];
b = [10; -6; -14; 18];
x = [0; 0; 0; 0];  % Başlangıç tahmini
epsilon = 0.05;  % Tolerans
maxit = 1000;

[na, ma] = size(A);
if na ~= ma
    disp('ERROR: Matrix A must be a square matrix')
    return
end
% check if b is a column matrix
[nb, mb] = size (b);
if nb ~= na || mb~=1
   disp( 'ERROR: Matrix b must be a column matrix')
   return
end
dx = zeros(na,1);
for k=1:maxit
    sum = 0;
    for i=1:na
        dx(i) = b(i);
        for j=1:na
            dx(i) = dx(i) - A(i,j)*x(j); 
        end
        dx(i) = dx(i)/A(i,i);
        x(i) = x(i) + dx(i);
        if (dx(i) >= 0)
            sum = sum + dx(i);
        else 
            sum = sum - dx(i);
        end
    end
    disp(k)
    disp(x)
    disp(sum)
    if(sum <= epsilon)
        break
    end
    
end
fprintf('The final answer obtained after %g iterations is  \n', k);