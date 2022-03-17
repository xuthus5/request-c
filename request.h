#include <stdio.h>
#include <curl/curl.h>

typedef struct {
	char *data;
	size_t size;
} memory_response;

// get_response 发起一个GET请求 返回想要的结果
char *get_response( char *url , struct curl_slist *headers);

char *post_response( char *url, char * payload , struct curl_slist *headers);

char *post_form_response( char *url, struct curl_httppost *payload, struct curl_slist *headers);
