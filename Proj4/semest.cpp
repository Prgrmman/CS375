#include <iostream>
#include <deque>

#define SIZE 15

typedef struct node_t{
    int distance; // visit time
    int color; // 0 = white, 1 = grey, 2 = red
} node;


using namespace std;

// prototypes
void initMatrix(int matrix[SIZE][SIZE]);
void initNodes(node nodes[SIZE]);
void printMatrix(int matrix[SIZE][SIZE]);
int minSemester(int matrix[SIZE][SIZE], node nodes[SIZE]);


/* MAIN driver code
 * Note:
 * cs1 = 0
 * cs2 = 1
 * .......
 * cs15 = 14
 */
int main()
{

    int matrix[SIZE][SIZE] ; // adjacency matrix
    node nodes[SIZE]; // node list
    initMatrix(matrix);

    int time = 0; // set start time to 0

    initNodes(nodes);
    cout << "The minimum number of semesters is " << minSemester(matrix, nodes) << endl;
    return 0;
}

/*
 * Algorithm uses breadth first search to determine
 * the min number of semesters needed to get the cs degree
 */
int minSemester(int matrix[SIZE][SIZE], node nodes[SIZE])
{
    // the final distance
    int finalDist = 0;
    // our queue of nodes
    deque<int> nodeQ;
    // add the source nodes
    nodeQ.push_back(0); nodeQ.push_back(1); nodeQ.push_back(2);
    nodes[0].color = nodes[1].color = nodes[2].color = 1; // set sources to grey
    nodes[0].distance = nodes[1].distance = nodes[2].distance = 0;
    // while not empry
    while(nodeQ.size() != 0){
        int v = nodeQ.front();
        // for each adjacent vertex v
        for(int u = 0; u < SIZE; u++){
            if(matrix[v][u] == 1 && nodes[u].color == 0){
                nodes[u].color = 1;
                nodes[u].distance = nodes[v].distance + 1;
                finalDist = nodes[u].distance;
                nodeQ.push_back(u);
            }
        }
        nodes[v].color = 2;
        nodeQ.pop_front(); // remove node from queue
    }
    return finalDist + 1;
}


// setup nodes for use
void initNodes(node nodes[SIZE])
{
    for (int i = 0; i < SIZE; i++){
        nodes[i] = {-1, 0}; // -1 for visit means not set
    }
    return;

}
// setup matrix for use
void initMatrix(int matrix[SIZE][SIZE])
{
    // initiazlize the matrix to -1
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            matrix[i][j] = 0;

    /*
     * Graph is hard coded in
     */
    matrix[1][3] = 1;       // cs4 requires cs2
    matrix[3][4] = 1;       // cs5 requires cs4
    matrix[0][5] = 1;       // cs6 requires cs1
    matrix[2][5] = 1;       // cs6 requires cs3
    matrix[3][6] = 1;       // cs7 requires cs4
    matrix[4][7] = 1;       // cs8 requires cs5
    matrix[5][7] = 1;       // cs8 requires cs6
    matrix[6][8] = 1;       // cs9 requires cs7
    matrix[8][9] = 1;       // cs10 requires cs9
    matrix[7][10] = 1;      // cs11 requires cs8
    matrix[2][11] = 1;      // cs12 requires cs3
    matrix[5][12] = 1;      // cs13 requires cs6
    matrix[3][13] = 1;      // cs14 requires cs4
    matrix[5][13] = 1;      // cs14 requires cs6
    matrix[13][14] = 1;     // cs15 requires cs14
    return;
}


void printMatrix(int matrix[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    return;
}

