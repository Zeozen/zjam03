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
    Menu* menu,
    zGrid* world
)/*-----------------------------------------------------------*/
{/*-----------------------------------------------------------*/
    // if (ActionPressed(controller, A_EDIT))
    // {
    //     return GAMESTATE_EDIT;
    // }

    r32 alpha = (t - t0) / 200.f;
    SET8IN64((1.f - alpha) * 255, &viewport->settings, ZSDL_SETTINGS_BYTE_FADE_ALPHA);
    if (alpha >= 1.f)
    {
        SET8IN64(0, &viewport->settings, ZSDL_SETTINGS_BYTE_FADE_ALPHA);
    }

    // static u8 cam_active = 0;
    // static u8 cross_active = 0;
    i2 mloc = MouseLocation(controller, viewport);
    // r2 mpos = CamToPos(mloc, viewport);

    i32 menu_action = TickMenu(menu[MENU_TITLE], mloc, controller);

    if (menu_action >= 0)
    {
        switch (menu_action)
        {
            case BTN_PLAY:
                return GAMESTATE_PLAY;
            break;
	        // case BTN_OPTS:
            //     return GAMESTATE_OPTS;
            // break;
	        case BTN_QUIT:
                return GAMESTATE_EXIT;
            break;
        }
    }


    // if (ActionPressed(controller, A_WHLU))
    // {
    //     if (viewport->camera->zoom < ZSDL_CAMERA_MAX_ZOOM)
    //         viewport->camera->zoom *= 1.1f;
    // }
        
    // if (ActionPressed(controller, A_WHLD))
    // {
    //     if (viewport->camera->zoom > ZSDL_CAMERA_MIN_ZOOM)
    //         viewport->camera->zoom *= 0.9f;
    // } 
    
    // static r2 grab_cam_loc = ZERO_R2;
    // if (ActionPressed(controller, A_MB_L))
    // {
    //     if (cam_active)
    //     {
    //         SetCursor(viewport, assets, CUR_GRAB);
    //         grab_cam_loc = CamToPos(MouseLocation(controller, viewport), viewport);
    //     }
    //     else
    //     {
    //         cross_active = 1;
    //         SetCursor(viewport, assets, CUR_CLICK);
    //         SpawnBubble(particles, 16, mpos, ZERO_R2, ZERO_R2, 1.f, 0.f, 4, COLOR_RED, (SDL_Color){0xff, 0xff, 0x00, 0x00});
    //     }
        
    // }

    // if (ActionHeld(controller, A_MB_L))
    // {
    //     if (cam_active)
    //     {
    //         r2 delta = sub_r2(mpos, grab_cam_loc);
    //         viewport->camera->pos = sub_r2(viewport->camera->pos, delta);
    //         grab_cam_loc = CamToPos(MouseLocation(controller, viewport), viewport);
    //     }
    // }

    // if (ActionReleased(controller, A_MB_L))
    // {
    //     if (cam_active)
    //     {
    //         SetCursor(viewport, assets, CUR_HAND);
    //     }
    //     if (cross_active)
    //     {
    //         cross_active = 0;
    //         SetCursor(viewport, assets, CUR_POINT);
    //     }
    // }

    // if (ActionPressed(controller, A_JUMP))
    // {
    //     cam_active = 1;
    //     SetCursor(viewport, assets, CUR_HAND);
    // }
    // if (ActionReleased(controller, A_JUMP))
    // {
    //     cam_active = 0;
    //     SetCursor(viewport, assets, CUR_POINT);
    // }

    // i2 mloc_spawn_dot =  add_i2(sub_i2(MouseLocation(controller, viewport), assets->cur[GET8IN64(viewport->settings, ZSDL_SETTINGS_BYTE_ACTIVE_CURSOR)]->hotspot), make_i2(ZSDL_CURSOR_BASE_SIZE-2, ZSDL_CURSOR_BASE_SIZE-2));

    // SpawnDot(particles, 16, add_r2(CamToPos(mloc_spawn_dot, viewport), make_r2(RNEG()*2, RNEG()*2)), make_r2(RNEG()*5.f, RNEG()*5.f), ZERO_R2, 1.f, COLOR_WHITE, COLOR_BLACK);
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
    Menu* menu,
    zGrid* world
)/*-----------------------------------------------------------*/
{/*-----------------------------------------------------------*/
    // static u32 submenu_active = BTN_OPTS_VIDEO;
    // i2 mloc = MouseLocation(controller, viewport);

    // i32 menu_action = TickMenu(menu[MENU_OPTIONS], mloc, controller);

    // if (menu_action >= 0)
    // {
    //     ToggleMenu(&menu[MENU_OPTIONS_AUDIO], ZDISABLED);
    //     ToggleMenu(&menu[MENU_OPTIONS_VIDEO], ZDISABLED);
    //     ToggleMenu(&menu[MENU_OPTIONS_INPUT], ZDISABLED);
    //     switch (menu_action)
    //     {
    //         case BTN_OPTS_VIDEO:
    //             submenu_active = BTN_OPTS_VIDEO;
    //             ToggleMenu(&menu[MENU_OPTIONS_VIDEO], ZENABLED);
    //         break;
	//         case BTN_OPTS_AUDIO:
    //             submenu_active = BTN_OPTS_AUDIO;
    //             ToggleMenu(&menu[MENU_OPTIONS_AUDIO], ZENABLED);
    //         break;
	//         case BTN_OPTS_INPUT:
    //             submenu_active = BTN_OPTS_INPUT;
    //             ToggleMenu(&menu[MENU_OPTIONS_INPUT], ZENABLED);
    //         break;
	//         case BTN_OPTS_RETRN:
    //             return GAMESTATE_MAIN;
    //         break;            
    //     }
    // }

    // i32 submenu_action;
    // switch (submenu_active)
    // {
    //     case BTN_OPTS_VIDEO:
    //     {
    //         submenu_action = TickMenu(menu[MENU_OPTIONS_VIDEO], mloc, controller);
    //         switch (submenu_action)
    //         {
    //             case BTN_OPTS_VIDEO_FSCREEN:
    //                 ToggleFullscreen(viewport);
    //                 ComputePixelScale(viewport);
    //                 CalculateScreen(viewport);
    //                 RefreshCursors(viewport, assets);
    //             break;
    //         }

    //     }
    //     break;
    //     case BTN_OPTS_AUDIO:
    //     {
    //         submenu_action = TickMenu(menu[MENU_OPTIONS_AUDIO], mloc, controller);
    //         switch (submenu_action)
    //         {
    //             case BTN_OPTS_AUDIO_MAIN_VOLUME:
    //             break;
    //         }
    //     break;            
    //     }
    //     case BTN_OPTS_INPUT:
    //     {
    //         submenu_action = TickMenu(menu[MENU_OPTIONS_INPUT], mloc, controller);
    //         switch (submenu_action)
    //         {
    //             case BTN_OPTS_INPUT_REBIND:
    //             break;            
    //         }
    //     break;
    //     }
    // }

    
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
    Menu* menu,
    zGrid* world
)/*-----------------------------------------------------------*/
{/*-----------------------------------------------------------*/
    if (ActionPressed(controller, A_EDIT))
    {
        return GAMESTATE_EDIT;
    }

    // i2 mloc = MouseLocation(controller, viewport);
    // r2 mpos = CamToPos(mloc, viewport);

//player update
    r2 acc = make_r2(controller->directional_vector.x * (PLAYER_INPUT_MAGNITUDE + (PLAYER_CRYSTAL_SPEEDBOOST * game->crystals_collected)- game->friends_collected * PLAYER_FRIEND_WEIGHT ) - game->player.vel.x * PLAYER_GROUND_FRICTION, PLAYER_GRAVITY);
    r2 vel = game->player.vel;
    r2 pos = game->player.pos;
    if (AbsR32(vel.x) < PLAYER_MAX_SPEED)
    {
        vel.x += (acc.x * dt);
    }
    else if ((acc.x * game->player.vel.x) < 0.f)
    {
        vel.x += (acc.x * dt);
        //vel = add_r2(vel, r2_mul_x(acc, dt));
        
    }
    vel.y += acc.y * dt;

u32 old_player_on_ground = game->player.onground;
//collision
    pos = add_r2(pos, r2_mul_x(vel, dt));
    if (vel.x > 0.f)
    {
        r2 posx_top = make_r2(pos.x + PLAYER_HALFWIDTH, game->player.pos.y - PLAYER_HALFHEIGHT);
        r2 posx_bot = make_r2(pos.x + PLAYER_HALFWIDTH, game->player.pos.y + PLAYER_HALFHEIGHT - WORLD_FRAC);
        i32 idx_x_top = PosToIdx(posx_top, world);
        i32 idx_x_bot = PosToIdx(posx_bot, world);
        if (world->cell[idx_x_top].collision == 1)
        {
            pos.x = IdxToPos(idx_x_top, world).x - PLAYER_HALFWIDTH ;
            vel.x = 0.f;
        }
        else if (world->cell[idx_x_bot].collision == 1)
        {
            pos.x = IdxToPos(idx_x_bot, world).x - PLAYER_HALFWIDTH ;
            vel.x = 0.f;
        }
    }
    else 
    {
        r2 posx_top = make_r2(pos.x - PLAYER_HALFWIDTH, game->player.pos.y - PLAYER_HALFHEIGHT);
        r2 posx_bot = make_r2(pos.x - PLAYER_HALFWIDTH, game->player.pos.y + PLAYER_HALFHEIGHT - WORLD_FRAC);
        i32 idx_x_top = PosToIdx(posx_top, world);
        i32 idx_x_bot = PosToIdx(posx_bot, world);
        if (world->cell[idx_x_top].collision == 1)
        {
            pos.x = IdxToPos(idx_x_top + 1, world).x + PLAYER_HALFWIDTH ;
            vel.x = 0.f;
        }
        else if (world->cell[idx_x_bot].collision == 1)
        {
            pos.x = IdxToPos(idx_x_bot + 1, world).x + PLAYER_HALFWIDTH ;
            vel.x = 0.f;
        }
    }
    if (vel.y > 0.f)
    {
        r2 posy_left = make_r2(pos.x - PLAYER_HALFWIDTH, pos.y + PLAYER_HALFHEIGHT);
        r2 posy_right = make_r2(pos.x + PLAYER_HALFWIDTH - WORLD_FRAC, pos.y + PLAYER_HALFHEIGHT);
        i32 idx_y_left = PosToIdx(posy_left, world);
        i32 idx_y_right = PosToIdx(posy_right, world);
        if (world->cell[idx_y_left].collision == 1)
        {
            pos.y = IdxToPos(idx_y_left, world).y - PLAYER_HALFHEIGHT;
            vel.y = 0.f;
            game->player.onground = 1;
            game->player.t_air_0 = 0;
            game->player.jumped = 0;
            
        }
        else if (world->cell[idx_y_right].collision == 1)
        {
            pos.y = IdxToPos(idx_y_right, world).y - PLAYER_HALFHEIGHT;
            vel.y = 0.f;
            game->player.onground = 1;
            game->player.t_air_0 = 0;
            game->player.jumped = 0;
        }        
        else if (world->cell[idx_y_left].collision == 2)
        {
            if (pos.y < IdxToPos(idx_y_left, world).y)
            {
                pos.y = IdxToPos(idx_y_left, world).y - PLAYER_HALFHEIGHT;
                vel.y = 0.f;
                game->player.onground = 1;
                game->player.t_air_0 = 0;
                game->player.jumped = 0;
            }
        }
        else if (world->cell[idx_y_right].collision == 2)
        {
            if (pos.y < IdxToPos(idx_y_right, world).y)
            {
                pos.y = IdxToPos(idx_y_right, world).y - PLAYER_HALFHEIGHT;
                vel.y = 0.f;
                game->player.onground = 1;
                game->player.t_air_0 = 0;
                game->player.jumped = 0;
            }
        }        
        else
        {
            if (game->player.onground)
            {
                game->player.onground = 0;
                game->player.t_air_0 = 0;
            }
            else
            {
                game->player.t_air_0++;
            }
        }
    }
    else 
    {
        r2 posy_left = make_r2(pos.x - PLAYER_HALFWIDTH, pos.y - PLAYER_HALFHEIGHT);
        r2 posy_right = make_r2(pos.x + PLAYER_HALFWIDTH - WORLD_FRAC, pos.y - PLAYER_HALFHEIGHT);
        i32 idx_y_left = PosToIdx(posy_left, world);
        i32 idx_y_right = PosToIdx(posy_right, world);
        if (world->cell[idx_y_left].collision == 1)
        {
            pos.y = IdxToPos(idx_y_left + world->width, world).y + PLAYER_HALFHEIGHT;
            vel.y = 0.f;
        }
        else if (world->cell[idx_y_right].collision == 1)
        {
            pos.y = IdxToPos(idx_y_right + world->width, world).y + PLAYER_HALFHEIGHT;
            vel.y = 0.f;
        }
    }

    if (old_player_on_ground == 0 && game->player.onground == 1)
    {
        Mix_PlayChannel(SFX_TAP, assets->sfx[SFX_TAP], 0);  
    }

    game->player.pos = pos;
    game->player.vel = vel;
    
    if (ActionPressed(controller, A_JUMP) && !game->player.jumped)
    {
        if (game->player.onground || (game->player.t_air_0 < 20))
        {
            game->player.vel.y = (PLAYER_JUMP_STRENGTH + game->crystals_collected * PLAYER_JUMP_STRENGTH_LEVELUP) * -1.f;
            game->player.onground = 0;
            game->player.jumped = 1;
            Mix_PlayChannel(SFX_JUMP, assets->sfx[SFX_JUMP], 0);
        }
    }

    u32 pidx = PosToIdx(game->player.pos, world);
    if (world->cell[pidx].type == CRYSTAL)
    {
        i32 discarded_idx = game->crystals_collected + game->friends_collected;
        world->cell[game->friend_idx[discarded_idx]].collision = 0;
        world->cell[game->friend_idx[discarded_idx]].type = 0;
        world->cell[game->friend_idx[discarded_idx]].sprite_mg = 0;
        for (i32 i = 0; i < 50; i++)
        {
            r2 vel = make_r2(RNEG()*40.f, RNEG()*40.f);
            SpawnDot(particles, 100, IdxToPos(game->friend_idx[discarded_idx], world), make_r2(RNEG()*40.f, RNEG()*40.f), r2_mul_x(vel, -1.f), 1.f, COLOR_RED, COLOR_BLACK_TRANSPARENT);
        }
        Mix_PlayChannel(SFX_FRIEND_DIE, assets->sfx[SFX_FRIEND_DIE], 0);


        game->crystals_collected++;
        world->cell[pidx].collision = 0;
        world->cell[pidx].type = 0;
        world->cell[pidx].sprite_mg = 0;
        Mix_PlayChannel(SFX_COLLECT_CRYSTAL, assets->sfx[SFX_COLLECT_CRYSTAL], 0);
        SpawnBubble(particles, 100, game->player.pos, ZERO_R2, ZERO_R2, 1.f, 0.f, 100.f, COLOR_WHITE, COLOR_WHITE_TRANSPARENT);
        
    }
    if (world->cell[pidx].type == FRIEND)
    {
        i32 discarded_idx = game->crystals_collected + game->friends_collected;
        world->cell[game->crystal_idx[discarded_idx]].collision = 0;
        world->cell[game->crystal_idx[discarded_idx]].type = 0;
        world->cell[game->crystal_idx[discarded_idx]].sprite_mg = 0;
        for (i32 i = 0; i < 50; i++)
        {
            r2 vel = make_r2(RNEG()*40.f, RNEG()*40.f);
            SpawnDot(particles, 100, IdxToPos(game->crystal_idx[discarded_idx], world), make_r2(RNEG()*40.f, RNEG()*40.f), r2_mul_x(vel, -1.f), 1.f, COLOR_PURPLE, COLOR_BLACK_TRANSPARENT);
        }
        Mix_PlayChannel(SFX_CRYSTAL_DIE, assets->sfx[SFX_CRYSTAL_DIE], 0);


        game->friends_collected++;
        world->cell[pidx].collision = 0;
        world->cell[pidx].type = 0;
        world->cell[pidx].sprite_mg = 0;
        Mix_PlayChannel(SFX_COLLECT_FRIEND, assets->sfx[SFX_COLLECT_FRIEND], 0);
        SpawnBubble(particles, 100, game->player.pos, ZERO_R2, ZERO_R2, 1.f, 0.f, 100.f, COLOR_WHITE, COLOR_WHITE_TRANSPARENT);
    }
    if (world->cell[pidx].type == GOAL)
    {
        if (game->crystals_collected == MAX_CRYSTALS)
        {
            game->event = EVNT_WIN_ALL_CRYSTALS;
            Mix_Volume(SFX_MUS_FLUT, 200);
            Mix_Volume(SFX_MUS_STAR, 200);
        }   
        else
        {
            game->event = EVNT_WIN_SACRIFICE_FRIENDS;
            Mix_Volume(SFX_MUS_STAR, 200);
        }

        game->fadeout = 1;
        return GAMESTATE_GOAL;
    }
    if (game->player.pos.y > game->doom_below)
    {
        i2 pcel = PosToCel(game->player.pos, world);
        u32 idx = CelToIdx(pcel, world);
        if ((world->cell[idx].type == CAMPFIRE) && (game->friends_collected == MAX_FRIENDS))
        {
            game->event = EVNT_WIN_ALL_FRIENDS;
            game->fadeout = 1;
            Mix_Volume(SFX_MUS_STAR, 200);
            Mix_Volume(SFX_MUS_PADS, 200);
            Mix_Volume(SFX_MUS_FLUT, 200);
            return GAMESTATE_GOAL;
        }
        else if (game->crystals_collected + game->friends_collected == MAX_CRYSTALS)
        {
            game->event = EVNT_LOSE_LUKEWARM;
            game->fadeout = 1;
            
            Mix_Volume(SFX_MUS_HARP, 0);
            return GAMESTATE_LOSE;
        }
        else
        {
            game->event = EVNT_LOSE_DOOMBELOW;
            game->fadeout = 1;
            Mix_Volume(SFX_MUS_HARP, 0);
            return GAMESTATE_LOSE;
        }
    }

    if ((game->player.pos.y < (world->origin.y + 17 * WORLD_UNIT)) && (game->friends_collected >= 1))
    {
        if (!game->sacrifice_made)
        {
            DrawTextScreenCentered(viewport, assets->fon[FONT_ID_ZSYS], COLOR_WHITE, (SDL_Rect){10, 10, ZSDL_INTERNAL_WIDTH-20, 40}, assets->str[STR_SACRIFICE_PROMPT]);
            if (ActionPressed(controller, A_ENTR))
            {
                game->sacrifice_made = 1;
                i2 pcel = PosToCel(game->player.pos, world);
                i2 sacrifice_cel_start;
                if (pcel.x < 26)
                {
                    sacrifice_cel_start = make_i2(22,15);
                }
                else
                {
                    sacrifice_cel_start = make_i2(26,15);
                }
                for (i32 i = 0; i < game->friends_collected; i++)
                {
                    u32 idx = CelToIdx(sacrifice_cel_start, world);
                    world->cell[idx].collision = 2;
                    world->cell[idx].sprite_mg = MAKE8FROM4(7, 0);
                    world->cell[idx].type = 1;
                    sacrifice_cel_start.y -= 2;
                }
                Mix_PlayChannel(SFX_FRIEND_CRY, assets->sfx[SFX_FRIEND_CRY], -1);
            }
        }
    }

//camera update
    viewport->camera->pos.y = game->player.pos.y - CAMERA_GROUND_OFFSET;
   
//doom update
    //game->doom_below -= 0.01f + 0.056f * game->crystals_collected + 0.020f * game->friends_collected;
    i2 pcel = PosToCel(game->player.pos, world);
    u32 idx = CelToIdx(pcel, world);
    // if ((world->cell[idx].type == CAMPFIRE) && (game->friends_collected == MAX_FRIENDS))
    // {
    //     game->doom_below -= 1.f;
    // }
    // else
    // {
        game->doom_below -= 0.01f + 0.049f * game->crystals_collected + 0.017f * game->friends_collected;
    // }

//anim update
    game->anim_environ = (t/35) % 4;
    u32 old_anim_chara = game->anim_chara;
    game->anim_chara = (t / (36 / (1 + game->crystals_collected))) % 2;
    if (old_anim_chara != game->anim_chara && game->player.anim == P_ANIM_RUN)
    {
        Mix_PlayChannel(SFX_FOOTSTEP, assets->sfx[SFX_FOOTSTEP], 0);
    }

    if (game->player.onground)
    {
        if (AbsR32(game->player.vel.x) <= 5.f)
        {
            game->player.anim = P_ANIM_IDLE;
        }
        else
        {
            game->player.anim = P_ANIM_RUN;
            if (game->player.vel.x < 0.f)
                game->player.dir = 1;
            else//(game->player.vel.x > 0.f)
                game->player.dir = 0;

        }
    }
    else
    {
        if (game->player.vel.y > 0.f)
        {
            game->player.anim = P_ANIM_FALL;
        }
        else
        {
            game->player.anim = P_ANIM_JUMP;
        }
    }

    static i32 friend_pos_breadcrumb_counter = 0;
    if (t % 20 == 0)
    {
        game->friend_pos_crumb[friend_pos_breadcrumb_counter] = game->player.pos;
        friend_pos_breadcrumb_counter = (friend_pos_breadcrumb_counter + 1) % MAX_FRIENDS;
        
    }
    for (i32 i = 0; i < 5; i++)
    {
        game->friend_pos[i] = lerp_r2(game->friend_pos[i], game->friend_pos_crumb[i], 0.01f + 0.01f*i);
        //game->friend_pos[i] = add_r2(game->friend_pos[i], r2_mul_x(game->player.vel, dt));
    }
    if (t % 100 == 0)
    {
        if ((game->friends_collected >= 1) && (!game->sacrifice_made))
        {
            i32 r = SFX_FRIEND_01 + RNG()*game->friends_collected;
            Mix_PlayChannel(r, assets->sfx[r], 0);
        }
    }

    if (t % 10 == 0)
    {
        for (i32 i = 0; i < game->crystals_collected; i++)
        {
            r2 vel = make_r2(RNEG()*20.f, RNEG()*20.f);
            SpawnDot(particles, 100, game->player.pos, make_r2(RNEG()*40.f, RNEG()*40.f), r2_mul_x(vel, -1.f), 1.f, COLOR_WHITE, COLOR_WHITE_TRANSPARENT);
        }

    }

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
    Menu* menu,
    zGrid* world
)/*-----------------------------------------------------------*/
{/*-----------------------------------------------------------*/
u32 t_elapsed = (t - t0);
    if (t_elapsed < 200)
    {
        r32 alpha = t_elapsed / 200.f;
        SET8IN64(alpha*0xff, &viewport->settings, ZSDL_SETTINGS_BYTE_FADE_ALPHA);
    }
    else if (t_elapsed == 200)
    {
        game->fadeout = 0;
        SET8IN64(0xff, &viewport->settings, ZSDL_SETTINGS_BYTE_FADE_ALPHA);
    }
    else if (t_elapsed <= 400)
    {
        r32 alpha = (t_elapsed-200) / 200.f;
        SET8IN64((1.f - alpha)*0xff, &viewport->settings, ZSDL_SETTINGS_BYTE_FADE_ALPHA);
    }
    else
    {
        if (ActionPressed(controller, A_JUMP))
        {
            RestartGame(game);
            game->fadeout = 1;
            return GAMESTATE_MAIN;
        }
    }


    return GAMESTATE_LOSE;
}

