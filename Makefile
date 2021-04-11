# We need an ARM cross compiler
CC=arm-linux-gnueabihf-gcc
# We turn off serveral security features: relro, stack protection, and PIE.
# We turn on debugging source and turn off optimizations. We also define
# a custom linker script.
CC_EXTRA_ARGS=-Wl,-z,norelro -fno-stack-protector -no-pie -ggdb -O0 -Xlinker -T ld/modified_arm_linker_script.ld

demo: src/demo.c src/bet_you_cant.S
	$(CC) src/demo.c src/bet_you_cant.S $(CC_EXTRA_ARGS)  -o $@

clean:
	rm demo