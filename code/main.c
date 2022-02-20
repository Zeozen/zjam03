#include <stdio.h>
#include "assets.h"
#include "game.h"
#include "update.h"
#include "render.h"
#include "zsdl.h"

#ifdef __EMSCRIPTEN__
#include "emscripten.h"
#endif

#define DT_MS 10
#define DT_SEC 0.01f

typedef struct
{
	Viewport* viewport;
	Game* game;
	Controller* controller;
	Assets* assets;
	Particles* particles;
	Menu* menus;
	zGrid* world;
	Gamestate gamestate_old;
	Gamestate gamestate_now;
	Gamestate gamestate_new;
	u32 t_0_gamestate_change;
} Engine;

void mainloop(void *arg)
{
	Engine* engine = (Engine*)(arg);
	static u32 current_time = 0;
	static u32 time_accumulator = 0;
	static u32 t = 0;
	static u32 t_r = 0; //separate tick counter for counting rendered frames

	//*vvvvvvvvvvvvvvvvvvvvvvvvvv GAMELOOP BEGIN vvvvvvvvvvvvvvvvvvvvvvvvvv*/
		u32 new_time   = SDL_GetTicks();
		u32 frame_time = new_time - current_time;
		if (frame_time > 250)
			frame_time = 250; // avoid spiral of death scenario
		current_time = new_time;
		time_accumulator += frame_time;



/* LOGIC UPDATE IN FIXED TIMESTEPS */
		while (time_accumulator >= DT_MS)
		{
			engine->gamestate_old = engine->gamestate_now;
			CollectInput(engine->controller);
			

			if (ActionPressed(engine->controller, A_RSIZ))
			{
				ComputePixelScale(engine->viewport);
				CalculateScreen(engine->viewport);
				RefreshCursors(engine->viewport, engine->assets);
			}
			if (ActionPressed(engine->controller, A_FSCR))
			{
				ToggleFullscreen(engine->viewport);
				ComputePixelScale(engine->viewport);
				CalculateScreen(engine->viewport);
				RefreshCursors(engine->viewport, engine->assets);
			}

			SDL_SetRenderTarget(engine->viewport->renderer, engine->viewport->render_layer[ZSDL_RENDERLAYER_DEBUGGING]);
			SDL_SetRenderDrawColor(engine->viewport->renderer, 0, 0, 0, 0);
			SDL_RenderClear(engine->viewport->renderer);
			
/* TRANSITION GAMESTATE BEGIN */
		    if (engine->gamestate_now != engine->gamestate_new)
    		{
   				static b8 transition_allowed[NUMBER_OF_GAMESTATES*NUMBER_OF_GAMESTATES] = 
    			{ //FROM	init    main    opts	play	event,  lose	vict	edit	exit	  TO
                			1,      0,      0,		0,  	0,      0,      0,		0,		0,		//init
                			1,      1,      1,		1,  	1,      1,      1,      1,		0,		//main
                			0,      1,      1,		0,  	0,      0,      0,      0,		0,		//opts
                			0,      1,      0,		1,  	1,      1,      1,      1,		0,		//play
                			1,      1,      0,		1,  	1,      1,      1,      0,		0,		//event
                			0,      0,      0,		1,  	1,      1,      0,      0,		0,		//lose
                			0,      0,      0,		1,  	1,      0,      1,      0,		0,		//vict
                			0,      1,      0,		1,  	0,      0,      0,      1,		0,		//edit
                			0,      1,      1,		1,  	1,      1,      1,      1,		1		//exit
    			};

    			if (transition_allowed[engine->gamestate_now + engine->gamestate_new * NUMBER_OF_GAMESTATES])
	    		{

/*	exit and cleanup current state	*/
#if DEBUGPRNT
printf("Game exiting state \t%s...\n", GetGamestateName(engine->gamestate_now));
#endif
	        		switch (engine->gamestate_now) 
	        		{
	            		case GAMESTATE_INIT:
						break;
	            		case GAMESTATE_MAIN:
							ToggleMenu(&engine->menus[MENU_TITLE], ZDISABLED);
							SDL_ShowCursor(0);
						break;
	            		case GAMESTATE_OPTS:
							//ToggleMenu(&engine->menus[MENU_OPTIONS], ZDISABLED);
						break;
	            		case GAMESTATE_PLAY:
							if (Mix_Playing(SFX_FRIEND_CRY))
							{
								Mix_HaltChannel(SFX_FRIEND_CRY);
							}
						break;
	            		case GAMESTATE_EVNT:
						break;
	            		case GAMESTATE_LOSE:
						break;
	            		case GAMESTATE_GOAL:
						break;
	            		case GAMESTATE_EDIT:
							SDL_ShowCursor(0);
							//save edits
							FILE* flvl = fopen("./assets/design/level.bin", "wb");
							u8* buf = malloc(sizeof(u8)*8);

							for (i32 i = 0; i < engine->world->width * engine->world->height; i++)
							{
								buf[0] = engine->world->cell[i].collision;
								buf[1] = engine->world->cell[i].type;
								buf[2] = engine->world->cell[i].id;
								buf[3] = engine->world->cell[i].sprite_bg;
								buf[4] = engine->world->cell[i].sprite_mg;
								buf[5] = engine->world->cell[i].sprite_fg;
								buf[6] = engine->world->cell[i].unused_0;
								buf[7] = engine->world->cell[i].unused_1;
								fwrite(buf, sizeof(u8), 8, flvl);
							}

							fclose(flvl);
							free(buf);
						break;
	            		case GAMESTATE_EXIT:
						break;
	        		}
					engine->gamestate_old = engine->gamestate_now;

/*	enter and setup next state	*/
#if DEBUGPRNT
printf("Game entering state \t%s...\n", GetGamestateName(engine->gamestate_new));
#endif
	        		switch (engine->gamestate_new) 
	        		{
	            		case GAMESTATE_INIT:
							engine->viewport->camera->zoom = ZSDL_CAMERA_MIN_ZOOM;
						break;
	            		case GAMESTATE_MAIN:
						{
							SDL_ShowCursor(1);
							ToggleMenu(&engine->menus[MENU_TITLE], ZENABLED);
							// reload level
							FILE* flvl = fopen("./assets/design/level.bin", "rb");
							u8* buf = malloc(sizeof(u8)*8);

							i32 c_countr = 4;
							i32 f_countr = 4;
							for (i32 i = 0; i < engine->world->width * engine->world->height; i++)
							{
								fread(buf, sizeof(u8), 8, flvl);
								engine->world->cell[i].collision = buf[0];
								engine->world->cell[i].type = buf[1];
								engine->world->cell[i].id = buf[2];
								engine->world->cell[i].sprite_bg = buf[3];
								engine->world->cell[i].sprite_mg = buf[4];
								engine->world->cell[i].sprite_fg = buf[5];
								engine->world->cell[i].unused_0 = buf[6];
								engine->world->cell[i].unused_1 = buf[7];

								if (engine->world->cell[i].type == FRIEND)
								{
									engine->game->friend_idx[f_countr] = i;
									f_countr--;
								}
								if (engine->world->cell[i].type == CRYSTAL)
								{
									engine->game->crystal_idx[c_countr] = i;
									c_countr--;
								}
							}

							fclose(flvl);
							free(buf);
							Mix_Volume(SFX_MUS_BASS, 200);
							Mix_Volume(SFX_MUS_HARP, 0);
							Mix_Volume(SFX_MUS_FLUT, 0);
							Mix_Volume(SFX_MUS_PADS, 0);
							Mix_Volume(SFX_MUS_STAR, 0);
							
						break;
						}
	            		case GAMESTATE_OPTS:
							//ToggleMenu(&engine->menus[MENU_OPTIONS], ZENABLED);
						break;						
	            		case GAMESTATE_PLAY:
							Mix_Volume(SFX_MUS_HARP, 200);
							SET8IN64(0, &engine->viewport->settings, ZSDL_SETTINGS_BYTE_FADE_ALPHA);
						break;
	            		case GAMESTATE_EVNT:
						break;
	            		case GAMESTATE_LOSE:
						break;
	            		case GAMESTATE_GOAL:
						break;
	            		case GAMESTATE_EDIT:
						{
							SDL_ShowCursor(1);
						// reload level
							FILE* flvl = fopen("./assets/design/level.bin", "rb");
							u8* buf = malloc(sizeof(u8)*8);

							for (i32 i = 0; i < engine->world->width * engine->world->height; i++)
							{
								fread(buf, sizeof(u8), 8, flvl);
								engine->world->cell[i].collision = buf[0];
								engine->world->cell[i].type = buf[1];
								engine->world->cell[i].id = buf[2];
								engine->world->cell[i].sprite_bg = buf[3];
								engine->world->cell[i].sprite_mg = buf[4];
								engine->world->cell[i].sprite_fg = buf[5];
								engine->world->cell[i].unused_0 = buf[6];
								engine->world->cell[i].unused_1 = buf[7];
							}

							fclose(flvl);
							free(buf);
						break;
						}
	            		case GAMESTATE_EXIT:
						break;
	        		}
#if DEBUGPRNT
printf("Gamestate change complete.\n");
#endif
					engine->gamestate_now = engine->gamestate_new;
					engine->t_0_gamestate_change = t;
	    		} // end if transition allowed
	    		else //keep current state, but push back and update old state
	    		{
					engine->gamestate_old = engine->gamestate_now;
#if DEBUGPRNT
printf("Gamestate change from %s \tto %s was deemed illegal!\n", GetGamestateName(engine->gamestate_now), GetGamestateName(engine->gamestate_new));
#endif
	    		}
			}
/* TRANSITION GAMESTATE END */

/* PERFORM STATE LOGIC UPDATE */
			switch (engine->gamestate_now)
			{
	            case GAMESTATE_INIT:
					engine->gamestate_new = GAMESTATE_EVNT;
					engine->game->event = EVNT_INTRO;
	                break;
	            case GAMESTATE_MAIN:
					engine->gamestate_new = UpdateMain(t, DT_SEC, engine->t_0_gamestate_change, engine->viewport, engine->game, engine->controller, engine->particles, engine->assets, engine->menus, engine->world);
	                break;
				case GAMESTATE_OPTS:
					engine->gamestate_new = UpdateOpts(t, DT_SEC, engine->t_0_gamestate_change, engine->viewport, engine->game, engine->controller, engine->particles, engine->assets, engine->menus, engine->world);
				break;					
	            case GAMESTATE_PLAY:
					engine->gamestate_new = UpdatePlay(t, DT_SEC, engine->t_0_gamestate_change, engine->viewport, engine->game, engine->controller, engine->particles, engine->assets, engine->menus, engine->world);
	                break;
	            case GAMESTATE_EVNT:
					engine->gamestate_new = UpdateEvent(t, DT_SEC, engine->t_0_gamestate_change, engine->viewport, engine->game, engine->controller, engine->particles, engine->assets, engine->menus, engine->world);				
	                break;
	            case GAMESTATE_LOSE:
					engine->gamestate_new = UpdateLose(t, DT_SEC, engine->t_0_gamestate_change, engine->viewport, engine->game, engine->controller, engine->particles, engine->assets, engine->menus, engine->world);
	                break;
	            case GAMESTATE_GOAL:
					engine->gamestate_new = UpdateGoal(t, DT_SEC, engine->t_0_gamestate_change, engine->viewport, engine->game, engine->controller, engine->particles, engine->assets, engine->menus, engine->world);	
	                break;
	            case GAMESTATE_EDIT:
					engine->gamestate_new = UpdateEdit(t, DT_SEC, engine->t_0_gamestate_change, engine->viewport, engine->game, engine->controller, engine->particles, engine->assets, engine->menus, engine->world);
	                break;
	            case GAMESTATE_EXIT:
		            break;
			}

			TickParticles(engine->particles, t, DT_SEC);
			// advance time
			t++;
			time_accumulator -= DT_MS;

			if (ActionPressed(engine->controller, A_QUIT))
        		engine->gamestate_new = GAMESTATE_EXIT;
		} //logic update end
		
/* RENDER UPDATE */
		//@TODO: calculate interpolation value from last render to smooth rendering
		//prev_state * (1-t) + curr_state * t
		CleanRenderTargets(engine->viewport);
		switch (engine->gamestate_now)
		{
			case GAMESTATE_INIT:
			break;
			case GAMESTATE_MAIN:
				RenderMain(t_r, engine->viewport, engine->game, engine->controller, engine->particles, engine->assets, engine->menus, engine->world);
			break;
			case GAMESTATE_OPTS:
				RenderOpts(t_r, engine->viewport, engine->game, engine->controller, engine->particles, engine->assets, engine->menus, engine->world);
			break;			
			case GAMESTATE_PLAY:
				RenderPlay(t_r, engine->viewport, engine->game, engine->controller, engine->particles, engine->assets, engine->menus, engine->world);
			break;
			case GAMESTATE_EVNT:
				RenderEvent(t_r, engine->viewport, engine->game, engine->controller, engine->particles, engine->assets, engine->menus, engine->world);
			break;
			case GAMESTATE_LOSE:
				RenderLose(t_r, engine->viewport, engine->game, engine->controller, engine->particles, engine->assets, engine->menus, engine->world);
			break;
			case GAMESTATE_GOAL:
				RenderGoal(t_r, engine->viewport, engine->game, engine->controller, engine->particles, engine->assets, engine->menus, engine->world);
			break;
			case GAMESTATE_EDIT:
				RenderEdit(t_r, engine->viewport, engine->game, engine->controller, engine->particles, engine->assets, engine->menus, engine->world);
			break;
			case GAMESTATE_EXIT:
			break;
		}
		t_r++;
		SDL_SetRenderTarget(engine->viewport->renderer, engine->viewport->render_layer[ZSDL_RENDERLAYER_ENTITIES]);
		DrawParticles(engine->viewport, t, engine->particles);
		FinalizeRenderAndPresent(engine->viewport);
	//main loop end
}


