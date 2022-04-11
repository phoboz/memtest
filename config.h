#ifndef _CONFIG_H
#define _CONFIG_H

#define SCREEN_WIDTH     320
#define SCREEN_HEIGHT    208

#define PLAYFIELD_WIDTH  320
#define PLAYFIELD_HEIGHT 200

#define SND_FREQ         14434
#define MIN_SND_VOL      1
#define MAX_SND_VOL      64
#define LOW_SND_VOL      30
#define FAINT_SND_DELTA  16


#define MAX_PLAYERS   2
#define MAX_ENEMIES   9
#define MAX_SHADES    (MAX_PLAYERS + MAX_ENEMIES)

#define LEVEL_BG_LAYER        0
#define LEVEL_MID_LAYER       0
#define LEVEL_FG_LAYER        0
#define SHADE_LAYER           1
#define CHARACTER_LAYER_START 2
#define CHARACTER_LAYER_END   13

#define CONSOLE_COLOR_INDEX   255
#define PERISH_INTENSITY      64

#define START_LEVEL 0

#endif

