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
    Assets* assets,
    Menu* menu
)/*-----------------------------------------------------------*/
{/*-----------------------------------------------------------*/


    static u8 cam_active = 0;
    static u8 cross_active = 0;
    i2 mloc = MouseLocation(controller, viewport);
    r2 mpos = CamToPos(mloc, viewport);

    i32 menu_action = TickMenu(menu[MENU_TITLE], mloc, controller);

    if (menu_action >= 0)
    {
        switch (menu_action)
        {
            case BTN_PLAY:
            break;
	        case BTN_OPTS:
                return GAMESTATE_OPTS;
            break;
	        case BTN_QUIT:
                return GAMESTATE_EXIT;
            break;
        }
    }


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
/*                        OPTIONS                            */
/*-----------------------------------------------------------*/
Gamestate UpdateOpts
(
    u32 t, 
    r32 dt, 
    u32 t0, 
    Viewport* viewport, 
    Game* game, 
    Controller* controller, 
    Particles* particles, 
    Assets* assets, 
    Menu* menu
)/*-----------------------------------------------------------*/
{/*-----------------------------------------------------------*/
    static u32 submenu_active = BTN_OPTS_VIDEO;
    i2 mloc = MouseLocation(controller, viewport);
    r2 mpos = CamToPos(mloc, viewport);

    i32 menu_action = TickMenu(menu[MENU_OPTIONS], mloc, controller);

    if (menu_action >= 0)
    {
        ToggleMenu(&menu[MENU_OPTIONS_AUDIO], ZDISABLED);
        ToggleMenu(&menu[MENU_OPTIONS_VIDEO], ZDISABLED);
        ToggleMenu(&menu[MENU_OPTIONS_INPUT], ZDISABLED);
        switch (menu_action)
        {
            case BTN_OPTS_VIDEO:
                submenu_active = BTN_OPTS_VIDEO;
                ToggleMenu(&menu[MENU_OPTIONS_VIDEO], ZENABLED);
            break;
	        case BTN_OPTS_AUDIO:
                submenu_active = BTN_OPTS_AUDIO;
                ToggleMenu(&menu[MENU_OPTIONS_AUDIO], ZENABLED);
            break;
	        case BTN_OPTS_INPUT:
                submenu_active = BTN_OPTS_INPUT;
                ToggleMenu(&menu[MENU_OPTIONS_INPUT], ZENABLED);
            break;
	        case BTN_OPTS_RETRN:
                return GAMESTATE_MAIN;
            break;            
        }
    }

    i32 submenu_action;
    switch (submenu_active)
    {
        case BTN_OPTS_VIDEO:
        {
            submenu_action = TickMenu(menu[MENU_OPTIONS_VIDEO], mloc, controller);
            switch (submenu_action)
            {
                case BTN_OPTS_VIDEO_FSCREEN:
                    ToggleFullscreen(viewport);
                    ComputePixelScale(viewport);
                    CalculateScreen(viewport);
                    RefreshCursors(viewport, assets);
                break;
            }

        }
        break;
        case BTN_OPTS_AUDIO:
        {
            submenu_action = TickMenu(menu[MENU_OPTIONS_AUDIO], mloc, controller);
            switch (submenu_action)
            {
                case BTN_OPTS_AUDIO_MAIN_VOLUME:
                break;
            }
        break;            
        }
        case BTN_OPTS_INPUT:
        {
            submenu_action = TickMenu(menu[MENU_OPTIONS_INPUT], mloc, controller);
            switch (submenu_action)
            {
                case BTN_OPTS_INPUT_REBIND:
                break;            
            }
        break;
        }
    }

    
    return GAMESTATE_OPTS;
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
    Assets* assets,
    Menu* menu
)/*-----------------------------------------------------------*/
{/*-----------------------------------------------------------*/



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
    Assets* assets,
    Menu* menu
)/*-----------------------------------------------------------*/
{/*-----------------------------------------------------------*/


    return GAMESTATE_LOSE;
}

