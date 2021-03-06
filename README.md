# JHU Comp Arch 605.611 Book Project

## Why?

This project attempts to create a starter buffer overflow that is slightly easier to use for use by undergraduates seeing their very first buffer overflow example.

It does so in the following ways:

- Creates fault handlers to make the program easier to redirect without GDB. It has some explanations on common errors and tells you where your program exited.
- It positions target code at a static virtual memory address that fits up with a buffer overflow ASCII string "HACK".

## How?

Signal handlers and modified linker scripts. I wrote up a blog post about some more details [here](nolinkhere.yet).

## Quick start

Replace arch with your architecture. Either i386, x86_64, or arm.

```bash
make arch
```

Go read the [problem statements](ProblemStatements.md). They're not too long and they hopefully help you solve the problem.

When you finish go see the solution [win.sh](win.sh).

```bash
./win.sh arch
```

### Building

#### i386 and x86_64 targets

```bash
make i386
make x86_64
```

### ARM target

If you aren't on an ARM machine you'll need an arm cross compiler to build the ARM binary.

You may either use the [Dockerfile](./Dockerfile) we provided that does this or just get any ARM cross compiler.

#### Dockerfile

This should build the `demo_arm` target.

```bash
./build_docker.sh
./run_docker.sh
```

#### Else

On Ubuntu:

```bash
sudo apt-get install gcc-arm-linux-gnueabihf 
```

### Running

You can either run the binary itself or use our run script to run the binary. The run script takes the following format:

```bash
./run.sh arch string
```

For example:

```bash
./run.sh i386 AAAAAAAAAAA
```

### Winning

Solutions are up in the `./win.sh` script. It takes the form:

```bash
./win.sh arch
```

For example:

```bash
./win.sh i386
```
