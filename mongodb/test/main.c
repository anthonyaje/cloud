#include <stdio.h>
#include <bson.h>
#include <mongoc.h>
#include <unistd.h>
#include <fcntl.h>

#include "cJSON/cJSON.h"

int main(){
	mongoc_client_t *client;
    mongoc_collection_t *collection;
    mongoc_cursor_t *cursor;
    const bson_t *doc;
    bson_t *query;
    char *str;

	mongoc_init ();
	printf("1\n");

    //client = mongoc_client_new ("mongodb://localhost:27017/");
    int sv_0 = dup(0);
    int sv_1 = dup(1);
    int sv_2 = dup(2);
	close(0);
	close(1);
	close(2);

	printf("1\n");

    client = mongoc_client_new ("mongodb://140.113.216.123:27017/");
	
	fflush(stdout);
	
	dup2(sv_1,1);	
	dup2(sv_0,0);	
	dup2(sv_2,2);	
	close(sv_1);
	close(sv_0);
	close(sv_2);

	printf("2\n");
	
    collection = mongoc_client_get_collection (client, "cloud", "Matrix");
	printf("3\n");
    query = bson_new ();
	printf("4\n");
    cursor = mongoc_collection_find (collection, MONGOC_QUERY_NONE, 0, 0, 0, query, NULL, NULL);
	printf("5\n");

	FILE* fp = fopen("matrix.txt","w");

    while (mongoc_cursor_next (cursor, &doc)) {
        str = bson_as_json (doc, NULL);
    //    printf ("[%s]\n", str);
	
			
		cJSON* root  = cJSON_Parse(str);
		char* name = cJSON_GetObjectItem(root,"Array")->valuestring;
		int row = cJSON_GetObjectItem(root,"i")->valueint;
		int col = cJSON_GetObjectItem(root,"j")->valueint;
		double value = cJSON_GetObjectItem(root,"val")->valuedouble;

		fprintf(fp,"%s %d %d %.1f\n",name,row,col,value);
/*		if(strcmp(name,"A")==0){
			printf("%010d,%s,%010d,%f\n",col,name,row,value);

		}
		else if(strcmp(name,"B")==0){
			printf("%010d,%s,%010d,%f\n",row,name,col,value);// i,k,j,v1,v2
		}
		else{
			printf("undefined matrix: %s\n",name);
			break;
		}
		
*/
        bson_free (str);
    }

	fclose(fp);

    bson_destroy (query);
    mongoc_cursor_destroy (cursor);
    mongoc_collection_destroy (collection);
    mongoc_client_destroy (client);

return 0;
}
