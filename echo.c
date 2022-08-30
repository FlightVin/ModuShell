#include "headers.h"
#include "echo.h"

void echo(char* str){
    if (strlen(str) > 5) printf("%s\n", &str[5]);
    else printf("\n");
}