#include "ppmload.h"

void main(void){
	struct ppmimg *image1 = NULL, *image2 = NULL, *image3 = NULL, *image4 = NULL;
//	struct ppming *image4 = NULL;

	//ppmimgの実体を生成
	image1 = makeimagestruct(image1);
	image2 = makeimagestruct(image2);
	image3 = makeimagestruct(image3);
	image4 = makeimagestruct(image4);

	//実際の画像の読み込み
	loadppmimage("Lenna.ppm", image1);
	//画像のクローン作製
	cloneppmimage(image1, image2);
	cloneppmimage(image1, image3);
	cloneppmimage(image1, image4);


	//画像のクローン手動作成
	//image3 = createppmimage(image3, image1->iwidth, image1->iheight, image1->cmode);

	for (int j = 0; j<image1->iheight; j++){
		for (int i = 0; i<image1->iwidth; i++){
			struct RGBColor trgb1 = getPnmPixel(image1, i, j);
			struct RGBColor trgb2 = getPnmPixel(image1, i, j);
			struct RGBColor trgb3 = getPnmPixel(image1, i, j);

			if (image1->cmode == 1){
			//	trgb1.dens = 255 - trgb.dens;
			}
			else{
			//	trgb1.R = trgb1.R;
				trgb1.G = 0;
				trgb1.B = 0;
				
				trgb2.R = 0;
				trgb2.B = 0;

				trgb3.R = 0;
				trgb3.G = 0;
				//*/
			}
			setPnmPixel(image2, i, j, trgb1);
			setPnmPixel(image3, i, j, trgb2);
			setPnmPixel(image4, i, j, trgb3);

		}
	}
	saveppmimage(image2, "RedOnly.ppm");
	saveppmimage(image3, "GreenOnly.ppm");
	saveppmimage(image4, "BlueOnly.ppm");

	deleteppmimg(image1);
	deleteppmimg(image2);
	deleteppmimg(image3);
	deleteppmimg(image4);

}