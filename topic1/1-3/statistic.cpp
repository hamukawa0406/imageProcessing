#include "ifstream_string.h"
#include "statistic.h"
#include <map>

Statistic::Statistic(InctImage& _img):
    img{_img}
{
    int count {};
    RGBColor trgb;
    sortedData.resize(img.getWidth()*img.getHeight());
    for(int j = 0; j < img.getHeight(); j++){
        for(int i = 0; i < img.getWidth(); i++){
            trgb = img.getPnmPixel(i, j);
            sortedData[count] = trgb.R;
            ++count;
        }
    }
    std::sort(sortedData.begin(), sortedData.end());
    setStatistic();
}

void Statistic::setStatistic(){
    double sum {};
    double powSum {};
    int count {};
    int cMax {};
    unsigned char preDens {};
    for(auto x : sortedData){
        sum += x;
        powSum += pow(x, 2);
        if(x == preDens){
            ++count;
        }
        else if(count > cMax){
            mode = preDens;
            cMax = count;
            count = 1;
        }
        else{
            count = 1;
        }
        preDens = x;
    }
    ave = calcAve(sum);
    var = calcVar(powSum);
    min = sortedData.front();
    max = sortedData.back();
    med = sortedData.at(sortedData.size() / 2);
    setHist(hist.size());
}

double Statistic::calcAve(double sum){
    return sum / sortedData.size();
}

double Statistic::calcVar(double sum){
    return sum - pow(ave, 2);
} 


void Statistic::setHist(unsigned int kaichou){
    unsigned char preDens {0};
    int ichikaichou = (int)(256/kaichou);
    int upperLim {ichikaichou};
    int i {};
    
    for(auto x : sortedData){
        if(x < upperLim){
            ++hist[i];
        }
        else{
            ++i;
            upperLim += ichikaichou;
        }
    }
}


void Statistic::printHist(){
    for(auto x: hist){
        std::cout << std::endl;
    }
}
//*/
double Statistic::getAve(){
    return ave;
}
double Statistic::getVar(){
    return var;
}
double Statistic::getMax(){
    return max;
}
double Statistic::getMin(){
    return min;
}
double Statistic::getMed(){
    return med;
}

double Statistic::getMode(){
    return mode;
}


