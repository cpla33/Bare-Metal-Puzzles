## An executable returning the OS-call response

This executable is able to launch the OS request hiddenly, returning the response only. It could be helpful for the compicated requests including subcommands like `grep` and so forth.

[go back](../README.md)

------

**1. Create the `test1.c` file as below:**


```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Requesting lsb release...\n\n");

    // requesting the name of the linux distro installed
    int result = system("lsb_release -a|grep Codename");

    if (result == -1) {
        perror("system"); // a standard C library function used to print a human-readable error message to stderr based on the current value of the global variable errno
        return 1;
    }

    return 0;
}
```

**2a. Compile it to create executable (for any architecture where the `gcc` compiler is installed):**

```sh
gcc test1.c -o test1
```

**2b. Cross-compilation for the Raspberri Pi (32-bit, Bullseye or Bookworm):**

```sh
# sudo apt install gcc-arm-linux-gnueabihf;
arm-linux-gnueabihf-gcc test1.c -o test1-rpi
```

**2c. Cross-compilation for the Raspberri Pi (64-bit, Bookworm):**

```sh
# // sudo apt install gcc-aarch64-linux-gnu;
aarch64-linux-gnu-gcc test1.c -o test1-rpi64
```

**3. Launch executable:**

```sh
chmod +x test1;
./test1
```