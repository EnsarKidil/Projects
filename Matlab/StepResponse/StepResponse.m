wn = 5;  
zeta = 0.476;

s = tf('s');
G = wn^2/(s^2 + 2*zeta*wn*s + wn^2);

figure;
step(G);
title('Basamak Yanıtı');
