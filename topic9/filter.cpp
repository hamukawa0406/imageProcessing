#include<iostream>
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


filter::filter(): select {5}, rank{5}, filt {}
{
}

RGBColor filter::filtering(InctImage *src, int i, int j){
    switch(select){
        case 1: //rank
            return rankFilter(src, i, j);
        case 2: //median
            return medianFilter(src, i, j);
        case 3: //mode
            return modeFilter(src, i, j);    
        case 4: //gaussian
            return gaussFilter(src, i, j);
        case 5: //sharp
            return sharpFilter(src, i, j);
    }
}
RGBColor filter::rankFilter(InctImage *src, int i, int j){
    std::array<RGBColor, size*size> rgbArr;
    areaSort(src, rgbArr, i, j);
    return rgbArr.at(rank);
}
RGBColor filter::medianFilter(InctImage *src, int i, int j){
    return rankFilter(src, i, j);
}

std::array<RGBColor, 9>::iterator filter::__upper_bound(std::array<RGBColor, size*size>::iterator first, std::array<RGBColor, size*size>::iterator second, unsigned char dens){
    auto next = first+1;
	for (auto itr = first; itr == next && next != second; itr++) {
		next = itr + 1;
    }
	return next;
}

RGBColor filter::modeFilter(InctImage *src, int i, int j){
    std::array<RGBColor, size*size> rgbArr;
    RGBColor mode;
    areaSort(src, rgbArr, i, j);
    int n{}, count {1};
    for(auto itr = std::adjacent_find(rgbArr.begin(), rgbArr.end(), [](const RGBColor& x, const RGBColor& y){return x.Dens == y.Dens;}),
            last = rgbArr.end(), next = rgbArr.end();
        itr != last;
    ){
        //std::cout << (int)itr->Dens << std::endl;
        //next = std::upper_bound(itr, last, itr->Dens, [](const RGBColor& x, const RGBColor& y){return x.Dens < y.Dens;});
        next = __upper_bound(itr, last, itr->Dens);
        count = std::distance(itr, next);
        if(n < count){
            n = count;
            mode = *itr;
        }
        itr = std::adjacent_find(next, last, [](const RGBColor& x, const RGBColor& y){return x.Dens == y.Dens;});
    }
    return mode;
}

void filter::areaSort(InctImage *src, std::array<RGBColor, size*size> &arr,int i, int j){
    RGBColor tRGB;
    auto itr = arr.begin();
    for(int y = 0; y < 3; y++){
        for(int x = 0; x < 3; x++){
            tRGB = src->getPnmPixel(i+x-1, j+y-1);
            *itr = tRGB;
            ++itr;
        }
    }
    std::sort(arr.begin(), arr.end(), 
              [](const RGBColor& x, const RGBColor& y)
              {return x.Dens < y.Dens;});
}

RGBColor filter::gaussFilter(InctImage *src, int i, int j){
    RGBColor tRGB;
    double dens {};
    double sumDens {};
    for(int y = 0; y < 3; y++){
        for(int x = 0; x < 3; x++){
            tRGB = src->getPnmPixel(i+x-1, j+y-1);
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

RGBColor filter::sharpFilter(InctImage *src, int i, int j){
    RGBColor tRGB;
    double dens {};
    double sumDens {};
    for(int y = 0; y < 3; y++){
        for(int x = 0; x < 3; x++){
            tRGB = src->getPnmPixel(i+x-1, j+y-1);
            dens = tRGB.Dens*sharp[x][y];
            sumDens += dens;
        }
    }
    return tRGB;
}

//*/