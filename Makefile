# add a few convenience phony targets
.DEFAULT_GOAL := amd64
all : demo_i386 demo_amd64 demo_arm
x86_64 : demo_amd64
amd64: demo_amd64
arm: demo_arm
i386: demo_i386
.PHONY: all x86_64 amd64 arm i386

# We need an ARM cross compiler for ARM builds
ARM_CC=arm-linux-gnueabihf-gcc
I386_CC=gcc 
AMD64_CC=gcc 

# We turn off serveral security features: relro, stack protection, and PIE.
# We turn on debugging source and turn off optimizations. We also define
# a custom linker script.
CC_EXTRA_ARGS = -Wl,-z,norelro -fno-stack-protector -no-pie -ggdb -O0

# We must specify a different linker script for each architecture
# Additionally our i386 program needs the -m32 flag.
ARM_CC_EXTRA_ARGS=$(CC_EXTRA_ARGS) -Xlinker -T ld/modified_arm_linker_script.ld
I386_CC_EXTRA_ARGS=$(CC_EXTRA_ARGS) -m32 -Xlinker -T ld/modified_i386_linker_script.ld
AMD64_CC_EXTRA_ARGS=$(CC_EXTRA_ARGS) -Xlinker -T ld/modified_amd64_linker_script.ld

# this is the guts of the build
demo_i386: src/demo.c src/arch/bet_you_cant_i386.S
	$(I386_CC) src/demo.c src/arch/bet_you_cant_i386.S $(I386_CC_EXTRA_ARGS)  -o $@

demo_amd64: src/demo.c src/arch/bet_you_cant_amd64.S
	$(AMD64_CC) src/demo.c src/arch/bet_you_cant_amd64.S $(AMD64_CC_EXTRA_ARGS)  -o $@

demo_arm: src/demo.c src/arch/bet_you_cant_arm.S
	$(ARM_CC) src/demo.c src/arch/bet_you_cant_arm.S $(ARM_CC_EXTRA_ARGS)  -o $@

# easy cleanup
clean:
	rm -f demo_arm demo_amd64 demo_i386