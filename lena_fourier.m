IMG = imread('lena24.bmp');

%取RGB进行二维快速傅里叶变换
R = fft2(IMG(:,:,1));
G = fft2(IMG(:,:,2));
B = fft2(IMG(:,:,3));

%移至屏幕中央
Rimg = fftshift(R);
Gimg = fftshift(G);
Bimg = fftshift(B);

%取对数傅里叶幅度谱
FR = log10(abs(Rimg)+1);
FG = log10(abs(Gimg)+1);
FB = log10(abs(Bimg)+1);

%取线性傅里叶相位谱
AR = angle(Rimg);
AG = angle(Gimg);
AB = angle(Bimg);

%绘制原始图像
subplot(2,4,1);imshow(IMG);title('原始图像');
%绘制RGB幅度频谱图像
subplot(2,4,2);imshow(FR,[]);title('R 幅值频谱');
subplot(2,4,3);imshow(FG,[]);title('G 幅值频谱');
subplot(2,4,4);imshow(FB,[]);title('B 幅值频谱');
%绘制RGB相位频谱图像
subplot(2,4,6);imshow(AR);title('R 相位频谱');
subplot(2,4,7);imshow(AG);title('G 相位频谱');
subplot(2,4,8);imshow(AB);title('B 相位频谱');

%开始逆变换
subplot(2,4,5);
%逆变换还原RGB图像
fr = real(ifft2(abs(R).*exp(i*angle(R))))/255.0;
fg = real(ifft2(abs(G).*exp(i*angle(G))))/255.0;
fb = real(ifft2(abs(B).*exp(i*angle(B))))/255.0;
%组合RGB并绘图
img(:,:,1) = fr;
img(:,:,2) = fg;
img(:,:,3) = fb;

imshow(img);
title('复原图像');