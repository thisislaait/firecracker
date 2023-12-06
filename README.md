======================================
Simple Shell Implementation Workflow
======================================

### 0. Betty would be proud

- Write and format the code according to the Betty style guide.
- Ensure the code passes all Betty checks.

### 1. Simple shell 0.1

#### Input Handling

- Display a prompt and wait for user input.
- Read a command line, ending with a newline character.
- Handle "end of file" condition (Ctrl+D).

#### Command Execution

- Execute simple commands without arguments.
- Display the prompt after executing a command.
- Handle errors if the executable is not found.

### 2. Simple shell 0.2

#### Command Lines with Arguments

- Modify the shell to handle command lines with arguments.
- Parse and execute commands with provided arguments.
- Display the prompt after executing a command.

### 3. Simple shell 0.3

#### PATH Handling

- Implement PATH handling to locate executables.
- Check the existence of a command before forking a process.

### 4. Simple shell 0.4

#### exit Built-in

- Implement the exit built-in command to exit the shell.
- Display an error message if arguments are provided to exit.

### 5. Simple shell 1.0

#### env Built-in

- Implement the env built-in command to print the current environment.
- Test the env command in interactive mode.

### 6. Simple shell 0.1.1 (Advanced)

#### Custom getline Function

- Implement a custom getline function.
- Use a buffer to read multiple characters at once.
- Minimize the use of the read system call.
- Use static variables for efficient implementation.

### 7. Simple shell 0.2.1 (Advanced)

#### Avoid strtok

- Implement the shell without using the strtok function.
- Use alternative methods to tokenize input.

### 8. Simple shell 0.4.1 (Advanced)

#### Exit Status with exit

- Allow the exit built-in to accept an optional exit status.
- Display an error message if the exit status is not an integer.

### 9. setenv, unsetenv (Advanced)

#### Environment Variable Management

- Implement setenv and unsetenv built-in commands.
- setenv initializes or modifies an environment variable.
- unsetenv removes an environment variable.

### 10. cd Built-in

#### Change Directory

- Implement the cd built-in command to change the current directory.
- Handle the special case of "cd -" to switch to the previous directory.
- Update the PWD environment variable.

### 11. ; (Advanced)

#### Command Separator

- Implement the command separator (;) to execute multiple commands.

### 12. && and || (Advanced)

#### Logical Operators

- Implement the && and || logical operators to control command execution.

### 13. alias (Advanced)

#### Alias Built-in

- Implement the alias built-in command.
- Allow defining, printing, and listing aliases.

### 14. Variables (Advanced)

#### Variable Replacement

- Handle variables replacement in commands.
- Implement $? and $$ variable replacements.

### 15. Comments (Advanced)

#### Comment Handling

- Handle comments in commands (lines starting with #).

### 16. File as input (Advanced)

#### File Input Mode

- Modify the shell to accept a file as a command line argument.
- Execute commands from the file one line at a time.
- Do not print a prompt or read from stdin in this mode.

======================================
End of Simple Shell Implementation Workflow