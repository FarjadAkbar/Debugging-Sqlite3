# Use an official Debian base image
FROM debian:bullseye

# Install required packages: gcc, gdb, sqlite3 development libraries
RUN apt-get update && apt-get install -y \
    build-essential \
    gdb \
    wget

# Set the working directory inside the container
WORKDIR /usr/src/sqlite


# Copy SQLite amalgamation files and main.c into the container
COPY sqlite3.c sqlite3.h sqlite3ext.h main.c ./
COPY .devcontainer .devcontainer
COPY .vscode .vscode

# Compile the main.c program along with SQLite
RUN gcc -g -I. -o sqlite_app main.c sqlite3.c -lpthread -ldl

# Default command to run the program in debug mode
CMD ["/bin/bash"]
