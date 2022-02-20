#ifndef ASSETS_H
#define ASSETS_H

//font
#define FONT_ID_ZSYS 0
#define FONT_PATH_ZSYS "./assets/font/font_zsys.png"

//texture aliases
#define T_TILE_ATLAS 0
#define T_UI_ATLAS 1
#define T_CHARACTER_ATLAS 2
//texture paths
#define T_TILE_ATLAS_PATH "./assets/texture/tilemap.png"
#define T_UI_ATLAS_PATH "./assets/texture/gui.png"
#define T_CHARACTER_ATLAS_PATH "./assets/texture/characters.png"

//cursors
#define CUR_POINT 0
#define CUR_CLICK 1
#define CUR_HAND 2
#define CUR_GRAB 3 
#define CUR_CROSS 4
//cursorpaths
#define CUR_PATH_POINT "./assets/cursor/cur_zsys_point.png"
#define CUR_PATH_CLICK "./assets/cursor/cur_zsys_click.png"
#define CUR_PATH_HAND "./assets/cursor/cur_zsys_hand.png"
#define CUR_PATH_GRAB "./assets/cursor/cur_zsys_grab.png"
#define CUR_PATH_CROSS "./assets/cursor/cur_zsys_cross.png"

#define MUS_BGM 0

//sound effect aliases
typedef enum
{
    SFX_HOVER,
    SFX_SELECT,
    SFX_TAP,
    SFX_FOOTSTEP,
    SFX_JUMP,
    SFX_COLLECT_CRYSTAL,
    SFX_COLLECT_FRIEND,
    SFX_FRIEND_01,
    SFX_FRIEND_02,
    SFX_FRIEND_03,
    SFX_FRIEND_04,
    SFX_FRIEND_05,
    SFX_MUS_BASS,
    SFX_MUS_HARP,
    SFX_MUS_FLUT,
    SFX_MUS_PADS,
    SFX_MUS_STAR,
    SFX_FRIEND_DIE,
    SFX_CRYSTAL_DIE,
    SFX_FRIEND_CRY
} SoundEffects;
//paths
#define SFX_PATH_HOVER "./assets/sound/hover.wav"
#define SFX_PATH_SELECT "./assets/sound/select.wav"
#define SFX_PATH_TAP "./assets/sound/tap.wav"
#define SFX_PATH_FOOTSTEP "./assets/sound/footstep.wav"
#define SFX_PATH_JUMP "./assets/sound/jump.wav"
#define SFX_PATH_COLLECT_CRYSTAL "./assets/sound/collect_crystal.wav"
#define SFX_PATH_COLLECT_FRIEND "./assets/sound/collect_friend.wav"
#define SFX_PATH_FRIEND_01 "./assets/sound/friend_01.wav"
#define SFX_PATH_FRIEND_02 "./assets/sound/friend_02.wav"
#define SFX_PATH_FRIEND_03 "./assets/sound/friend_03.wav"
#define SFX_PATH_FRIEND_04 "./assets/sound/friend_04.wav"
#define SFX_PATH_FRIEND_05 "./assets/sound/friend_05.wav"
#define SFX_PATH_FRIEND_05 "./assets/sound/friend_05.wav"
#define SFX_PATH_MUS_BASS "./assets/sound/sacrifice_bgm_bass.wav"
#define SFX_PATH_MUS_HARP "./assets/sound/sacrifice_bgm_harp.wav"
#define SFX_PATH_MUS_FLUT "./assets/sound/sacrifice_bgm_flute.wav"
#define SFX_PATH_MUS_PADS "./assets/sound/sacrifice_bgm_pad.wav"
#define SFX_PATH_MUS_STAR "./assets/sound/sacrifice_bgm_twinkle.wav"
#define SFX_PATH_FRIEND_DIE "./assets/sound/die_friend.wav"
#define SFX_PATH_CRYSTAL_DIE "./assets/sound/die_crystal.wav"
#define SFX_PATH_FRIEND_CRY "./assets/sound/cry_friend.wav"


#define GUI_DESIGN_PATH "./assets/design/gui.ini"

#define STR_INTRO 0
#define STR_ENDING_LUKEWARM 1   //pick up five powerups, but don't reach goal
#define STR_ENDING_EARLY_DEATH 2 //die before picking up five powerups
#define STR_ENDING_ALL_CRYSTALS 3 //reach goal with all five crystals
#define STR_ENDING_ALL_FRIENDS 4 //reach cave with all friends
#define STR_ENDING_SACRIFICE 5 //pick up a mix of powerups, and use gathered friends as ladder to reach goal
#define STR_SACRIFICE_PROMPT 6 
#endif //ASSETS_H