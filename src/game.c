#include <stdio.h>
#include <stdlib.h>
#include  "game.h"

struct game_state* create_game_state() {

    struct game_state *state = malloc(sizeof(struct game_state));

    if (state == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    // Initialize the game state to menu
    state->state = GAME_STATE_MENU;
    state->curr_frame = 0;

    // Return address of game state (don't deference it here, just return the pointer)
    return state;
}

void game_init() {


}

void game_update(struct game_state *gamestate){
    gamestate->curr_frame++;
    entity_update_all(gamestate->em);
}

void game_render(struct game_state *gamestate) {
    printf("Current frame: %d\n", gamestate->curr_frame);
}

void game_shutdown(struct game_state *gamestate) {
    free(gamestate);
    gamestate = NULL;
    printf("Game shutdown successfully\n");
    return;
}
