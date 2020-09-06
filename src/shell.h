#ifndef SHELL_H
#define SHELL_H

void displayCode(int errorCode,char* command);
int parse(char ui[]);
int shellUI();

#endif