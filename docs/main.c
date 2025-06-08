#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Running 'ifconfig'...\n\n");
    
    int result = system("lsusb|grep Synaptics");
    
    if (result == -1) {
        perror("system");
        return 1;
    }
    
    return 0;
}

