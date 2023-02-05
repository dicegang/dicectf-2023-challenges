#ifndef TILE
#define TILE

#include <stdint.h>

typedef struct
{
    uint8_t x;
    uint8_t y;
} point_t;

typedef enum
{
    FLOOR,
    COIN,
    GATE,
    WALL,
} tile_type_t;

typedef union
{
    uint8_t byte;
    tile_type_t type : 2;
    struct
    {
        uint8_t : 2, to : 6;
    } gate;
    struct
    {
        uint8_t : 2, coins : 6;

    } pile;
    struct
    {
        uint8_t : 2, : 3, idx : 3;
    } wall;
    struct
    {
        uint8_t : 2, fg : 3, bg : 3;
    } style;
} __attribute__((packed)) tile_t;

#endif