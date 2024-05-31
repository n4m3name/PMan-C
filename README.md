# PMan - C

A simple process manager written in C

*Assignment 1 of CSC360: Operating Systems, University of Victoria - Summer 2024*

## Usage
### **Compiling:**
A makefile (based on that from assignment helper files) has been provided: In order to compile, run `make`.  

**\+ Note:** `# commented` install rules have been provided in the makefile which add the executable to the path. (This cannot be done on the UVic server.)

### **Running:**
To use pman, run the executable `./pman` within the `A1` folder. (If you've added the executable to the path, run `pman`).  

The following list of available commands can be accessed with the `h` command during use:
```
    bg <path>        - Start a program in the background
    bgkill <pid>     - Kill a background program
    bgkill a         - Kill all background programs
    bglist           - List all running background programs
    bgstart <pid>    - Start a stopped background program
    bgstop <pid>     - Stop a running background program
    pstat <pid>      - Display statistics of a background program
    q                - Quit the program
```
Where:
- \<path\> is the path to executable (or the command if in path)
- \<pid\> is the process id (use `bglist` for running pid's)

I recommend running `bgkill a` **before** quitting - this way no processes will be left running indefinitely adter exiting the program. 

**\+ Note:** The convention that 1:=running 0:=stopped is used in the output of `bglist` and `pstat`.

### **Testing:**
The provided tester program `./inf` has been edited to be more usable with pman. No tags are printed to the terminal - this way many instances can be run, stopped, started, and inspected using the above commands without making a mess in the terminal. Sleep has been replaced with usleep to verify utime, stime when running `pstat`.  

`./inf` should be compiled by running the make command in the `A1` folder. To start an instance of it while using pman, run the command `bg ./inf`.  

The current implementation should work with any basic linux program whether executable or in the path, although functionality is lost for interactive programs (such as vim, nano) since I can't launch separate terminals from the school server.