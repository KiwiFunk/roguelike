#include <stdlib.h>
#include <stdio.h>
#include "entity.h"

struct entity_manager* init_entity_manager() {

    struct entity_manager* em = malloc(sizeof(struct entity_manager));
    if (!em) {
        fprintf(stderr, "Failed to allocate memory for entity manager\n");
        return NULL;
    }

    em->count = 0;
    em->capacity = INITIAL_CAPACITY;

    // Allocate memory for entity array and set pointer
    em->entities = malloc(INITIAL_CAPACITY * sizeof(struct entity));
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
    // Check entity manager exists (not Null) and has space
    // Handle case where entity manager is full (count >= capacity)
    // If full, realloc
    // Add memory address of e to em array and increment count
     if (em == NULL) {
        fprintf(stderr, "Entity manager is NULL\n");
        return;
    }
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

struct entity* create_entity(entity_type type, int x, int y) {


}

void destroy_entity(struct entity *e) {

}
