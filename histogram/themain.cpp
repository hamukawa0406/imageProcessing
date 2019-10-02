#include "ppmload.h"
#include<stdio.h>

//void inputScale(double *scale);
void makeLUT(unsigned char min, unsigned char max);
//void sizeCvtNearestNeighbor(struct ppmimg *src, struct ppmimg *dst, double scale);
unsigned char min(unsigned char a, unsigned char b, unsigned char c);
unsigned char max(unsigned char a, unsigned char b, unsigned char c);
unsigned char roundAngle(unsigned char angle);

char dstName[256] = {0};
unsigned char Lut[256] = {0};


int main(void){
	int i, x, y;
	int a, b;
	unsigned char ave = 0;
	char inputTxt[256] = {0};
	char dstName[256] = {0};
	double scale = 1;
	struct ppmimg *image1=NULL, *image2=NULL;
	int data[256] = {0};
	int dataSum  = 0;
 	bool minFlag = false;
	bool maxFlag = false;
	

//	inputScale(&scale);

	sprintf(dstName, "Linear.ppm");

	image1 = makeimagestruct(image1);
	image2 = makeimagestruct(image2);
	loadppmimage("Boat.ppm",image1);
	image2 = createppmimage(image2, image1->iwidth, image1->iheight, 1);
	for(y=0; y < image1->iheight; y++){
		for(x=0; x<image1->iwidth; x++){
			if(image1->cmode == 1){
				puts("入力画像はカラーにしてください。");
				continue;
			}
			else{
				struct RGBColor trgb = getPnmPixel(image1, x, y);
				data[(int)(trgb.R)] += 1;
			}
		}
	}



	for(i = 0; i < 256; i++){
		dataSum += data[i];
		if(dataSum >= 1966 && minFlag == false){
			a = i;
			minFlag = true;
			continue;
		}
		if(dataSum >= 63570 && maxFlag == false){
			b = i;
			maxFlag = true;
			break;
		}
	}

	makeLUT(a, b);

	for(y=0; y < image1->iheight; y++){
		for(x=0; x<image1->iwidth; x++){
			if(image1->cmode == 1){
				puts("入力画像はカラーにしてください。");
				continue;
			}
			else{
				struct RGBColor trgb = getPnmPixel(image1, x, y);
				struct RGBColor _trgb;
				_trgb.dens = Lut[trgb.R];
				setPnmPixel(image2, x, y, _trgb);
			}
		}
	}

	printf("magicnumber = %s\n", image2->magicnumber);
	saveppmimage(image2, dstName);
	deleteppmimg(image1);
	deleteppmimg(image2);

	return 0;
}

void makeLUT(unsigned char min, unsigned char max){
	int k;
	static int dosu = 0;
	double a, b;

	a = 255 / (max - min);
	b = 0 - a * min;
	printf("min = %d, max = %d, a=%f, b=%f\n", min, max, a, b);
	
	for(k = 0; k < 256; ++k){
		if(k < min){
			Lut[k] = 0;
		}
		else if(k >= min && k <= max){
			Lut[k] = (unsigned char)(a * k + b);
		}
		else{
			Lut[k] = 255;
		}
		
	}
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
