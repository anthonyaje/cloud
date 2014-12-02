#include <cstdio>
#include <cstring>
#include <cstdlib>
#define BUF_SIZE 1048576
#define DELIMITERS " /t"
using namespace std;
//int M_dim;

int main(int argc, char ** argv)
{
/*	if(argc == 2){
        M_dim = atoi(argv[1]);
    }
    else{
        printf("Usage: <mapper/reducer> <matrix_dimension>\n");
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
        char name;
	int row,col;
	double value;
	token = strtok(line,DELIMITERS);
        name = *token;
        token = strtok(NULL,DELIMITERS);
        row = atoi(token);
        token = strtok(NULL,DELIMITERS);
        col = atoi(token);
        token = strtok(NULL,DELIMITERS);
        value= atof(token);
        if(name=='A'){
            printf("%010d,%c,%010d,%f\n",col,name,row,value);
        }
        else{

            printf("%010d,%c,%010d,%f\n",row,name,col,value);// i,k,j,v1,v2
        }

    }
    return 0;
}

