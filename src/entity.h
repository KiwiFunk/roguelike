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
    entity_type type;
    int x, y;
    int hp;
};

struct entity_manager {
    entity entities[INITIAL_CAPACITY];
    int count;                          // Track current number of entities
    int capacity;                       // Track current capacity of array
};

// Entity manager functions
struct entity_manager* init_entity_manager();
void cleanup_entity_manager(struct entity_manager* manager);

// Entity functions
struct entity* create_entity(entity_type type, int x, int y);
void destroy_entity(struct entity* e);
