arm-linux-gnueabihf-gcc demo.c bet_you_cant.S -Wl,-z,norelro  -fno-stack-protector -no-pie -ggdb -O0 -Xlinker -T default_arm.ld  -o demo
