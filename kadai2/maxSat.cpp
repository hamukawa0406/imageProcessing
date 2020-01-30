#include "ifstream_string.h"
#include<iostream>

#define EQUAL_NUM -1

struct HSVColor {
	int H, S, V;
};

struct HSVColor RGB2HSV(RGBColor);
RGBColor HSV2RGB(struct HSVColor);
struct HSVColor maximizeSaturation(struct HSVColor);
int min(int a, int b, int c);
int max(int a, int b, int c);
int roundAngle(int angle);
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
			struct HSVColor hsv;
			if(inImg.getImageMode() == 1){
				std::cout << "ファイルタイプが違う" << std::endl;
			}else{
				hsv = RGB2HSV(trgb);
				hsv = maximizeSaturation(hsv);
				trgb = HSV2RGB(hsv);
			}
			outImg.setPnmPixel(i, j, trgb);
		}
	}
	outImg.savePnmImage("maxSatImg.ppm");

	inImg.ReleaseImage();
	outImg.ReleaseImage();

	return 0;
}


struct HSVColor RGB2HSV(RGBColor rgbTmp)
{
	struct HSVColor hsv;
	unsigned char maxColor = max(rgbTmp.R, rgbTmp.G, rgbTmp.B);
	unsigned char minColor = min(rgbTmp.R, rgbTmp.G, rgbTmp.B);

	if(rgbTmp.R == rgbTmp.G && rgbTmp.G == rgbTmp.B){
		hsv.H = 0;
	}
	else{
		if(maxColor == rgbTmp.R){
			hsv.H = 60 * ((double)(rgbTmp.G - rgbTmp.B) / (maxColor - minColor));
		}
		else if(maxColor == rgbTmp.G){
			hsv.H = 60 * ((double)(rgbTmp.B - rgbTmp.R) / (maxColor - minColor)) + 120;
		}
		else if(maxColor == rgbTmp.B){
			hsv.H = 60 * ((double)(rgbTmp.R - rgbTmp.G) / (maxColor - minColor)) + 240;
		}
		else{
			printf("エラー\n");
		}

		if(hsv.H < 0 || hsv.H >= 360)
			hsv.H = roundAngle(hsv.H);
	}
	//後で外れ値丸める処理書いとけよ俺 <- 書いたぞ、俺

	hsv.S = (double)(maxColor - minColor) / maxColor * 100;
	hsv.V = (double)maxColor / 255 * 100;

	return hsv;
}

RGBColor HSV2RGB(struct HSVColor hsv){
	int max = hsv.V;
	int min = max - ((hsv.S/100.0)*max);
	RGBColor rgb;
	double r, g, b;

	double s = (double)hsv.S/100;
	double v = (double)hsv.V/100;

	int dh = hsv.H/60;
	double p = v * (1-s);
	double q = v * (1 - s*((double)hsv.H/60 - dh));
	double t = v * (1 - s*(1 - ((double)hsv.H/60 - dh)));

	switch(dh){
		case 0:
		    r = v;
			g = t;
			b = p;
			break;
        case 1:
		    r = q;
			g = v;
			b = p;
            break;
		case 2:
		    r = p;
			g = v;
			b = t;
			break;
		case 3:
		    r = p;
			g = q;
			b = v;
			break;
		case 4:
		    r = t;
			g = p;
			b = v;
			break;
        case 5:
		    r = v;
			g = p;
			b = q;
			break;
	}

	rgb.R = r*255;
	rgb.G = g*255;
	rgb.B = b*255;
	
	return rgb;
}

struct HSVColor maximizeSaturation(struct HSVColor hsv){
    hsv.S = 100;
    return hsv;
}


int min(int a, int b, int c)
{
	if(a < b){
		if(a < c) return a;
	}
	else{
		if(b < c) return b;
	}
	return c;
}

int max(int a, int b, int c)
{
	if(a > b){
		if(a > c) return a;
	}
	else{
		if(b > c) return b;
	}
	return c;
}

int roundAngle(int angle)
{
	if(angle < 0)
		return angle + 360;
	else if(angle >= 360)
		return angle - 360;
}
