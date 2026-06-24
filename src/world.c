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

void world_is_walkable(){
    // Check if the tile at (x, y) is walkable (i.e., not a wall)
    // Return true if walkable, false otherwise
}

// Binary Space Partitioning (BSP) algorithm to split the world into rooms and corridors.
// Room Node to traverse, depth in the bsp tree, and max depth to stop recursion
void bsp_split(struct room *r, int curr_depth, int max_depth) {
    if (curr_depth >= max_depth) {
        r->left = NULL;
        r->right = NULL;
        return;
    }

    // Handle memory allocation
    struct room *room_a = malloc(sizeof(struct room));
    struct room *room_b = malloc(sizeof(struct room));

    if (!room_a || !room_b) {
        fprintf(stderr, "Failed to allocate memory for rooms\nAbort at iteration depth %d\n", depth);
        free(room_a);
        free(room_b);
        r->left = NULL;
        r->right = NULL;
        return;
    }

    // Handle splitting logic
    int split_vertical = r->width > r->height;

    if (split_vertical == 1) {
        // Split left/right (X changes)
        int split_point = r->width / 2;

        room_a->x = r->x;
        room_a->y = r->y;
        room_a->width = split_point;
        room_a->height = r->height;

        room_b->x = r->x + split_point;
        room_b->y = r->y;
        room_b->width = r->width - split_point;
        room_b->height = r->height;
    } else {
        // Split top/bottom (Y changes)
        int split_point = r->height / 2;

        room_a->x = r->x;
        room_a->y = r->y;
        room_a->width = r->width;
        room_a->height = split_point;

        room_b->x = r->x;
        room_b->y = r->y + split_point;
        room_b->width = r->width;
        room_b->height = r->height - split_point;
    }

    r->left = room_a;
    r->right = room_b;

    // Recursively call func
    bsp_split(r->left, curr_depth + 1, max_depth);
    bsp_split(r->right, curr_depth + 1, max_depth);
}
