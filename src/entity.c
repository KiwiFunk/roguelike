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

void add_entity(struct entity_manager *em, struct entity *e) {
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
    if (em) {
        // Recursively destroy and release memory for all entities in the manager
        // Then free the entity array
        // finally the manager itself
        free(em);
    }
    em = NULL; // Avoid dangling pointer
}

// Entity Functions

struct entity* create_entity(entity_type type, int x, int y) {


}

void destroy_entity(struct entity *e) {
    // Destroy entity e and free memory
     if (e) {
        free(e);
    }
     e = NULL; // Avoid dangling pointer
}

// Convenience Functions

void spawn_entity() {

}
