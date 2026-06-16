typedef enum {
    ENTITY_TYPE_PLAYER,
    ENTITY_TYPE_ENEMY,
    ENTITY_TYPE_ITEM
} entity_type;

// Compiler should pad to 4 bytes for alignment, try to keep same size
typedef struct {
    int hp;
    int attack_power;
    int speed;
} EnemyData;

typedef struct {
    int heal_amount;
    int is_key_item;
} ItemData;

typedef struct {
    int max_hp;
    int mana;
} PlayerData;

// Macros
#define MAX_ENTITIES 100                // Cap for maximum entities in memory at once
#define INITIAL_CAPACITY 10             // Initial size of entity array

// Structures
struct entity {
    int id;                             // Unique identifier for entity
    int x, y;
    entity_type type;
    union {                             // Use union - entity will only use one set per instance
        EnemyData enemy_data;
        ItemData item_data;
        PlayerData player_data;
    } data;
};

struct entity_manager {
    int count;                          // Track current number of entities
    int capacity;                       // Track current capacity of array
    int next_id;                        // Track next available ID for new entities
    struct entity *entities;            // Point to start of entities (dynamically allocated array)
};

// Entity manager functions
struct entity_manager* init_entity_manager();
void cleanup_entity_manager(struct entity_manager* em);

// Entity functions
void spawn_enemy(int x, int y, int hp, int attack_power, int speed, struct entity_manager *em);
void spawn_item(int x, int y, int heal_amount, int is_key_item, struct entity_manager *em);
void spawn_player(int x, int y, int max_hp, int mana, struct entity_manager *em);
void destroy_entity_at_index(struct entity_manager* em, int target);
