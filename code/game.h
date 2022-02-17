#ifndef GAME_H
#define GAME_H

#include "zmath.h"
#include "zgrid.h"
#include "zsdl.h"

#define NUMBER_OF_GAMESTATES 9
typedef enum
{
    GAMESTATE_INIT,
    GAMESTATE_MAIN,
    GAMESTATE_OPTS,
    GAMESTATE_PLAY,
    GAMESTATE_EVNT,
    GAMESTATE_LOSE,
    GAMESTATE_GOAL,
    GAMESTATE_EDIT,
    GAMESTATE_EXIT,
} Gamestate;

#define PLAYER_WIDTH 8
#define PLAYER_HALFWIDTH 4
#define PLAYER_HEIGHT 8
#define PLAYER_HALFHEIGHT 4
#define PLAYER_MAX_SPEED 48
#define PLAYER_GROUND_FRICTION 8.f
#define CAMERA_GROUND_OFFSET 64
#define PLAYER_GRAVITY 200.f
#define PLAYER_INPUT_MAGNITUDE 500
#define PLAYER_JUMP_STRENGTH 80.f
typedef struct
{
    r2 acc;
    r2 vel;
    r2 pos;
    b8 onground;
} Player;

#define MAX_DAYS 9
#define HOME_RADIUS 128
typedef struct
{
    Player player;
    u32 day_now;
    u32 progress_tree;
    u32 progress_mount;
} Game;





char* GetGamestateName(Gamestate state);

Game* CreateGame();
void FreeGame(Game* game);
void RestartGame(Game* game);



#endif // GAME_H
