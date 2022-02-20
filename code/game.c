#include <stdio.h>
#include <stdlib.h>
#include "game.h"

char* GetGamestateName(Gamestate state)
{
	switch (state)
	{
		case GAMESTATE_INIT:
			return "[Gamestate Init]";
		case GAMESTATE_MAIN:
			return "[Gamestate Main]";
		case GAMESTATE_OPTS:
			return "[Gamestate Options]";
		case GAMESTATE_PLAY:
			return "[Gamestate Play]";
		case GAMESTATE_EVNT:
			return "[Gamestate Event]";
		case GAMESTATE_LOSE:
			return "[Gamestate Lose]";
		case GAMESTATE_GOAL:
			return "[Gamestate Goal]";
		case GAMESTATE_EDIT:
			return "[Gamestate Edit]";
		case GAMESTATE_EXIT:
			return "[Gamestate Exit]";
		default:
			return "[Gamestate Unknown]";
	}
}


Game* CreateGame()
{
    Game* new_game = malloc(sizeof(Game));

	RestartGame(new_game);
    return new_game;
}

void FreeGame(Game* game)
{
    if (game != NULL)
        free(game);
    printf("Game freed.\n");
}



void RestartGame(Game* game)
{
	memset(game, 0, sizeof(Game));
	game->doom_below = 64.f;
	game->player.pos = ZERO_R2;
	game->sacrifice_made = 0;
	SEED_ZRNG();
}


void DrawPlayer(Game* game, Viewport* viewport, Assets* assets)
{
	SDL_SetRenderTarget(viewport->renderer, viewport->render_layer[ZSDL_RENDERLAYER_ENTITIES]);
	i2 p_loc = PosToCam(game->player.pos, 1.f, viewport);
	SDL_Rect p_src = {game->anim_chara * WORLD_UNIT, game->player.anim * WORLD_UNIT, WORLD_UNIT, WORLD_UNIT};
	// r2 p_stretch = make_r2(1.f, 1.f);
	// p_stretch.y = LerpR32()
	SDL_Rect p_dst = {p_loc.x - WORLD_UNIT*0.5, p_loc.y - WORLD_UNIT*0.5, WORLD_UNIT, WORLD_UNIT};
	SDL_RenderCopyEx(viewport->renderer, assets->tex[T_CHARACTER_ATLAS], &p_src, &p_dst, 0.0, NULL, game->player.dir);
}


