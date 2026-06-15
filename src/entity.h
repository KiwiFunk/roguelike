typedef enum {
    ENTITY_TYPE_PLAYER,
    ENTITY_TYPE_ENEMY,
    ENTITY_TYPE_ITEM
} entity_type;

// Macros
#define MAX_ENTITIES 100                // Cap for maximum entities in memory at once
#define INITIAL_CAPACITY 10             // Initial size of entity array

// Structures
struct entity {
    int id;
    int x, y;
    int hp;
    entity_type type;
};

struct entity_manager {
    int count;                                  // Track current number of entities
    int capacity;                               // Track current capacity of array
    struct entity **entities;                   // Point to dynamically allocated array of entity pointers
};

// Entity manager functions
struct entity_manager* init_entity_manager();
void add_entity(struct entity_manager* em, struct entity* e);
void cleanup_entity_manager(struct entity_manager* em);

// Entity functions
struct entity* create_entity(entity_type type, int x, int y);
void destroy_entity(struct entity* e);

// Convenience functions
void spawn_entity(entity_type type, int x, int y, struct entity_manager *em);
