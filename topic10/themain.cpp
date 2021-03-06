#include "ifstream_string.h"

void thresholding(struct ppmimg *src, struct ppmimg *dst, unsigned char threshold);

int main(void){
		InctImage* image1 = new InctImage();
		//ppmimg�̎��̂𐶐�

		//���ۂ̉摜�̓ǂݍ���
		try{
			image1->loadppmimage("Lenna.ppm");
		}
		catch(string str){
			cout << str << endl;
		}
		//�摜�̃N���[���쐻

		cout << "cmode=" << image1->getImageMode() << endl;
		cout << "magicNum=" << image1->getMagicNumber() << endl;
		InctImage* Rimage = new InctImage(image1->getWidth(), image1->getHeight(), image1->getDepth(), image1->getImageMode());
		InctImage* Gimage = new InctImage(image1->getWidth(), image1->getHeight(), image1->getDepth(), image1->getImageMode());
		InctImage* Bimage = new InctImage(image1->getWidth(), image1->getHeight(), image1->getDepth(), image1->getImageMode());


		//�摜�̃N���[���蓮�쐬
		//image3 = createppmimage(image3, image1->iwidth, image1->iheight, image1->cmode);

		for (int j = 0; j<image1->getHeight(); j++){
			for (int i = 0; i<image1->getWidth(); i++){

				RGBColor tRgb;

				tRgb = image1->getPnmPixel(i, j);

				RGBColor trGb = tRgb;
				RGBColor trgB = tRgb;
				

				if (image1->getImageMode() == 1){
				//	trgb1.dens = 255 - trgb.dens;
				}
				else{
				//	trgb1.R = trgb1.R;
					tRgb.setG(0);
					tRgb.setB(0);
					
					trGb.setB(0);
					trGb.setR(0);

					trgB.setR(0);
					trgB.setG(0);
				}
				Rimage->setPnmPixel(i, j, tRgb);
				Gimage->setPnmPixel(i, j, trGb);
				Bimage->setPnmPixel(i, j, trgB);

			}
		}
		Rimage->savePnmImage("RedOnly.ppm");
		Gimage->savePnmImage("GreenOnly.ppm");
		Bimage->savePnmImage("BlueOnly.ppm");

		image1->ReleaseImage();
		Rimage->ReleaseImage();
		Gimage->ReleaseImage();
		Bimage->ReleaseImage();

	return 0;
}

void thresholding(struct ppmimg *src, struct ppmimg *dst, unsigned char threshold){
	int x, y;
	char _dstName[256];
	sprintf(_dstName, dstName);
	for(y=0; y < dst->iheight; y++){
		for(x=0; x<dst->iwidth; x++){
			struct RGBColor trgb = getPnmPixel(src, x, y);
			struct RGBColor dstrgb; 
			if(src->cmode == 1){
				if(trgb.dens > threshold){
					dstrgb.dens = 255;
				}
				else{
					dstrgb.dens = 0;
				}
			}
			else{
				puts("入力画像はグレースケールにしてください。");
				continue;
			}
			setPnmPixel(dst,x,y,dstrgb);
		}
	}
	sprintf(dstName, "%s%d.pgm", _dstName, threshold);
	saveppmimage(dst, dstName);
}