int main(int argc, char* argv[])
{
/*vvvvvvvvvvvvvvvvvvvvvvvvvv INIT vvvvvvvvvvvvvvvvvvvvvvvvvv*/
	SetupSDL();
	Viewport* viewport = CreateViewport("To make sacred");
	Game* game = CreateGame();
	Controller* controller = CreateController();
	Assets* assets = CreateAssets(viewport);
	viewport->camera = CreateCamera(ZERO_R2);
	Particles* particles = InitParticles();
	Menu* menus = malloc(sizeof(Menu) * MAX_MENUS);
	i2 wrld_dim = make_i2(48, 128);
	zGrid* world = CreateGrid(wrld_dim.x, wrld_dim.y, make_r2(-WORLD_UNIT_F * wrld_dim.x/2, -WORLD_UNIT_F * wrld_dim.y + WORLD_UNIT_F * 4.f));
	menus[MENU_TITLE] = CreateMenu("main");
	//menus[MENU_OPTIONS] = CreateMenu("options");
	//menus[MENU_OPTIONS_VIDEO] = CreateMenu("options_video");
	//menus[MENU_OPTIONS_AUDIO] = CreateMenu("options_audio");
	//menus[MENU_OPTIONS_INPUT] = CreateMenu("options_input");

	Engine* engine = (Engine*)malloc(sizeof(Engine));
	engine->viewport = viewport;
	engine->game = game;
	engine->controller = controller;
	engine->assets = assets;
	engine->particles = particles;
	engine->gamestate_now = GAMESTATE_INIT;
	engine->gamestate_new = GAMESTATE_INIT;
	engine->menus = menus;
	engine->world = world;




/*^^^^^^^^^^^^^^^^^^^^^^^^^^ INIT ^^^^^^^^^^^^^^^^^^^^^^^^^^*/

/*vvvvvvvvvvvvvvvvvvvvvvvvvv LOAD ASSETS vvvvvvvvvvvvvvvvvvvvvvvvvv*/
	LoadFont(assets, FONT_ID_ZSYS, viewport->renderer, FONT_PATH_ZSYS);
	SDL_SetRenderDrawColor(viewport->renderer, 0, 0, 0, 0xff);
	SDL_SetRenderTarget(viewport->renderer, NULL);
	SDL_RenderClear(viewport->renderer);
	DrawTextScreenCentered(viewport, assets->fon[FONT_ID_ZSYS], COLOR_WHITE, (SDL_Rect){0, 0, ZSDL_INTERNAL_WIDTH, ZSDL_INTERNAL_HEIGHT}, "loading...");
	SDL_RenderPresent(viewport->renderer);

LoadTexture(assets, T_TILE_ATLAS, viewport->renderer, T_TILE_ATLAS_PATH);
LoadTexture(assets, T_UI_ATLAS, viewport->renderer, T_UI_ATLAS_PATH);
LoadTexture(assets, T_CHARACTER_ATLAS, viewport->renderer, T_CHARACTER_ATLAS_PATH);


LoadCursor(assets, CUR_POINT, CUR_PATH_POINT);
LoadCursor(assets, CUR_CLICK, CUR_PATH_CLICK);
LoadCursor(assets, CUR_HAND, CUR_PATH_HAND);
LoadCursor(assets, CUR_GRAB, CUR_PATH_GRAB);
LoadCursor(assets, CUR_CROSS, CUR_PATH_CROSS);

LoadSound(assets, SFX_SELECT, SFX_PATH_SELECT);
LoadSound(assets, SFX_TAP, SFX_PATH_TAP);
LoadSound(assets, SFX_HOVER, SFX_PATH_HOVER);
LoadSound(assets, SFX_FOOTSTEP, SFX_PATH_FOOTSTEP);
LoadSound(assets, SFX_JUMP, SFX_PATH_JUMP);
LoadSound(assets, SFX_COLLECT_CRYSTAL, SFX_PATH_COLLECT_CRYSTAL);
LoadSound(assets, SFX_COLLECT_FRIEND, SFX_PATH_COLLECT_FRIEND);
LoadSound(assets, SFX_FRIEND_01, SFX_PATH_FRIEND_01);
LoadSound(assets, SFX_FRIEND_02, SFX_PATH_FRIEND_02);
LoadSound(assets, SFX_FRIEND_03, SFX_PATH_FRIEND_03);
LoadSound(assets, SFX_FRIEND_04, SFX_PATH_FRIEND_04);
LoadSound(assets, SFX_FRIEND_05, SFX_PATH_FRIEND_05);
LoadSound(assets, SFX_MUS_BASS, SFX_PATH_MUS_BASS);
LoadSound(assets, SFX_MUS_HARP, SFX_PATH_MUS_HARP);
LoadSound(assets, SFX_MUS_FLUT, SFX_PATH_MUS_FLUT);
LoadSound(assets, SFX_MUS_PADS, SFX_PATH_MUS_PADS);
LoadSound(assets, SFX_MUS_STAR, SFX_PATH_MUS_STAR);

LoadSound(assets, SFX_FRIEND_DIE, SFX_PATH_FRIEND_DIE);
LoadSound(assets, SFX_CRYSTAL_DIE, SFX_PATH_CRYSTAL_DIE);
LoadSound(assets, SFX_FRIEND_CRY, SFX_PATH_FRIEND_CRY);

GenerateString(assets, STR_ENDING_LUKEWARM, "Is this fine?}Are you satisfied?}You can do more!");

GenerateString(assets, STR_ENDING_EARLY_DEATH, 
"Tomorrow, and tomorrow, and tomorrow,}Creeps in this petty pace from day to day,}To the last syllable of recorded time;}And all our yesterdays have lighted fools}The way to dusty death. Out, out, brief candle!}Life's but a walking shadow, a poor player,}That struts and frets his hour upon the stage,}And then is heard no more. It is a tale}Told by an idiot, full of sound and fury,}Signifying nothing.");

GenerateString(assets, STR_INTRO, 
"The crystals are coveted as they give power.}The path to becoming one with the stars, is a grueling}and lonesome road not taken by many.}After all, in order to reach it...");

GenerateString(assets, STR_ENDING_ALL_CRYSTALS, 
"You've gained great power!}Going out in a blaze of glory!}It might be lonely up there,}but future generations look to you as their guide.");

GenerateString(assets, STR_ENDING_SACRIFICE, 
"You obtain power to stand above and beyond!}But Even when it's pulsating in your palm,}it feels hollow, empty.}You've gained power, but at what cost?");

GenerateString(assets, STR_ENDING_ALL_FRIENDS, 
"You won't light up the night sky,}but the fire that you tend with others}and the smiling hearts you share}burn just as bright.}");

GenerateString(assets, STR_SACRIFICE_PROMPT, 
"Press [ ENTER ] to sacrifice!!");

/*^^^^^^^^^^^^^^^^^^^^^^^^^^ LOAD ASSETS ^^^^^^^^^^^^^^^^^^^^^^^^^^*/
SetCursor(viewport, assets, CUR_POINT);

//START IN FULLSCREEN
// ToggleFullscreen(engine->viewport);
ComputePixelScale(engine->viewport);
CalculateScreen(engine->viewport);
RefreshCursors(engine->viewport, engine->assets);

MixSFX();

Mix_PlayChannel(SFX_MUS_FLUT, engine->assets->sfx[SFX_MUS_FLUT], -1);
Mix_PlayChannel(SFX_MUS_BASS, engine->assets->sfx[SFX_MUS_BASS], -1);
Mix_PlayChannel(SFX_MUS_HARP, engine->assets->sfx[SFX_MUS_HARP], -1);
Mix_PlayChannel(SFX_MUS_PADS, engine->assets->sfx[SFX_MUS_PADS], -1);
Mix_PlayChannel(SFX_MUS_STAR, engine->assets->sfx[SFX_MUS_STAR], -1);



/*vvvvvvvvvvvvvvvvvvvvvvvvvv MAIN LOOP vvvvvvvvvvvvvvvvvvvvvvvvvv*/
#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop_arg(mainloop, engine, -1, 1);
#else
	while (engine->gamestate_now != GAMESTATE_EXIT)
		mainloop(engine);
#endif
/*^^^^^^^^^^^^^^^^^^^^^^^^^^ MAIN LOOP ^^^^^^^^^^^^^^^^^^^^^^^^^^*/

#if DEBUGPRNT
printf("\n~~~Exiting game!~~~\n");
#endif		
	// free all things
	FreeParticles(particles);
	FreeMenus(menus);
	FreeGrid(world);
	FreeController(controller);
	FreeAssets(assets);
	FreeViewport(viewport);
	FreeGame(game);
	free(engine);

	Mix_Quit();
	IMG_Quit();
	SDL_Quit();

	return 0;
}