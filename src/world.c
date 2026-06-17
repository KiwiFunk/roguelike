#include <stdio.h>
#include <stdlib.h>
#include "world.h"

struct world* world_create(int w, int h) {

    // Allocate memory for the world struct
    struct world* new_world = malloc(sizeof(struct world));
    if (!new_world) {
        fprintf(stderr, "Failed to allocate memory for world\n");
        return NULL;
    }

    // Allocate memory for the tiles array
    tile_type *tiles = malloc(w * h * sizeof(tile_type));
    if (!tiles) {
        fprintf(stderr, "Failed to allocate memory for tiles\n");
        free(new_world);
        return NULL;
    }

    // Set properties
    new_world->width = w;
    new_world->height = h;
    new_world->tiles = tiles;

    return new_world;               // Return pointer to the newly created world
}
