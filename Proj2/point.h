#ifndef POINT_H
#define POINT_H

typedef  struct Point{
    double x, y;
    int index;

}point_t;

typedef struct pair{
    point_t p1, p2;
} pair_t;

double square(double n);
double distance(point_t p1, point_t p2);

#endif
