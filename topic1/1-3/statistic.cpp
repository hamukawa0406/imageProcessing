#include "ifstream_string.h"
#include "statistic.h"

Statistic::Statistic()
{
}

Statistic::Statistic(InctImage _img): img{_img}
{
    ave = calcAve();
    var = calcVar();
    max = calcMax();
    min = calcMin();
    med = calcMed();
    mode = calcMode();
    setHist();
}

double Statistic::calcAve(){
    double sum {};
    RGBColor trgb;
    for(int j = 0; j < img.getHeight(); j++){
        for(int i = 0; i < img.getWidth(); i++){
            trgb = img.getPnmPixel(i, j);
            sum += trgb.R;
        }
    }
    return sum / ((double)img.getWidth()*img.getHeight());
}

void Statistic::printHist(){

}

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


