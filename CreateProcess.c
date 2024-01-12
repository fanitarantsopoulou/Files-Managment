#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <sys/time.h> 
#include <sys/resource.h>
#include <time.h>
#include <sys/wait.h>
#include <errno.h>


int getPolicy(){ // The system call sched_getscheduler(0); is used to retrieve the scheduling policy of the current process.
	
	return sched_getscheduler(0);
	
} // end getPolicy

int getP() { // The system call getpriority(PRIO_PROCESS, getpid()) is used to retrieve the priority (nice value) of the current process.
	
    int nice_val = getpriority(PRIO_PROCESS, getpid());
    if (nice_val == -1) {
        perror("Error getting nice value");
        printf("errno: %d\n", errno);
    }
    return nice_val;
    
} // end getP

int executeTask(){
	long long sum=0;
	for (long long i=0;i<=1500000000;i++){
		sum=sum+i;
	}
	return sum;
	
} // end executeTask

int main() {
	
  // Initializing 2 structs 
  struct timespec start; // Represents the second the process began
  struct timespec end; // Represents the second the process ended

  // Using CLOCK_MONOTONIC to ensure that there are no sudden jumps backward or forward in time and to maintain the functionality of the code
  clock_gettime(CLOCK_MONOTONIC, &start);

  
  
	pid_t p;
	int child_p;
	int child_pr;
	int parent_p;
	int parent_pr;
	
    
    // Creating a child process
    if ((p = fork()) == -1) { // Checking if the process is not successfull.
		perror("Error. Process failed.\n");
        return -1;
    }
    
    if (p==0){ // Child
		
		child_p=getPolicy();
		child_pr=getP();
		
		printf("Nice value for PID=%d is %d\n", getpid(), child_pr);
        printf("Policy is normal for %d\n", child_p);
		
		executeTask();
		
	clock_gettime(CLOCK_MONOTONIC, &end);
	
	printf("Total time execution for process %d = %.6f seconds\n", getpid(), (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9); // Use .6f for precision of 6 decimal digits
    // Using nano seconds is to include the fractional part of the seconds for a more precise measurement of time
	} 
	
	else{ // Parent 
	parent_p=getPolicy();
	parent_pr=getP();
	
	printf("Nice value for PID=%d is %d\n", getppid(), parent_pr);
    printf("Policy is normal for %d\n", parent_p);

	wait(NULL); // The parent is waiting for the child process to be completed
		
	executeTask();
	

	clock_gettime(CLOCK_MONOTONIC, &end);
	printf("Total time execution for process %d = %.6f seconds\n", getpid(), (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9); // Use .6f for precision of 6 decimal digits
    // Using nano seconds is to include the fractional part of the seconds for a more precise measurement of time

	
	 }
	
	
	return 0;


}
