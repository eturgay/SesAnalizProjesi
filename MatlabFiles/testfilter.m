clear
close all
% crate noise
n = 0.1*randn(1,44100);
% create sigle sinosoid
t = linspace(0,1,44100);
s1 = sin(2*pi*400*t);
s2 = sin(2*pi*880*t);
s =  n + s1 + s2;
figure;plot(s)

M = 100;
h=zeros(1,M);
for i=1:M
    h(i) = 0.42 - 0.5 * cos(2*pi*i/M) + 0.08 * cos(4*pi*i/M);
end;
W = sum(h);
h = h/W;
figure;plot(M);
s_f = conv(h,s);

s_d = downsample(s_f,20);
figure;hold; plot(s(1:1000));plot(s_f(16:1015),'r');
figure;plot(abs(fft(s_d,2024)));
hold;plot(abs(fft(s,2024)),'r');


