#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "shellmemory.h"
#include "memorymanager.h"
#include "shell.h"
#include "kernel.h"

#define TRUE 1
#define FALSE 0

int set(char * words[]){
    char* varName = words[1];
    char* value = words[2];
    int errorCode = setVariable(varName,value);
    return errorCode;
}

int print(char * words[]){

    char* varName = words[1];
    char* value = getValue(varName);

    if (strcmp(value,"_NONE_")==0) {
        printf ("VARIABLE DOES NOT EXIST\n");
    } else {
        printf("%s\n",value);
    }
    return 0;
}

static int run(char * words[]){

    char * filename = words[1];
    FILE * fp = fopen(filename,"r");
    int errorCode = 0;
    // if file cannot be opened, return ERRORCODE -3
    if (fp==NULL) return -3;
    char buffer[1000];
    printf(" STARTING EXECUTION OF %s \n",filename);
    while (!feof(fp)){
        fgets(buffer,999,fp);
        errorCode = parse(buffer);
        if (errorCode == 1) {
            errorCode = 0;
            break;
        } else if (errorCode != 0) {
            buffer[strlen(buffer)-2]='\0';
            displayCode(errorCode,buffer);
            break;
        }
    }
    printf("TERMINATING EXECUTION OF %s \n",filename);
    fclose(fp);
    return 0;
}

int exec(char *words[]){
    printf("\tSTARTING ALL CONCURRENT PROGRAMS\n");
    int errorCode = 0;
    int index = 1; 
     while(strcmp(words[index], "_NONE_") != 0){
        FILE *file = fopen(words[index], "r");
        if (file == NULL) {
            printf("SCRIPT '%s' NOT FOUND.\n", words[index]);
            return 1;
        }
        errorCode = launcher(file);
        if(errorCode == -7) printf("SCRIPT '%s' HAS MORE THAN 10 PAGES\n", words[index]);
        if(errorCode != 0){
            return 1;
        } 
        index++;
    }
    scheduler();

    printf("\tTERMINATING ALL CONCURRENT PROGRAMS\n");
    return errorCode;
}


int interpreter(char* words[]){
    //default errorCode if no error occurred AND user did not enter the "quit" command
    int errorCode = 0;
    //At this point, we are checking for each possible commands entered
    if ( strcmp(words[0],"help") == 0 ) {
        
        // if it's the "help" command, we display the description of every commands
        printf("-------------------------------------------------------------------------------------------------------\n");
        printf("COMMANDS\t\t\tDESCRIPTIONS\n");
        printf("-------------------------------------------------------------------------------------------------------\n");
        printf("help\t\t\t\tDisplays all commands\n");
        printf("quit\t\t\t\tTerminates the shell\n");
        printf("set VAR STRING\t\t\tAssigns the value STRING to the shell memory variable VAR\n");
        printf("print VAR\t\t\tDisplays the STRING value assigned to the shell memory variable VAR\n");
        printf("run SCRIPT.TXT\t\t\tExecutes the file SCRIPT.txt\n");
        printf("exec p1 p2 p3\t\t\tExecutes programs p1 p2 p3 concurrently\n");
        printf("-------------------------------------------------------------------------------------------------------\n");

    } else if ( strcmp(words[0],"quit") == 0) {

        // if it's the "quit" command
        //errorCode is 1 when user voluntarily wants to quit the program.
        errorCode = 1;

    } else if ( strcmp(words[0],"set") == 0 ) {
       
        // If one argument missing, return ERRORCODE -2 for invalid number of arguments
        if ( ( strcmp(words[1],"_NONE_") == 0 ) || ( strcmp(words[2],"_NONE_") == 0 ) ) {
            errorCode = -2;
        } else {
            // ERRORCODE -1 : Out of Memory might occur
            errorCode = set(words);
        }
    }  else if ( strcmp(words[0],"print") == 0 ) {
        
        if ( strcmp(words[1],"_NONE_") == 0 ) return -2;

        // Call the print function
        errorCode = print(words);

    } else if ( strcmp(words[0],"run") == 0 ) {
        
        if ( strcmp(words[1],"_NONE_") == 0 ) return -2;

        
        errorCode = run(words);
    } else if ( strcmp(words[0],"exec") == 0 ) {
        if ( strcmp(words[1],"_NONE_") == 0  || strcmp(words[4],"_NONE_") != 0 ) return -2;

        errorCode = exec(words);
    } else {
        // Error code for unknown command
        errorCode = -4;
    }

    return errorCode;
    
}