#ifndef SHELLMEMORY_H
#define SHELLMEMORY_H

int setVariable (char * varName, char * value);
char* getValue (char *var);

void shellmemInit();
void shellmemFree();

#endif