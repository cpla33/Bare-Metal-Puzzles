---
layout: default
title: Bare Metal Puzzles
---

# Bare Metal Puzzles

A growing number of simple yet powerful low-level sketches.

-----------

### 1. An executable returning the OS call response

**a). Create the `test1.c` file as below:**

> ```c
> #include <stdio.h>
> #include <stdlib.h>
>
>int main() {
>    printf("Requesting 'history'...\n\n");
>
>    int result = system("history|grep ssh");
>     
>    if (result == -1) {
>        perror("system");
>        return 1;
>    }
>     
>    return 0;
>}


**b). Compile it to create executable for `x86` architecture:**

> `gcc test1.c -o test1`

Compile it for the Raspberri Pi (running ordinary 32-bit OS):

> `// sudo apt install gcc-arm-linux-gnueabihf`
> `arm-linux-gnueabihf-gcc test1.c -o test1-rpi`

Compile it for the Raspberri Pi (running ordinary 32-bit OS):

> `// sudo apt install gcc-aarch64-linux-gnu`
> `aarch64-linux-gnu-gcc test1.c -o test1-rpi64`


**c). Launch executable:**

> `// chmod +x test1-rpi`
> `./test1`