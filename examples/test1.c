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