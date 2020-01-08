#include "ifstream_string.h"
#include "statistic.h"
#include <map>
#include <iomanip>

Statistic::Statistic(InctImage& _img):
    img{_img},
    outname {"statistics.txt"}
{
    writing_file.open(outname, std::ios::out);
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
    setHist();
}

double Statistic::calcAve(double sum){
    return sum / sortedData.size();
}

double Statistic::calcVar(double sum){
    return sum - pow(ave, 2);
} 


void Statistic::setHist(){
    unsigned char preDens {0};
    int ichikaichou {(int)(256/hist.size())};
    int upperLim {ichikaichou};
    int i {};
    
    for(auto x : sortedData){
        while(x >= upperLim){
            ++i;
            upperLim += ichikaichou;
        }
        ++hist[i];
    }
}

void Statistic::outputStatistic(){

    writing_file << getAve() << std::endl;
    writing_file << getVar() << std::endl;
    writing_file << getMax() << std::endl;
    writing_file << getMin() << std::endl;
    writing_file << getMed() << std::endl;
    writing_file << getMode() << std::endl;
    printHist();
}

void Statistic::printHist(){
    int ichikaichou {256/(int)hist.size()};
    int classValue {ichikaichou / 2};
    int value {};
    int roughness {100};
    writing_file << "class value      frequency" << std::endl;

    for(auto x = 0; x < hist.size(); x++){
        int i = 0;
        writing_file << std::setw(7) << classValue << "     ";
        value = hist[x];
        while(value > 0){
            writing_file << '*';
            ++i;
            value -= roughness;
        }
        i = 0;
        classValue += ichikaichou;
        writing_file << std::endl;
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


