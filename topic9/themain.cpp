#include "ifstream_string.h"
#include "filter.h"
#include<iostream>
#include<array>
#include<algorithm>

/*
            {{1/16, 1/8, 1/16}},
            {{1/8, 1/4, 1/8}},
            {{1/16, 1/8, 1/16}}
        };
//*/ 

int main(void){
	int inSelect{}, inRank;
	InctImage* image1 = new InctImage();

	try{
		image1->loadppmimage("inussg.pgm");
	}
	catch(string str){
		cout << str << endl;
	}

	cout << "cmode=" << image1->getImageMode() << endl;
	cout << "magicNum=" << image1->getMagicNumber() << endl;
	InctImage* dstImage = new InctImage(image1->getWidth(), image1->getHeight(), image1->getDepth(), image1->getImageMode());

	std::cout << "1...ランク値フィルタ" << std::endl;
	std::cout << "2...中央値フィルタ" << std::endl;
	std::cout << "3...最頻値フィルタ" << std::endl;
	std::cout << "4...ガウシアンフィルタ" << std::endl;
	std::cout << "5...鮮鋭化フィルタ" << std::endl;
    std::cout << "どのフィルタリングをかけますか" << std::endl;

	do{
		std::cin >> inSelect;
	}while(inSelect <= 0 || inSelect > 5);
	

	filter flt = filter(*image1, *dstImage, inSelect);

	for (int j = 1; j<image1->getHeight() - 1; j++){
		for (int i = 1; i<image1->getWidth() - 1; i++){
			RGBColor tRGB;

			tRGB = flt.filtering(i, j);

			dstImage->setPnmPixel(i, j, tRGB);
		}
	}
	dstImage->savePnmImage();

	image1->ReleaseImage();
	dstImage->ReleaseImage();

	return 0;
}