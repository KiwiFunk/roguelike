typedef enum {
    ENTITY_TYPE_PLAYER,
    ENTITY_TYPE_ENEMY,
    ENTITY_TYPE_ITEM
} entity_type;

struct entity {
    int id;
    entity_type type;
    int x, y;
    int hp;
};
