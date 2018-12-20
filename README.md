# Synacor challenge 
A solution to the synacor challenge implemented in C.

## Introduction 

This project is a possible answer to the synacor challenge: https://challenge.synacor.com.

The goal of this challenge is to code a virtual machine able to read and execute the `challenge.bin` file.

The `arch-spec` file specifies all the characteristics the machine should have.

## Structure of the project

All the sources are in the vm folder.

- `main.c`
    defines the memory array, the registers, initializes the stack and contains the main event loop
- `stack.c`
    defines the structure used for the stack and its associated functions (push and pop)
- `utils.c`
    defines 
    - the read function which read the memory, executes the proper operation following the opcode listing and returns the next operation adress
    - the load function which fill the memory array with the challenge.bin content
    - some debugging functions which show the state of the stack, the memory and the registers
- `save.c`
    defines the save and load functions
- `decipher.c`
    defines the function which translates the memory into a readable program
    

## Debugger 

In order to solve the teleporter enigma, I implemented some commands which can be used inside the game itself. 

Each command must begin with the `$` character. 

- `reg` 
    show the values in every registers
- `setreg a b`
    set the value of the register a to b
- `mem`
    show the different values of the memory
- `memv a`
    show the a-th value of the memory
- `stack`
    show the values stored in the stack
- `source`
    write into the file `sources.txt` the content of the memory in a more readable way than just with opcodes
- `save`
    save the current game (create a `save.txt` file)
- `load`
    load the game state saved in the `save.txt` file
- `debug`
    toggle the debug mode. When it is on, every memory operation is stored in the `debugging.txt`file under the same format as in `sources.txt` 