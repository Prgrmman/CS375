#include <iostream>
#include <vector>
#include <string>
#include <algorithm>



using namespace std;

/*
 * type definitions
 */
enum Arrow{LESS_I, LESS_J, LESS_K, DIAG, NONE};

typedef struct{
    int value;
    Arrow arrow;
}value_t;

typedef vector<vector<vector<value_t>>> matrix;

/*
 * function prototypes
 */
void printValue(value_t value);
string findLCS(matrix values, vector<string> strings);
void lcs_length(matrix & values, vector<string> strings);
void initTable(matrix & m, int x, int y, int z);
void printTable(matrix &);
int max(int a, int b, int c);

int main(){

    // pad strings with an initial space
    vector<string> inputs = {" 6541254939322816220209974565477289648317", " 3142522751761601737419090933147067701840", " 2807030561290354259513570160162463275171"};
    int xLength = inputs[0].length();
    int yLength = inputs[1].length();
    int zLength = inputs[2].length();

    matrix table;
    initTable(table, xLength, yLength, zLength);
    lcs_length(table, inputs);

    string result = findLCS(table,inputs);
    reverse(result.begin(), result.end());
    cout << "Result: " << result << endl;

    return 0;
}
// traverses table to generate the longest common sequence
string findLCS(matrix values, vector<string> strings){
    //we need to traverse table starting form the bottom corner
    int i = strings[0].length() -1;
    int j = strings[1].length() -1;
    int k = strings[2].length() -1;
    string result = "";
    while(i > 0 && j > 0 && k > 0){
        if (values[i][j][k].arrow == DIAG){
            if (strings[0].at(i) != ' ')
                result += strings[0].at(i);
            cout << strings[0].at(i) << endl;
            i--;
            j--;
            k--;
        }
        else if(values[i][j][k].arrow == LESS_I)
            i--;
        else if(values[i][j][k].arrow == LESS_J)
            j--;
        else if(values[i][j][k].arrow == LESS_K)
            k--;
        else
            break; // implied that the arrow is NONE
    }
    return result;
}

//function to run the longest common length routine
void lcs_length(matrix & values, vector<string> strings){
    for(int i = 0; i < strings[0].size(); i++){
        for(int j = 0; j < strings[1].size(); j++){
            for(int k = 0; k < strings[2].size(); k++){
                char x = strings[0].at(i);
                char y = strings[1].at(j);
                char z = strings[2].at(k);

                //check for i,j, or k ==0
                if(i == 0 || j == 0 || k == 0){
                    values[i][j][k].value = 0;
                    values[i][j][k].arrow = NONE;
                }
                // see if xi == yj == zk 
                else if(x == y && y == z){
                    values[i][j][k].value = values[i-1][j-1][k-1].value + 1;
                    values[i][j][k].arrow = DIAG;
                }
                else{
                    // find the max of three different options
                    int a = values[i-1][j][k].value;
                    int b = values[i][j-1][k].value;
                    int c = values[i][j][k-1].value;
                    int m = max(a,b,c);

                    values[i][j][k].value = m;
                    if (m == a)
                        values[i][j][k].arrow = LESS_I;
                    else if (m == b)
                        values[i][j][k].arrow = LESS_J;
                    else
                        values[i][j][k].arrow = LESS_K;

                }
            }
        }
    }
}

// creates empty arrow table

// prints a value
void printValue(value_t value){
    cout << value.value << " " <<  value.arrow << endl;
}


void initTable(matrix & m, int x, int y, int z){
    vector<value_t> zValue;
    vector<vector<value_t>> yValue;
    for(int k = 0; k < z; k++){
        value_t value = {0,NONE};
        zValue.push_back(value);
    }
    for(int j = 0; j < y; j++){
        yValue.push_back(zValue);
    }
    for(int i = 0; i < x; i++){
        m.push_back(yValue);
    }

}
void printTable(matrix & m){
    for(int i = 0; i < m.size(); i++){

        for(int j = 0; j < m[0].size(); j++){

            for(int k = 0; k < m[0][0].size(); k++){
                cout << "i = " << i << " j = " << j << " k = " << k << "\t"
                    << m[i][j][k].value << endl;
            }
        }
    }


}
// returns the max of a,b,c
int max(int a, int b, int c){
    int largest = a;
    if (b > largest)
        largest = b;
    if(c > largest)
        largest = c;
    return largest;
}
