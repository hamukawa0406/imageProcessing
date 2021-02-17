#include<iostream>
#include<array>
#include "ifstream_string.h"

class filter {
    private:
        int select;
        int rank;
        static const int size {3};
        std::array<std::array<int, size>, size> filt; 
        std::array<std::array<const double, size>, size> static gaussian;
        std::array<std::array<const double, size>, size> static sharp; 
    public:
        InctImage srcImg;
        InctImage dstImg;
        filter(int inSelc);
        void setRank(int _rank);
        RGBColor filtering(int i, int j);
        RGBColor rankFilter(int i, int j);
        RGBColor medianFilter(int i, int j);
        RGBColor modeFilter(int i, int j);
        RGBColor gaussFilter(int i, int j);
        RGBColor sharpFilter(int i, int j);
        void areaSort(std::array<RGBColor, size*size> &arr, int i, int j);
        std::array<RGBColor, 9>::iterator __upper_bound(std::array<RGBColor, size*size>::iterator first, std::array<RGBColor, size*size>& arr,
                            unsigned char dens);
        
        

};