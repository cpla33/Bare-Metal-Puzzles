#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Requesting the bitness of the OS...\n\n");

    FILE *fp; // type (actually a structure) used to represent file streams
    char buffer[128]; // expecting the "32\n" or "64\n" string
    int bitness;

    // Run the command and open a pipe to read the output
    fp = popen("getconf LONG_BIT", "r"); // the architecture itself could be 64-bit however (easy to check with "uname -m" or "arch" commands)
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