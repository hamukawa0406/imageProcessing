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
	int inSelect{}, inRank{};
/*
	try{
		image1->loadppmimage("inussg.pgm");
	}
	catch(string str){
		cout << str << endl;
	}
//*/
	std::cout << "1...ランク値フィルタ" << std::endl;
	std::cout << "2...中央値フィルタ" << std::endl;
	std::cout << "3...最頻値フィルタ" << std::endl;
	std::cout << "4...ガウシアンフィルタ" << std::endl;
	std::cout << "5...鮮鋭化フィルタ" << std::endl;
    std::cout << "どのフィルタリングをかけますか" << std::endl;

	do{
		std::cin >> inSelect;
	}while(inSelect <= 0 || inSelect > 5);
	

	filter flt = filter(inSelect);


	cout << "cmode=" << flt.srcImg.getImageMode() << endl;
	cout << "magicNum=" << flt.srcImg.getMagicNumber() << endl;

	for (int j = 1; j < flt.srcImg.getHeight() - 1; j++){
		for (int i = 1; i < flt.srcImg.getWidth() - 1; i++){
			RGBColor tRGB;

		    tRGB = flt.filtering(i, j);

			flt.dstImg.setPnmPixel(i, j, tRGB);
		}
	}
	flt.dstImg.savePnmImage();

	flt.srcImg.ReleaseImage();
	flt.dstImg.ReleaseImage();

	return 0;
}