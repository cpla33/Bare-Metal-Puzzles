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