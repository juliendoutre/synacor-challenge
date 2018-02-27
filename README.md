# Synacor challenge 
A solution to the synacor challenge implemented in C.

## Introduction 

This project is a possible answer to the synacor challenge: https://challenge.synacor.com.

The goal of this challenge is to code a virtual machine able to read and execute the challenge.bin file.

The arch-spec file specifies all the characteristics the machine should have.

## Specifications

In this challenge, your job is to use this architecture spec to create a virtual machine capable of running the included binary. Along the way, you will find codes; submit these to the challenge website to track your progress.  

Good luck!

### architecture
- three storage regions
  - memory with 15-bit address space storing 16-bit values
  - eight registers
  - an unbounded stack which holds individual 16-bit values
- all numbers are unsigned integers 0..32767 (15-bit)
- all math is modulo 32768; 32758 + 15 =&gt; 5

### binary format
- each number is stored as a 16-bit little-endian pair (low byte, high byte)
- numbers 0..32767 mean a literal value
- numbers 32768..32775 instead mean registers 0..7
- numbers 32776..65535 are invalid
- programs are loaded into memory starting at address 0
- address 0 is the first 16-bit value, address 1 is the second 16-bit value, etc

### execution
- After an operation is executed, the next instruction to read is immediately after the last argument of the current operation.  If a jump was performed, the next operation is instead the exact destination of the jump.
- Encountering a register as an operation argument should be taken as reading from the register or setting into the register as appropriate.

### hints
- Start with operations 0, 19, and 21.
- Here's a code for the challenge website: bDEEQRplquKf
- The program "9,32768,32769,4,19,32768" occupies six memory addresses and should:
  - Store into register 0 the sum of 4 and the value contained in register 1.
  - Output to the terminal the character with the ascii code contained in register 0.

### opcode listing

- ```halt: 0```
  stop execution and terminate the program
- ```set: 1 a b```
  set register &lt;a&gt; to the value of &lt;b&gt;
- ```push: 2 a```
  push &lt;a&gt; onto the stack
- ```pop: 3 a```
  remove the top element from the stack and write it into &lt;a&gt;; empty stack = error
- ```eq: 4 a b c```
  set &lt;a&gt; to 1 if &lt;b&gt; is equal to &lt;c&gt;; set it to 0 otherwise
- ```gt: 5 a b c```
  set &lt;a&gt; to 1 if &lt;b&gt; is greater than &lt;c&gt;; set it to 0 otherwise
- ```jmp: 6 a```
  jump to &lt;a&gt;
- ```jt: 7 a b```
  if &lt;a&gt; is nonzero, jump to &lt;b&gt;
- ```jf: 8 a b```
  if &lt;a&gt; is zero, jump to &lt;b&gt;
- ```add: 9 a b c```
  assign into &lt;a&gt; the sum of &lt;b&gt; and &lt;c&gt; (modulo 32768)
- ```mult: 10 a b c```
  store into &lt;a&gt; the product of &lt;b&gt; and &lt;c&gt; (modulo 32768)
- ```mod: 11 a b c```
  store into &lt;a&gt; the remainder of &lt;b&gt; divided by &lt;c&gt;
- ```and: 12 a b c```
  stores into &lt;a&gt; the bitwise and of &lt;b&gt; and &lt;c&gt;
- ```or: 13 a b c```
  stores into &lt;a&gt; the bitwise or of &lt;b&gt; and &lt;c&gt;
- ```not: 14 a b```
  stores 15-bit bitwise inverse of &lt;b&gt; in &lt;a&gt;
- ```rmem: 15 a b```
  read memory at address &lt;b&gt; and write it to &lt;a&gt;
- ```wmem: 16 a b```
  write the value from &lt;b&gt; into memory at address &lt;a&gt;
- ```call: 17 a```
  write the address of the next instruction to the stack and jump to &lt;a&gt;
- ```ret: 18```
  remove the top element from the stack and jump to it; empty stack = halt
- ```out: 19 a```
  write the character represented by ascii code &lt;a&gt; to the terminal
- ```in: 20 a```
  read a character from the terminal and write its ascii code to &lt;a&gt;; it can be assumed that once input starts, it will continue until a newline is encountered; this means that you can safely read whole lines from the keyboard and trust that they will be fully read
- ```noop: 21```
  no operation


## Structure of the project

All the sources are in the vm folder.

- ```main.c```
    defines the memory array, the registers, initializes the stack and contains the main event loop
- ```stack.c```
    defines the structure used for the stack and its associated functions (push and pop)
- ```utils.c```
    defines 
    - the read function which read the memory, executes the proper operation following the opcode listing and returns the next operation adress
    - the load function which fill the memory array with the challenge.bin content
    - some debugging functions which show the state of the stack, the memory and the registers
- ```save.c```
    defines the save and load functions
- ```decipher.c```
    defines the function which translates the memory into a readable program
    

## Debugger 

In order to solve the teleporter enigma, I implemented some commands which can be used inside the game itself. 

Each command must begin with the '$' character. 

- ```reg``` 
    show the values in every registers
- ```setreg a b```
    set the value of the register a to b
- ```mem```
    show the different values of the memory
- ```memv a```
    show the a-th value of the memory
- ```stack```
    show the values stored in the stack
- ```source```
    write into the file ```sources.txt``` the content of the memory in a more readable way than just with opcodes
- ```save```
    save the current game (create a ```save.txt``` file)
- ```load```
    load the game state saved in the ```save.txt``` file
- ```debug```
    toggle the debug mode. When it is on, every memory operation is stored in the ```debugging.txt```file under the same format as in ```sources.txt``` 