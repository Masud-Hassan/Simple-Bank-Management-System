#include <stdio.h>
#include <stdlib.h>
#include <process.h>

int main(){

    _execl("main.c", "main.c", "google.com", NULL);

    return 0;
}