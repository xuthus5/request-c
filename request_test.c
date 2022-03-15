#include "request.h"

int get_response_test() {
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/json; charset: utf-8");
    char *list_response = get_response("https://central.xuthus.cc/api/storage/upyun/list?path=/", headers);
    printf("%s", list_response);
}

int main() {
    get_response_test();
}
