#include "render.h"
#include "assets.h"
#include <stdio.h>

/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
void RenderMain
(
    u32 t_r,
    Viewport* viewport, 
    Game* game, 
    Controller* controller, 
    Particles* particles,
    Assets* assets,
    Menu* menu,
    zGrid* world
)/*-----------------------------------------------------------*/
{/*-----------------------------------------------------------*/

//      SDL_SetRenderTarget(viewport->renderer, viewport->render_layer[ZSDL_RENDERLAYER_BACKGROUND]);

// //draw world
//     SDL_SetRenderDrawColor(viewport->renderer, 0x22, 0x15, 0x15, 0xff);
//     SDL_SetRenderDrawColor(viewport->renderer, 0x00, 0x00, 0x00, 0xff);
//     SDL_RenderFillRect(viewport->renderer, NULL);

//     i2 origo_to_screen = PosToCam(ZERO_R2, 1.f, viewport);
//     SDL_SetRenderDrawColor(viewport->renderer, 0xcc, 0xaa, 0xaa, 0x33);
//     SDL_RenderDrawLine(viewport->renderer, origo_to_screen.x, 0, origo_to_screen.x, ZSDL_INTERNAL_HEIGHT);
//     SDL_RenderDrawLine(viewport->renderer, 0, origo_to_screen.y, ZSDL_INTERNAL_WIDTH, origo_to_screen.y);
    
// //draw home
//     SDL_SetRenderDrawColor(viewport->renderer, 0xbb, 0xbb, 0xbb, 0xbb);
//     ZSDL_RenderDrawCircle(viewport, 32.f * viewport->camera->zoom, PosToCam(ZERO_R2, 1.f, viewport));

//     SDL_SetRenderTarget(viewport->renderer, viewport->render_layer[ZSDL_RENDERLAYER_ENTITIES]);

//     SDL_SetRenderTarget(viewport->renderer, viewport->render_layer[ZSDL_RENDERLAYER_FOREGROUND]);
    
    SDL_SetRenderTarget(viewport->renderer, viewport->render_layer[ZSDL_RENDERLAYER_UI]);
//draw title
    SDL_Rect tit_src = {0, 0, 208, 64};
    SDL_Rect tit_dst = {ZSDL_INTERNAL_WIDTH*0.5 - tit_src.w*0.5, ZSDL_INTERNAL_HEIGHT*0.5 - tit_src.h*0.5, tit_src.w, tit_src.h};
    SDL_RenderCopy(viewport->renderer, assets->tex[T_UI_ATLAS], &tit_src, &tit_dst);

    DrawMenu(menu[MENU_TITLE], viewport, assets);


     
 
}


/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
void RenderOpts
(
    u32 t_r,
    Viewport* viewport, 
    Game* game, 
    Controller* controller, 
    Particles* particles,
    Assets* assets,
    Menu* menu,
    zGrid* world
)/*-----------------------------------------------------------*/
{/*-----------------------------------------------------------*/

    // SDL_SetRenderTarget(viewport->renderer, viewport->render_layer[ZSDL_RENDERLAYER_UI]);
    // DrawMenu(menu[MENU_OPTIONS], viewport, assets);
    // DrawMenu(menu[MENU_OPTIONS_VIDEO], viewport, assets);
    // DrawMenu(menu[MENU_OPTIONS_AUDIO], viewport, assets);
    // DrawMenu(menu[MENU_OPTIONS_INPUT], viewport, assets);
}



