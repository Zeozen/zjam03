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
    Assets* assets
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

    //DrawTextWorld(viewport, assets->fon[FONT_ID_ZSYS], COLOR_WHITE, ZERO_R2, 8.f, "THERE");
    //DrawTextWorld(viewport, assets->fon[FONT_ID_ZSYS], COLOR_WHITE, ZERO_R2, 4.f, "HELLO");

    i2 mloc = MouseLocation(controller, viewport);
    SDL_Point mpoint = {mloc.x, mloc.y};
    i2 test_btn_src = ZERO_I2;
    i2 test_btn_siz = make_i2(32, 17);
    i2 test_btn_dst = make_i2(ZSDL_INTERNAL_HALFWIDTH-test_btn_siz.x/2, ZSDL_INTERNAL_HALFHEIGHT-test_btn_siz.y/2);
    SDL_Rect test_btn_r = {test_btn_dst.x, test_btn_dst.y, test_btn_siz.x, test_btn_siz.y};
    if (SDL_PointInRect(&mpoint, &test_btn_r))
    {
        if (ActionHeld(controller, A_MB_L))
            test_btn_src.x = 8 * 3 * 2;
        else
            test_btn_src.x = 8 * 3 * 1;
    }
    DrawNineSliced(viewport, assets->tex[T_UI_ATLAS], test_btn_src, test_btn_dst, test_btn_siz, ZSYS_NINESLICE_DIMENSIONS);
 
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
    Assets* assets
)/*-----------------------------------------------------------*/
{/*-----------------------------------------------------------*/


    #ifdef DBUG_MOUSE
    char txt_mraw[50];
    char txt_mpos[50];
    char txt_mcam[50];
    i2 mraw = MouseLocation(controller, viewport);
    r2 mpos = CamToPos(mraw, viewport);
    i2 mcam = PosToCam(mpos, viewport);
    sprintf(txt_mraw, "mraw: (%d, %d)", mraw.x, mraw.y);
    sprintf(txt_mpos, "mpos: (%f, %f)", mpos.x, mpos.y);
    sprintf(txt_mcam, "mcam: (%d, %d)", mcam.x, mcam.y);
    DrawTextScreen(viewport, assets->fon[0], COLOR_WHITE, make_i2(3, 3), txt_mraw);
    DrawTextScreen(viewport, assets->fon[0], COLOR_WHITE, make_i2(3, 3 + assets->fon[0]->siz.y), txt_mpos);
    DrawTextScreen(viewport, assets->fon[0], COLOR_WHITE, make_i2(3, 3+ assets->fon[0]->siz.y*2), txt_mcam);
    #endif
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
    Assets* assets
)/*-----------------------------------------------------------*/
{/*-----------------------------------------------------------*/

}

