#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>


int checkArguments(int argc);
void printFileTypeAndName(char *path);
void menu_RegularFiles();
void menu_Dir();
void menu_SymLink();


int checkArguments(int argc) {
    if(argc < 2) {
        perror("Incorrect number of arguments! Usage: ./a.out <file/directory/link> ...\n");
        exit(1);
    }
    return 0;
}

// Function for printing the type, name and menu for the given arguments
void printFileTypeAndName(char *path) {
    
    struct stat filestat;

    printf("\n%s", path);
    
    if(lstat(path, &filestat) == -1) {
        printf("Error: %s\n", strerror(errno));
        return;
    }

    if(S_ISREG(filestat.st_mode)) {
        printf("- REGULAR FILE\n");
        menu_RegularFiles();
    }

    else if(S_ISDIR(filestat.st_mode)) {
        printf(" - DIRECTORY\n");
        menu_Dir();
    }

    else if(S_ISLNK(filestat.st_mode)) {
        printf(" - SYMBOLIC LINK\n");
        menu_SymLink();
    }

    else {
        printf("File type not supported.\n");
    }

}

void menu_RegularFiles(){
    printf("\n----  MENU ----\n");
    printf("-n: name\n-d: size\n-h: hard link count\n-m: time of last modification\n-a: access rights\n-l: create symbolic link\n");
}

void menu_SymLink(){
    printf("\n----  MENU ----\n");
    printf("-n: name\n-l: delete symbolic link\n-d: size of symbolic link\n-t: size of target file\n-a: access rights\n");
}

void menu_Dir(){
    //not implemented yet
}


int main(int argc, char *argv[]) {

    checkArguments(argc);

    for(int i = 1; i < argc; i++) {
        printFileTypeAndName(argv[i]);
    }
   
    return 0;
}