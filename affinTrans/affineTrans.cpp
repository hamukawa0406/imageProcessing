#include "affineTrans.h"

affineTrans::affineTrans():
    scale {0},
    rotate {0},
    paraTrans {0}
{
    a = scale.x*cos(rotate);
    b = -1*scale.x*sin(rotate);
    c = paraTrans.x;
    d = scale.y*sin(rotate);
    e = scale.y*cos(rotate);
    f = paraTrans.y;
}


affineTrans::affineTrans(struct pointD s, double r, struct point p):
    scale {s},
    rotate {r},
    paraTrans {p}
{
    a = scale.x*cos(rotate);
    b = -1*scale.x*sin(rotate);
    c = paraTrans.x;
    d = scale.y*sin(rotate);
    e = scale.y*cos(rotate);
    f = paraTrans.y;
}

struct point affineTrans::getSrcPoint(const struct point p, const struct point srcImageSize){
    struct point srcP {0, 0};
    struct point dstImgSize {srcImageSize.x / 2, srcImageSize.y / 2};
    srcP.x = (int)((scale.y*cos(rotate)*p.x + sin(rotate)*p.y
                   - (paraTrans.x + dstImgSize.x)*scale.y*cos(rotate) - (paraTrans.y + dstImgSize.y)*sin(rotate) + dstImgSize.x)
                  / (scale.x*scale.y*cos(rotate)*cos(rotate) + sin(rotate)*sin(rotate)));
    //(int)(((double)e*p.x - b*p.y + b*f - c*e)/(a*e - b*d));
    srcP.y = (int)(((-1)*sin(rotate)*p.x + scale.x*cos(rotate)*p.y
                  + (paraTrans.y - dstImgSize.y)*scale.x*cos(rotate) + (dstImgSize.x - paraTrans.x)*sin(rotate) + dstImgSize.y)
                  / (scale.x*scale.y*cos(rotate)*cos(rotate) + sin(rotate)*sin(rotate))) ;
    //(int)(((double)-1*d*p.x + a*p.y + c*d - a*f)/(a*e - b*d));
    return srcP;
}