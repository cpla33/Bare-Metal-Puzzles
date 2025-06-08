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

`gcc test1.c -o test1`

**c). Launch executable:**

`./test1`