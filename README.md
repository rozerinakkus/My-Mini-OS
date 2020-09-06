# My-Mini-OS


## Compiling the shell
  ### Compiling manualy 
  ```bash
  gcc -c memorymanager.c shell.c interpreter.c shellmemory.c kernel.c cpu.c pcb.c ram.c memorymanager.c
  gcc -o mykernel memorymanager.o shell.o interpreter.o shellmemory.o kernel.o cpu.o pcb.o ram.o
  ```
  ### Compiling with make file
  ```bash
  make
  ```
## Running the kernal
```bash
./mykernel
```
## The promtline
```bash
Kernel 1.1 loaded!
Welcome to the Rozerin's Kernel!
Kernel Version 1.2 Created March 2020
$
```
## Testing Kernel
```bash
./mykernel < testfile.txt
```
## Commands:
  * help: Displays all the commands
  * quit: Exits / terminates the shell with “Bye!”
  * set VAR STRING: Assigns a value to shell memory
  * print VAR: Prints the STRING assigned to VAR
  * run SCRIPT.TXT : Executes the file SCRIPT.TXT
  * exec P1 P2 P3: Executes concurrent programs
