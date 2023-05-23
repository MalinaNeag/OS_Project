# 📁 Unix File System Program

This is a C program that uses system calls and library functions in Unix to take multiple arguments representing paths to regular files / directories / symbolic links.

## ⚙️ Functionality

The program provides the following functionalities:

### 📚 I. File Type Menu 

The program will pass through all the arguments, and for each file, depending on the file type, the name of the file and the type of the file will be displayed. After that, an interactive menu will be displayed, with all the options available for that specific file type.

The user should then input the desired options for that file from the keyboard, as a single string. The options will be preceded by the ‘-’ sign and will contain multiple letters corresponding to each option. An example input from the keyboard looks like this: -nal. Note that some options may require additional input information.

After entering the options string, the information about that file will be printed to the standard output.

If one of the letters of the string is not a valid option, an error message will be displayed and the menu will appear again.

####  📄 Regular File

- Name (-n)
- Size (-d)
- Hard link count (-h)
- Time of last modification (-m)
- Access rights (-a)
- Create symbolic link (-l, this will wait for user input for the name of the link)

The access rights will be displayed in the format:

User:
- Read - yes
- Write - yes
- Exec - no

Group:
- Read - yes
- Write - no
- Exec - no

Others:
- Read - yes
- Write - no
- Exec - no

#### 🔗 Symbolic Link

- Name (-n)
- Delete symbolic link (-l)
- Size of symbolic link (-d)
- Size of target file (-t)
- Access rights (-a)

Note that if the -l option is given, the other following options will no longer be performed

#### 📂 Directory 

- Name (-n)
- Size (-d)
- Access rights (-a)
- Total number of files with the .c extension (-c)

### ⛓️ II. Child Processes and Pipes 

The parent process will create for each argument one child process that will handle the next features:

#### 💻 Regular File with .c Extension

If the argument is a regular file with the .c extension, the parent will create one more process (a second child process) that will execute a script which compiles the file and prints at standard output the number of errors and the number of warnings.
The output data of the script will be send to the parent process which will compute a score based on number of errors and warnings:

- 0 errors and 0 warnings: 10

- at least one error: 1

- no errors, but more than 10 warnings: 2

- no errors, but maximum 10 warnings: 2 + 8*(10 – number_of_warnings)/10.

The parent writes the following message in a file named grades.txt: "<FILE_NAME>: <SCORE>".

#### 📄  Regular File without .c Extension

If the argument is a regular file but doesn't have the .c extension, the second child prints the number of lines.

#### 📂 Directory 

If the argument is a directory, the parent will create a second child process that will execute a command for creating a file with the .txt extension and a specific name (e.g., dirName_file.txt).

#### 🔗 Symbolic link 

If the argument is a symbolic link, the second child process will execute a command for changing the permissions of the symbolic link as it follows:

- read, write and execution rights for the user
- read and write rights for the group (no execution rights should be granted for the group of user!)
- no read, write or execution rights for other users

The parent process receives the return state of its child processes and prints the following message 

```
The process with PID <PID> has ended with the exit code <EXIT_CODE>
```

## 💡 Usage

To use this program, run the following command:

```
./unix_file_system_program <file/directory/symbolic_link paths separated by space>
```

Note that the program requires root privileges to access certain files and directories.

