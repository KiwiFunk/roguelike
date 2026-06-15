#include <stdlib.h>
#include <stdio.h>
#include "entity.h"

// Entity Manager Functions

struct entity_manager* init_entity_manager() {

    struct entity_manager* em = malloc(sizeof(struct entity_manager));
    if (!em) {
        fprintf(stderr, "Failed to allocate memory for entity manager\n");
        return NULL;
    }

    em->count = 0;
    em->capacity = INITIAL_CAPACITY;

    // Allocate memory for entity array and set pointer
    em->entities = malloc(INITIAL_CAPACITY * sizeof(struct entity *));
    // If malloc fails, free em and return NULL
    if (!em->entities) {
        fprintf(stderr, "Failed to allocate memory for entity array\n");
        free(em);
        return NULL;
    }

    // Return memory address for entity manager (Don't dereference)
    return em;
}

static void add_entity(struct entity_manager *em, struct entity *e) {
    // Null checks
    if (em == NULL || e == NULL) {
        fprintf(stderr, "Failed to add entity: Manager or Entity is NULL\n");
        if (e) destroy_entity(e); // Clean up if entity valid but !manager
        return;
    }

    // Check em has capacity for new entity (count < capacity)
    if (em->count >= em->capacity) {

        if (em->capacity >= MAX_ENTITIES) {
            fprintf(stderr, "Cannot add entity: Reached maximum capacity of %d\n", MAX_ENTITIES);
            destroy_entity(e);  // Clean up entity to avoid memory leak since failed to add to em
            return;
        }

        int new_capacity = em->capacity * 2;
        if (new_capacity > MAX_ENTITIES) {
            new_capacity = MAX_ENTITIES;
        }

        // Realloc to a tempory pointer to avoid losing reference to original memory if realloc fails
        struct entity **temp = realloc(em->entities, new_capacity * sizeof(struct entity *));

        // Gracefully handle realloc failure and clean up new enitiy with warning
        if (temp == NULL) {
            fprintf(stderr, "Failed to reallocate memory for entity array\n");
            destroy_entity(e);
            return;
        }

        // Update em with new address (realloc handles copying data and cleaning up old pointer)
        em->entities = temp;
        em->capacity = new_capacity;
        printf("Em capacity increased to %d\n", em->capacity);
    }

    // Add pointer to new entity to em array and increment count
    em->entities[em->count] = e;
    em->count++;
}

void cleanup_entity_manager(struct entity_manager* em) {

    if(!em) {
        fprintf(stderr, "Entity manager is NULL, nothing to clean up\n");
        return;
    }

    // Clean up each entity belonging to the entity manager
    for (int i = 0; i < em->count; i++) {
        destroy_entity(em->entities[i]);    // Pointers can be called with array notation
    }

    free(em->entities);         // Free the array of entity pointers
    free(em);                   // Free the entity manager itself
    em = NULL;                  // Avoid dangling pointer
}

// Entity Functions

// Internal base function, keep static (private)
static struct entity* create_entity(entity_type type, int x, int y) {

    struct entity* e = malloc(sizeof(struct entity));
    if (!e) {
        fprintf(stderr, "Failed to allocate memory for entity\n");
        return NULL;
    }

    e->id = rand(); // Assign random - Change later
    e->x = x;
    e->y = y;
    e->type = type;

    return e;
}

static struct entity* create_enemy(int x, int y, int hp, int attack_power, int speed) {
    struct entity* e = create_entity(ENTITY_TYPE_ENEMY, x, y);
    if (!e) return NULL;

    e->data.enemy_data.hp = hp;
    e->data.enemy_data.attack_power = attack_power;
    e->data.enemy_data.speed = speed;

    return e;
}

static struct entity* create_item(int x, int y, int heal_amount, bool is_key_item) {
    struct entity* e = create_entity(ENTITY_TYPE_ITEM, x, y);
    if (!e) return NULL;

    e->data.item_data.heal_amount = heal_amount;
    e->data.item_data.is_key_item = is_key_item;

    return e;
}

static struct entity* create_player(int x, int y, int max_hp, int mana) {
    struct entity* e = create_entity(ENTITY_TYPE_PLAYER, x, y);
    if (!e) return NULL;

    e->data.player_data.max_hp = max_hp;
    e->data.player_data.mana = mana;

    return e;
}

void destroy_entity(struct entity *e) {
    // Destroy entity e and free memory
     if (e) {
        free(e);
    }
     e = NULL; // Avoid dangling pointer
}

// Public Functions
void spawn_enemy(int x, int y, int hp, int attack_power, int speed, struct entity_manager *em) {
    struct entity* e = create_enemy(x, y, hp, attack_power, speed);
    add_entity(em, e);
    return;
}

void spawn_item(int x, int y, int heal_amount, bool is_key_item, struct entity_manager *em) {
    struct entity* e = create_item(x, y, heal_amount, is_key_item);
    add_entity(em, e);
    return;
}

void spawn_player(int x, int y, int max_hp, int mana, struct entity_manager *em) {
    struct entity* e = create_player(x, y, max_hp, mana);
    add_entity(em, e);
    return;
}
