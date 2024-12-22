# Custom Shell Program

This is a simple custom shell program written in C. It can execute built-in commands (cd, exit), and launch external programs by creating child processes. This project is aimed at practicing the implementation of a basic command-line shell.

<h2>Features</h2>

* Custom Shell program that reads user input, splits it into tokens, and executes the appropriate commands.
* Built-int commands:
  * cd: Changes the current working directory.
  * exit: Exits the shell program.
* Supports running external programs (e.g., ls, echo, etc.).
* Continuously prompts for input until the exit command is invoked.

<h2>Requirements</h2>

* C Compiler: The shell is written in C, so you'll need a C Compiler to build it.
* Linux/macOS: The program uses POSIX functions (fork, execvp, chdir, etc.), so it is designed to work on Unix-based systems. Windows users may need a POSIX compatibility layer (e.g., Cygwin or WSL) to run the program.

<h2>Installation</h2>

To install the project and build the shell program, follow these steps:
1. Clone the Repository:<br>

  git clone [https://github.com/yourusername/custom-shell.git](https://github.com/SohamPrabhu/customshell.git)

  
2. Use the makefile to build the shell:<br>

  make

3. Run the shell after compiling, you can run it with:<br>

  ./shell

<h2>Usage</h2>

Once the shell starts, you will see a prompt ($). You can enter commands as follows:

* cd <directory>: Changes the current directory.
* exit: Exits the shell program.
* any other command that is support on a Unix-based system.

<h2>Code Overview</h2>

* main.c: The main file that contains the core logic of the shell.
  * main_loop(): The primary loop that keeps the shell running and prompts the user for input.
  * main_cd(): Handles the cd command.
  * main_exit(): Handles the exit command.
  * main_size_builtIn(): Returns the number of built-in commands.
  * main_read_line(): Reads a line of input from the user.
  * main_split_line(): Splits the input line into individual tokens (arguments).
  * main_launch(): Launches an external program by forking a child process and using execvp.
  * main_execute(): Executes a built-in or external command.






  

