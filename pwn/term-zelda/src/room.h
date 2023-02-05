#ifndef ROOM
#define ROOM

#include "tile.h"

#define ROOM_WIDTH 16
#define ROOM_HEIGHT 8

typedef enum
{
    NORTH,
    EAST,
    SOUTH,
    WEST
} direction_t;

typedef struct
{
    point_t spawn;
    uint16_t flags;
    direction_t direction;
    uint8_t seed;
    tile_t tiles[ROOM_HEIGHT][ROOM_WIDTH];
} __attribute__((packed)) room_t;

#endif