#include "ppmload.h"
#include<stdio.h>

void makeLUT(unsigned int kaichou);
void cvtGray(struct ppmimg *src, struct ppmimg *dst, int _switch);
unsigned char min(unsigned char a, unsigned char b, unsigned char c);
unsigned char max(unsigned char a, unsigned char b, unsigned char c);
unsigned char roundAngle(unsigned char angle);

unsigned char Lut[256] = {0};
char dstName[256] = {0};

int main(void){
	unsigned char Lut[256] = {0};
	int i, channel;
	unsigned char ave = 0;
	unsigned int kaichousu = 8;
	struct ppmimg *image1=NULL, *image2=NULL;
    
	do{
	    puts("何諧調に変換しますか？(2/4/8/16/32)");
	    printf("諧調数: ");
		fflush(stdin);
	    scanf("%d", &kaichousu);
	}while(!(kaichousu == 2 || kaichousu == 4 ||
	         kaichousu == 8 || kaichousu == 16 ||
		     kaichousu == 32));
	
	sprintf(dstName, "cvtGray_%dtone", kaichousu);

	do{
	    puts("グレースケール変換します。方法は？");
		puts("0: G-channel");
		puts("1: 単純平均");
		puts("2: 中間値");
		puts("3: NTST加重平均");
	    printf("方法: ");
		fflush(stdin);
	    scanf("%d", &channel);
	}while(!(channel == 0 || channel == 1 ||
	         channel == 2 || channel == 3));
	

	makeLUT(kaichousu);

	image1 = makeimagestruct(image1);
	image2 = makeimagestruct(image2);
	loadppmimage("Lenna.ppm",image1);
	image2 = createppmimage(image2,image1->iwidth,image1->iheight,image1->cmode);
	cvtGray(image1, image2, channel);

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
