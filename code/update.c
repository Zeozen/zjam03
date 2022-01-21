#include "update.h"

/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
Gamestate UpdateMain
(
    u32 t, 
    r32 dt, 
    Viewport* viewport, 
    Game* game, 
    Controller* controller, 
    Dots* dots, 
    Assets* assets
)/*-----------------------------------------------------------*/
{/*-----------------------------------------------------------*/
    if (ActionPressed(controller, A_QUIT))
        return GAMESTATE_EXIT;

    r2 cam_loc = viewport->camera->pos;
    r2 move = r2_mul_x(i2_to_r2(controller->directional_vector), 1.f);
    viewport->camera->pos = add_r2(cam_loc, move);

    if (ActionPressed(controller, A_WHLU))
        viewport->camera->zoom += 0.1f;
    if (ActionPressed(controller, A_WHLD))
        viewport->camera->zoom -= 0.1f;


    return GAMESTATE_MAIN;
}



/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
Gamestate UpdatePlay
(
    u32 t, 
    r32 dt, 
    Viewport* viewport, 
    Game* game, 
    Controller* controller, 
    Dots* dots, 
    Assets* assets
)/*-----------------------------------------------------------*/
{/*-----------------------------------------------------------*/
    if (ActionPressed(controller, A_QUIT))
        return GAMESTATE_EXIT;
    


    return GAMESTATE_PLAY;
}

/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
Gamestate UpdateLose
(
    u32 t, 
    r32 dt, 
    Viewport* viewport, 
    Game* game, 
    Controller* controller, 
    Dots* dots, 
    Assets* assets
)/*-----------------------------------------------------------*/
{/*-----------------------------------------------------------*/
    if (ActionPressed(controller, A_QUIT))
        return GAMESTATE_EXIT;

    return GAMESTATE_LOSE;
}

