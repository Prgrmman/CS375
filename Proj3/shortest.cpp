#include <iostream>
#include <vector>
#include <climits>
#include <map>
#include "Matrix.h"


using namespace std;

void printMatrix(Matrix& m);
Matrix computeFloyd(Matrix dMatrix, Matrix & pMatrix, int cityCount);
int sumLarge(int a, int b);
void printPath(Matrix & pMatrix, int q, int r);

int main(){

    string cityNames[] = {"Toronto", "Kingston", "Montreal", "Buffalo", "Rochester", "Syracuse", "Albany", "Binghamton", "Scranton", "Allentown", "New York City"};

    int cityCount = 11; // how many cities there are
    Matrix matrix(cityCount,cityCount); // create matrix
    matrix.fillMatrix(INT_MAX); // initialize all values to infinity


    // establish map within the matrix
    for (int i = 0; i < cityCount; i++){
        matrix.addPair(cityNames[i], i);
    }


    // manually input transitions
    matrix.set("Kingston", "Toronto", 180);
    matrix.set("Kingston", "Montreal", 160);
    matrix.set("Montreal", "Albany", 130);
    matrix.set("Toronto", "Buffalo", 100);
    matrix.set("Buffalo", "Rochester", 60);
    matrix.set("Rochester", "Syracuse", 70);
    matrix.set("Kingston", "Syracuse", 65);
    matrix.set("Syracuse", "Albany", 100);
    matrix.set("Albany", "New York City", 140);
    matrix.set("New York City", "Binghamton", 180);
    matrix.set("New York City", "Scranton", 100);
    matrix.set("New York City", "Allentown", 70);
    matrix.set("Allentown", "Scranton", 65);
    matrix.set("Scranton", "Binghamton", 60);
    matrix.set("Binghamton", "Syracuse", 70);

    Matrix pMatrix = matrix;
    Matrix finished = computeFloyd(matrix,pMatrix, cityCount);
    cout << "Shortest distance between New York City and Toronto:" << endl;

    int key1 = matrix.getKey("New York City");
    int key2 = matrix.getKey("Toronto");
    cout << "New York City" << endl;
    printPath(pMatrix, key1, key2);
    cout << "Toronto" << endl;
    return 0;
}

// implement floyd's algorithm
// D is the series of adjacency arrays
// P is a matrix used to keep track of the shortest path
Matrix computeFloyd(Matrix dMatrix, Matrix & pMatrix, int cityCount){
    // initialize pMatrix
    pMatrix.fillMatrix(0);
    Matrix next = dMatrix; // necessary so as to copy internal maps
    for(int k = 0; k < cityCount; k++){
        for(int i = 0; i < cityCount; i++){

            for(int j =0; j < cityCount; j++){

                if(dMatrix[i][j] > sumLarge(dMatrix[i][k], dMatrix[k][j])){
                    next[i][j] = sumLarge(dMatrix[i][k], dMatrix[k][j]);
                    pMatrix[i][j] = k;
                }
                else
                    next[i][j] = dMatrix[i][j];
            }
        }
        dMatrix = next; // move next into dMatrix
    }
    return next;
}

void printPath(Matrix & pMatrix, int q, int r){
    if(pMatrix[q][r] != 0){
        printPath(pMatrix, q, pMatrix[q][r]);
        string city = pMatrix.valueAtKey(pMatrix[q][r]);
        cout << city << endl;
        printPath(pMatrix, pMatrix[q][r], r);
    }
    return;
}
int sumLarge(int a, int b){
    if (a == INT_MAX || b == INT_MAX)
        return INT_MAX;
    else
        return a+b;
}

//method prints matrix
void printMatrix(Matrix& m){
    for(int r = 0; r < m.getRowSize(); r++){
        for (int c = 0; c < m.getColSize(); c++){
            cout << m[r][c] << " ";
        }
        cout << endl;
    }
}
