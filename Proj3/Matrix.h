#ifndef MATRIX_H
#define MATRIX_H
#include <string>
#include <vector>
#include <cstdlib>
#include <map>

/*
 *  I'm using the assumption that this is not a directed graph!"
 */

class Matrix{
    private:
        int ** internal_matrix;
        int rowSize;
        int colSize;
        bool allocated;
        std::map<std::string, int> names; // makes for named value access
        std::map<int, std::string> keys; // reveerse map of names

    public:
        Matrix(int rSize, int cSize);
        Matrix();
        Matrix(const Matrix&);
        ~Matrix();
        int* operator[](int i){
            if (allocated)
                return internal_matrix[i];
            else 
                return NULL;
        }
        void operator=(const Matrix&);
       
        void addPair(std::string, int); 
        void allocate();
        void clear();
        int getRowSize();
        int getColSize();
        void fillMatrix(int value);
        int get(std::string, std::string);
        void set(std::string, std::string, int value);
        void set(const Matrix &);
        int getKey(std::string);
        std::string valueAtKey(int i);
};




#endif
