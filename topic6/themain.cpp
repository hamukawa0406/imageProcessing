#include "ppmload.h"
#include<stdio.h>

//最近傍法    http://www7a.biglobe.ne.jp/~fairytale/article/program/graphics.html 参考
//線形補間法　　　http://www7a.biglobe.ne.jp/~fairytale/article/program/graphics.html 参考
//バイキュービック補間法　　<- 死ぬ

void makeLUT(unsigned int kaichou);

void cvtGray(struct ppmimg *src, struct ppmimg *dst, int _switch);
unsigned char min(unsigned char a, unsigned char b, unsigned char c);
unsigned char max(unsigned char a, unsigned char b, unsigned char c);
unsigned char roundAngle(unsigned char angle);

unsigned char Lut[256] = {0};
char dstName[256] = {0};

int main(void){
	unsigned char Lut[256] = {0};
	int i;
	unsigned char ave = 0;
	double expansion = 1;
	struct ppmimg *image1=NULL, *image2=NULL;
    
	puts("何倍に拡大しますか?");
    printf("倍率: ");
	fflush(stdin);
    scanf("%lf", &expansion);
	
	sprintf(dstName, "cvtExpansion", kaichousu);

	image1 = makeimagestruct(image1);
	image2 = makeimagestruct(image2);
	loadppmimage("Lenna.ppm",image1);
	image2 = createppmimage(image2, (int)(image1->iwidth*expansion), (int)(image1->iheight*expansion),image1->cmode);
	cvtExPansion(image1, image2, channel);

	deleteppmimg(image1);
	deleteppmimg(image2);

	return 0;
}


void makeLUT(unsigned int kaichou){
	int k;
	static int i = 0;
	static int dosu = 0;
	static int ichikaichou = (int)(256 / kaichou);
	
	for(k = 0; k < 256; ++k){
		if(i < ichikaichou){
	        Lut[k] = dosu;
		    ++i;
		}
	    else{
		    dosu += ichikaichou;
		    i = 0;
		}
		
	}
}

void cvtGray(struct ppmimg *src, struct ppmimg *dst, int _switch){
	char _dstName[256];
	unsigned char Y;
	for(int j=0;j<src->iheight;j++){
		for(int i=0;i<src->iwidth;i++){
			struct RGBColor trgb = getPnmPixel(src,i,j);
			if(src->cmode == 1){
				puts("入力画像はカラーにしてください。");
				continue;
			}
			else{
				switch(_switch){
					case 0:
					    Y = trgb.G;
						sprintf(_dstName, "%s_G-Channel", dstName);
						break;
					case 1:
					    Y = (unsigned char)((trgb.R + trgb.G + trgb.B ) / 3);
						sprintf(_dstName, "%s_RGBave", dstName);
						break;	        
					case 2:
					    Y = (unsigned char)((max(trgb.R, trgb.G, trgb.B) + min(trgb.R, trgb.G, trgb.B)) / 2);
						sprintf(_dstName, "%s_median", dstName);
						break;
					case 3:
					    Y = (unsigned char)(0.298912*trgb.R + 0.586611*trgb.G + 0.114478*trgb.B);
						sprintf(_dstName, "%s_NTST", dstName);
						break;
				}

				trgb.R = Lut[Y];
				trgb.G = Lut[Y];
				trgb.B = Lut[Y];
			}
			setPnmPixel(dst,i,j,trgb);
		}
	}
	sprintf(dstName, "%s.ppm", _dstName);
	saveppmimage(dst, dstName);
}


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
