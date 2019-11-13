#include "ifstream_string.h"
#include "affineTrans.h"

int main(void){
		InctImage* image1 = new InctImage();

		try{
			image1->loadppmimage("Lenna.ppm");
		}
		catch(string str){
			cout << str << endl;
		}

		InctImage afterImage { InctImage(image1->getWidth(), image1->getHeight(), image1->getDepth(), image1->getImageMode()) };

		
        struct pointD pA {0};
		double angle  {0.0};
		struct point pC {0};

		std::cout << "x方向の倍率 ";
		std::cin >> pA.x;
		std::cout << "y方向の倍率 ";
		std::cin >> pA.y;
		std::cout << "回転角度(360度) ";
		std::cin >> angle;
		std::cout << "x方向の平行移動 ";
		std::cin >> pC.x;
		std::cout << "y方向の平行移動 ";
		std::cin >> pC.y;

		angle = angle * M_PI / 180;
		std::cout << angle;

		affineTrans aff  {affineTrans(pA, angle, pC)};

		struct point srcImgSize {image1->getWidth(), image1->getHeight()};

		for (int j = 0; j<image1->getHeight(); j++){
			for (int i = 0; i<image1->getWidth(); i++){

				RGBColor inRGB;
				struct point pp {i, j};
				struct point pa {aff.getSrcPoint(pp, srcImgSize)};

				if (pa.x >= 0 && pa.x < image1->getWidth() && pa.y >= 0 && pa.y < image1->getHeight()){
					inRGB = image1->getPnmPixel(pa.x, pa.y);

				} 
				else{
					inRGB = {0, 0, 0};
				}
//			    std::cout << pa.x << " " << pa.y << endl; //" " << inRGB.R << " " << inRGB.G << " " << inRGB.B << std::endl;

				
				afterImage.setPnmPixel(i, j, inRGB);
			}
		}
		afterImage.savePnmImage("affineTrans.ppm");

		image1->ReleaseImage();
		afterImage.ReleaseImage();

	return 0;
}