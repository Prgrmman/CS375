#ifndef MATRIX_H
#define MATRIX_H


class Matrix{
    private:
        double ** internal_matrix;
        void allocate(int n, int m);
        void deleteMatrix();
        bool isAllocated;

    public:
        // Fields
        int rows;
        int columns;
        // constructor / destruct
        Matrix(int n, int m);
        Matrix(const Matrix& m);
        ~Matrix();
        double* operator[](int n);
        //user funcntions

};

Matrix::Matrix(int n, int m)
{
    rows = n;
    columns = m;

    internal_matrix = new double*[n];
    for (int i = 0; i < n; i++)
        internal_matrix[i] = new double[m];
}

Matrix::Matrix(const Matrix& m)
{
    int r = m.rows;
    int c = m.columns;
    allocate(r,c);
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            internal_matrix[i][j] = m.internal_matrix[i][j];
        }
    }
}

Matrix::~Matrix()
{
    deleteMatrix();
}

double* Matrix::operator[](int n)
{
    return internal_matrix[n];

}

void Matrix::allocate(int n, int m){
    isAllocated = true;
    rows = n;
    columns = m;

    internal_matrix = new double*[n];
    for (int i = 0; i < n; i++)
        internal_matrix[i] = new double[m];
}

void Matrix::deleteMatrix()
{
    for(int i = 0; i < rows; i++)
        delete[] internal_matrix[i];
    delete[] internal_matrix;
    isAllocated = false;
}







#endif