/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
void RenderPlay
(
    u32 t_r,
    Viewport* viewport, 
    Game* game, 
    Controller* controller, 
    Particles* particles,
    Assets* assets,
    Menu* menu,
    zGrid* world
)/*-----------------------------------------------------------*/
{/*-----------------------------------------------------------*/
    //i2 mloc = MouseLocation(controller, viewport);
    //r2 mpos = CamToPos(mloc, viewport);
    SDL_SetRenderTarget(viewport->renderer, viewport->render_layer[ZSDL_RENDERLAYER_ENTITIES]);

    SDL_Rect f_src = {16, 0, 8, 8};
    SDL_Rect f_dst = {0, 0, 8, 8};

    if (!game->sacrifice_made)
    {
        for (i32 i = 0; i < game->friends_collected; i++)
        {
            i2 dst_cam = PosToCam(add_r2(game->friend_pos[i], make_r2(-4.f, -4.f)), 1.f, viewport);
            f_dst.x = dst_cam.x;
            f_dst.y = dst_cam.y;
            SDL_RenderCopy(viewport->renderer, assets->tex[T_CHARACTER_ATLAS], &f_src, &f_dst);
        }
    }
    DrawPlayer(game, viewport, assets);

    DrawGrid(world, viewport, assets, game->anim_environ);

    SDL_SetRenderTarget(viewport->renderer, viewport->render_layer[ZSDL_RENDERLAYER_FOREGROUND]);
//draw doom
    r2 doombelow_pos = make_r2(world->origin.x, game->doom_below);
    i2 doom_loc = PosToCam(doombelow_pos, 1.f, viewport);
    SDL_Rect db = {doom_loc.x, doom_loc.y, ZSDL_INTERNAL_WIDTH, ZSDL_INTERNAL_HEIGHT - doom_loc.y };
    SDL_SetRenderDrawColor(viewport->renderer, 0xff, 0, 0, 0xff);
    SDL_RenderFillRect(viewport->renderer, &db);


    SDL_SetRenderTarget(viewport->renderer, viewport->render_layer[ZSDL_RENDERLAYER_UI]);


}

/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
void RenderLose
(
    u32 t_r,
    Viewport* viewport, 
    Game* game, 
    Controller* controller, 
    Particles* particles,
    Assets* assets,
    Menu* menu,
    zGrid* world
)/*-----------------------------------------------------------*/
{/*-----------------------------------------------------------*/

    if (game->fadeout)
    {
        //i2 mloc = MouseLocation(controller, viewport);
        //r2 mpos = CamToPos(mloc, viewport);

        SDL_SetRenderTarget(viewport->renderer, viewport->render_layer[ZSDL_RENDERLAYER_ENTITIES]);
        DrawPlayer(game, viewport, assets);


        DrawGrid(world, viewport, assets, game->anim_environ);

        SDL_SetRenderTarget(viewport->renderer, viewport->render_layer[ZSDL_RENDERLAYER_FOREGROUND]);
    //draw doom
        r2 doombelow_pos = make_r2(world->origin.x, game->doom_below);
        i2 doom_loc = PosToCam(doombelow_pos, 1.f, viewport);
        SDL_Rect db = {doom_loc.x, doom_loc.y, ZSDL_INTERNAL_WIDTH, ZSDL_INTERNAL_HEIGHT - doom_loc.y };
        SDL_SetRenderDrawColor(viewport->renderer, 0xff, 0, 0, 0xff);
        SDL_RenderFillRect(viewport->renderer, &db);


        SDL_SetRenderTarget(viewport->renderer, viewport->render_layer[ZSDL_RENDERLAYER_UI]);
    }
    else
    {
        SDL_SetRenderTarget(viewport->renderer, viewport->render_layer[ZSDL_RENDERLAYER_UI]);
        DrawTextScreen(viewport, assets->fon[FONT_ID_ZSYS], COLOR_WHITE, PIC_TXT_DST_LOC, assets->str[STR_ENDING_LUKEWARM]);
        //SDL_RenderCopy(viewport->renderer, assets->tex[T_UI_ATLAS], &(SDL_Rect){0, PICTURE_INTRO_SRC_Y, PICTURE_SRC_W, PICTURE_SRC_H}, &PICTURE_DST);
    }
}

/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
void RenderEdit
(
    u32 t_r,
    Viewport* viewport, 
    Game* game, 
    Controller* controller, 
    Particles* particles,
    Assets* assets,
    Menu* menu,
    zGrid* world
)/*-----------------------------------------------------------*/
{/*-----------------------------------------------------------*/

    DrawGrid(world, viewport, assets, game->anim_environ);
}


