#include "ifstream_string.h"
#include "statistic.h"

int main(void){
		InctImage* image1 = new InctImage();
		InctImage* image2 = new InctImage();
		//ppmimg�̎��̂𐶐�

		//���ۂ̉摜�̓ǂݍ���
		try{
			image1->loadppmimage("aveRGB.ppm");
			image2->loadppmimage("monocro.ppm");
		}	
		catch(string str){
			cout << str << endl;
		}
/*
        for(int j = 0; j < image1->getHeight(); ++j){
			for(int i = 0; i < image1->getWidth(); ++i){
				std::cout << (int)image1->getPnmPixel(i, j).R << std::endl;
			}
		}
//*/
		Statistic stat(*image1);
		stat.outputStatistic();
		image1->ReleaseImage();
		image2->ReleaseImage();

	return 0;
}
