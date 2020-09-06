#ifndef PCB_H
#define PCB_H

typedef struct PCB
{
    int pid;
    int PC_page;
    int PC_offset;
    int max_lines;
    int max_pages;
    int pageTable[10];
    int PC;
    
}PCB;

PCB* makePCB(int pid, int max_pages, int max_lines);

#endif

