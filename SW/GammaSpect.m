
x = 1:1:2048;
x_tick = 0:512:2048;
y_1 = foreground(1:2048);
y_2 = u235_count + 65535*u235_ovf; 
%plot measured data-------------------------
semilogy(x,y_1,x,y_2);
xlim([0,2048]);
xticks(x_tick);

title("Gamma spektrum vizsgálata");
ylabel("Impulzusszám ");
xlabel("A/D csatornaszám");
legend({'Háttérsugárzás','Uránium tartalmú minta'});
legend('boxoff');
grid minor;
