#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int checkArguments(int argc);
void printMenu(char *options);

int checkArguments(int argc) {
    if(argc < 2) {
        perror("Incorrect number of arguments! Usage: ./a.out <file/directory/link> ...\n");
        exit(1);
    }
    return 0;
}

void printMenu(char *options) {
    printf("\n----  MENU ----\n");
    printf("n: name\nm: last modification\na: access\n");
    printf("Please, enter your options: ");
    fgets(options, 20, stdin);
}

int main(int argc, char *argv[]) {
    
    char options[20];
    checkArguments(argc);
    printMenu(options);

}