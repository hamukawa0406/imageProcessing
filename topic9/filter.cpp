#include<iostream>
#include<array>
#include <algorithm>
#include "ifstream_string.h"
#include "filter.h"


filter::filter(): select {3}, rank{5}, filt {}
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
        /*
        case 4: //gaussian
            return gaussFilter(src, i, j);
        case 5: //sharp
            return sharpFilter(src, i, j);
        //*/
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
            tRGB = src->getPnmPixel(i+x-1, j+x-1);
            *itr = tRGB;
            ++itr;
        }
    }
    std::sort(arr.begin(), arr.end(), 
              [](const RGBColor& x, const RGBColor& y)
              {return x.Dens < y.Dens;});
}
//*/