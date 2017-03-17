#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void readList(int* data, char * filename, int size);

//my algorithm
void  writekey(int *data, int size, char* filename);

int compare(const void *a, const void * b);
int countLines(char* filename);


int main(int argc, char* argv[]){
    int i;
    char str[100];

    if(argc!=3) {
        printf("Usage: progname <input_file> <output_file>");
        exit(0);
    }
    //write numbers to data
    int numLines = countLines(argv[1]);
    int *data;
    data = (int*) malloc(numLines * sizeof(int));
    readList(data, argv[1], numLines);
    // do some tests
    writekey(data,numLines, argv[2]);
    free (data);
    return 0;

    // open the destination file
}

// code talen from http://www.tutorialspoint.com/c_standard_library/c_function_qsort.htm
int compare(const void *a, const void * b){
 return ( *(int*)a - *(int*)b );
}

void  writekey(int *data, int size, char* filename){
    qsort(data, size, sizeof(int), compare); // sort the data
    int i, low, high, key;
    int diff;
    bool isFound;

    FILE* fp;
    if((fp = fopen(filename, "w"))== NULL){
        perror("Error opening output file");
        exit(0);
    }
    for(i=0; i < size-1; i++){
        key = data[i];
        for(high =i+1; high < size; high++){
            low = high-1;
            if (data[low] == key)
                low--;
            while (low >= 0){
                diff = data[high] - data[low];
                if (diff == key){
                    // we found it!
                    fprintf(fp, "%d %d %d\n", key, data[high],data[low]);
                    break;
                    //return i;
                }
                if (diff > key)
                    break;
                if (data[low] == key)
                    low --;
                low --;
            }
        }
    }
    fclose(fp);
    return;
}

// reads an array from file into an integer array
void readList(int* data, char * filename, int size){
    FILE* fp;
    if((fp = fopen(filename, "r")) == NULL){
        perror("File could not be open");
        exit(0);
    }
    char buffer[100]; // buffer to process lines
    int i;
    for(i = 0; i < size; i++){
       fgets(buffer, 100, fp);
        sscanf(buffer, "%d", &(data[i]));
    }

    return;
}

int countLines(char* filename){
    FILE* fp;
    int lines = 0;
    if((fp = fopen(filename,"r")) == NULL)
        return 0;
    char buffer[100];
    while(fgets(buffer, 100, fp)){
        lines++;
    }
    fclose(fp);
    return lines;
}
