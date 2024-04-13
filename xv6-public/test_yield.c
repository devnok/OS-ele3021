#include "types.h"
#include "user.h"

int main(int argc, char *argv[]) {
	int pid = fork();
	if(pid == 0){ // child process
		while(1){
			printf(1, "Child\n");
			yield();
		}
	}
	else { // parent process
		while(1){
			printf(1, "Parent\n");
			yield();
		}
	}
}
