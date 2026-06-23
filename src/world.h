typedef enum {
    TILE_FLOOR,
    TILE_WALL,
    TILE_CORRIDOR
} tile_type;

struct world {
    int width, height;
    tile_type *tiles;       // i = (y * width) + x
};

struct room {
    int x, y;               // Top-left corner of the room
    int width, height;      // Dimensions of the room
    struct room *left;      // Pointers to left and right child rooms for BSP tree structure
    struct room *right;
};

struct world* world_create(int w, int h);
void world_destroy(struct world* w);

tile_type world_get_tile(struct world* w, int x, int y);
void world_set_tile(struct world* w, int x, int y, tile_type type);
bool is_walkable(struct world* w, int x, int y);
