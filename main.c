#include <request.h>

int main() {
    char * response = get_response("https://xuthus.cc", NULL);
    printf("data: %s", response);
}