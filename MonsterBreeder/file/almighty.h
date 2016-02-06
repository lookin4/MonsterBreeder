#ifndef GAME_ALLMIGHTY_H
#define GAME_ALLMIGHTY_H

#include"../GL/freeglut.h"
#include"../lkn_library/font.h"
#include"../lkn_library/sound.h"
#include"../lkn_library/image.h"
#include"../lkn_library/vector3.h"
#include"../lkn_library/input_manager.h"
#include"../game/message_box.h"

extern void(*func)(void);
extern void title();
extern void farm();
extern void battle();

extern lkn::GLFONT* font;
extern lkn::GLFONT* min_font;
extern lkn::GLFONT* max_font;

extern int frame;

extern lkn::Sound* decision_music;
extern lkn::Sound* cancel_music;
extern lkn::Sound* select_music;

extern lkn::Vec3* eye;
extern lkn::Vec3* target;

//extern game::MyMessageBox* message_box;

namespace lkn{
	enum {
		YES,
		NO,
		YES_NO_MAX
	};
}

#endif