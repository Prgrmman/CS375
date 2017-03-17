#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <float.h>
#include "point.h"
#include "timer.h"


using namespace std;

void readFile(string name, Point* points);
int numPoints(string filename);

pair_t bruteForce(point_t* points, int n);
pair_t divideAndConquer(point_t* points, int low, int high);

void sortByX(point_t* points, int start, int end);
void sortByY(point_t* points, int start, int end);
pair_t closestInStrip(point_t* points, int size, double dist);

int main(int argc, char* argv[]){
    // let's read what the arguments are
    if (argc != 3){
        cerr << "Expected <command> <input file> <output file>" << endl;
        return 0;
    }
    string inputName = argv[1];
    string outputName = argv[2];
    int size = numPoints(inputName);
    if (size == 0){
        cout << "empty file" << endl;
        return 0;
    }
    if (size == 1 ){
        cout << "Not enough points" << endl;
        return 0;
    }
    point_t* points;
    points = new point_t[size];
    readFile(inputName, points);

    Timer timer;

    timer.start();
    pair_t pair = bruteForce(points, size);
    timer.stop();
    cout << "Time for bruteForce: " << timer.getElapsed() << endl;

    timer.start(); // reset the timer
    pair = divideAndConquer(points, 0, size-1);
    timer.stop();

    cout << "Time for divideAndConquer approach: " << timer.getElapsed() << endl;

    //write the result to file
    fstream file;
    file.open(outputName.c_str(), ios::out);
    file << pair.p1.index << " " << pair.p2.index << " " << distance(pair.p1, pair.p2);
    cout << distance(pair.p1, pair.p2) << endl;
    file.close();

    delete [] points;
    return 0;

}



// read point data from file specified by string and populate point vector
// I don't know the input format, so I'm going to write the real function later
void readFile(string name, point_t *points){
    fstream file;
    file.open(name.c_str(), ios::in);
    string line;
    double x, y;
    int i = 0;
    while(getline(file,line)){
        stringstream ss;
        ss << line;
        ss >> x >> y;
        point_t point = {x,y,i};
        points[i] = point;
        i++;
    }
    file.close();
    return;
}
int numPoints(string filename){
    fstream file;
    file.open(filename.c_str());
    string line;
    int i = 0;
    while(getline(file, line))
        i++;
    file.close();
    return i;

}

// returns an array of the two closest points
pair_t bruteForce(point_t* points, int n){
    point_t p1 = {-1,-1,-1}; // index of -1 means point does not exist
    point_t p2 = {-1,-1,-1};
    if (n < 2)
        return {p1,p2};
    double min = DBL_MAX; // set intial min to infinity
    pair_t pair;
    pair.p1 = points[0];
    for(int i = 0; i < n; i++){
        point_t p1 = points[i];
        for (int j = i+1; j < n; j++){
            point_t p2 = points[j];
            if (distance(p1,p2) < min){
                min = distance(p1,p2);
                pair.p1 = p1;
                pair.p2 = p2;
            }
        }
    }
    return pair;

}

pair_t divideAndConquer(point_t* points, int low, int high){
    // base case
    int size = high - low + 1;
    if (size <= 3)
        return bruteForce(points, size);
    sortByX(points,low,high); // sort points by x to make vertical line down the center
    int middle = (low + high) / 2;
    point_t point = points[middle]; // the midpoint


    pair_t lpair = divideAndConquer(points, low, middle);
    pair_t rpair = divideAndConquer(points, middle+1, high);

    double distL = distance(lpair.p1, lpair.p2);
    double distR = distance(rpair.p1, rpair.p2);

    if (lpair.p1.index == -1){
        // no distance on the left
        distL = DBL_MAX;
    }
    if (rpair.p1.index == -1){
        // no distance on the right
        distR = DBL_MAX;
    }
    pair_t minpair;


    double distance;

    if (distL < distR){
        distance = distL;
        minpair = lpair;

    }
    else{
        distance = distR;
        minpair = rpair;
    }

    // populate the middle strip
    point_t strip[size];
    int n = 0;
    for (int i = low; i < size; i++){
        if (abs(points[i].x - point.x) < distance){
            strip[n++] = points[i];
        }
    }
    pair_t spair;
    if (n == 0){
        return minpair;
    }
    sortByY(strip, 0, n-1);
    spair = closestInStrip(strip, n, distance);

    // determine if the strip distance is less than the left of right
    if (spair.p2.index != -1){
        return spair;
    }
    else{
        return minpair;


    }

}



// sorts given range by x coordinate
void sortByX(point_t* points, int start, int end){
    sort(&points[start], &points[end], [](point_t p1, point_t p2){
            return p1.x < p2.x;
            }
        );
}
// sorts given range by y coordinate
void sortByY(point_t* points, int start, int end){
    sort(&points[start], &points[end], [](point_t p1, point_t p2){
            return p1.y < p2.y;
            }
        );
}

//returns a pair of points that are closest in the strip,
//returns null if the distance between those points is greater than dist
pair_t closestInStrip(point_t* points, int size, double dist){
    pair_t pair;
    pair.p1 = {-1,-1,-1};
    pair.p2 = {-1,-1,-1}; // if the second pair remains like this, then we didn't find smaller
    for (int i = 0; i < size; i++){
        point_t p1 = points[i];
        for(int j = i+1; j < size && (points[j].y - p1.y) < dist; j++){
            point_t p2 = points[j];
            if (distance(p1,p2) < dist){
                dist = distance(p1,p2);
                pair.p1 = p1;
                pair.p2 = p2;
            }
        }


    }
    return pair;
}
