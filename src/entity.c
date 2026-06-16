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
    em->next_id = 1;

    // Allocate memory for entity array and set pointer
    em->entities = malloc(INITIAL_CAPACITY * sizeof(struct entity));

    // If malloc fails, free em and return NULL
    if (!em->entities) {
        fprintf(stderr, "Failed to allocate memory for entity array\n");
        free(em);
        return NULL;
    }
    return em;                  // Return memory address for entity manager (Don't dereference)
}

void cleanup_entity_manager(struct entity_manager* em) {
    if (!em) return;

    free(em->entities);         // Flat array, All entities are purged when freeing em->entities.
    free(em);
}

// Mem Pipeline

static void resize_entity_manager(struct entity_manager* em) {
    if (em->capacity >= MAX_ENTITIES) {
        fprintf(stderr, "Warning: Reached hard maximum entity cap of %d\n", MAX_ENTITIES);
        return;
    }

    int new_capacity = em->capacity * 2;
    if (new_capacity > MAX_ENTITIES) {
        new_capacity = MAX_ENTITIES;
    }

    // realloc to a tempory pointer to avoid losing reference to original memory if realloc fails
    struct entity *temp = realloc(em->entities, new_capacity * sizeof(struct entity));
    if (temp == NULL) {
        fprintf(stderr, "Critical: Failed to reallocate entity pool storage\n");
        return;
    }

    // Update em with new address (realloc handles moving data and cleaning up old pointer)
    em->entities = temp;
    em->capacity = new_capacity;
    printf("Entity manager expanded capacity to %d\n", em->capacity);
}

void destroy_entity_at_index(struct entity_manager* em, int target) {
    if (!em || target < 0 || target >= em->count) return;

    int last_index = em->count - 1;

    // Swap and compact
    if (target != last_index) {
        em->entities[target] = em->entities[last_index];
    }

    // Decrement count to 'remove' last entiry from pool. This will be overwritten on next add_entity call.
    em->count--;
}

// Spawning Logic

static struct entity* get_next_free_slot(struct entity_manager* em) {

    // Check if allocated capacity is sufficient, if not attempt to expand
    if (em->count >= em->capacity) {
        resize_entity_manager(em);
    }

    // Handle limit
    if (em->count >= em->capacity) {
        fprintf(stderr, "Error: Reached maximum entity capacity of %d\n", MAX_ENTITIES);
        return NULL;
    }

    // Use pointer arithmetic to get address of next free slot and increment count to reserve it
    struct entity* slot = &em->entities[em->count];
    em->count++;

    // Set baseline properties
    slot->id = em->next_id++;

    return slot;
}

// Public Spawn Functions
void spawn_enemy(int x, int y, int hp, int attack_power, int speed, struct entity_manager *em) {
    struct entity* e = get_next_free_slot(em);
    if (!e) return;

    e->type = ENTITY_TYPE_ENEMY;
    e->x = x;
    e->y = y;
    e->data.enemy_data.hp = hp;
    e->data.enemy_data.attack_power = attack_power;
    e->data.enemy_data.speed = speed;
}

void spawn_item(int x, int y, int heal_amount, int is_key_item, struct entity_manager *em) {
    struct entity* e = get_next_free_slot(em);
    if (!e) return;

    e->type = ENTITY_TYPE_ITEM;
    e->x = x;
    e->y = y;
    e->data.item_data.heal_amount = heal_amount;
    e->data.item_data.is_key_item = is_key_item;
}

void spawn_player(int x, int y, int max_hp, int mana, struct entity_manager *em) {
    struct entity* e = get_next_free_slot(em);
    if (!e) return;

    e->type = ENTITY_TYPE_PLAYER;
    e->x = x;
    e->y = y;
    e->data.player_data.max_hp = max_hp;
    e->data.player_data.mana = mana;
}

// Update Functions
void entity_update_all(struct entity_manager *em) {
    for (int i = 0; i < em->count; i++) {
        struct entity *e = &em->entities[i];    // Dereference to get entity at index i
        // Placeholder for entity-specific update logic    }
}
