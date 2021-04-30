.section .win_sec,"awx",@progbits
_bet_you_cant_get_here:
    mov winstrptr, %rdi
    call puts
    movq $0, %rdi
    call exit
winstr:
    .string "  _____\n /     \\\n| () () |\n \\  ^  /\n  |||||\n  |||||\n\nOh no! There's haxx0rs in the mainframe!\n"
winstrptr:
    .quad winstr