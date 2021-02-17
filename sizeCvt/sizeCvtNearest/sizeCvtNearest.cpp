#include "ppmload.h"
#include<stdio.h>
#include<chrono>

//最近傍法    http://www7a.biglobe.ne.jp/~fairytale/article/program/graphics.html 参考
//線形補間法　　　http://www7a.biglobe.ne.jp/~fairytale/article/program/graphics.html 参考
//バイキュービック補間法　　<- 死ぬ

//void inputScale(double *scale);
void sizeCvtNearestNeighbor(struct ppmimg *src, struct ppmimg *dst, double scale);
unsigned char min(unsigned char a, unsigned char b, unsigned char c);
unsigned char max(unsigned char a, unsigned char b, unsigned char c);
unsigned char roundAngle(unsigned char angle);

char dstName[256] = {0};


int main(void){
	int i;
	unsigned char ave = 0;
	char inputTxt[256] = {0};
	double scaleBig = 2.7;
	double scaleSmall = 1/3.0;
	struct ppmimg *image1=NULL, *image2=NULL, *image3=NULL;
    std::chrono::system_clock::time_point start, end;

//	inputScale(&scale);
	
	sprintf(dstName, "sizeCvtNearestNeighbor");

	image1 = makeimagestruct(image1);
	image2 = makeimagestruct(image2);
	image3 = makeimagestruct(image3);
	loadppmimage("bike.ppm",image1);
	image2 = createppmimage(image2, (int)(image1->iwidth*scaleBig), (int)(image1->iheight*scaleBig),image1->cmode);
	image3 = createppmimage(image3, (int)(image1->iwidth*scaleSmall), (int)(image1->iheight*scaleSmall),image1->cmode);
    start = std::chrono::system_clock::now();
	sizeCvtNearestNeighbor(image1, image2, scaleBig);
    end = std::chrono::system_clock::now();
	sizeCvtNearestNeighbor(image1, image3, scaleSmall);

    double time = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0);
    printf("time %f[ms]\n", time);

	deleteppmimg(image1);
	deleteppmimg(image2);
	deleteppmimg(image3);

	return 0;
}
/*
void inputScale(double &scale){
	puts("何倍に拡大しますか?");
    printf("倍率: ");
	fflush(stdin);
    scanf("%s", scale);
	
	sprintf(dstName, "sizeCvtNearestNeighbor");
}
*/
void sizeCvtNearestNeighbor(struct ppmimg *src, struct ppmimg *dst, double scale){
	int x, y;
	char _dstName[256];
	sprintf(_dstName, dstName);
	for(y=0; y < dst->iheight; y++){
		for(x=0; x<dst->iwidth; x++){
	//		struct RGBColor trgb = getPnmPixel(src,x,y);
			if(src->cmode == 1){
				puts("入力画像はカラーにしてください。");
				continue;
			}
			else{
                // 四捨五入して最近傍を求める
                // scaleは拡大率
                int xp = (int)(x / scale);
                int yp = (int)(y / scale);
                
                if (xp < src->iwidth && yp < src->iheight) {
                    struct RGBColor trgb = getPnmPixel(src, xp, yp);
                    setPnmPixel(dst, x, y, trgb);
				}
			}
		//	setPnmPixel(dst,x,y,trgb);
		}
	}
	if(scale >= 1){
	    sprintf(dstName, "%sBig.ppm", _dstName);
	}
	else
	    sprintf(dstName, "%sSmall.ppm", _dstName);
	
	saveppmimage(dst, dstName);
	sprintf(dstName, _dstName);
}

//*/
unsigned char min(unsigned char a, unsigned char b, unsigned char c)
{
	if(a < b){
		if(a < c) return a;
	}
	else{
		if(b < c) return b;
	}
	return c;
}

unsigned char max(unsigned char a, unsigned char b, unsigned char c)
{
	if(a > b){
		if(a > c) return a;
	}
	else{
		if(b > c) return b;
	}
	return c;
}

unsigned char roundAngle(unsigned char angle)
{
	if(angle < 0)
		return angle + 360;
	else if(angle >= 360)
		return angle - 360;
}
