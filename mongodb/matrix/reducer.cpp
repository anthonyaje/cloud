#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#define BUF_SIZE 1048576
using namespace std;


int M_dim = 16 ;
double value_table[BUF_SIZE];

int main(int argc, char ** argv)
{
	if(argc == 2){
		M_dim = atoi(argv[1]);
	}
	else{
		cerr<<"Usage: <mapper/reducer> <matrix_dimension>\n";
		return -1;
	}
	
	char* line = new char[BUF_SIZE];
        while(fgets(line, BUF_SIZE - 1, stdin) != NULL){
	//A's part
        for(int i = strlen(line); i >= 0; i--){
            if(line[i] == '\n' || line[i] == '\r'){
                line[i] = '\0';
            }
        }
        char* token;
        token = strtok(line,",");
        char* J = token;
        token = strtok(NULL,",");
        char M_name = *token;
        if(M_name == 'A'){
            token = strtok(NULL,",");
            int I = atoi(token);
            token = strtok(NULL,"\0");
            double A_value = atof(token);
            value_table [I] =A_value;
        }else{
            token = strtok(NULL,",");
            char* K = token;
            token = strtok(NULL,",");
            double B_value = atof(token);
            for(int i=0;i<M_dim;i++) printf("%s\t%010d,%s\t%f,%f\n",J,i,K,value_table[i],B_value);
        }
    }
    delete [] line;
    return 0;
}

