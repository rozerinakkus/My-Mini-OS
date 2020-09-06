
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "ram.h"
#include "cpu.h"
#include "kernel.h"
#include "shell.h"
#include "memorymanager.h"



void resetRAM();
void removeFrame(int ind);

ReadyQueueNode* head = NULL;
ReadyQueueNode* tail = NULL;
ReadyQueueNode* oldhead = NULL;
int sizeOfQueue = 0;

char *RAM[40];
CPU* cpu;


int main(int argc, char const *argv[]){
    int error  = 0;
    boot();
    error  = kernel();
    return error;
}


int kernel()
{
    shellUI();
}

int boot(){
    //reset every slot of the ram before kernel()
    resetRAM();

    //remove previously created BackingStore folder 
    system("rm -r BackingStore");

    //Create new BackingStore folder
    system("mkdir BackingStore");
    

    return 0;
}

void addToReady(PCB* pcb) {
    //creade new readyquqeuenode pointer 
    ReadyQueueNode* newNode = malloc(sizeof(ReadyQueueNode));

    newNode->aPCB = pcb;
    //last in the ready queue
    newNode->next = NULL;
    if (head == NULL){
        head = newNode;
        tail = newNode;
    } else {

        //fixin the pointers 
        tail->next = newNode;
        tail = newNode;
        tail->aPCB = pcb;
    }
   
}


void scheduler(){
    cpu = malloc(sizeof(CPU));
    cpu->quanta = 2;

    while((head != NULL) && (head != tail->next)){
        int flag = 0;

        PCB* toRemove = head->aPCB;
        if(toRemove->pageTable[toRemove->PC_page] == -1) pageFault(toRemove);

        //copy from pcb to cpu
        cpu->IP = toRemove->pageTable[toRemove->PC_page];	    
        cpu->offset = toRemove->PC_offset;

        oldhead = head;
        int numInstr = toRemove->max_lines- ((toRemove->PC_page) * 4 + toRemove->PC_offset);
        
        //if the number of instructions are more than the  quanta 
        if(numInstr > cpu->quanta){
        	flag = run(cpu->quanta);
        	if(flag == 1){
        		toRemove->PC_offset = 0;
        		(toRemove->PC_page)++;

                //if the pageFault is resolved, add the pcb  to the end o the ready queue
        		if(pageFault(toRemove) == 0) addToReady(toRemove); 
        	}
        	else{
        		toRemove->PC_offset = cpu->offset;
        		toRemove->PC = (cpu->IP) * 4 + cpu->offset;
                addToReady(toRemove);	//adding pcb to the end of the ready queue
        	}
        }
        //if there are less instructions than the quanta
        else{
        	flag = run(numInstr);
            for(int i = 0; i < 10; i++){
            	if(toRemove->pageTable[i] != -1){
            		int ind = (toRemove->pageTable[i]) * 4;
                    removeFrame(ind);
            	}
            }
            deleteStorageFile(toRemove->pid);
            free(oldhead);
        }
        head = head->next;
    }
    head = NULL;
    tail = head;

    //reset ram when the scheduler is done
    resetRAM(); 
    
       
}


void resetRAM(){
    //resetting the ram array

    for(int i = 0; i < 40; i++) {
        RAM[i] = NULL;
    }
}


void removeFrame(int ind){
    //removing the 4 array slots corrsponding to a frame starting from the given index 
    for (int i = 0; i<4; i++){
        RAM[ind+i] = NULL;
    }

}