#include "ifstream_string.h"
#include "statistic.h"

int main(void){
	string Red {"RedOnly.ppm"};
	string Green {"GreenOnly.ppm"};
	string Blue {"BlueOnly.ppm"};
	InctImage* image1 = new InctImage();
	InctImage* image2 = new InctImage();
	InctImage* image3 = new InctImage();
	
	//ppmimg�̎��̂𐶐�

	//���ۂ̉摜�̓ǂݍ���
	try{
		image1->loadppmimage(Red);
		image2->loadppmimage(Green);
		image3->loadppmimage(Blue);
	}	
	catch(string str){
		cout << str << endl;
	}
	RGBColor trgb;
	for(int j = 0; j < image1->getHeight(); ++j){
		for(int i = 0; i < image1->getWidth(); ++i){
			trgb = image2->getPnmPixel(i, j);
			trgb.setR(trgb.getG());
			trgb.setG(0);
			image2->setPnmPixel(i, j, trgb);
			trgb = image3->getPnmPixel(i, j);
			trgb.setR(trgb.getB());
			trgb.setB(0);
			image3->setPnmPixel(i, j, trgb);
		}
	}
	Statistic stat1(*image1);
	Statistic stat2(*image2);
	Statistic stat3(*image3);
	stat1.outputStatistic();
	stat2.outputStatistic();
	stat3.outputStatistic();
	image1->ReleaseImage();
	image2->ReleaseImage();
	image3->ReleaseImage();

	return 0;
}
