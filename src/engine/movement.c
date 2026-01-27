#include "engine.h"

// ստուգում է, արդյոք տրված դիրքում կարելի է շարժվել
static int can_move(t_map *map, int x, int y)
{
    if (!map || !map->grid)
        return 0;

    char c = map->grid[y][x];
    if (c == '1') // '1' = wall
        return 0;
    return 1;
}

void    move_forward(t_cub *cub)
{
    double  new_x;
    double  new_y;

    new_x = cub->player.x + cub->player.dir_x * 0.1;
    new_y = cub->player.y + cub->player.dir_y * 0.1;
    if (cub->game.map.grid[(int)cub->player.y][(int)new_x] != '1')
        cub->player.x = new_x;
    if (cub->game.map.grid[(int)new_y][(int)cub->player.x] != '1')
        cub->player.y = new_y;
}

// շարժում ետ
void move_backward(t_cub *cub)
{
    int new_x = cub->game.map.player_x;
    int new_y = cub->game.map.player_y;

    if (cub->game.map.player_dir == 'N')
        new_y += MOVE_SPEED;
    else if (cub->game.map.player_dir == 'S')
        new_y -= MOVE_SPEED;
    else if (cub->game.map.player_dir == 'E')
        new_x -= MOVE_SPEED;
    else if (cub->game.map.player_dir == 'W')
        new_x += MOVE_SPEED;

    if (can_move(&cub->game.map, new_x, new_y))
    {
        cub->game.map.player_x = new_x;
        cub->game.map.player_y = new_y;
    }
}

// ուղղությունը փոփոխելու ֆունկցիա (ճոճել դեպի ձախ/աջ)
void turn_left(t_cub *cub)
{
    if (cub->game.map.player_dir == 'N') cub->game.map.player_dir = 'W';
    else if (cub->game.map.player_dir == 'W') cub->game.map.player_dir = 'S';
    else if (cub->game.map.player_dir == 'S') cub->game.map.player_dir = 'E';
    else if (cub->game.map.player_dir == 'E') cub->game.map.player_dir = 'N';
}

void turn_right(t_cub *cub)
{
    if (cub->game.map.player_dir == 'N') cub->game.map.player_dir = 'E';
    else if (cub->game.map.player_dir == 'E') cub->game.map.player_dir = 'S';
    else if (cub->game.map.player_dir == 'S') cub->game.map.player_dir = 'W';
    else if (cub->game.map.player_dir == 'W') cub->game.map.player_dir = 'N';
}
