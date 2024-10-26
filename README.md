# CCSB (Clang Custom String Buffer)

**CCSB** is a simple implementation of a string buffer in C used and created by me, so I decided to share it with anyone who wants to use it. It enhances ergonomics in string manipulation and provides a simple and efficient interface for manipulate strings without the overhead of excessive memory allocation.

## Features

- **Simple Interface**: Offers easy-to-use functions for string manipulation.
- **Efficient Memory Management**: Implements a reallocation system to avoid memory wastage.

## Usage 

Here is a simple example demonstrating how to use CCSB:

```c
#include "ccsb.h"
#include <stdio.h>

int main(void) {
    // Create a new string buffer
    StrBuf sb = NewSB("Hello");
    if (sb == NULL) {
        fprintf(stderr, "Failed to create string buffer.\n");
        return 1;
    }

    // Write more strings to the buffer
    writeSB(sb, ", world!");
    writeByteSB(sb, ' ');
    writeSB(sb, "This is a test.");

    // Retrieve and print the content of the buffer
    char* content = getContentSB(sb);
    if (content != NULL) {
        printf("String Buffer Content: %s\n", content);
        free(content);
    }

    // Print the current capacity and length of the buffer
    printf("Capacity: %d\n", getCapSB(sb));
    printf("Length: %d\n", getLenSB(sb));

    // Reset the buffer
    resetSB(sb);

    // Clean up
    destroySB(&sb);
    
    return 0;
}
