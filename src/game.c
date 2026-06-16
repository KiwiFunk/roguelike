#include <stdio.h>
#include <stdlib.h>
#include  "game.h"

struct game_state* game_init() {

    struct game_state *state = malloc(sizeof(struct game_state));

    if (state == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    state->state = GAME_STATE_MENU;         // Initialize the game state to menu
    state->curr_frame = 0;
    state->em = NULL;                       // Entities only persist during gameplay

    // Return address of game state (don't deference it here, just return the pointer)
    return state;
}

void game_start(struct game_state *gamestate) {
    gamestate->state = GAME_STATE_RUNNING;
    gamestate->em = init_entity_manager();
    spawn_player(0, 0, 100, 50, gamestate->em);
    spawn_enemy(5, 5, 50, 10, 2, gamestate->em);
    spawn_item(3, 3, 20, 0, gamestate->em);
}

void game_update(struct game_state *gamestate){
    gamestate->curr_frame++;

    if(gamestate->em != NULL){
        entity_update_all(gamestate->em);
    }
}

void game_render(struct game_state *gamestate) {
    printf("Current frame: %d\n", gamestate->curr_frame);

    for (size_t i = 0; i < gamestate->em->count; i++) {
        struct entity *e = &gamestate->em->entities[i];

        printf(
            "Entity ID: %d, Type: %d, Position: (%d, %d)\n",
            e->id,
            e->type,
            e->x,
            e->y
        );
    }
}

void game_shutdown(struct game_state *gamestate) {
    free(gamestate);
    gamestate = NULL;
    printf("Game shutdown successfully\n");
    return;
}
