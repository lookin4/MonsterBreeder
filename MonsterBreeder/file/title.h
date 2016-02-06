#ifndef GAME_TITLE_H
#define GAME_TITLE_H

enum {
	TITLE_START,
	TITLE_EXIT,
	TITLE_MAX
};

extern lkn::Image* title_image;
extern lkn::Image* title_background_image;

extern lkn::Sound* opening_music;

#endif