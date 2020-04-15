# **Simple Shell**

## **Description**

Simple_shell is a basic reproduction of the /bin/sh shell implemented with custom functions built during the course of Holberton School Trimester 0. It allows the user to input commands for the shell to execute, either internally or externally. It runs commands and then prompts the user for more input. This is the default behavior until the shell is terminated.

## **How it Works**

Simple_shell will tokenize the user's input, then check if the command they entered is an alias. If it is, the command is expanded to its aliased value. If not, simple_shell checks if the command is a builtin. If it is, it sends the command to its child process to execute. If it's not a builtin, simple_shell checks for the exectuable in the user's PATH, which is the default search path for executables. If it finds the executable in the PATH, simple_shell checks whether the calling process has the correct access permissions to the file it's calling. If it's not an alias or builtin, and simple_shell doesn't find it in the PATH, then the user inputted an invalid command. Simple_shell will print an error message to inform the user that their command is invalid, and will print the prompt (\$ ) again and wait for the user's next input.

## **Usage**

Simple_shell can be run both in interactive mode and non-interactive mode. Interactive mode indicates that the shell is connected to the STDIN and prints the prompt ($ ) accordingly. If run in non-interactive mode, no prompt ($ ) is printed. Also, the command and arguments must be piped into the shell at the command line.
