#include <stdio.h>
#include <stdlib.h>
#include "pcb.h"

PCB* makePCB(int pid, int max_pages, int max_lines){
    PCB* pcb = (PCB*)malloc(sizeof(PCB));
    pcb->PC = 0;
    pcb->PC_offset =0;
    pcb->PC_page=0;
     pcb->max_pages = max_pages;
    pcb->max_lines = max_lines;
    pcb->pid = pid;
    for(int i = 0; i < 10; i++) {
        pcb->pageTable[i] = - 1;
    }
    return pcb;
}
