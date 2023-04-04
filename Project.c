#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

//Note: TO BE MODIFIED: the formatted scanf 
int checkArguments(int argc) {
    if(argc < 2) {
        perror("Incorrect number of arguments! Usage: ./a.out <file/directory/link> ...\n");
        exit(1);
    }
    return 0;
}

void menu_RegularFiles(){
    printf("\n----  MENU ----\n");
    printf("-n: name\n-d: size\n-h: hard link count\n-m: time of last modification\n-a: access rights\n-l: create symbolic link\n");
    printf("\nPlease, enter your options: ");
}

void menu_Directory(){
    printf("\n----  MENU ----\n");
    printf("-n: name\n");
    printf("\nPlease, enter your options: ");
}

void menu_SymbolicLink(){
    printf("\n----  MENU ----\n");
    printf("-n: name\n-l: delete symbolic link\n-d: size of symbolic link\n-t: size of target file\n-a: access rights\n");
    printf("\nPlease, enter your options: ");
}

void printAccessRights(struct stat filestat) {
    
    printf("\nAccess rights:\n");

    printf("\nUSER:\n-read: %s\n-write: %s\n-execute: %s\n", 
           (filestat.st_mode & S_IRUSR) ? "yes" : "no",
           (filestat.st_mode & S_IWUSR) ? "yes" : "no",
           (filestat.st_mode & S_IXUSR) ? "yes" : "no");

    printf("\nGROUP:\n-read: %s\n-write: %s\n-execute: %s\n", 
           (filestat.st_mode & S_IRGRP) ? "yes" : "no",
           (filestat.st_mode & S_IWGRP) ? "yes" : "no",
           (filestat.st_mode & S_IXGRP) ? "yes" : "no");

    printf("\nOTHERS:\n-read: %s\n-write: %s\n-execute: %s\n", 
           (filestat.st_mode & S_IROTH) ? "yes" : "no",
           (filestat.st_mode & S_IWOTH) ? "yes" : "no",
           (filestat.st_mode & S_IXOTH) ? "yes" : "no");
}

void printRegularFileInfo(char *filepath) {
    
    char options[20];
    
    struct stat filestat;
    
    if(scanf("%20s", options) != 1) {
        perror("Scanf failed.\n");
        menu_RegularFiles();
    }

    int numberOfOptions = strlen(options);
    

    if(lstat(filepath, &filestat) == -1) {
        printf("Error: %s\n", strerror(errno));
        return;
    }

    for(int i = 1; i < numberOfOptions; i++) {
        
        switch (options[i]) {
            
            case 'n':
                printf("\nName: %s\n", filepath);
                break;
            
            case 'm':
                printf("\nLast modified: %s", ctime(&filestat.st_mtime));
                break;
            
            case 'a':
                printAccessRights(filestat);
                break;
            
            case 'h':
                printf("\nHard link count: %ld\n", filestat.st_nlink);
                break;
            
            case 'd':
                printf("\nSize: %ld bytes\n", filestat.st_size);
                break;
            
            case 'l':
                printf("\nEnter name of symbolic link: ");
                char linkname[256];
                scanf("%s", linkname);
                
                if (symlink(filepath, linkname) == -1) {
                    printf("\nError creating symbolic link: %s\n", strerror(errno));
                } else {
                    printf("\nSymbolic link created: %s -> %s\n", linkname, filepath);
                }
            
            default:
                break;
        }
    }
}

void printSymbolicLinkInfo(char *linkpath) {
    
    struct stat filestat;
    struct stat targetstat;

    char options[20];

    if(scanf("%20s", options) != 1) {
        perror("Scanf failed.\n");
        menu_SymbolicLink();
    }

    int numberOfOptions = strlen(options);
    
    if(lstat(linkpath, &filestat) == -1) {
        printf("Error: %s\n", strerror(errno));
        return;
    }

    for(int i = 1; i < numberOfOptions; i++) {
        
        switch (options[i]) {
        
        case 'n':
            printf("\nName: %s\n", linkpath);
            break;
        
        case 'd':
            printf("\nSize of symbolic link: %ld bytes\n", filestat.st_size);
            break;
        
        case 't':
          
            if(stat(linkpath, &targetstat) == -1) {
                printf("Error: %s\n", strerror(errno));
                return;
            }
            if(S_ISREG(targetstat.st_mode)) {
                printf("\nSize of target file: %ld bytes\n", targetstat.st_size);
            } else {
                printf("\nTarget file is not a regular file.\n");
            }
            break;

        case 'a':
            printAccessRights(filestat);
            break;
        
        case 'l':
            if(unlink(linkpath) == -1) {
                printf("\nError: %s\n", strerror(errno));
            } else {
                printf("\nSymbolic link deleted.\n");
                return;
            }
            break;
        
        default:
            break;
        }
    }
}

void printArgumentsInfo(char *path) {
    
    struct stat filestat;
   
    printf("\n%s", path);
    
    if(lstat(path, &filestat) == -1) {
        printf("Error: %s\n", strerror(errno));
        return;
    }

    switch (filestat.st_mode & S_IFMT) {
        case S_IFREG:
            printf("- REGULAR FILE\n");
            menu_RegularFiles();
            printRegularFileInfo(path);
            break;
        case S_IFDIR:
            printf(" - DIRECTORY\n");
            menu_Directory();
            break;
        case S_IFLNK:
            printf(" - SYMBOLIC LINK\n");
            menu_SymbolicLink();
            printSymbolicLinkInfo(path);
            break;
        default:
            printf("File type not supported.\n");
            break;
    }
}


int main(int argc, char *argv[]) {

    checkArguments(argc);

    for(int i = 1; i < argc; i++) {
        printArgumentsInfo(argv[i]);
    }
   
    return 0;
}
