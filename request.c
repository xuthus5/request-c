#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>
#include "request.h"

size_t memory_response_write_func(void *src, size_t size, size_t nmemb, memory_response *dst) {
    size_t data_size = dst->size + size * nmemb;

    dst->data = realloc(dst->data, data_size + 1);
    if (dst->data == NULL) {
        fprintf(stderr, "realloc() failed\n");
        exit(EXIT_FAILURE);
    }
    memcpy(dst->data + dst->size, src, size * nmemb);
    dst->data[data_size] = '\0';
    dst->size = data_size;
    return size * nmemb;
}

void init_memory_response(memory_response *s) {
    s->size = 0;
    s->data = malloc(s->size + 1);
    if (s->data == NULL) {
        fprintf(stderr, "malloc() failed\n");
        exit(EXIT_FAILURE);
    }
    s->data[0] = '\0';
}

char *get_response(char *url, struct curl_slist *headers) {
    CURL *curl;
    memory_response resp;
    init_memory_response(&resp);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, memory_response_write_func);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resp);
        if (headers != NULL) {
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        }
        CURLcode res = curl_easy_perform(curl);
        if (res != 0) {
            exit(res);
        }
        curl_easy_cleanup(curl);
        printf("[DEBUG]\nurl: %s\nmethod: %s\nbody: %s\n", url, "GET", resp.data);
        return resp.data;
    }
    return NULL;
}

char *post_response(char *url, char *payload, struct curl_slist *headers) {
    CURL *curl;
    memory_response resp;
    init_memory_response(&resp);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, 1);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, memory_response_write_func);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resp);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload);
        if (headers != NULL) {
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        }
        CURLcode res = curl_easy_perform(curl);
        if (res != 0) {
            exit(res);
        }
        printf("[DEBUG]\nurl: %s\nmethod: %s\nbody: %s\n", url, "POST", resp.data);
        curl_easy_cleanup(curl);
        return resp.data;
    }
    return NULL;
}

char *post_form_response( char *url, struct curl_httppost *payload, struct curl_slist *headers) {
    CURL *curl;
    memory_response resp;
    init_memory_response(&resp);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, 1);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, memory_response_write_func);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resp);
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, payload);
        if (headers != NULL) {
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        }
        CURLcode res = curl_easy_perform(curl);
        if (res != 0) {
            exit(res);
        }
        printf("[DEBUG]\nurl: %s\nmethod: %s\nbody: %s\n", url, "POST_FORM", resp.data);
        curl_easy_cleanup(curl);
        curl_formfree(payload);
        return resp.data;
    }
    return NULL;
}