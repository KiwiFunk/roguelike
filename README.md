# Roguelike Game
This is a simple work-in-progress roguelike game written in C. The game will feature a procedurally generated dungeon, basic combat mechanics, and a variety of items and enemies to encounter.

## Architecture
With entities, the manager has a pointer to an array of pointers to entities. This allows our array of pointers to be dynamically sized, whilst entities themselves keep the same memory address. If an entity is suddenly removed, we dont have to worry about its position in that array changing, as it still lives at the same memory address.

## Building
To build the project, you will need gcc and make installed on your system. Once you have those, you can run the following commands:

`make` - This will compile the source code and create an executable named `roguelike`.  
`make clean` - This will remove the compiled executable and any object files, allowing you to start fresh.  
`make run` - This will compile the code (if it hasn't been compiled already) and then run the `roguelike` executable.
