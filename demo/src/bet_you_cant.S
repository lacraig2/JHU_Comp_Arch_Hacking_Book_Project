    .section .win_sec, "ax"
_bet_you_cant_get_here:
    adr r0, winstr
    bl puts
    movs r0, #0
    b exit
winstr:
    .ascii "  _____\n /     \\\n| () () |\n \\  ^  /\n  |||||\n  |||||\n\nOh no! There's haxx0rs in the mainframe!\n"
