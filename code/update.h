#ifndef UPDATE_H
#define UPDATE_H

#include "game.h"
#include "zsdl.h"

Gamestate UpdateMain(u32 t, r32 dt, u32 t0, Viewport* viewport, Game* game, Controller* controller, Particles* particles, Assets* assets, Menu* menu, zGrid* world);
Gamestate UpdateOpts(u32 t, r32 dt, u32 t0, Viewport* viewport, Game* game, Controller* controller, Particles* particles, Assets* assets, Menu* menu, zGrid* world);
Gamestate UpdatePlay(u32 t, r32 dt, u32 t0, Viewport* viewport, Game* game, Controller* controller, Particles* particles, Assets* assets, Menu* menu, zGrid* world);
Gamestate UpdateLose(u32 t, r32 dt, u32 t0, Viewport* viewport, Game* game, Controller* controller, Particles* particles, Assets* assets, Menu* menu, zGrid* world);

#endif // !UPDATE_H
