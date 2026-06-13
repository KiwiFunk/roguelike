typedef enum {
    GAME_STATE_MENU,
    GAME_STATE_RUNNING,
    GAME_STATE_EXIT
} GameState;

struct game_state {
    GameState state;
    int curr_frame;
};

// Explicitly declare that the function takes no parameters in C
struct game_state* game_init(void);

// read inputs

void game_update(struct game_state *state);

void game_render(struct game_state *state);

void game_shutdown(struct game_state *state);
