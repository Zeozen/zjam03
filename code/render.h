#ifndef RENDER_H
#define RENDER_H
#include "game.h"
#include "zsdl.h"

void RenderMain(u32 t_r, Viewport* viewport, Game* game, Controller* controller, Particles* particles, Assets* assets, Menu* menu, zGrid* world);
void RenderOpts(u32 t_r, Viewport* viewport, Game* game, Controller* controller, Particles* particles, Assets* assets, Menu* menu, zGrid* world);
void RenderPlay(u32 t_r, Viewport* viewport, Game* game, Controller* controller, Particles* particles, Assets* assets, Menu* menu, zGrid* world);
void RenderLose(u32 t_r, Viewport* viewport, Game* game, Controller* controller, Particles* particles, Assets* assets, Menu* menu, zGrid* world);
void RenderGoal(u32 t_r, Viewport* viewport, Game* game, Controller* controller, Particles* particles, Assets* assets, Menu* menu, zGrid* world);
void RenderEdit(u32 t_r, Viewport* viewport, Game* game, Controller* controller, Particles* particles, Assets* assets, Menu* menu, zGrid* world);
void RenderEvent(u32 t_r, Viewport* viewport, Game* game, Controller* controller, Particles* particles, Assets* assets, Menu* menu, zGrid* world);


#endif // !RENDER_H