/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
Gamestate UpdateGoal
(
    u32 t, 
    r32 dt, 
    u32 t0,
    Viewport* viewport, 
    Game* game, 
    Controller* controller, 
    Particles* particles, 
    Assets* assets,
    Menu* menu,
    zGrid* world
)/*-----------------------------------------------------------*/
{/*-----------------------------------------------------------*/
    u32 t_elapsed = (t - t0);
    if (t_elapsed < 200)
    {
        r32 alpha = t_elapsed / 200.f;
        SET8IN64(alpha*0xff, &viewport->settings, ZSDL_SETTINGS_BYTE_FADE_ALPHA);
    }
    else if (t_elapsed == 200)
    {
        game->fadeout = 0;
        SET8IN64(0xff, &viewport->settings, ZSDL_SETTINGS_BYTE_FADE_ALPHA);
    }
    else if (t_elapsed <= 400)
    {
        r32 alpha = (t_elapsed-200) / 200.f;
        SET8IN64((1.f - alpha)*0xff, &viewport->settings, ZSDL_SETTINGS_BYTE_FADE_ALPHA);
    }
    else
    {
        if (ActionPressed(controller, A_JUMP))
        {
            RestartGame(game);
            game->fadeout = 1;
            return GAMESTATE_MAIN;
        }
    }


    return GAMESTATE_GOAL;
}


