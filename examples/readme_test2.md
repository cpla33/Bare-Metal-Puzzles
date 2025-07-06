## An executable reusing the OS call response

[go back](../README.md)

------

**1. Create the `test2.c` file as below:**


```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Requesting 'history'...\n\n");

    // requesting the name of the linux distro installed
    int result = system("lsb_release -a|grep Codename");

    if (result == -1) {
        perror("system");
        return 1;
    }

    return 0;
}
```

**2a. Compile it to create executable (for any architecture where the `gcc` compiler is installed):**

```sh
gcc test2.c -o test2
```

**3. Cross-compilation for the Raspberri Pi:

```sh
# sudo apt install gcc-arm-linux-gnueabihf;
arm-linux-gnueabihf-gcc test2.c -o test2-rpi
```

or:

```sh
# // sudo apt install gcc-aarch64-linux-gnu;
aarch64-linux-gnu-gcc test2.c -o test2-rpi64
```

**c). Launch executable:**

```sh
chmod +x test2-rpi;
./test1
```