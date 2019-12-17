#include<iostream>
#include<array>
#include "ifstream_string.h"

class filter {
    private:
        int select;
        int rank;
        static const int size {3};
        //InctImage srcImg;
        std::array<std::array<int, size>, size> filt; 
        std::array<std::array<const double, size>, size> static gaussian;
        std::array<std::array<const double, size>, size> static sharp; 
    public:
        filter();
        filter(int);
        int getFilter(int i, int j);
        RGBColor filtering(InctImage *src, int i, int j);
        RGBColor rankFilter(InctImage *src, int i, int j);
        RGBColor medianFilter(InctImage *src, int i, int j);
        RGBColor modeFilter(InctImage *src, int i, int j);
        RGBColor gaussFilter(InctImage *src, int i, int j);
        RGBColor sharpFilter(InctImage *src, int i, int j);
        int calcFilter(int x, int y);
        void areaSort(InctImage *src, std::array<RGBColor, size*size> &arr, int i, int j);
        std::array<RGBColor, 9>::iterator __upper_bound(std::array<RGBColor, size*size>::iterator first, std::array<RGBColor, size*size>::iterator second,
                            unsigned char dens);
        
        

};