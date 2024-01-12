#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

//Declaration

pid_t wait(int *status);  
pid_t waitpid(pid_t p, int *status, int options); 
 

int main() {
	
    pid_t p;
    int status;
    
    //Creating a child process
    if ((p = fork()) == -1) { 
		perror("Error. Process failed.\n");
        return -1;
    }

    if (p == 0) { //Checking if this is the child
        execlp("./3122170_3122069_FileProp", "3122170_3122069_FileProp", (char *)NULL);
        //If we reach here, the execlp has failed.
        perror("Error occured.\n");
        return -1;
    } else { //Checking if this is the parent
        
        waitpid(p, &status, 0);

        if (WIFEXITED(status)) {
   
            printf("Parent process with id %d\n is waiting for child to complete...", WEXITSTATUS(status));
        } else {
     
            printf("Error occured. \n");
            status=-1;
        }
    }

    return 0;
}
