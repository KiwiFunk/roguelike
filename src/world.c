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

    // Split the room into two smaller rooms (left and right)
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

    // Split the room horizontally or vertically based on dimensions
    room_a->x = r->x;
    room_a->y = r->y;
    room_a->width = r-> width > r->height ? r->width / 2 : r->width;
    room_a->height = r->height > r->width ? r->height / 2 : r->height;

    room_b->x = r->x + room_a->width;
    room_b->y = r->y + room_a->height;
    room_b->width = r->width - room_a->width;
    room_b->height = r->height - room_a->height;

    // Assign to left and right child pointers of the room struct
    r->left = room_a;
    r->right = room_b;

    // Recursively traverse the BSP tree
    bsp_split(r->left, depth - 1, max_depth);
    bsp_split(r->right, depth - 1, max_depth);
}
