#include "ppmload.h"
#include<stdio.h>
#include<math.h>
#include<chrono>


//最近傍法    http://www7a.biglobe.ne.jp/~fairytale/article/program/graphics.html 参考
//線形補間法　　　http://www7a.biglobe.ne.jp/~fairytale/article/program/graphics.html 参考
//バイキュービック補間法　　<- 死ぬ

void sizeCvtBiCubic(struct ppmimg *src, struct ppmimg *dst, double scale);
unsigned char roundAngle(double angle);
double myAbs(double a);

char dstName[256] = {0};

int main(void){
	int i;
	unsigned char ave = 0;
	char inputTxt[256] = {0};
	double scaleBig = 2.7;
	double scaleSmall = 1/3.0;
	struct ppmimg *image1=NULL, *image2=NULL, *image3=NULL;
    std::chrono::system_clock::time_point start, end;

//	inputScale(&scale);
	
	sprintf(dstName, "sizeCvtNearestNeighbor");

	image1 = makeimagestruct(image1);
	image2 = makeimagestruct(image2);
	image3 = makeimagestruct(image3);
	loadppmimage("bike.ppm",image1);
	image2 = createppmimage(image2, (int)(image1->iwidth*scaleBig), (int)(image1->iheight*scaleBig),image1->cmode);
	image3 = createppmimage(image3, (int)(image1->iwidth*scaleSmall), (int)(image1->iheight*scaleSmall),image1->cmode);
    start = std::chrono::system_clock::now();
	sizeCvtBiCubic(image1, image2, scaleBig);
    end = std::chrono::system_clock::now();
	sizeCvtBiCubic(image1, image3, scaleSmall);

    double time = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0);
    printf("time %f[ms]\n", time);

	deleteppmimg(image1);
	deleteppmimg(image2);
	deleteppmimg(image3);

	return 0;
}

void sizeCvtBiCubic(struct ppmimg *src, struct ppmimg *dst, double scale){
    int a = -1.5;
	char _dstName[256];
	sprintf(_dstName, dstName);

	// 使い回す変数は最初に処理しておく
	double parameter[5] = {0};
	parameter[0] = a + 3.0;
	parameter[1] = a + 2.0;
	parameter[2] = -a*4.0;
	parameter[3] = a*8.0;
	parameter[4] = a*5.0;

	for (int y = 0; y < dst->iheight; y++) {
        for (int x = 0; x < dst->iwidth; x++) {
            // 元画像における画素の対応する場所
            double x0 = x/scale;
            double y0 = y/scale;
            
            // 基点とする画素
            int xBase = (int)x0;
            int yBase = (int)y0;
                
            int color = 0;  // 補間する画素

            struct RGBColor color_element;
            color_element.R = 0;
            color_element.G = 0;
            color_element.B = 0;
            
                
            // バイキュービックの処理範囲
            if (xBase >= 1 && xBase < src->iwidth - 2 && yBase >= 1 && yBase < src->iheight - 2) {
                       
                // 基点の周辺16画素を取得して処理
                for (int j = -1; j <= 2; j++) {
                    for (int i = -1; i <= 2; i++) {
                        // 実際に処理する画素を設定
                        int xCurrent = xBase + i;
                        int yCurrent = yBase + j;
                                        
                        // 距離決定
                        double distX = myAbs(xCurrent - x0);
                        double distY = myAbs(yCurrent - y0);
                                        
                        // 重み付け
                        double weight = 0.0;  // 重み変数
                                        
                        // まずはX座標の距離で重みを設定
    	                // 1以下、2以下のとき、それぞれ重み付け
                        if (distX <= 1.0) {
                            weight = (1.0 - parameter[0]*distX*distX + parameter[1]*distX*distX*distX);
                        }
						else if (distX <= 2.0) {
                            weight = (parameter[2] + parameter[3]*distX - parameter[4]*distX*distX + a*distX*distX*distX);
                        }
						else {
                            continue;  // 何も処理しないので、次のループへ
                        }
                                        
                        // Y座標の距離で重みを設定
                        if (distY <= 1.0) {
                            weight *= (1.0 - parameter[0]*distY*distY + parameter[1]*distY*distY*distY);
                        }
						else if (distY <= 2.0) {
                            weight *= (parameter[2] + parameter[3]*distY - parameter[4]*distY*distY + a*distY*distY*distY);
                        }
						else {
                            continue;
                        }
                    //    printf("%f ", weight);
                                        
                        // 実際に画素を取得
                        struct RGBColor color_process = getPnmPixel(src, xCurrent, yCurrent);
                                        
                        // 画素をRGB分割し、重みをかけて足し合わせる
                        color_element.R = roundAngle(color_element.R + color_process.R*weight);
                        color_element.G = roundAngle(color_element.G + color_process.G*weight);
                        color_element.B = roundAngle(color_element.B + color_process.B*weight);
                    }
                 //   putchar('\n');
                }
                //putchar('\n');
            }
                
        	setPnmPixel(dst, x, y, color_element);

        }
	}

	if(scale >= 1){
	    sprintf(dstName, "%sBig.ppm", _dstName);
	}
	else
	    sprintf(dstName, "%sSmall.ppm", _dstName);
	
	saveppmimage(dst, dstName);
	sprintf(dstName, _dstName);
}

unsigned char roundAngle(double angle)
{
	if(angle < 0)
		return 0;
	else if(angle >= 256)
        return 255;
    else (unsigned char)angle;
}

double myAbs(double a){
    return (a >= 0) ? a : (-1)*a;
}
