#include "room.h"
#include "tile.h"
#include <curses.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define DEBUG 1

int player_characters[] = {'^', '>', 'v', '<'};
tile_t *on_tile = NULL;
room_t rooms[] = {{.spawn = {.x = 9, .y = 4},
                   .direction = WEST,
                   .tiles =
                       {
                           // walls
                           [2][3] = 0b01000011,
                           [2][4] = 0b00000011,
                           [2][5] = 0b00000011,
                           [2][6] = 0b00000011,
                           [2][7] = 0b00000011,
                           //    [2][7] = {.type = WALL, .gate_style = {.char_idx = 1, .color = 2}},
                           [2][8] = 0b00000011,
                           [2][9] = 0b00000011,
                           [2][10] = 0b01100011,
                           [3][3] = 0b10100011,
                           [3][2] = 0b01000011,
                           [3][10] = 0b00100011,
                           [4][2] = 0b00100011,
                           [4][10] = 0b00100011,
                           [5][2] = 0b10000011,
                           [5][3] = 0b01100011,
                           [5][10] = 0b00100011,
                           [6][3] = 0b10000011,
                           [6][4] = 0b00000011,
                           [6][5] = 0b00000011,
                           [6][6] = 0b00000011,
                           [6][7] = 0b00000011,
                           [6][8] = 0b00000011,
                           [6][9] = 0b00000011,
                           [6][10] = 0b10100011,
                           // gate
                           [4][3] = 0b00000110,
                       }},
                  {.spawn = {.x = 9, .y = 4},
                   .direction = WEST,
                   .tiles = {
                       // walls
                       [2][3] = 0b01000011,
                       [2][4] = 0b00000011,
                       [2][5] = 0b00000011,
                       [2][6] = 0b00000011,
                       [2][7] = 0b00000011,
                       [2][8] = 0b00000011,
                       [2][9] = 0b00000011,
                       [2][10] = 0b01100011,
                       [3][3] = 0b10100011,
                       [3][2] = 0b01000011,
                       [3][10] = 0b00100011,
                       [4][2] = 0b00100011,
                       [4][10] = 0b00100011,
                       [5][2] = 0b10000011,
                       [5][3] = 0b00000011,
                       [5][4] = 0b00000011,
                       [5][5] = 0b00000011,
                       [5][6] = 0b00000011,
                       [5][7] = 0b00000011,
                       [5][8] = 0b00000011,
                       [5][9] = 0b00000011,
                       [5][10] = 0b10100011,
                       // gate
                       [4][3] = 0b00000010,
                   }}};

