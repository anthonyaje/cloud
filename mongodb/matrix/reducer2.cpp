#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define BUF_SIZE 1048576
using namespace std;

//int M_dim; 

int main(int argc, char ** argv){
/*	if(argc == 2){
        M_dim = atoi(argv[1]);
    }
    else{
        cout<<"Usage: <mapper/reducer> <matrix_dimension>\n";
        return -1;
    }
*/
    char line[BUF_SIZE];
    char * word = NULL;
    double count = 0.0;

    while(fgets(line, BUF_SIZE - 1, stdin) != NULL){
        int i;
        for(i = strlen(line); i >= 0; i--){
            if(line[i] == '\n' || line[i] == '\r'){
                line[i] = '\0';
            }
        }

        char * token = strchr(line, '\t');
        if(token != NULL){
	    *token = '\0';
            int len_word = token - line;
            if(word == NULL){
                word = (char *)malloc(sizeof(char) * (len_word + 1));
                strcpy(word, line);
            }

            if(strcmp(word, line)){
                char* token2 = strtok(word,",");
                int I = atoi(token2);
                token2 = strtok(NULL,",");
                int K = atoi(token2);
                printf("%d %d %.1f\n", I,K, count);
                free(word);
                word = (char *)malloc(sizeof(char) * (len_word + 1));
                strcpy(word, line);

                count = 0;
            }
		*token = '\t';
            count += atof(token + 1);
        }
    }
                char* token2 = strtok(word,",");
                int I = atoi(token2);
                token2 = strtok(NULL,",");
                int K = atoi(token2);
                printf("%d %d %.1f\n", I,K, count);

    if(word != NULL){
        free(word);
    }

    return 0;
}

