int main() {
    FILE *fp;
    char buffer[256];
    char arch[128] = {0}; // initializes all elements of the arch array to zero (i.e., null characters), because strings in C rely on the null terminator ('\0') to mark the end

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