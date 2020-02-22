#include "utility.h"

void activeList(enemy *&head,enemy*&last,castle&ct, int timestep );		//Make The Active Lists each timestep

void enemy_killed(castle&ct, int timestep, enemy*&killedHead, enemy*&killedLast);		//Make the killed List each timestep