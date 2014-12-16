#include <stdio.h>
#include <bson.h>
#include <mongoc.h>
#include <unistd.h>
#include <fcntl.h>

#include "cJSON/cJSON.h"
#include "cJSON/cJSON.c"

int main(){
	mongoc_client_t *client;
    mongoc_collection_t *collection;
    mongoc_cursor_t *cursor;
    const bson_t *doc;
    bson_t *query;
    char *str;

	mongoc_init ();

	int stdout_cpy = dup(1);
	int stderr_cpy = dup(2);
	close(1);
	close(2);
    //client = mongoc_client_new ("mongodb://localhost:27017/");
    client = mongoc_client_new ("mongodb://140.113.216.123:27017/");
    collection = mongoc_client_get_collection (client, "cloud", "Matrix");
    query = bson_new ();
    cursor = mongoc_collection_find (collection, MONGOC_QUERY_NONE, 0, 0, 0, query, NULL, NULL);

	fflush(stdout);
	dup2(stdout_cpy,1);
	dup2(stderr_cpy,2);
	close(stdout_cpy);
	close(stderr_cpy);

	FILE* fp = fopen("input_matrix.txt","w");
    while (mongoc_cursor_next (cursor, &doc)) {
        str = bson_as_json (doc, NULL);
		cJSON* root  = cJSON_Parse(str);
		char* name = cJSON_GetObjectItem(root,"Array")->valuestring;
		int row = cJSON_GetObjectItem(root,"i")->valueint;
		int col = cJSON_GetObjectItem(root,"j")->valueint;
		double value = cJSON_GetObjectItem(root,"val")->valuedouble;

		fprintf(fp,"%s %d %d %f\n",name,row,col,value);
        bson_free (str);
    }

	fclose(fp);

    bson_destroy (query);
    mongoc_cursor_destroy (cursor);
    mongoc_collection_destroy (collection);
    mongoc_client_destroy (client);

return 0;
}
