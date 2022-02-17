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

     SDL_SetRenderTarget(viewport->renderer, viewport->render_layer[ZSDL_RENDERLAYER_BACKGROUND]);

//draw world
    SDL_SetRenderDrawColor(viewport->renderer, 0x22, 0x15, 0x15, 0xff);
    SDL_SetRenderDrawColor(viewport->renderer, 0x00, 0x00, 0x00, 0xff);
    SDL_RenderFillRect(viewport->renderer, NULL);

    i2 origo_to_screen = PosToCam(ZERO_R2, 1.f, viewport);
    SDL_SetRenderDrawColor(viewport->renderer, 0xcc, 0xaa, 0xaa, 0x33);
    SDL_RenderDrawLine(viewport->renderer, origo_to_screen.x, 0, origo_to_screen.x, ZSDL_INTERNAL_HEIGHT);
    SDL_RenderDrawLine(viewport->renderer, 0, origo_to_screen.y, ZSDL_INTERNAL_WIDTH, origo_to_screen.y);
    
//draw home
    SDL_SetRenderDrawColor(viewport->renderer, 0xbb, 0xbb, 0xbb, 0xbb);
    ZSDL_RenderDrawCircle(viewport, 32.f * viewport->camera->zoom, PosToCam(ZERO_R2, 1.f, viewport));

    SDL_SetRenderTarget(viewport->renderer, viewport->render_layer[ZSDL_RENDERLAYER_ENTITIES]);

    SDL_SetRenderTarget(viewport->renderer, viewport->render_layer[ZSDL_RENDERLAYER_FOREGROUND]);

    SDL_SetRenderTarget(viewport->renderer, viewport->render_layer[ZSDL_RENDERLAYER_UI]);
    DrawMenu(menu[MENU_TITLE], viewport, assets);

    //DrawTextWorld(viewport, assets->fon[FONT_ID_ZSYS], COLOR_WHITE, ZERO_R2, 8.f, "THERE");
    //DrawTextWorld(viewport, assets->fon[FONT_ID_ZSYS], COLOR_WHITE, ZERO_R2, 4.f, "HELLO");
 
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

    SDL_SetRenderTarget(viewport->renderer, viewport->render_layer[ZSDL_RENDERLAYER_UI]);
    DrawMenu(menu[MENU_OPTIONS], viewport, assets);
    DrawMenu(menu[MENU_OPTIONS_VIDEO], viewport, assets);
    DrawMenu(menu[MENU_OPTIONS_AUDIO], viewport, assets);
    DrawMenu(menu[MENU_OPTIONS_INPUT], viewport, assets);
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
    i2 mloc = MouseLocation(controller, viewport);
    r2 mpos = CamToPos(mloc, viewport);

    SDL_SetRenderTarget(viewport->renderer, viewport->render_layer[ZSDL_RENDERLAYER_ENTITIES]);
//draw player
    i2 p_loc = PosToCam(game->player.pos, 1.f, viewport);
    SDL_Rect p_rect = {p_loc.x - PLAYER_HALFWIDTH, p_loc.y - PLAYER_HALFHEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT};
    SDL_SetRenderDrawColor(viewport->renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderFillRect(viewport->renderer, &p_rect);

//draw house
    i2 origin_loc = PosToCam(ZERO_R2, 1.f, viewport);
    SDL_Rect house_rect = {origin_loc.x - HOME_RADIUS, origin_loc.y - HOME_RADIUS, HOME_RADIUS*2, HOME_RADIUS};
    SDL_SetRenderDrawColor(viewport->renderer, 0x55, 0x55, 0x55, 0xff);
    SDL_RenderDrawRect(viewport->renderer, &house_rect);

    DrawGrid(world, viewport, assets);

    SDL_SetRenderTarget(viewport->renderer, viewport->render_layer[ZSDL_RENDERLAYER_UI]);
    i32 midx = PosToIdx(mpos, world);
        u8 sd_row = GET4IN8(world->cell[PosToIdx(mpos, world)].sprite_mg, BITPOS_SPRITE_ROW);
    u8 sd_col = GET4IN8(world->cell[PosToIdx(mpos, world)].sprite_mg, BITPOS_SPRITE_COL);
	i2 txt_loc = ZERO_I2;
	char txt[50];
	sprintf(txt, "mouse idx %d, spr row: %d col: %d", midx, sd_row, sd_col);
	DrawTextScreen(viewport, assets->fon[FONT_ID_ZSYS], COLOR_WHITE, txt_loc, txt);

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

}

