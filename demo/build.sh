arm-linux-gnueabihf-gcc src/demo.c src/bet_you_cant.S -Wl,-z,norelro  -fno-stack-protector -no-pie -ggdb -O0 -Xlinker -T default_arm.ld  -o demo
