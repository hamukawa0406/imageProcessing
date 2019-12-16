#include "ifstream_string.h"
#include "filter.h"


filter::filter(): select {1}, rank{5}
{
}

RGBColor filter::filtering(InctImage *src, int i, int j){
    RGBColor tRGB;
    RGBColor tRGB[size*size];
    int i {};
    for(int y = 0; y < size; y++){
        for(int x = 0; x < size; x++){
            tRGB = src->getPnmPixel(i + x, j + y);
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
    }



}
