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
		Statistic stat(*image1);
		Statistic stat2(*image2);
		stat.outputStatistic();
		stat2.outputStatistic();
		image1->ReleaseImage();
		image2->ReleaseImage();

	return 0;
}
