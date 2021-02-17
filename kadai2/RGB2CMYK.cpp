#include<stdio.h>
#include "ifstream_string.h"

struct CMYKColor {
	unsigned char C, M, Y, K;
};

struct CMYKColor RGB2CMYK(RGBColor);
RGBColor CMYK2RGB(struct CMYKColor);

unsigned char min(unsigned char a, unsigned char b);
unsigned char min3(unsigned char a, unsigned char b, unsigned char c);

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
			struct CMYKColor tcmyk;
			if(inImg.getImageMode() == 1){
				std::cout << "ファイルタイプが違う" << std::endl;
			}else{
				tcmyk = RGB2CMYK(trgb);
				trgb = CMYK2RGB(tcmyk);
			}
			outImg.setPnmPixel(i, j, trgb);
		}
	}
	outImg.savePnmImage("RGB2CMYK.ppm");

	inImg.ReleaseImage();
	outImg.ReleaseImage();

	return 0;
}



struct CMYKColor RGB2CMYK(RGBColor rgbTmp)
{
	struct CMYKColor cmyk;
	cmyk.K = min3(255 - rgbTmp.R, 255 - rgbTmp.G, 255 - rgbTmp.B);
	if( cmyk.K == 255) cmyk.K = 254;
	cmyk.C = (double)(255 - rgbTmp.R - cmyk.K) / (255 - cmyk.K) * 255;
	cmyk.M = (double)(255 - rgbTmp.G - cmyk.K) / (255 - cmyk.K) * 255;
	cmyk.Y = (double)(255 - rgbTmp.B - cmyk.K) / (255 - cmyk.K) * 255;

	return cmyk;
}

RGBColor CMYK2RGB(struct CMYKColor cmyk)
{
	RGBColor trgb;
	trgb.R = 255 - cmyk.C*(255 - cmyk.K)/255.0 - cmyk.K;
	trgb.G = 255 - cmyk.M*(255 - cmyk.K)/255.0 - cmyk.K;
	trgb.B = 255 - cmyk.Y*(255 - cmyk.K)/255.0 - cmyk.K;
	
	return trgb;
}

unsigned char min(unsigned char a, unsigned char b)
{
	if(a < b) return a;
	else return b;
}

unsigned char min3(unsigned char a, unsigned char b, unsigned char c)
{
	if(a < b){
		if(a < c) return a;
	}
	else{
		if(b < c) return b;
	}
	return c;
}
