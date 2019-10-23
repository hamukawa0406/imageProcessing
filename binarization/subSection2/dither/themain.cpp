#include "ppmload.h"
#include<stdio.h>

//参考　教科書p154

class dither {
    private:
	    int in1;
	    static const int bayer[4][4];
	    static const int halftone[4][4];
	    static const int screw[4][4];
	    static const int screw2[4][4];
	    static const int medEmph[4][4];
	    static const int dotConc[4][4];
		int dthr[4][4];
	public:
		dither();
		dither(int);

};

const int dither::bayer[4][4] = 
                  {{  0,  8,  2, 10},
                   { 12,  4, 14,  6},
				   {  3, 11,  1,  9},
				   { 15,  7, 13,  5}
				   };
const int dither::halftone[4][4] = 
	                 {{ 10,  4,  6,  8},
                      { 12,  0,  2, 14},
				      {  7,  9, 11,  5},
				      {  3, 15, 13,  1}
				   };
const int dither::screw[4][4] = 
                  {{ 13,  7,  6, 12},
                   {  8,  1,  0,  5},
				   {  9,  2,  3,  4},
				   { 14, 10, 11, 15}
				  };
const int dither::screw2[4][4] = 
	               {{ 15,  4,  8, 12},
                    { 11,  0,  1,  5},
				    {  7,  3,  2,  9},
				    { 14, 10,  6, 13}
				   };
const int dither::medEmph[4][4] = 
	                {{ 12,  4,  8, 14},
                     { 11,  0,  2,  6},
				     {  7,  3,  1, 10},
				     { 15,  9,  5, 13}
				    };

const int dither::dotConc[4][4] = 
	                {{ 13,  4,  8, 14},
                     { 10,  0,  1,  7},
				     {  6,  3,  2, 11},
				     { 15,  9,  5, 13}
				    };    

void dithering(struct ppmimg *src, struct ppmimg *dst, int channel);
unsigned char roundAngle(unsigned char angle);

char dstName[256] = {0};



int main(void){
	int i;
	unsigned char dither = 0;
	struct ppmimg *image1=NULL, *image2=NULL;

	sprintf(dstName, "dithering");

	do{
		fflush(stdin);
		puts("ディザ法で2値化させる");
		puts("1: Bayer");
		puts("2: halftone");
		puts("3: Screw");
		puts("4: Screw2");
		puts("5: medianEmphasize");
		puts("6: dotConcentrate");
		scanf("%d", &dither);
	}while(dither < 0 && dither > 6);

	image1 = makeimagestruct(image1);
	image2 = makeimagestruct(image2);
	loadppmimage("LENNA.pgm",image1);
	image2 = createppmimage(image2, image1->iwidth, image1->iheight, image1->cmode);
	dithering(image1, image2, dither);

	deleteppmimg(image1);
	deleteppmimg(image2);

	return 0;
}



void dithering(struct ppmimg *src, struct ppmimg *dst, int channel){
	int x, y;
	char _dstName[256];
	sprintf(_dstName, dstName);
	for(y=0; y < dst->iheight; y++){
		for(x=0; x<dst->iwidth; x++){
			struct RGBColor trgb = getPnmPixel(src, x, y);
			struct RGBColor dstrgb; 
			if(src->cmode == 1){
				switch(channel){
					case 1:
					    sprintf(dstName, "%sBayer.pgm", _dstName);
					    break;
					case 2:
					    sprintf(dstName, "%sHalftone.pgm", _dstName);
					    break;
					case 3:
					    sprintf(dstName, "%sScrew.pgm", _dstName);
					    break;
					case 4:
					    sprintf(dstName, "%sScrew2.pgm", _dstName);
					    break;
					case 5:
					    sprintf(dstName, "%sMedianEmph.pgm", _dstName);
					    break;
					case 6:
					    sprintf(dstName, "%sBayerDotConc.pgm", _dstName);
					    break;
				}
			}
			else{
				puts("入力画像はグレースケールにしてください。");
				continue;
			}
			setPnmPixel(dst,x,y,dstrgb);
		}
	}
	saveppmimage(dst, dstName);
}

unsigned char roundAngle(unsigned char angle)
{
    while(angle < 0 && angle >= 256){
	    if(angle < 0)
		    angle = angle + 256;
	    else if(angle >= 256)
		    angle =  angle - 256;
    }
    return angle;
}
