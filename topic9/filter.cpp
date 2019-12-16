#include <algorithm>
#include "ifstream_string.h"
#include "filter.h"


filter::filter(): select {1}, rank{5}
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

void filter::areaSort(InctImage *src, std::array<RGBColor, size*size> &arr,int i, int j){
    RGBColor tRGB;
    RGBColor *rgbP = arr.begin();
    for(int y = 0; y < 3; y++){
        for(int x = 0; x < 3; x++){
            tRGB = src->getPnmPixel(i+x-1, j+x-1);
            *(rgbP) = tRGB;
            ++rgbP;
        }
    }
    std::sort(arr.begin(), arr.end());
}