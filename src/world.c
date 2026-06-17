#include <stdio.h>
#include <stdlib.h>
#include "world.h"

struct world* world_create(int w, int h) {

    struct world* new_world = malloc(sizeof(struct world));
    if (!new_world) {
        fprintf(stderr, "Failed to allocate memory for world\n");
        return NULL;
    }

    tile_type *tiles = malloc(w * h * sizeof(tile_type));
    if (!tiles) {
        fprintf(stderr, "Failed to allocate memory for tiles\n");
        free(new_world);
        return NULL;
    }

    new_world->width = w;
    new_world->height = h;
    new_world->tiles = tiles;

    return new_world;                       // Return pointer to the newly created world
}

void world_destroy(struct world* w) {
    if (!w) return;

    free(w->tiles);                         // Free the tiles array
    free(w);                                // Free the world struct
}

tile_type world_get_tile(struct world* w, int x, int y) {

    if (!w || x < 0 || y < 0 || x >= w->width || y >= w->height) {
        fprintf(stderr, "Invalid coordinates for world_get_tile\n");
        return NULL;                        // Return NULL so calling function can handle
    }

    return w->tiles[(y * w->width) + x];    // i = (y * width) + x
}

void world_set_tile(struct world* w, int x, int y, tile_type type) {

    if (!w || x < 0 || y < 0 || x >=w->width || y >= w->height) {
        fprintf(stderr, "Invalid coordinates for world_set_tile\n");
        return;
    }

    w->tiles[(y * w->width) + x] = type;
    return;
}
