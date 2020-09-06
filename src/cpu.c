#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"ram.h"
#include"interpreter.h"
#include"shell.h"
#include "cpu.h"

#define DEFAULT_QUANTA 2
const int MAX_OFFSET=4;

// typedef struct CPU{ 
//     int IP; 
//     char IR[1000]; 
//     int quanta; 
//     int offset;
// } CPU;

int run(int quanta){
    //only runs the default quanta  = 2 instructions  even if the quanta is bigger 
    
        while(quanta > 0){
        //calculate the address index
    	int ind = (cpu->IP) * MAX_OFFSET +(cpu->offset);
        strcpy(cpu->IR, RAM[ind]);
        parse(cpu->IR);
        
        cpu->offset++;
        if(cpu->offset >= MAX_OFFSET) return 1;
        quanta--;
    }
    return 0;
}
