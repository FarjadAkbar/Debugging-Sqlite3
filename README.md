SQLite Debugger in Docker
This project demonstrates how to run and debug SQLite queries in a C program using Docker and VSCode. The setup allows you to compile the SQLite amalgamation and debug a sample main.c file step by step.

Prerequisites
Docker
Visual Studio Code
VSCode Extensions:
ms-vscode.cpptools (C/C++ IntelliSense, debugging, and code browsing)
ms-vscode-remote.remote-containers (Remote - Containers)
christiancollen.SQLite (SQLite extension for VSCode)


Getting Started
1. Building and Running the Container
Open the project in VSCode.
If prompted, open the project inside the Dev Container:
Go to View -> Command Palette (Ctrl + Shift + P) and type Remote-Containers: Reopen in Container.
The Dev Container will build automatically using the provided Dockerfile.


Set breakpoints in the main.c file.
Run the Build task from VSCode (Ctrl + Shift + B).
Start debugging (F5):
The debugger will attach, and you'll be able to step through the code line by line.
The launch.json configuration uses gdb to debug the compiled binary inside the container.