/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
Gamestate UpdateEdit
(
    u32 t, 
    r32 dt, 
    u32 t0,
    Viewport* viewport, 
    Game* game, 
    Controller* controller, 
    Particles* particles, 
    Assets* assets,
    Menu* menu,
    zGrid* world
)/*-----------------------------------------------------------*/
{/*-----------------------------------------------------------*/

    if (ActionPressed(controller, A_EDIT))
    {
        return GAMESTATE_PLAY;
    }

    i2 mloc = MouseLocation(controller, viewport);
    r2 mpos = CamToPos(mloc, viewport);
    i2 mcel = PosToCel(mpos, world);
    u32 midx = CelToIdx(mcel, world);

    static u8 tool_type = 0;
    if (ActionPressed(controller, A_WHLU))
    {
        tool_type = (tool_type + 1) % TOOLS_MAX;
    }
    if (ActionPressed(controller, A_WHLD))
    {
        tool_type = ((tool_type - 1) + TOOLS_MAX) % TOOLS_MAX;
    }
    //     tool_type = ERASE; 
    // if (ActionPressed(controller, A_2))
    //     tool_type = SOLID; 
    // if (ActionPressed(controller, A_3))
    //     tool_type = HALF; 
    // if (ActionPressed(controller, A_4))
    //     tool_type = FRIEND; 
    // if (ActionPressed(controller, A_5))
    //     tool_type = CRYSTAL;
    // if (ActionPressed(controller, A_6))
    //     tool_type = GOAL; 
    
    char tool_txt[100];
    sprintf(tool_txt, "tool: %d}cel [%d,%d]}idx: %d", tool_type, mcel.x, mcel.y, midx);
    DrawTextScreen(viewport, assets->fon[FONT_ID_ZSYS], COLOR_WHITE, ZERO_I2, tool_txt);
    

    if (ActionHeld(controller, A_MB_L) && ValidateCel(mcel, world))
    {
        i32 idx = CelToIdx(mcel, world);
        switch (tool_type)
        {
            case ERASE:
                world->cell[idx].collision = 0;
                world->cell[idx].sprite_mg = 0;
                world->cell[idx].sprite_bg = 0;
                world->cell[idx].type = 0;
            break;
            case SOLID:
                world->cell[idx].collision = 1;
                world->cell[idx].sprite_mg = MAKE8FROM4(1, 0);
                world->cell[idx].type = 1;
            break;
            case HALF:
                world->cell[idx].collision = 2;
                world->cell[idx].sprite_mg = MAKE8FROM4(2, 0);
                world->cell[idx].type = 1;
            break;
            case FRIEND:
                world->cell[idx].collision = 0;
                world->cell[idx].sprite_mg = MAKE8FROM4(3, 0);
                world->cell[idx].type = FRIEND;
            break;
            case CRYSTAL:
                world->cell[idx].collision = 0;
                world->cell[idx].sprite_mg = MAKE8FROM4(4, 0);
                world->cell[idx].type = CRYSTAL;
            break;
            case GOAL:
                world->cell[idx].collision = 0;
                world->cell[idx].sprite_mg = MAKE8FROM4(5, 0);
                world->cell[idx].type = GOAL;
            break;
            case CAMPFIRE:
                world->cell[idx].collision = 0;
                world->cell[idx].sprite_mg = MAKE8FROM4(6, 0);
                world->cell[idx].type = CAMPFIRE;
            break;
            case STAR_BG:
                world->cell[idx].sprite_bg = MAKE8FROM4(8, 0);
                world->cell[idx].type = 0;
            break;
            case CAMP_BG:
                world->cell[idx].sprite_bg = MAKE8FROM4(9, 0);
                world->cell[idx].type = CAMPFIRE;
            break;
        }
    }
    
    viewport->camera->pos = add_r2(viewport->camera->pos, i2_to_r2(controller->move_vector));
    


    return GAMESTATE_EDIT;
}



