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

#define PLAYER_WIDTH 6
#define PLAYER_HALFWIDTH 3
#define PLAYER_HEIGHT 8
#define PLAYER_HALFHEIGHT 4
#define PLAYER_MAX_SPEED 48
#define PLAYER_GROUND_FRICTION 8.f
#define CAMERA_GROUND_OFFSET 0
#define PLAYER_GRAVITY 200.f
#define PLAYER_INPUT_MAGNITUDE 500
#define PLAYER_JUMP_STRENGTH 85.f
#define PLAYER_JUMP_STRENGTH_LEVELUP 20.f
#define PLAYER_FRIEND_WEIGHT 80.f
#define PLAYER_CRYSTAL_SPEEDBOOST 80.f

typedef struct
{
    r2 acc;
    r2 vel;
    r2 pos;
    b8 onground;
    u32 t_air_0;
    b8 jumped;
    u8 anim;
    u8 dir;
} Player;

typedef enum
{
    P_ANIM_IDLE,
    P_ANIM_RUN,
    P_ANIM_JUMP,
    P_ANIM_FALL,
    P_ANIM_GOAL
} ePanim;

#define MAX_CRYSTALS 5
#define MAX_FRIENDS 5
typedef struct
{
    Player player;
    u32 crystals_collected;
    u32 friends_collected;
    r32 doom_below;
    r32 doom_above;
    u32 event;
    b8 fadeout;
    b8 sacrifice_made;
    u32 anim_environ;
    u32 anim_chara;
    r2 friend_pos[MAX_FRIENDS];
    r2 friend_pos_crumb[MAX_FRIENDS];
    i32 friend_idx[MAX_FRIENDS];
    i32 crystal_idx[MAX_CRYSTALS];
} Game;

typedef enum
{
    ERASE,
    SOLID,
    HALF,
    FRIEND,
    CRYSTAL,
    GOAL,
    CAMPFIRE,
    SACRIFICE,
    STAR_BG,
    CAMP_BG
} eTools;
#define TOOLS_MAX 10

typedef enum
{
    EVNT_TITLE_INTRO,
    EVNT_INTRO,
    EVNT_LOSE_DOOMBELOW,
    EVNT_LOSE_LUKEWARM,
    EVNT_WIN_ALL_CRYSTALS,
    EVNT_WIN_ALL_FRIENDS,
    EVNT_WIN_SACRIFICE_FRIENDS
} eEvents;

#define PICTURE_SRC_W 208
#define PICTURE_SRC_H 160
#define PICTURE_SRC_X 0
#define PICTURE_INTRO_SRC_Y 256
#define PICTURE_LOSE_SRC_Y 96
#define PICTURE_WIN_CRYSTALS_SRC_Y 416
#define PICTURE_WIN_FRIENDS_SRC_Y 576
#define PICTURE_WIN_SACRIFICE_SRC_Y 736
#define PICTURE_DST (SDL_Rect){88, 8, PICTURE_SRC_W, PICTURE_SRC_H}
#define PIC_TXT_DST (SDL_Rect){1, 169, ZSDL_INTERNAL_WIDTH - 2, 47}
#define PIC_TXT_DST_LOC make_i2(30, 169)




char* GetGamestateName(Gamestate state);

Game* CreateGame();
void FreeGame(Game* game);
void RestartGame(Game* game);

void DrawPlayer(Game* game, Viewport* viewport, Assets* assets);


#endif // GAME_H
