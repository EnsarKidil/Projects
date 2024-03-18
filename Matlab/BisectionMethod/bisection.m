UpperLimit = 1;
DownLimit = 0;
err = 10^-8;
sayac = 1;
while UpperLimit - DownLimit >= err
    if hw((UpperLimit+DownLimit)/2)*hw(DownLimit) < 0 
        UpperLimit = (UpperLimit+DownLimit)/2;
    elseif hw((UpperLimit+DownLimit)/2)*hw(DownLimit) > 0
        DownLimit = (UpperLimit+DownLimit)/2;
    end
    up(sayac,1) = UpperLimit;
    down(sayac,1) = DownLimit;
    middlepoint(sayac,1) = (UpperLimit+DownLimit)/2;
    condition(sayac,1) = (UpperLimit - DownLimit)/2;
    negorpos(sayac,1) = hw((UpperLimit+DownLimit)/2)*hw(DownLimit);
    sayac= sayac + 1;
end

t = table(up,down,middlepoint,condition,negorpos);
solution = (UpperLimit + DownLimit)/2;
solutionbymatlab = fzero(@hw,0);
x = [1 4];
y = exp(x).*(3.2*sin(x)-0.5*cos(x));
xlabel("x");
ylabel("y");
plot(x,y);


function f = hw(x) 
    f = exp(x).*(3.2*sin(x)-0.5*cos(x));
end

