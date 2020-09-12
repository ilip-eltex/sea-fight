#include "game.h"

int calculateShipPoints(user_t *player)
{
    for(uint16_t x =0; x <= 15; x++)
    {
        for(uint16_t y=0; y <=10; y++)
        {
            if(player->map[x][y] == (char)BOAT)
            {
                player->hp++;
            }
        }
    }

    return player->hp;
}

int calculateShot(user_t *player, uint16_t x, uint16_t y)
{
            if(player->map[x][y] == (char)BOAT)
            {
                player->map[x][y] = (char)HIT;
                player->hp--;
                return (char)HIT;
            }
            else if(player->map[x][y] == (char)SEA)
            {
                player->map[x][y] = (char)WET;
                return (char)WET;
            }
    return 0;
}

int chekingAliveBoat(user_t *player)
{
    if(player->hp == 0)
    {
        /*
        Вызов какого-нибудь окошечка
        */
    }
}
