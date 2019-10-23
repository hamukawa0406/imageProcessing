#include "ppmload.h"
#include "dither.h"
#include<stdio.h>

//参考　教科書p154

char dstName[256] = {0};

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


dither::dither(int x): channel(x), threshold(0)
{
	char _dstName[256];
	sprintf(_dstName, dstName);
	switch(x){
		case 1:
		    for(int j = 0; j < 4; j++){
				for(int i = 0; i < 4; i++){
					dthr[i][j] = bayer[i][j];
				}
			}
			sprintf(dstName, "%sBayer.pgm", _dstName);
			break;
		case 2:
		    for(int j = 0; j < 4; j++){
				for(int i = 0; i < 4; i++){
					dthr[i][j] = halftone[i][j];
				}
			}
			sprintf(dstName, "%sHalftone.pgm", _dstName);	
			break;
		case 3:
		    for(int j = 0; j < 4; j++){
				for(int i = 0; i < 4; i++){
					dthr[i][j] = screw[i][j];
				}
			}
	    	sprintf(dstName, "%sScrew.pgm", _dstName);
			break;
		case 4:
		    for(int j = 0; j < 4; j++){
				for(int i = 0; i < 4; i++){
					dthr[i][j] = screw2[i][j];
				}
			}
		    sprintf(dstName, "%sScrew2.pgm", _dstName);
			break;
		case 5:
		    for(int j = 0; j < 4; j++){
				for(int i = 0; i < 4; i++){
					dthr[i][j] = medEmph[i][j];
				}
			}
			sprintf(dstName, "%sMedianEmph.pgm", _dstName);
			break;
		case 6:
		    for(int j = 0; j < 4; j++){
				for(int i = 0; i < 4; i++){
					dthr[i][j] = dotConc[i][j];
				}
			}
	    	sprintf(dstName, "%sBayerDotConc.pgm", _dstName);
			break;
	}
}

int dither::getDither(int i, int j){
	return dthr[i][j];
}
void dither::dithering(struct ppmimg *src, struct ppmimg *dst, int i, int j){
	for(int y = 0; y < 4; y++){
		for(int x = 0; x < 4; x++){
			struct RGBColor trgb = getPnmPixel(src, i + x, j + y);
			struct RGBColor dstrgb;
			threshold = calcDither(x, y);
			if(judgeBinarization(trgb.dens)) dstrgb.dens = 255;
			else dstrgb.dens = 0;
            setPnmPixel(dst,i + x,j + y,dstrgb);
		}
	}
}

int dither::calcDither(int x, int y){
	int ans = getDither(x, y)*16+8;
	return ans;
}

bool dither::judgeBinarization(unsigned char dens){
	if(dens >= threshold) return true;
	else return false;
}

unsigned char roundAngle(unsigned char angle);



int main(void){
	int i;
	unsigned char dthCannel = 0;
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
		printf("dither: ");
		scanf("%d", &dthCannel);
	}while(dthCannel < 0 && dthCannel > 6);

	image1 = makeimagestruct(image1);
	image2 = makeimagestruct(image2);
	loadppmimage("LENNA.pgm",image1);
	image2 = createppmimage(image2, image1->iwidth, image1->iheight, image1->cmode);

	dither dth(dthCannel);

	for(int y = 0; y < image2->iheight; y += 4){
		for(int x = 0; x < image2->iwidth; x += 4){
			dth.dithering(image1, image2, x, y);
		}
	}
	saveppmimage(image2, dstName);

	deleteppmimg(image1);
	deleteppmimg(image2);

	return 0;
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
