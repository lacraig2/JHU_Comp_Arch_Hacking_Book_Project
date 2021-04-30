#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ucontext.h>
#include <ucontext.h>
#include <unistd.h>
#include <stdbool.h>


void fault_handler(int signo, siginfo_t *info, void *extra){
	printf("------------------------ERROR-------------------------\n");
   printf("Goodbye cruel world! I was a young program. And I have died too soon!\n");
    printf("You can avenge my death! I received a %s.\n", strsignal(signo));
	if (info && signo == SIGSEGV){
		if (info->si_addr){
			printf("Seems like the faulty address was %p.\n",info->si_addr);
		}else{
			// we don't want the address to be (null). It's common and might
			// be confusing
			printf("Seems like the faulty address was 0\n");
		}
		if (info->si_code == SEGV_MAPERR){
			printf("Looks like that address isn't mapped\n");
		}else if (info->si_code == SEGV_ACCERR){
			printf("Looks like the permissions are wrong for accessing that address\n");
		}
	}else{
		printf("Looks like I was near address %p at my untimely demise.\n", info->si_addr);
	}
	fflush(stdout);
    abort();
}

void call_strcpy(char* A){
	char buf[16];
	strcpy(buf, A);
}

void set_up_handlers(){
    struct sigaction act;
	memset(&act,0,sizeof(struct sigaction));
	sigemptyset(&act.sa_mask);
    act.sa_flags = 0; //SA_SIGINFO;
    act.sa_sigaction = fault_handler;


	if (sigaction(SIGFPE, &act, NULL) == -1) {
		perror("sigfpe: sigaction");
		exit(1);
	}
	if (sigaction(SIGSEGV, &act, NULL) == -1) {
		perror("sigsegv: sigaction");
		exit(1);
	}
	if (sigaction(SIGILL, &act, NULL) == -1) {
		perror("sigill: sigaction");
		exit(1);
	}
}


int main(int argc, char* argv[]){
	set_up_handlers();
    printf("Hello to the string consumer 3000!\n");
    if (argc > 1){
        printf("You provided me a string! Yum!\n");
        call_strcpy(argv[1]);
    } else{
        printf("Provide your name as the first argument\n");
        printf("./demo jimbob\n");
    }
}
