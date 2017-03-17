#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include "Matrix.h"

// Type definitions
typedef struct{
    double x;
    double y;
}solution_pair;

// prototypes
void gaussElim(Matrix& matrix);
void reduce(Matrix& matrix);
void printMatrix(Matrix& matrix);
void createMatrix(double arr1[3], double arr2[3], Matrix& matrix);
void subtract(Matrix& matrix, int r1, int r2);
solution_pair solve(double arr1[3], double arr2[3]);
void factor(double arr[3], double factor);
bool solutionFeasible(solution_pair sol, double constraints[3][3]);
solution_pair minObjective(std::vector<solution_pair>& solutions, double obj[2]);

using namespace std;

/*
 * objective: 
 * z = 0.12*x + 0.15 * y
 * 
 * constraints:
 * 60*x + 60 *y >= 300
 * 12*x + 6*y >= 36
 * 10*x + 30*y >= 90
 */

int main()
{
    double constraints[][3] = {
        {60,60,300},
        {12,6,36},
        {10,30,90}
    }; 
    double objective[] = {0.12, 0.15};

    vector<solution_pair> feasibleSolutions;
    for(int i = 0; i < 3; i++){
        for (int j = i+1; j < 3; j++){
            solution_pair sol = solve(constraints[i], constraints[j]);
            if (solutionFeasible(sol, constraints))
                feasibleSolutions.push_back(sol);
        }

    } 
    if (feasibleSolutions.size() == 0)
        cout << "There are no solutions!" << endl;
    else{
        solution_pair sol = minObjective(feasibleSolutions, objective);
        double value = sol.x * objective[0] + sol.y * objective[1];
        cout << "Drink " << sol.x << " cup(s) of drink X and " << sol.y
           << " cup(s) of drink Y for a cost of $" << value << endl;
    }
    return 0;

}
/*
 * uses enumeration method to find min solution
 */
solution_pair minObjective(vector<solution_pair>& solutions, double obj[2])
{
    solution_pair* ptr = &solutions[0];
    double min = ptr->x * obj[0] + ptr->y * obj[1];
    for(int i =1; i < solutions.size(); i++){
        double value = solutions[i].x * obj[0] + solutions[i].y * obj[1];
        if (value < min){
            min = value;
            ptr = &solutions[i];
        }
    }
    return *ptr;
}
/*
 * returns the solution to a system of 2 linear equations
 * the assumption is that they are solvable
 */
solution_pair solve(double arr1[3], double arr2[3])
{
    Matrix matrix(2,3);   
    createMatrix(arr1, arr2, matrix);
    gaussElim(matrix);
    reduce(matrix);

    double ratio = matrix[0][1] / matrix[1][1];
    factor(matrix[1], ratio);
    subtract(matrix,0,1);
    factor(matrix[1], 1/ratio);

    reduce(matrix);
    solution_pair sol = {matrix[0][2], matrix[1][2]};
    return sol;
}
/*
 * returns true if the solution is feasible within the contraints
 * all contraints are in the form >=
 */
bool solutionFeasible(solution_pair sol, double constraints[3][3])
{
    for (int i = 0; i < 3; i++){
        double value = sol.x * constraints[i][0] + sol.y * constraints[i][1];
        if (value < constraints[i][2])
            return false;
    }
    return true;

}

/*
 * performs gaussian elimination on matrix m
 * code taken from www.cs.rutgers.edu
 */
void gaussElim(Matrix& matrix)
{
    int n = matrix.rows;
    int m = matrix.columns;
    for (int i = 0; i < n-1; i++){
        for (int j = i+1; j < n; j++){
            double ratio = matrix[j][i] / matrix[i][i];
            for (int k = i; k < m; k++){
                matrix[j][k] -= (ratio * matrix[i][k]);
            }
        }
    }
}

/*
 * divide each row by first non zero term in that row.
 */
void reduce(Matrix& matrix)
{
    int n = matrix.rows;
    int m = matrix.columns;
    double factor = 1;
    for(int i = 0; i < n; i++){
        bool foundFactor = false;
        for(int j = 0; j < m; j++){
            if (matrix[i][j] != 0 && !foundFactor){
                factor = matrix[i][j];
                foundFactor = true;
            }
            matrix[i][j] /= factor;
        }
    }
}
/*
 * substract r2 from r1
 */
void subtract(Matrix& matrix, int r1, int r2)
{
    for(int i = 0; i < matrix.columns; i++)
        matrix[r1][i] -= matrix[r2][i];
}

/*
 * multiplies all values in array by factor
 */
void factor(double arr[3], double factor)
{
    for(int i = 0; i < 3; i++){
        arr[i] *= factor;
    }
}
/*
 * assigns the first two rows of a matrix
 */
void createMatrix(double arr1[3], double arr2[3], Matrix& matrix)
{
    memcpy(matrix[0], arr1, 3 * sizeof(double));
    memcpy(matrix[1], arr2, 3 * sizeof(double));
}


void printMatrix(Matrix& matrix)
{
    int n = matrix.rows;
    int m = matrix.columns;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
