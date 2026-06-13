#include <stdio.h>
#include "game.h"

int main()
{

    // Initialize the game
    struct game_state *state = game_init();

    // Check if allocation succeeded
    if (state == NULL) {
        fprintf(stderr, "Failed to initialize game\n");
        return 1;
    }

    state->state = GAME_STATE_RUNNING;

    for (int frame = 0; frame < 100; frame++) {
        game_update(state);
        game_render(state);
    }

    // Shutdown the game
    game_shutdown(state);

    return 0;
}
