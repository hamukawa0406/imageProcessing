#include "ppmload.h"
#include "cvtGray.h"
#include<stdio.h>

void cvtGray(struct ppmimg *src, struct ppmimg *dst, char *name){
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
			    Y = roundAngle((int)(0.298912*trgb.R + 0.586611*trgb.G + 0.114478*trgb.B));
			    sprintf(_dstName, "%sGray", name);
			}

			trgb.dens = Y;
			setPnmPixel(dst, i, j, trgb);
		}
	}
	sprintf(name, "%s.pgm", _dstName);
	saveppmimage(dst, name);
}

unsigned char roundAngle(int angle)
{
    while(angle < 0 && angle >= 256){
	    if(angle < 0)
		    angle = angle + 256;
	    else if(angle >= 256)
		    angle =  angle - 256;
    }
    return angle;
}
