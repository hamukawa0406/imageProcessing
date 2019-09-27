#include "ppmload.h"
#include<stdio.h>

//最近傍法    http://www7a.biglobe.ne.jp/~fairytale/article/program/graphics.html 参考
//線形補間法　　　http://www7a.biglobe.ne.jp/~fairytale/article/program/graphics.html 参考
//バイキュービック補間法　　<- 死ぬ

void sizeCvtLinear(struct ppmimg *src, struct ppmimg *dst, double scale);
unsigned char min(unsigned char a, unsigned char b, unsigned char c);
unsigned char max(unsigned char a, unsigned char b, unsigned char c);
unsigned char roundAngle(unsigned char angle);

char dstName[256] = {0};

int main(void){
	int i;
	unsigned char ave = 0;
	char inputTxt[256] = {0};
	double scale = 1;
	struct ppmimg *image1=NULL, *image2=NULL;

//	inputScale(&scale);

	puts("何倍に拡大しますか?");
    printf("倍率: ");
	fflush(stdin);
    scanf("%lf", &scale);
	
	sprintf(dstName, "sizeCvtLinear");

	image1 = makeimagestruct(image1);
	image2 = makeimagestruct(image2);
	loadppmimage("Lenna.ppm",image1);
	image2 = createppmimage(image2, (int)(image1->iwidth*scale), (int)(image1->iheight*scale),image1->cmode);
	sizeCvtLinear(image1, image2, scale);

	deleteppmimg(image1);
	deleteppmimg(image2);

	return 0;
}

void sizeCvtLinear(struct ppmimg *src, struct ppmimg *dst, double scale){
	int x, y;
	char _dstName[256];
	sprintf(_dstName, dstName);
	for(y=0; y < dst->iheight; y++){
		for(x=0; x<dst->iwidth; x++){
			if(src->cmode == 1){
				puts("入力画像はカラーにしてください。");
				continue;
			}
			else{
                int x0 = (int)(x / scale);
                int y0 = (int)(y / scale);
                if (x0 < ((src->iwidth) - 1) && y0 < ((src->iheight) - 1)) {
                    // 左上の画素との距離
                    double a = x / scale - x0;
                    double b = y / scale - y0;
                
                    struct RGBColor color[4];
					struct RGBColor new_element;
                        
                    color[0] = getPnmPixel(src, x0, y0);
                    color[1] = getPnmPixel(src, x0+1, y0);
                    color[2] = getPnmPixel(src, x0, y0+1);
                    color[3] = getPnmPixel(src, x0+1, y0+1);
                        
                    for (int k = 0; k < 3; k++) {                                
                        // Xの距離×Yの距離を各画素の重みとする
                        new_element.R = (unsigned char)((1-a)*(1-b)*color[0].R
                                            + a*(1-b)*color[1].R
                                            + (1-a)*b*color[2].R
                                            + a*b*color[3].R);
                        new_element.G = (unsigned char)((1-a)*(1-b)*color[0].G
                                            + a*(1-b)*color[1].G
                                            + (1-a)*b*color[2].G
                                            + a*b*color[3].G);
                        new_element.B = (unsigned char)((1-a)*(1-b)*color[0].B
                                            + a*(1-b)*color[1].B
                                            + (1-a)*b*color[2].B
                                            + a*b*color[3].B);
                    }
                        
                    setPnmPixel(dst, x, y, new_element);
                }

			}
		}
	}
	sprintf(dstName, "%s.ppm", _dstName);
	saveppmimage(dst, dstName);
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
