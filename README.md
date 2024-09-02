# ModuShell

This is an introduction to the project. For a technical report, please refer to [this](https://github.com/FlightVin/ModuShell/blob/main/REPORT.md).

## Table of Contents
1. [Overview](#overview)
2. [Key Accomplishments](#key-accomplishments)
    - [Command Execution and Process Management](#command-execution-and-process-management)
    - [Background Process Management](#background-process-management)
    - [Advanced Features](#advanced-features)
    - [Signal Handling](#signal-handling)
    - [Autocompletion](#autocompletion)
    - [Built-In Commands](#built-in-commands)

## Overview

This is a C-Shell project - a comprehensive implementation of a Unix-like command-line shell in the C programming language. This project was developed to showcase a deep understanding of operating system principles, process management, and system programming. The shell provides an intuitive and efficient interface for executing commands, managing background processes, and handling various Unix features like I/O redirection, piping, and signals.

## Key Accomplishments

### Command Execution and Process Management
The C-Shell successfully implements a robust command execution system that supports both foreground and background processes. Users can chain commands using `;` and `&` operators, similar to Unix terminals. The shell ensures efficient process handling, with foreground processes being monitored for execution time and background processes being tracked and managed effectively.

### Background Process Management
C-Shell includes comprehensive management for background processes. When a command is executed in the background using the `&` operator, the shell tracks the process and allows users to monitor or control it through built-in commands like `jobs`, `fg`, `bg`, and `sig`. This feature enhances multitasking capabilities within the shell, providing users with a more flexible and powerful environment for handling multiple processes simultaneously.

### Advanced Features
The shell includes advanced features such as I/O redirection, allowing users to direct output to files or take input from files seamlessly. Piping between commands is also supported, enabling complex command sequences where the output of one command becomes the input for the next.

### Signal Handling
The C-Shell is equipped with comprehensive signal handling capabilities. It responds to common signals such as `^C` for terminating processes, `^Z` for pushing processes to the background, and `^D` for logging out of the shell. These features contribute to a smooth and user-friendly experience.

### Autocompletion
An intuitive autocompletion feature is included, enhancing the user experience by providing suggestions based on the current input. This feature mimics the behavior of modern Unix shells, offering a list of possible file or directory names when the `tab` key is pressed, or completing the name if there's only one match.

### Built-In Commands
The shell supports a variety of built-in commands such as `echo`, `cd`, `pwd`, `exit`, `ls`, `pinfo`, `history`, `discover`, `jobs`, `sig`, `fg`, and `bg`. These commands cover essential functionalities, from navigating the filesystem to managing processes and retrieving system information.
