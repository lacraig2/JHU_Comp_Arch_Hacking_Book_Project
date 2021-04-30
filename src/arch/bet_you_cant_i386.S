.section .win_sec,"awx",@progbits
_bet_you_cant_get_here:
    push winstrptr
    call puts
    push $0
    call exit
winstr:
    .string "  _____\n /     \\\n| () () |\n \\  ^  /\n  |||||\n  |||||\n\nOh no! There's haxx0rs in the mainframe!\n"
winstrptr:
    .long winstr