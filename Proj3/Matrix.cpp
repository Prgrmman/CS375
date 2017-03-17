#include "Matrix.h"
#include <iterator>
#include <iostream>

using namespace std;


Matrix::Matrix(){
    allocated = false;
}
// constructor
Matrix::Matrix(int rsize, int csize){
    rowSize = rsize;
    colSize = csize;
    allocate();
}
Matrix::~Matrix(){
    clear();
}
// copy constructor
Matrix::Matrix(const Matrix& matrix){
    // reallocate if different dimensions
    rowSize = matrix.rowSize;
    colSize = matrix.colSize;
    allocate();
    // copy values
    for (int r = 0; r < rowSize; r++)
        for (int c = 0; c < colSize; c++)
            internal_matrix[r][c] = matrix.internal_matrix[r][c];
    //copy map
    names = matrix.names;
    keys = matrix.keys;
}

void Matrix::operator=(const Matrix& matrix){
    set(matrix);
    allocated = true;
    //copy map
    names = matrix.names;
    keys = matrix.keys;
}
// Methods for Matrix class
void Matrix::allocate(){
    internal_matrix = (int**)malloc(sizeof(int *) * rowSize); // allocate rows
    for(int i = 0; i < rowSize; i++)
        internal_matrix[i] = (int*)malloc(sizeof(int) * colSize); // allocate columns
    allocated = true;
}
//method to delete adjMatrix
void Matrix::clear(){
    for(int i = 0; i < rowSize; i++)
        free(internal_matrix[i]);
    free(internal_matrix);
    allocated = false;
}
//fills every entry with value
void Matrix::fillMatrix(int value){
    for (int r = 0; r < rowSize; r++)
        for(int c = 0; c < colSize; c++)
            internal_matrix[r][c] = value;
}
//methods do add keys into matrix
void Matrix::addPair(string key, int value){
    names.insert(make_pair(key, value));
    keys.insert(make_pair(value, key));
}
// accessor methods
int Matrix::getRowSize(){return rowSize;}
int Matrix::getColSize(){return colSize;}

// allows for matrix to be accessed by named pairs
int Matrix::get(string key1, string key2){
    int i = names.at(key1);
    int j = names.at(key2);
    return internal_matrix[i][j];
}

//allows to set named pairs
void Matrix::set(string key1, string key2, int value){
    int i = names.at(key1);
    int j = names.at(key2);
    // assuming not a digraph
    internal_matrix[i][j] = value;
    internal_matrix[j][i] = value;
}

// setts matrix to another matrix
// NOTE: they must have the same dimensions
void Matrix::set(const Matrix& matrix){
    int r = matrix.rowSize;
    int c = matrix.colSize;
    for(int i = 0; i < r; i++)
        for(int j = 0; j < c; j++)
            internal_matrix[i][j] = matrix.internal_matrix[i][j];

}
int Matrix::getKey(string key){
    return names.at(key);
}

string Matrix::valueAtKey(int i){
    return keys.at(i);

}
