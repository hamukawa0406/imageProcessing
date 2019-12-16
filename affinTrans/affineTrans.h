#define _USE_MATH_DEFINES
#include<iostream>
#include<cmath>

struct point {
    int x {0};
    int y {0};
};

struct pointD {
    double x {0};
    double y {0};
};

class affineTrans {
    private:
        struct point pt; 
        const struct pointD scale;
        const double rotate; //弧度法
        const struct point paraTrans;
        double a, b, c, d, e, f;
    public:
        affineTrans();
		affineTrans(struct pointD s, double r, struct point p);
        struct point getSrcPoint(const struct point _pt, const struct point srcImgSize);
};