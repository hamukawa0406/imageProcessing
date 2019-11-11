#include "ifstream_string.h"

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

		InctImage* monoImage = new InctImage(image1->getWidth(), image1->getHeight(), image1->getDepth(), image1->getImageMode());
		InctImage* aveRGBImage = new InctImage(image1->getWidth(), image1->getHeight(), image1->getDepth(), image1->getImageMode());


		//�摜�̃N���[���蓮�쐬
		//image3 = createppmimage(image3, image1->iwidth, image1->iheight, image1->cmode);
		unsigned char monoDens, aveDens;

		for (int j = 0; j<image1->getHeight(); j++){
			for (int i = 0; i<image1->getWidth(); i++){

				RGBColor inRGB;

				inRGB = image1->getPnmPixel(i, j);
				RGBColor mono = inRGB;
				RGBColor aveRGB = inRGB;
				

				if (image1->getImageMode() == 1){
				//	trgb1.dens = 255 - trgb.dens;
				}
				else{
				//	trgb1.R = trgb1.R;
				    aveDens = (unsigned char)(((double)inRGB.getR() + (double)inRGB.getG() + (double)inRGB.getB()) / 3);
				    aveRGB.setR(aveDens);
					aveRGB.setG(aveDens);
					aveRGB.setB(aveDens);
					
				    monoDens = (unsigned char)(0.299*inRGB.getR() + 0.587*inRGB.getG() + 0.114*inRGB.getB());
					mono.setR(monoDens);
					mono.setB(monoDens);
					mono.setR(monoDens);

				}
				monoImage->setPnmPixel(i, j, mono);
				aveRGBImage->setPnmPixel(i, j, aveRGB);

			}
		}
		aveRGBImage->savePnmImage("aveRGB.ppm");
		monoImage->savePnmImage("monocro.ppm");

		image1->ReleaseImage();
		aveRGBImage->ReleaseImage();
		monoImage->ReleaseImage();

	return 0;
}