/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
Gamestate UpdateEvent
(
    u32 t, 
    r32 dt, 
    u32 t0,
    Viewport* viewport, 
    Game* game, 
    Controller* controller, 
    Particles* particles, 
    Assets* assets,
    Menu* menu,
    zGrid* world
)/*-----------------------------------------------------------*/
{/*-----------------------------------------------------------*/
    if (game->event == EVNT_INTRO)
    {
        static u32 sequence = 0;
        static u32 t0_fadeout = 0;

        switch(sequence)
        {
            case 0:
            {
                r32 alpha = (t - t0) / 200.f;
                SET8IN64((1.f - alpha) * 255, &viewport->settings, ZSDL_SETTINGS_BYTE_FADE_ALPHA);
                if (alpha >= 1.f)
                {
                    sequence = 1;
                }
            }
            break;
            case 1:
            {
                SET8IN64(0, &viewport->settings, ZSDL_SETTINGS_BYTE_FADE_ALPHA);
                
                if (ActionPressed(controller, A_MB_L) || ActionPressed(controller, A_JUMP) || ActionPressed(controller, A_ENTR))
                {
                    sequence = 2;
                    t0_fadeout = t;
                }
            }
            break;
            case 2:
            {
                r32 alpha = (t - t0_fadeout) / 200.f;
                SET8IN64(alpha * 255, &viewport->settings, ZSDL_SETTINGS_BYTE_FADE_ALPHA);
                if (alpha >= 1.f)
                {
                    sequence = 0;
                    return GAMESTATE_MAIN;
                }
            }
            break;
        }
    }

    return GAMESTATE_EVNT;
}
