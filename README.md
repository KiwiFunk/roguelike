# Roguelike Game
This is a simple work-in-progress roguelike game written in C. The game will feature a procedurally generated dungeon, basic combat mechanics, and a variety of items and enemies to encounter.

## Architecture
The game is structured around a few core systems: Entity Management, Rendering, Input Handling, and Game Logic. Each system is designed to be modular and independent, allowing for easy maintenance and future expansion.

### Entity Management
With our game, we need to call updates on each enitity around 60 times per second. Initially, we used an array of pointers to entities to keep each entity at a consistent memory address. However, this means every time we want to update every entity per frame, we end up pointer chasing and causing cache misses. But then, how do we keep updates efficient, whilst also handling the problem of other subsystems referencing entities that may be moved in memory?

Since this is a roguelike, and not a huge open world game, the solution is a simple ID Lookup Table. This allows us to store entities in an easy to traverse, contiguous block of memory, whilst also giving a way for subsystems to ensure they are referencing the correct entity, even if it has been moved in memory.

We can then keep out enitity pool perfectly compacted (if an entity is removed, we can move -1 to it's place), and when this happens, we can use that ID to find the new location. By pairing with a hash map, the lower entity count of this game means it will be very fast to find.

Lastly, we don't want to check every frame if an entity has moved in the pool, so we can yse event-driven programming to trigger an event when an entity is moved, and then update the lookup table accordingly. This way, we only pay the cost of updating the lookup table when an entity is actually moved, rather than every frame.

## Building
To build the project, you will need gcc and make installed on your system. Once you have those, you can run the following commands:

`make` - This will compile the source code and create an executable named `roguelike`.  
`make clean` - This will remove the compiled executable and any object files, allowing you to start fresh.  
`make run` - This will compile the code (if it hasn't been compiled already) and then run the `roguelike` executable.
