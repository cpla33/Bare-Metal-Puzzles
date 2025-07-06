## An executable reusing the OS call response

This executable is able to determine and process hidden OS request and reuse it for some calculations. While the `uname -m` or `arch` commands could return the bitness of the CPU (usually 64-bit today), the the number of bits in a `long int` type is equal to the OS-bitness.

| Response  | Description |
| --------- | ----------- | 
| `x86_64`     | 64-bit Intel/AMD |
| `i686` or `i386`    | 32-bit Intel |
| `armv7l` | 32-bit ARM |
| `aarch64` | 64-bit ARM |

In Linux, the bitness of the system typically matches the bitness of the kernel, which in turn reflects in the size of data types like `long`.

[go back](../README.md)

------

**1. Create the `test3.c` file as below:**

```sh
touch test3.c;
gedit test3.c
```


```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp;
    char buffer[256];
    char arch[128] = {0}; // initializes all elements of the arch array to zero (i.e., null characters),
    // because strings in C rely on the null terminator ('\0') to mark the end

    printf("Detecting CPU architecture...\n\n");

    // Run the command to get CPU architecture
    fp = popen("uname -m", "r");
    if (fp == NULL) {
        perror("popen failed");
        return 1;
    }

    // Read the output into buffer
    if (fgets(buffer, sizeof(buffer), fp) != NULL) {
        // Remove newline
        buffer[strcspn(buffer, "\n")] = 0;
        strncpy(arch, buffer, sizeof(arch) - 1);
    }

    // Close the process
    int status = pclose(fp);
    if (status == -1) {
        perror("pclose failed");
    }

    // Identify architecture (by searching the substring in the given string)
    if (strcmp(arch, "x86_64") == 0) {
        printf("Detected: 64-bit Intel/AMD (x86_64)\n");
    } else if (strcmp(arch, "i686") == 0 || strcmp(arch, "i386") == 0) {
        printf("Detected: 32-bit Intel (i686/i386)\n");
    } else if (strcmp(arch, "armv7l") == 0) {
        printf("Detected: 32-bit ARM (armv7l)\n");
    } else if (strcmp(arch, "aarch64") == 0) {
        printf("Detected: 64-bit ARM (aarch64)\n");
    } else {
        printf("Unknown or unsupported architecture: %s\n", arch);
    }

    return 0;
}
```
-----

## Compilation:

**Compile it to create executable for the current OS where the `gcc` compiler is installed (64-bit Intel/AMD):**

```sh
gcc test3.c -o test3
```
-----
## Cross-compilation:

**Raspberry Pi (ARM64, 32-bit OS: Bullseye or Bookworm):**

```sh
# sudo apt install gcc-arm-linux-gnueabihf;
arm-linux-gnueabihf-gcc test3.c -o test3-rpi32
```

**Raspberry Pi (ARM, 64-bit OS: Bookworm):**

```sh
# // sudo apt install gcc-aarch64-linux-gnu;
aarch64-linux-gnu-gcc test3.c -o test3-rpi64
```

**BeagleBone Black (32-bit ARMv7):**

```sh
# // sudo apt install gcc-arm-linux-gnueabihf;
arm-linux-gnueabihf-gcc test3.c -o test3-armv7
```

**Allwinner D1 (64-bit RISC-V):**

Assuming to get an ELF-file.

```sh
# // sudo apt install gcc-riscv64-linux-gnu;
riscv64-linux-gnu-gcc test3.c -o test3-riscv
```
-----

## Launching executable:

```sh
chmod u=rwx,g=rx,o=rx test3;
./test3
```