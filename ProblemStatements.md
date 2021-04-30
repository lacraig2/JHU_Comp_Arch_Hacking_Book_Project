# Problem Statements

In Problem One we saw how we can use a buffer overflow vulnerability to write past the bounds of our buffer and change other variables on the stack. One of the items stored on the stack in our program is our return address, which indicates where the program should return after finishing a function. If we manage to overwrite this value we can use our buffer overflow to change the execution path of the program. In the following section you will discover the length required to change the return address of the program, format the address of a given function as a string to make the program reach the function, and then explain how we can fix our program. A simplified version of the vulnerable C function is as follows:

```C
    int main(int argc, char* argv[]){
        char buf[10];
        strcpy(buf, argv[1]);
        return 0;
    }
```

## Part A

In this program we have a vulnerability. The `strcpy` function will copy as many bytes as we enter on the command line and write it into a limited buffer of length 10 on the stack. If you write a string longer than 10 it will begin to write past its buffer length and will eventually modify the return address. Find the minimum length string required to crash the program. Record your string and the output of the program.
  
## Part B

Now that we have modified the return address and crashed the program let's focus on making it go somewhere we'd like to go. To make this easier we have placed a function at 0x4b434148. Adjust your string from the first part until the return address goes to 0x4b434148. Record your string and the output of the program.

## Part C

Discuss how you might fix this program such that it is no longer vulnerable to the buffer overflow.
