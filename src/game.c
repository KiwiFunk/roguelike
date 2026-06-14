#include <stdio.h>
#include <stdlib.h>
#include  "game.h"

struct game_state* game_init() {

    // Allocate memory for the game state
    struct game_state *state = malloc(sizeof(struct game_state));

    // Check if malloc was successful
    if (state == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        // Return NULL to indicate failure to caller
        return NULL;
    }

    // Initialize the game state to menu
    state->state = GAME_STATE_MENU;
    state->curr_frame = 0;

    // Return address of game state (don't deference it here, just return the pointer)
    return state;
}

void game_update(struct game_state *gamestate){
    gamestate->curr_frame++;
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
