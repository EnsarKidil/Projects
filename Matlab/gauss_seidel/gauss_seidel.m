% Girdiler
A = [8 -2 -2 0; -2 8 0 -2 ; -2 0 8 -2; 0 -2 -2 8];
b = [10; -6; -14; 18];
x = [0; 0; 0; 0];  % Başlangıç tahmini
n = size(x,1);
normVal=Inf;
tol=0.01; itr=0;
while normVal>tol
    x_old=x;
    
    for i=1:n
        
        sigma=0;
        
        for j=1:i-1
                sigma=sigma+A(i,j)*x(j);
        end
        
        for j=i+1:n
                sigma=sigma+A(i,j)*x_old(j);
        end
        
        x(i)=(1/A(i,i))*(b(i)-sigma);
    end
    itr=itr+1;
    normVal=norm(x_old-x);
end