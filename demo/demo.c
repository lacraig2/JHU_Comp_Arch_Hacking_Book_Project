#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ucontext.h>
#include <ucontext.h>
#include <signal.h>
#include <unistd.h>

int (*printf_internal)( const char * format, ... ) = printf;


void fault_handler(int signo, siginfo_t *info, void *extra){
	printf("------------------------ERROR-------------------------\n");
    printf("Goodbye cruel world! I was a young program. And I have died too soon!\n");
    printf("You can avenge my death! I received Signal Number %d\n", signo);
    printf("Looks like I was near address %p at my untimely demise.\n", info->si_addr);
    abort();
}

void set_up_handlers(){
    struct sigaction act;
    act.sa_flags = SA_SIGINFO;
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
	if (sigaction(SIGBUS, &act, NULL) == -1) {
		perror("sigbus: sigaction");
		exit(1);
	}
}
//__attribute__((section(".win_sec"))) __asm__(
//
//	.L0 .ascii "  _____\n"
//    .L1 .ascii " /     \\\n"
//	printf("| () () |\n");
//	printf(" \\  ^  /\n");
//	printf("  |||||\n");
//	printf("  |||||\n");	
//	printf("\n");
//	printf("Oh no! There's haxx0rs in the mainframe!\n");
//}
//__attribute__((section(".win_msg"))) char *win_message = "  _____\n"  \
//	" /     \\\n" \
//	"| () () |\n" \
//	" \\  ^  /\n" \
//	"  |||||\n" \
//	"  |||||\n"	\
//	"\n" \
//	"Oh no! There's haxx0rs in the mainframe!\n";

//__attribute__((section(".win_sec"))) __attribute__((naked)) void bet_you_cant_get_here(){
//    __asm__(
//    "mov r0, %1 \n"
//    : "=r" (win_message));
//    __asm__(
//    "bl puts\n"
////    "mov r7, 1\n"
//    "mov r0, 0\n"
//    "b exit\n"
//);
//}

//__attribute__((section(".win_sec"))) __attribute__((naked)) void bet_you_cant_get_here() {
//	printf_internal("  _____\n");  
//	printf(" /     \\\n");
//	printf("| () () |\n");
//	printf(" \\  ^  /\n");
//	printf("  |||||\n");
//	printf("  |||||\n");	
//	printf("\n");
//	printf("Oh no! There's haxx0rs in the mainframe!\n");
//}

int main(int argc, char* argv[]){
    printf("Hello to the string consumer 3000!\n");
    char buf[10];
	set_up_handlers();
    if (argc > 1){
        printf("You provided me a string! Yum!\n");
        strcpy(buf,argv[1]);
    } else{
        printf("Provide your name as the first argument\n");
        printf("./demo jimbob\n");
    }
}
