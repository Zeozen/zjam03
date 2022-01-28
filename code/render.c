#include "render.h"
#include "assets.h"

/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
void RenderMain
(
    Viewport* viewport, 
    Game* game, 
    Controller* controller, 
    Dots* dots,
    Assets* assets
)/*-----------------------------------------------------------*/
{/*-----------------------------------------------------------*/
    SDL_SetRenderTarget(viewport->renderer, viewport->render_layer[ZSDL_RENDERLAYER_BACKGROUND]);
    SDL_SetRenderDrawColor(viewport->renderer, 0x33, 0x22, 0x22, 0xff);
    SDL_RenderFillRect(viewport->renderer, NULL);
    SDL_SetRenderDrawColor(viewport->renderer, 0xff, 0xff, 0xff, 0xff);
    i2 rect_location = PosToCam(make_r2(0.f, 0.f), viewport->camera);
    SDL_Rect test_rect = {rect_location.x, rect_location.y, 16*viewport->camera->zoom, 16*viewport->camera->zoom};
    SDL_RenderDrawRect(viewport->renderer, &test_rect);

    SDL_SetRenderTarget(viewport->renderer, viewport->render_layer[ZSDL_RENDERLAYER_FOREGROUND]);
    SDL_SetTextureColorMod(assets->fon[0]->glyphs, 255, 255, 255);
    char text[6] = "AaBbCc";
    for (i32 i = 0; i < 6; i++)
    {
        i32 idx = text[i] - 32;
        i2 src_coord = make_i2(idx%ZFONT_WIDTH, idx/ZFONT_WIDTH);
        src_coord = mul_i2(src_coord, assets->fon[0]->siz);
        SDL_Rect fon_src = {src_coord.x, src_coord.y, assets->fon[0]->siz.x, assets->fon[0]->siz.y};
        i2 txt_dst = PosToCam(make_r2(-10.f+ i * assets->fon[0]->siz.x + assets->fon[0]->spacing.x, -25.f), viewport->camera);
        SDL_Rect fon_dst = {txt_dst.x, txt_dst.y, assets->fon[0]->siz.x*viewport->camera->zoom, assets->fon[0]->siz.y*viewport->camera->zoom};
        SDL_RenderCopy(viewport->renderer, assets->fon[0]->glyphs, &fon_src, &fon_dst);
    }
}

/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
void RenderPlay
(
    Viewport* viewport, 
    Game* game, 
    Controller* controller, 
    Dots* dots,
    Assets* assets
)/*-----------------------------------------------------------*/
{/*-----------------------------------------------------------*/
   
}

/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
void RenderLose
(
    Viewport* viewport, 
    Game* game, 
    Controller* controller, 
    Dots* dots,
    Assets* assets
)/*-----------------------------------------------------------*/
{/*-----------------------------------------------------------*/

}

