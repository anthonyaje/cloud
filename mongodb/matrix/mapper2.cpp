#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define BUF_SIZE 1048576
using namespace std;
//int M_dim;

int main(int argc, char ** argv)
{
	/*
 	if(argc == 2){
        M_dim = atoi(argv[1]);
    }
    else{
        cout<<"Usage: <mapper/reducer> <matrix_dimension>\n";
        return -1;
    }
*/

    char line[BUF_SIZE];
    while(fgets(line, BUF_SIZE - 1, stdin) != NULL){
        for(int i = strlen(line); i >= 0; i--){
            if(line[i] == '\n' || line[i] == '\r'){
                line[i] = '\0';
            }
        }
        char* token = NULL;
        token = strtok(line,"\t");
        token = strtok(NULL,"\t");
        char* I_K = token;
       	token = strtok(NULL,",");
        double val1 = atof(token);
        token = strtok(NULL,",");
        double val2 = atof(token);
        printf("%s\t%f\n",I_K,val1*val2);
    }
    return 0;
}