/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
void RenderGoal
(
    u32 t_r,
    Viewport* viewport, 
    Game* game, 
    Controller* controller, 
    Particles* particles,
    Assets* assets,
    Menu* menu,
    zGrid* world
)/*-----------------------------------------------------------*/
{/*-----------------------------------------------------------*/

    if (game->fadeout)
    {
        //i2 mloc = MouseLocation(controller, viewport);
        //r2 mpos = CamToPos(mloc, viewport);

        SDL_SetRenderTarget(viewport->renderer, viewport->render_layer[ZSDL_RENDERLAYER_ENTITIES]);
        DrawPlayer(game, viewport, assets);


        DrawGrid(world, viewport, assets, game->anim_environ);

        SDL_SetRenderTarget(viewport->renderer, viewport->render_layer[ZSDL_RENDERLAYER_FOREGROUND]);
    //draw doom
        r2 doombelow_pos = make_r2(world->origin.x, game->doom_below);
        i2 doom_loc = PosToCam(doombelow_pos, 1.f, viewport);
        SDL_Rect db = {doom_loc.x, doom_loc.y, ZSDL_INTERNAL_WIDTH, ZSDL_INTERNAL_HEIGHT - doom_loc.y };
        SDL_SetRenderDrawColor(viewport->renderer, 0xff, 0, 0, 0xff);
        SDL_RenderFillRect(viewport->renderer, &db);


        SDL_SetRenderTarget(viewport->renderer, viewport->render_layer[ZSDL_RENDERLAYER_UI]);
    }
    else
    {
        SDL_SetRenderTarget(viewport->renderer, viewport->render_layer[ZSDL_RENDERLAYER_UI]);
        if (game->event == EVNT_WIN_ALL_CRYSTALS)
        {
            DrawTextScreen(viewport, assets->fon[FONT_ID_ZSYS], COLOR_WHITE, PIC_TXT_DST_LOC, assets->str[STR_ENDING_ALL_CRYSTALS]);
            SDL_RenderCopy(viewport->renderer, assets->tex[T_UI_ATLAS], &(SDL_Rect){0, PICTURE_WIN_CRYSTALS_SRC_Y, PICTURE_SRC_W, PICTURE_SRC_H}, &PICTURE_DST);
            DrawTextScreen(viewport, assets->fon[FONT_ID_ZSYS], COLOR_WHITE, PIC_TXT_DST_LOC, assets->str[STR_ENDING_ALL_CRYSTALS]);
        }
        if (game->event == EVNT_WIN_SACRIFICE_FRIENDS)
        {
            SDL_RenderCopy(viewport->renderer, assets->tex[T_UI_ATLAS], &(SDL_Rect){0, PICTURE_WIN_SACRIFICE_SRC_Y, PICTURE_SRC_W, PICTURE_SRC_H}, &PICTURE_DST);
            DrawTextScreen(viewport, assets->fon[FONT_ID_ZSYS], COLOR_WHITE, PIC_TXT_DST_LOC, assets->str[STR_ENDING_SACRIFICE]);
        }
        if (game->event == EVNT_WIN_ALL_FRIENDS)
        {
            SDL_RenderCopy(viewport->renderer, assets->tex[T_UI_ATLAS], &(SDL_Rect){0, PICTURE_WIN_FRIENDS_SRC_Y, PICTURE_SRC_W, PICTURE_SRC_H}, &PICTURE_DST);
            DrawTextScreen(viewport, assets->fon[FONT_ID_ZSYS], COLOR_WHITE, PIC_TXT_DST_LOC, assets->str[STR_ENDING_ALL_FRIENDS]);
        }
    }
}

/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
void RenderEvent
(
    u32 t_r,
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
        SDL_SetRenderTarget(viewport->renderer, viewport->render_layer[ZSDL_RENDERLAYER_UI]);
        DrawTextScreen(viewport, assets->fon[FONT_ID_ZSYS], COLOR_WHITE, PIC_TXT_DST_LOC, assets->str[STR_INTRO]);
        SDL_RenderCopy(viewport->renderer, assets->tex[T_UI_ATLAS], &(SDL_Rect){0, PICTURE_INTRO_SRC_Y, PICTURE_SRC_W, PICTURE_SRC_H}, &PICTURE_DST);
    }
}