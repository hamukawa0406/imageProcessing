#include<iostream>
#include<iterator>
#include<array>
#include <algorithm>
#include "ifstream_string.h"
#include "filter.h"

std::array<std::array<const double, filter::size>, filter::size>  filter::gaussian {{
            {0.0625, 0.125, 0.0625},
            {0.125, 0.25, 0.125},
            {0.0625, 0.125, 0.0625}
}};

std::array<std::array<const double, filter::size>, filter::size>  filter::sharp {{
            {0, -1, 0},
            {-1, 5, -1},
            {0, -1, 0}
}};



filter::filter(int inSelc) : select{ inSelc }, rank{}, filt{}
{
    int inRank;
    switch(select){
        case 1:
            srcImg.loadppmimage("inussg.pgm");
			dstImg = InctImage(srcImg.getWidth(), srcImg.getHeight(), srcImg.getDepth(), srcImg.getImageMode());
            dstImg.setFileName("rank.pgm");
            do{
                std::cout << "ランク値(0~8):" << std::endl;
                std::cin >> inRank;
            }while(inRank < 0 && inRank >= 9);
            setRank(inRank);
            break;
        case 2:
            srcImg.loadppmimage("inunoise.pgm");
			dstImg = InctImage(srcImg.getWidth(), srcImg.getHeight(), srcImg.getDepth(), srcImg.getImageMode());
            dstImg.setFileName("median.pgm");
            setRank(5);
            break;
        case 3:
            srcImg.loadppmimage("inussg.pgm");
			dstImg = InctImage(srcImg.getWidth(), srcImg.getHeight(), srcImg.getDepth(), srcImg.getImageMode());
            dstImg.setFileName("mode.pgm");
            break;
        case 4:
            srcImg.loadppmimage("inussg.pgm");
			dstImg = InctImage(srcImg.getWidth(), srcImg.getHeight(), srcImg.getDepth(), srcImg.getImageMode());
            dstImg.setFileName("gaussian.pgm");
            break;
        case 5:
            srcImg.loadppmimage("inussg.pgm");
			dstImg = InctImage(srcImg.getWidth(), srcImg.getHeight(), srcImg.getDepth(), srcImg.getImageMode());
            dstImg.setFileName("shapen.pgm");
            break;
    }
}

void filter::setRank(int _rank){
    rank = _rank;
}

RGBColor filter::filtering(int i, int j){
    switch(select){
        case 1: //rank
            return rankFilter(i, j);
        case 2: //median
            return medianFilter(i, j);
        case 3: //mode
            return modeFilter(i, j);    
        case 4: //gaussian
            return gaussFilter(i, j);
        case 5: //sharp
            return sharpFilter(i, j);
    }
}
RGBColor filter::rankFilter(int i, int j){
    std::array<RGBColor, size*size> rgbArr;
    areaSort(rgbArr, i, j);
    return rgbArr.at(rank);
}
RGBColor filter::medianFilter(int i, int j){
    return rankFilter(i, j);
}

std::array<RGBColor, 9>::iterator filter::__upper_bound(std::array<RGBColor, size*size>::iterator first, std::array<RGBColor, size*size> &arr, unsigned char dens){
	auto itr = first;
	for (; std::next(itr, 1) != arr.end() && itr->Dens == std::next(itr, 1)->Dens; itr++) {
		if (std::next(itr, 1) == arr.end()) return arr.end();
	}
    return std::next(itr, 1);
}

RGBColor filter::modeFilter(int i, int j){
    std::array<RGBColor, size*size> rgbArr;
    areaSort(rgbArr, i, j);
	RGBColor mode{ rgbArr.at((int)size * size / 2 + 1) };
    int n{}, count {};
    for(auto itr = std::adjacent_find(rgbArr.begin(), rgbArr.end(), [](const RGBColor& x, const RGBColor& y){return x.Dens == y.Dens;}),
            last = rgbArr.end(), next = rgbArr.end();
        itr != last;
    ){
        //std::cout << (int)itr->Dens << std::endl;
        //next = std::upper_bound(itr, last, itr->Dens, [](const RGBColor& x, const RGBColor& y){return x.Dens < y.Dens;});

		next = __upper_bound(itr, rgbArr, itr->Dens);
        count = std::distance(itr, next);
        if(n < count){
            n = count;
            mode = *itr;

//            std::cout << "mode n " << (int)mode.Dens << " " << n << std::endl;
        }
        itr = std::adjacent_find(next, last, [](const RGBColor& x, const RGBColor& y){return x.Dens == y.Dens;});
    }
    return mode;
}

void filter::areaSort(std::array<RGBColor, size*size> &arr,int i, int j){
    RGBColor tRGB;
    auto itr = arr.begin();
    for(int y = 0; y < 3; y++){
        for(int x = 0; x < 3; x++){
            tRGB = srcImg.getPnmPixel(i+x-1, j+y-1);
            *itr = tRGB;
//			std::cout << (int)itr->Dens << " ";
            ++itr;
        }
//		std::cout << std::endl;
    }
    std::sort(arr.begin(), arr.end(), 
              [](const RGBColor& x, const RGBColor& y)
              {return x.Dens < y.Dens;});
}

RGBColor filter::gaussFilter(int i, int j){
    RGBColor tRGB;
    double dens {};
    double sumDens {};
    for(int y = 0; y < 3; y++){
        for(int x = 0; x < 3; x++){
            tRGB = srcImg.getPnmPixel(i+x-1, j+y-1);
            dens = (double)tRGB.Dens*gaussian[x][y];
            sumDens += dens;
//            std::cout << gaussian[x][y] << std::endl;
        }
    }
    if(sumDens > 255) tRGB.Dens = 255;
    else if(sumDens <0) tRGB.Dens = 0;
    else tRGB.Dens = sumDens;
//    std::cout << "tRGB.Dens " << sumDens << std::endl;
    return tRGB;
}

RGBColor filter::sharpFilter(int i, int j){
    RGBColor tRGB;
    double dens {};
    double sumDens {};
    for(int y = 0; y < 3; y++){
        for(int x = 0; x < 3; x++){
            tRGB = srcImg.getPnmPixel(i+x-1, j+y-1);
            dens = tRGB.Dens*sharp[x][y];
            sumDens += dens;
        }
    }
	if (sumDens > 255) tRGB.Dens = 255;
	else if (sumDens < 0) tRGB.Dens = 0;
	else tRGB.Dens = sumDens;
    return tRGB;
}

//*/