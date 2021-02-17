#include<stdio.h>
#include "ifstream_string.h"

struct CMYColor {
	unsigned char C, M, Y;
};

struct CMYColor RGB2CMY(RGBColor);
RGBColor CMY2RGB(struct CMYColor);

int main(void){
    InctImage inImg;

	try{
		inImg.loadppmimage("Lenna.ppm");
	}
	catch(string str){
		cout << str << endl;
	}

    InctImage outImg(inImg.getWidth(), inImg.getHeight(), inImg.getDepth(), inImg.getImageMode());

	for(int j = 0; j < inImg.getHeight(); j++){
		for(int i = 0; i < inImg.getWidth(); i++){
			RGBColor trgb = inImg.getPnmPixel(i,j);
			struct CMYColor tcmy;
			if(inImg.getImageMode() == 1){
				std::cout << "ファイルタイプが違う" << std::endl;
			}else{
				tcmy = RGB2CMY(trgb);
				trgb = CMY2RGB(tcmy);
			}
			outImg.setPnmPixel(i, j, trgb);
		}
	}
	outImg.savePnmImage("RGB2CMY.ppm");

	inImg.ReleaseImage();
	outImg.ReleaseImage();

	return 0;
}

struct CMYColor RGB2CMY(RGBColor rgbTmp)
{
	struct CMYColor cmy;
	cmy.C = 255 - rgbTmp.R;
	cmy.M = 255 - rgbTmp.G;
	cmy.Y = 255 - rgbTmp.B;

	return cmy;
}

RGBColor CMY2RGB(struct CMYColor cmy) 
{
	RGBColor rgb;
	rgb.R = 255 - cmy.C;
	rgb.G = 255 - cmy.M;
	rgb.B = 255 - cmy.Y;

	return rgb;
}

