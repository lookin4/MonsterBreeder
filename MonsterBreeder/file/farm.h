#ifndef GAME_FARM_H
#define GAME_FARM_H

#include"almighty.h"

enum {
	FARM_TRAINING,
	FARM_REST,
	FARM_BATTLE,
	FARM_ITEM,
	FARM_FILE,
	FARM_PARK,
	FARM_MAX
};

enum {
	TRAINING_DOMINO,
	TRAINING_SYATEKI,
	TRAINING_BENKYO,
	TRAINING_KYOSEKI,
	TRAINING_HASIRI,
	TRAINING_MARUTA,
	TRAINING_OMORI,
	TRAINING_YUKA,
	TRAINING_MEISO,
	TRAINING_POOL,
	TRAINING_MAX
};

extern lkn::Sound* spring_music;

extern lkn::Image* sibahu_image;
extern lkn::Image* sibahu2_image;
extern lkn::Image* farm_background_image;
extern lkn::Image* farm_sky_image;
extern lkn::Image* koya_kabe_image;
extern lkn::Image* koya_tobira_image;

extern lkn::Image* waku_image;

#endif