#include "ifstream_string.h"

int main(void){
    InctImage* image1 = new InctImage();
	//ppmimg�̎��̂𐶐�

	//���ۂ̉摜�̓ǂݍ���
	image1->loadppmimage("Lenna.ppm");
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
			printf("asdf\n");

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