struct
{
    point_t pos;
    uint8_t coins;
    direction_t direction;
    struct
    {
        point_t pos;
        direction_t direction;
        uint32_t room_idx;
    } previous_room;
    uint32_t room_idx;
} player = {.coins = 0x1, .previous_room = {.room_idx = -1}};
uint32_t direction_to_coords[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

void enter_room(int room_idx)
{
    int is_previous_room = player.previous_room.room_idx == room_idx;

    point_t saved_pos = player.pos;
    direction_t saved_direction = player.direction;

    if (is_previous_room)
    {

        player.previous_room.direction = (player.previous_room.direction + 2) % 4;
        int *coords = direction_to_coords[player.previous_room.direction];
        player.previous_room.pos.x += coords[0];
        player.previous_room.pos.y += coords[1];

        player.pos = player.previous_room.pos;
        player.direction = player.previous_room.direction;
    }
    else
    {
        room_t *room = &rooms[room_idx];
        player.pos = room->spawn;
        player.direction = room->direction;
    }
    player.previous_room.direction = saved_direction;
    player.previous_room.pos = saved_pos;
    player.previous_room.room_idx = player.room_idx;
    player.room_idx = room_idx;
}

void move_checked(direction_t direction, int room_idx)
{
    int *coords = direction_to_coords[direction];
    int x = coords[0];
    int y = coords[1];

    tile_t *next_tile = &rooms[room_idx].tiles[player.pos.y + y][player.pos.x + x];
    // nice try wall clippers :sunglasses:
    if (next_tile->type == WALL || on_tile->type == WALL)
    {
        return;
    }
    player.pos.x += x;
    player.pos.y += y;
}

void keypress(int ch, int room_idx)
{
    switch (ch)
    {
    case KEY_DOWN:;
        move_checked(player.direction = SOUTH, room_idx);
        break;
    case KEY_UP:
        move_checked(player.direction = NORTH, room_idx);
        break;
    case KEY_LEFT:
        move_checked(player.direction = WEST, room_idx);
        break;
    case KEY_RIGHT:
        move_checked(player.direction = EAST, room_idx);
        break;
    case 'q':
        endwin();
        exit(0);
        break;
    case 'p':
    {
        on_tile->type = COIN;
        on_tile->pile.coins = player.coins;
        player.coins = 0;
        break;
    }
    case 'g':
    {
        if (on_tile->type == COIN)
        {
            player.coins += on_tile->pile.coins;
            on_tile->byte = 0;
        }
        break;
    }
    // reset the player
    case 'r':
    {
        player.pos = rooms[0].spawn;
        player.direction = rooms[0].direction;
        player.previous_room.room_idx = -1;
        player.coins = 0;
        player.room_idx = 0;
        break;
    }
    default:
        break;
    }
}

void draw_walls(point_t room_start)
{
    attron(COLOR_PAIR(COLOR_MAGENTA));
    for (int i = 0; i < ROOM_HEIGHT; ++i)
    {
        move(room_start.y + i, room_start.x - 1);
        addch(ACS_VLINE);
        move(room_start.y + i, room_start.x + ROOM_WIDTH);
        addch(ACS_VLINE);
    }
    move(room_start.y - 1, room_start.x - 1);
    addch(ACS_ULCORNER);
    for (int i = 0; i < ROOM_WIDTH; ++i)
    {
        addch(ACS_HLINE);
    }
    addch(ACS_URCORNER);
    move(room_start.y + ROOM_HEIGHT, room_start.x - 1);
    addch(ACS_LLCORNER);
    for (int i = 0; i < ROOM_WIDTH; ++i)
    {
        addch(ACS_HLINE);
    }
    addch(ACS_LRCORNER);
    attroff(COLOR_PAIR(COLOR_MAGENTA));
}

int main()
{
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);

    open_flag();

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            init_pair(j + i * 8, j, i);
        }
    }
    wbkgd(stdscr, COLOR_PAIR(0));
    int wall_characters[] = {ACS_HLINE, ACS_VLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER, '?', '?'};

    point_t room_start;
    getmaxyx(stdscr, room_start.y, room_start.x);
    room_start.x = (room_start.x - ROOM_WIDTH) / 2;
    room_start.y = (room_start.y - ROOM_HEIGHT) / 2;

    enter_room(0);
    int ch;
    for (;;)
    {
        int room_idx = player.room_idx;
        for (int i = 0; i < 40; i++)
        {
            on_tile = &rooms[room_idx].tiles[player.pos.y][player.pos.x];
            if ((ch = getch()) != ERR)
            {
                keypress(ch, room_idx);
            }
        }
        on_tile = &rooms[player.room_idx].tiles[player.pos.y][player.pos.x];
        if (on_tile->type == GATE)
        {
            enter_room(on_tile->gate.to);
        }
        draw_walls(room_start);

        // render tiles
        room_t *room = &rooms[player.room_idx];
        for (int i = 0; i < ROOM_HEIGHT; ++i)
        {
            move(room_start.y + i, room_start.x);
            for (int j = 0; j < ROOM_WIDTH; ++j)
            {
                tile_t *tile = &room->tiles[i][j];
                int color = COLOR_PAIR(tile->style.fg + (tile->type != WALL ? (tile->style.bg * 8) : 0));
                attron(color);
                switch (tile->type)
                {
                case FLOOR:
                    addch(' ');
                    break;
                case WALL:
                    addch(wall_characters[tile->wall.idx]);
                    break;
                case GATE:
                    addch(ACS_DIAMOND);
                    break;
                case COIN:
                    addch(ACS_DEGREE);
                    break;
                }
                attroff(color);
            }
        }

        attron(COLOR_PAIR(COLOR_WHITE));

        move(room_start.y - 1, room_start.x);
        printw("room %ld", player.room_idx);

        move(room_start.y + ROOM_HEIGHT, room_start.x);
        addstr("term-zelda");

        move(room_start.y + ROOM_HEIGHT + 2, room_start.x);
        addstr(" [p]ut    [g]et ");
        move(room_start.y + ROOM_HEIGHT + 3, room_start.x);
        addstr(" [r]eset  [q]uit ");

#if DEBUG
        char *directions[] = {"NORTH", "EAST", "SOUTH", "WEST"};

        move(room_start.y - 1, room_start.x + ROOM_WIDTH + 2);
        printw("x: %d, y: %d    ", player.pos.x, player.pos.y);
        move(room_start.y, room_start.x + ROOM_WIDTH + 2);
        printw("direction: %d (%s)    ", player.direction, directions[player.direction]);

        move(room_start.y + 2, room_start.x + ROOM_WIDTH + 2);
        printw("last_x: %d, last_y: %d    ", player.previous_room.pos.x, player.previous_room.pos.y);
        move(room_start.y + 3, room_start.x + ROOM_WIDTH + 2);
        printw("last_direction: %s    ", directions[player.previous_room.direction]);

        move(room_start.y + 4, room_start.x + ROOM_WIDTH + 2);
        printw("room_idx: %d    ", player.previous_room.room_idx);
        move(room_start.y + 5, room_start.x + ROOM_WIDTH + 2);
        printw("tile_addr: %p    ", on_tile);

#endif

        attroff(COLOR_PAIR(COLOR_WHITE));

        attron(COLOR_PAIR(COLOR_YELLOW));

        move(room_start.y - 1, room_start.x + 13);
        printw("%xc", player.coins);

        attroff(COLOR_PAIR(COLOR_YELLOW));

        // draw player
        move(room_start.y + player.pos.y, room_start.x + player.pos.x);
        attron(COLOR_PAIR(COLOR_CYAN));
        addch(player_characters[player.direction]);
        attroff(COLOR_PAIR(COLOR_CYAN));

        refresh();
    }
}

// this is not necessary, but since the challenge is already very long :D
void open_flag()
{
    for (int i = 0; i < 10; i++)
        printf("%d", open("flag.txt", O_RDONLY));
}