//
// Created by Arthur Andrade - home on 25/10/24.
//
#ifndef CCSB_H // Clang custom string buffer
#define CCSB_H

// Define a pointer type for the string buffer structure
typedef struct strBuf *StrBuf;

// Function to create a new string buffer with an initial string
StrBuf NewSB(char*);

// Function to write a string to the buffer
int writeSB(StrBuf, char*);

// Function to write a single byte (character) to the buffer
int writeByteSB(StrBuf, char);

// Function to set a capacity to the buffer
int setCapSB(StrBuf, int);

// Function to retrieve the capacity from the buffer
int getCapSB(StrBuf);

// Function to retrieve the current usage from the buffer
int getLenSB(StrBuf sb);

// Function to retrieve the current string content from the buffer
char* getContentSB(StrBuf);

// Function to reset the buffer, clearing its content
int resetSB(StrBuf);

// Function to destroy the buffer
void destroySB(StrBuf*);

#endif // CCSB_H
