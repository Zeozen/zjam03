#include "update.h"

/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
Gamestate UpdateMain
(
    u32 t, 
    r32 dt, 
    u32 t0,
    Viewport* viewport, 
    Game* game, 
    Controller* controller, 
    Particles* particles, 
    Assets* assets
)/*-----------------------------------------------------------*/
{/*-----------------------------------------------------------*/
    if (ActionPressed(controller, A_QUIT))
        return GAMESTATE_EXIT;

    static u8 cam_active = 0;
    static u8 cross_active = 0;
    r2 mpos = CamToPos(MouseLocation(controller, viewport), viewport);

    if (ActionPressed(controller, A_WHLU))
    {
        if (viewport->camera->zoom < ZSDL_CAMERA_MAX_ZOOM)
            viewport->camera->zoom *= 1.1f;
    }
        
    if (ActionPressed(controller, A_WHLD))
    {
        if (viewport->camera->zoom > ZSDL_CAMERA_MIN_ZOOM)
            viewport->camera->zoom *= 0.9f;
    } 
    
    static r2 grab_cam_loc = ZERO_R2;
    if (ActionPressed(controller, A_MB_L))
    {
        if (cam_active)
        {
            SetCursor(viewport, assets, CUR_GRAB);
            grab_cam_loc = CamToPos(MouseLocation(controller, viewport), viewport);
        }
        else
        {
            cross_active = 1;
            SetCursor(viewport, assets, CUR_CLICK);
            SpawnBubble(particles, 16, mpos, ZERO_R2, ZERO_R2, 1.f, 0.f, 4, COLOR_RED, (SDL_Color){0xff, 0xff, 0x00, 0x00});
        }
        
    }

    if (ActionHeld(controller, A_MB_L))
    {
        if (cam_active)
        {
            r2 delta = sub_r2(mpos, grab_cam_loc);
            viewport->camera->pos = sub_r2(viewport->camera->pos, delta);
            grab_cam_loc = CamToPos(MouseLocation(controller, viewport), viewport);
        }
    }

    if (ActionReleased(controller, A_MB_L))
    {
        if (cam_active)
        {
            SetCursor(viewport, assets, CUR_HAND);
        }
        if (cross_active)
        {
            cross_active = 0;
            SetCursor(viewport, assets, CUR_POINT);
        }
    }

    if (ActionPressed(controller, A_JUMP))
    {
        cam_active = 1;
        SetCursor(viewport, assets, CUR_HAND);
    }
    if (ActionReleased(controller, A_JUMP))
    {
        cam_active = 0;
        SetCursor(viewport, assets, CUR_POINT);
    }

    i2 mloc_spawn_dot =  add_i2(sub_i2(MouseLocation(controller, viewport), assets->cur[GET8IN64(viewport->settings, ZSDL_SETTINGS_BYTE_ACTIVE_CURSOR)]->hotspot), make_i2(ZSDL_CURSOR_BASE_SIZE-2, ZSDL_CURSOR_BASE_SIZE-2));

    SpawnDot(particles, 16, add_r2(CamToPos(mloc_spawn_dot, viewport), make_r2(RNEG()*2, RNEG()*2)), make_r2(RNEG()*5.f, RNEG()*5.f), ZERO_R2, 1.f, COLOR_WHITE, COLOR_BLACK);
    return GAMESTATE_MAIN;
}



/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
Gamestate UpdatePlay
(
    u32 t, 
    r32 dt, 
    u32 t0,
    Viewport* viewport, 
    Game* game, 
    Controller* controller, 
    Particles* particles, 
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
    u32 t0,
    Viewport* viewport, 
    Game* game, 
    Controller* controller, 
    Particles* particles, 
    Assets* assets
)/*-----------------------------------------------------------*/
{/*-----------------------------------------------------------*/
    if (ActionPressed(controller, A_QUIT))
        return GAMESTATE_EXIT;

    return GAMESTATE_LOSE;
}

