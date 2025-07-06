## An executable reusing the OS call response

This executable is able to determine and process hidden OS request and reuse it for some calculations. While the `uname -m` or `arch` commands could return the bitness of the CPU (usually 64-bit today), the the number of bits in a `long int` type is equal to the OS-bitness.

| Type      | Size (in bits) on 64-bit Linux | Size on 32-bit Linux |
| --------- | ------------------------------ | -------------------- |
| `int`     | 32 bits                        | 32 bits              |
| `long`    | 64 bits                        | 32 bits              |
| `pointer` | 64 bits                        | 32 bits              |

In Linux, the bitness of the system typically matches the bitness of the kernel, which in turn reflects in the size of data types like `long`.

[go back](../README.md)

------

**1. Create the `test2.c` file as below:**

```sh
nano test2.c
```


```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Requesting the bitness of the OS...\n\n");

    FILE *fp; // type (actually a structure) used to represent file streams
    char buffer[128]; // expecting the "32\n" or "64\n" string to get
    int bitness;

    // Run the command and open a pipe to read the output
    fp = popen("getconf LONG_BIT", "r"); // the architecture itself could be 64-bit,
    //however (easy to check with "uname -m" or "arch" commands)
    if (fp == NULL) {
        perror("popen");
        return 1;
    }

    // Read the output from the command
    if (fgets(buffer, sizeof(buffer), fp) != NULL) {
        // Convert the result to an integer
        bitness = atoi(buffer);
        printf("Detected OS bitness: %d-bit\n", bitness);

        // Example calculation using the bitness
        int memory_words = bitness / 8;
        printf("Assuming one word = %d bytes\n", memory_words);
    } else {
        fprintf(stderr, "Failed to read output from getconf\n");
    }

    pclose(fp); // closes the stream opened by popen
    return 0;
}
```

**2a. Compile it to create executable (for the current OS where the `gcc` compiler is installed):**

```sh
gcc test2.c -o test2
```

**2b. Cross-compilation for the Raspberri Pi (32-bit, Bullseye or Bookworm):**

```sh
# sudo apt install gcc-arm-linux-gnueabihf;
arm-linux-gnueabihf-gcc test2.c -o test2-rpi32
```

**2c. Cross-compilation for the Raspberri Pi (64-bit, Bookworm):**

```sh
# // sudo apt install gcc-aarch64-linux-gnu;
aarch64-linux-gnu-gcc test2.c -o test2-rpi64
```

**3. Launch executable:**

```sh
chmod 755 test2;
./test2
```