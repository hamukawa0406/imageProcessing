#include "ppmload.h"

void main(void){
	struct ppmimg *image1 = NULL, *image2 = NULL, *image3 = NULL;

	image1 = makeimagestruct(image1);
	image2 = makeimagestruct(image2);
	image3 = makeimagestruct(image3);
	loadppmimage("Lenna.ppm", image1);
	cloneppmimage(image1, image2);
	cloneppmimage(image1, image3);

	for (int j = 0; j<image1->iheight; j++){
		for (int i = 0; i<image1->iwidth; i++){
			struct RGBColor trgb1 = getPnmPixel(image1, i, j);
			struct RGBColor trgb2 = getPnmPixel(image1, i, j);
			struct RGBColor trgb3 = getPnmPixel(image1, i, j);

			if (image1->cmode == 1){
				trgb2.dens = 255 - trgb1.dens;
			}
			else{
				trgb2.R = (unsigned char)(((double)trgb1.R + (double)trgb1.G + (double)trgb1.B) / 3);
				trgb2.G = (unsigned char)(((double)trgb1.R + (double)trgb1.G + (double)trgb1.B) / 3);
				trgb2.B = (unsigned char)(((double)trgb1.R + (double)trgb1.G + (double)trgb1.B) / 3);

				trgb3.R = (unsigned char)(0.299*trgb1.R + 0.587*trgb1.G + 0.114*trgb1.B);
				trgb3.G = (unsigned char)(0.299*trgb1.R + 0.587*trgb1.G + 0.114*trgb1.B);
				trgb3.B = (unsigned char)(0.299*trgb1.R + 0.587*trgb1.G + 0.114*trgb1.B);
			}
			setPnmPixel(image2, i, j, trgb2);
			setPnmPixel(image3, i, j, trgb3);

		}
	}
	saveppmimage(image2, "RGBaverage.ppm");
	saveppmimage(image3, "monocro.ppm");

	deleteppmimg(image1);
	deleteppmimg(image2);
	deleteppmimg(image3);
}