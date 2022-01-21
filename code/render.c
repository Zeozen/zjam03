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
    SDL_SetRenderDrawColor(viewport->renderer, 0xff, 0xff, 0xff, 0xff);
    i2 rect_location = PosToCam(make_r2(0.f, 0.f), viewport->camera);
    SDL_Rect test_rect = {rect_location.x, rect_location.y, 16*viewport->camera->zoom, 16*viewport->camera->zoom};
    SDL_RenderDrawRect(viewport->renderer, &test_rect);
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

