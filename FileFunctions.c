#include <stdio.h>
#include <stdlib.h>
FILE *f = NULL; //Initializing a global variable (pointer) in order to not use parameters at the functions
#define MAX_FILENAME_LENGTH 20 
#define MAX_TEXT_LENGTH 100 

void open() {
	
    char filename[MAX_FILENAME_LENGTH]; 
    printf("Enter the name of the file to create/open (20 characters): \n");
    scanf("%s", filename);

    f = fopen(filename, "a+"); // If the file doesn't exist, it will be created. Open for both reading and appending in binary mode.

    if (f == NULL) {
        printf("File creation/opening failed.\n");
    } else {
        printf("File has been opened successfully.\n");
    }
} //end open

void close() {
    if (f != NULL) { 
        fclose(f);
        f = NULL;
        printf("File has been closed successfully.\n");
    } else {
        printf("No file is currently open.\n");
    }
} //end close

void read() {
	if (f != NULL) {
		fseek(f, 0, SEEK_SET); //Setting the pointer at the beginning of the file
		
	}else{
		printf("You may open a file first\n");
	}
} //end read

void write() {
    if (f != NULL) {
		fseek(f, 0, SEEK_SET); 
		char text[MAX_TEXT_LENGTH+1]; 
		printf("Enter the first 100 characters of the text:\n");
		fgets(text, 100, stdin);
		fprintf(f, "%s", text); 
		
	}else{
		printf("You may open a file first\n");
	}
} //end write

void exit();


int main() {

    char choice;

    printf("I/O calls.\n");

    while (1) {
        printf("a. Create/Open file.\n");
        printf("b. Close file.\n");
        printf("c. Read file.\n");
        printf("d. Write in file.\n");
        printf("e. Exit.\n");

        scanf(" %c", &choice);

        switch (choice) {
            case 'a':
            case 'A':
                open();
                break;
            case 'b':
            case 'B':
                close();
                break;
            case 'c':
            case 'C':
                read();
                break;
            case 'd':
            case 'D':
                write();
                break;
            case 'e':
            case 'E':
                exit(0); //0 represents EXIT_SUCCESS.
                break;
            default:
                printf("Invalid choice. Please enter another one.\n");
        }
    }

    return 0;
}
