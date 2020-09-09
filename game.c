#include "game.h"

int calculateShipPoints(user_t *player, uint16_t x, uint16_t y)
{
    for(uint16_t x =0; x <= 15; x++)
    {
        for(uint16_t y=0; y <=10; y++)
        {
            if(player->map[x][y] == BOAT)
            {
                player->hp++;
            }
        }
    }

    return player->hp;
}

int calculateShot(user_t *player, uint16_t x, uint16_t y)
{
            if(player->map[x][y] == BOAT)
            {
                player->map[x][y] = HIT;
            }
            else if(player->map[x][y] == SEA)
            {
                player->map[x][y] = WET;
            }
    
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
