/*
* time: 2019.10.16
* author: fuyuanhao
* descript: read bmp and statistic histogram
* image: lena.bmp
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

int main(int argc, char** argv)
{
	BITMAPFILEHEADER bmpFileHeader;
	BITMAPINFOHEADER bmpInfoHeader;
	RGBQUAD bmpColorTable[256];
	BYTE bmpValue[512 * 512];
	FILE *fp;

	fp = fopen("lena.bmp", "rb");
	if (!fp){
		printf("Cann't open the file!\n");
		return 0;
	}

	fread(&bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
	fread(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
	fread(bmpColorTable, sizeof(RGBQUAD), 256, fp);
	fread(bmpValue, 1, 512 * 512, fp);	
	
	//将图像灰度值存入一位数组中
	int grayValue[512 * 512] = { 0 };
	for (int i = 0; i < 512 * 512; i++)
	{
		grayValue[i] = bmpColorTable[bmpValue[i]].rgbBlue;
	}

	//直方图
	int grayCount[256] = { 0 };
	double grayFrequency[256] = { 0.0 };
	for (int i = 0; i < 512 * 512; i++)
	{
		grayCount[grayValue[i]]++;
	}
	for (int i = 0; i < 256; i++){
		if (grayCount[i]){
			grayFrequency[i] = grayCount[i] / (512.0*512.0);
			printf("灰度值%3d 频数为%6d 频率为%f\n", i, grayCount[i], grayFrequency[i]);
		}	
	}

	//最大值
	int grayMax = 0;
	for (int i = 0; i < 256; i++){
		if (grayCount[i] && (i > grayMax)){
			grayMax = i;
		}
	}
	printf("最大灰度值为%d\n", grayMax);

	//最小值
	int grayMin = 255;
	for (int i = 0; i < 256; i++){
		if (grayCount[i] && (i < grayMin)){
			grayMin = i;
		}
	}
	printf("最小灰度值为%d\n", grayMin);

	//期望 E(X)
	double grayMean = 0.0;
	for (int i = 0; i < 255; i++){
		if (grayCount[i]){
			grayMean += i * grayFrequency[i];
		}
	}
	printf("期望为%f\n", grayMean);

	//方差
	// D(X) = E(X^2) - E(X)^2
	double grayMean2 = 0.0;
	for (int i = 0; i < 255; i++){
		grayMean2 += i * i * grayFrequency[i];
	}
	double grayVariance = grayMean2 - grayMean * grayMean;
	printf("方差为%f\n", grayVariance);

	//熵
	double grayEntropy = 0.0;
	for (int i = 0; i < 255; i++){
		if (grayCount[i]){
			grayEntropy += -grayFrequency[i] * log2(grayFrequency[i]);
		}
	}
	printf("图像熵为%f\n", grayEntropy);
	
	printf("-----------------------------------位图文件头-------------------------------------------\n");
	printf("文件标识符 = 0x%X\n", bmpFileHeader.bfType);
	printf("文件大小 = %d 字节\n", bmpFileHeader.bfSize);
	printf("保留字段1 = %d\n", bmpFileHeader.bfReserved1);
	printf("保留字段2 = %d\n", bmpFileHeader.bfReserved2);
	printf("位图数据的地址 = %d 字节\n", bmpFileHeader.bfOffBits);

	printf("-----------------------------------位图信息头-------------------------------------------\n");
	printf("本结构大小 = %d 字节\n", bmpInfoHeader.biSize);
	printf("位图的宽度 = %d\n", bmpInfoHeader.biWidth);
	printf("位图的高度 = %d\n", bmpInfoHeader.biHeight);
	printf("目标设备位平面数 = %d \n", bmpInfoHeader.biPlanes);
	printf("位深度 = %d 位\n", bmpInfoHeader.biBitCount);
	printf("压缩类型 = %d\n", bmpInfoHeader.biCompression);
	printf("位图的大小 = %d 字节\n", bmpInfoHeader.biSizeImage);
	printf("目标设备水平分辨率 = %d \n", bmpInfoHeader.biXPelsPerMeter);
	printf("目标设备垂直分辨率 = %d \n", bmpInfoHeader.biYPelsPerMeter);
	printf("使用的色彩数 = %d \n", bmpInfoHeader.biClrUsed);
	printf("重要的色彩数 = %d \n", bmpInfoHeader.biClrImportant);

	fclose(fp);
	return 0;

}