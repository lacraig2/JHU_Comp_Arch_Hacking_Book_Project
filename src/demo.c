/*
* Luke Craig
* 4/30/2021
* GPLv3
*/

#define _GNU_SOURCE 
/* 
* Without this there's no register definitions.
* I was going to make it open source, but I guess it *must* be GPL
* to get the register definitions.
*/

#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <ucontext.h>

void* address_to_hit = (void*)0x4b434148;

void fault_handler(int signo, siginfo_t *info, void *ucontext) {
	puts("\n\n\n------------------------FAULT-------------------------\n");
    puts("Goodbye cruel world! I was a young program. And I have died too soon!\n");
    puts("You can avenge my death! I received a fault.");
	printf("That means something went wrong. I received a \"%s\".\n",strsignal(signo));
	puts("If you haven't seen that term before google it! The Wikipedia article is pretty good.\n");

	puts("Signal Information:");
	fflush(stdout);
	// sometimes this isn't NULL and is just invalid. we flush befor then
	// so that some info comes across at least. In my tests the alternate
	// stack fixes this.
	if (info != NULL){
		if (info->si_addr){
			printf("Seems like the faulty address was %p.\n",info->si_addr);
		}else{
			// we don't want the address to be (null). It's common and might
			// be confusing
			puts("Seems like the faulty address was 0\n");
		}
		if (signo == SIGSEGV){
			if (info->si_code == SEGV_MAPERR){
				puts("Looks like that address isn't mapped.");
			}else if (info->si_code == SEGV_ACCERR){
				puts("Looks like the permissions are wrong for accessing that address.\n");
			}
		}else if (signo == SIGILL){
			puts("It seems that you hit a valid memory region, but not quite the right address. The system found junk instructions.\n");
		}
	}else{
		puts("Seems like the system didn't provide us with more info.\n");
	}
	fflush(stdout);

	puts("\nRegister state:");

	ucontext_t *context = (ucontext_t*)extra;
	if (context != NULL){
		#if defined(i386)
		printf("eax           0x%x\n", context->uc_mcontext.gregs[REG_EAX]); 
		printf("ecx           0x%x\n", context->uc_mcontext.gregs[REG_ECX]); 
		printf("edx           0x%x\n", context->uc_mcontext.gregs[REG_EDX]); 
		printf("ebx           0x%x\n", context->uc_mcontext.gregs[REG_EBX]); 
		printf("esp           0x%x\n", context->uc_mcontext.gregs[REG_ESP]); 
		printf("ebp           0x%x\n", context->uc_mcontext.gregs[REG_EBP]); 
		printf("esi           0x%x\n", context->uc_mcontext.gregs[REG_ESI]); 
		printf("edi           0x%x\n", context->uc_mcontext.gregs[REG_EDI]); 
		printf("eip           0x%x\n", context->uc_mcontext.gregs[REG_EIP]); 
		#elif defined(__x86_64__)
		printf("rax           0x%llx\n", context->uc_mcontext.gregs[REG_RAX]); 
		printf("rcx           0x%llx\n", context->uc_mcontext.gregs[REG_RCX]); 
		printf("rdx           0x%llx\n", context->uc_mcontext.gregs[REG_RDX]); 
		printf("rbx           0x%llx\n", context->uc_mcontext.gregs[REG_RBX]); 
		printf("rsp           0x%llx\n", context->uc_mcontext.gregs[REG_RSP]); 
		printf("rbp           0x%llx\n", context->uc_mcontext.gregs[REG_RBP]); 
		printf("rsi           0x%llx\n", context->uc_mcontext.gregs[REG_RSI]); 
		printf("rdi           0x%llx\n", context->uc_mcontext.gregs[REG_RDI]); 
		printf("rip           0x%llx\n", context->uc_mcontext.gregs[REG_RIP]); 
		#elif defined(__arm__)
		printf("R0           0x%lx\n", context->uc_mcontext.arm_r0); 
		printf("R1           0x%lx\n", context->uc_mcontext.arm_r1); 
		printf("R2           0x%lx\n", context->uc_mcontext.arm_r2); 
		printf("R3           0x%lx\n", context->uc_mcontext.arm_r3); 
		printf("R4           0x%lx\n", context->uc_mcontext.arm_r4); 
		printf("R5           0x%lx\n", context->uc_mcontext.arm_r5); 
		printf("R6           0x%lx\n", context->uc_mcontext.arm_r6); 
		printf("R7           0x%lx\n", context->uc_mcontext.arm_r7); 
		printf("R8           0x%lx\n", context->uc_mcontext.arm_r8); 
		printf("R9           0x%lx\n", context->uc_mcontext.arm_r9); 
		printf("R10          0x%lx\n", context->uc_mcontext.arm_r10);
		printf("FP           0x%lx\n", context->uc_mcontext.arm_fp); 
		printf("SP           0x%lx\n", context->uc_mcontext.arm_sp); 
		printf("LR           0x%lx\n", context->uc_mcontext.arm_lr); 
		printf("PC           0x%lx\n", context->uc_mcontext.arm_pc); 
		#endif
	}else{
		printf("context is null\n");
	}
	printf("\nKeep in mind we want our address to be %p\n",address_to_hit);
	fflush(stdout);
    exit(0);
}

void set_up_handlers(){
	// set up alternate stack
	stack_t sigstk;
	// https://pubs.opengroup.org/onlinepubs/9699919799/functions/sigaltstack.html
	if ((sigstk.ss_sp = malloc(SIGSTKSZ)) == NULL){
		perror("couldn't register alternate stack\n");
		exit(1);
	}
	sigstk.ss_size = SIGSTKSZ;
	sigstk.ss_flags = 0;
	if (sigaltstack(&sigstk,(stack_t *)0) < 0){
		perror("sigaltstack");
		exit(1);
	}
    
	struct sigaction act;
	memset(&act,0,sizeof(struct sigaction));
	sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO | SA_ONSTACK | SA_RESTART;
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

void call_strcpy(char* A){
	char buf[16];
	strcpy(buf, A);
}

int main(int argc, char* argv[]){
	set_up_handlers();
    printf("Hello to the string consumer 3000!\n");
	printf("It'd sure be neat if you could redirect flow to %p\n", address_to_hit);
    if (argc > 1){
        printf("You provided me a string! Great! I'll strcpy it!\n");
        call_strcpy(argv[1]);
    } else{
        printf("Provide your name as the first argument\n");
        printf("./demo jimbob\n");
    }
}
