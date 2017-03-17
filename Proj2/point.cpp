#include <math.h>
#include "point.h"



double square(double n){
    return n*n;
}
double distance(point_t p1, point_t p2){
    int x1 = p1.x;
    int x2 = p2.x;
    int y1 = p1.y;
    int y2 = p2.y;
    return sqrt(square(x1-x2) + square(y1-y2));

}
