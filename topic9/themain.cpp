#include "ifstream_string.h"
#include "filter.h"
#include<iostream>

/*
            {{1/16, 1/8, 1/16}},
            {{1/8, 1/4, 1/8}},
            {{1/16, 1/8, 1/16}}
        };
//*/ 

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
	InctImage* dstImage = new InctImage(image1->getWidth(), image1->getHeight(), image1->getDepth(), image1->getImageMode());


	//�摜�̃N���[���蓮�쐬
	//image3 = createppmimage(image3, image1->iwidth, image1->iheight, image1->cmode);

	filter flt = filter();

	for (int j = 1; j<image1->getHeight() - 1; j++){
		for (int i = 1; i<image1->getWidth() - 1; i++){
			RGBColor tRgb;
			flt.

			tRgb = image1->getPnmPixel(i, j);

			

			if (image1->getImageMode() == 1){
			//	trgb1.dens = 255 - trgb.dens;
			}
			else{
			//	trgb1.R = trgb1.R;
				tRgb.setG(0);
				tRgb.setB(0);
			}
			dstImage->setPnmPixel(i, j, tRgb);

		}
	}
	dstImage->savePnmImage("RedOnly.ppm");

	image1->ReleaseImage();
	dstImage->ReleaseImage();

	return 0;
}