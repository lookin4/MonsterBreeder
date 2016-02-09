#define _CRT_SECURE_NO_WARNINGS

#include"../GL/freeglut.h"
#include"../lkn_library/sound.h"
#include"../lkn_library/input_manager.h"
#include"../lkn_library/image.h"
#include"../game/monster.h"
#include"almighty.h"
#include"title.h"

extern game::Monster* monster;
extern game::Suezo* suezo;


int title_count = 0;
bool title_init = 0;
int title_movie;

void title() {
	if (title_init == 0) {
		title_init = 1;
		alSourcePlay(opening_music->source);

		target->y = 0;
		target->x = 0;
		target->z = 0;

		eye->y = 0;
		eye->x = 0;
		eye->z = 1000;
		frame = 0;
		
		
		monster = suezo;

		

		//////////////////////////////
		wcscpy(monster->name, L"‚·‚¦‚«‚·‚¦‚¼[");
		monster->HP = 90;
		monster->power_point = 100;
		monster->intelligence_point = 180;
		monster->hit_probability_point = 170;
		monster->dodge_point = 120;
		monster->strong_point = 80;
		//////////////////////////////



	}

	glColor4f(1, 1, 1, 1);
	title_background_image->changeImage();
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0.f, 0.f);
		glVertex2f(-430.f, 430.f);
		glTexCoord2f(0.f, 1.f);
		glVertex2f(-430.f, -430.f);
		glTexCoord2f(1.f, 1.f);
		glVertex2f(430.f, -430.f);
		glTexCoord2f(1.f, 0.f);
		glVertex2f(430.f, 430.f);
	}
	glEnd();



	title_image->changeImage();

	glEnable(GL_BLEND);
	glBlendFunc(
		GL_SRC_ALPHA,
		GL_ONE_MINUS_SRC_ALPHA
		);

	glPushMatrix();
	if (frame < 200) {
		if (lkn::InputManager::getInstance()->keyPless(0x0d)) {
			frame = 200;
		}
		title_movie = 200 + (400 - frame * 2);
	}
	glTranslatef(0, title_movie, 0);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0.f, 0.f);
		glVertex2f(-250.f, 250.f);
		glTexCoord2f(0.f, 1.f);
		glVertex2f(-250.f, -250.f);
		glTexCoord2f(1.f, 1.f);
		glVertex2f(250.f, -250.f);
		glTexCoord2f(1.f, 0.f);
		glVertex2f(250.f, 250.f); 	}
	glEnd();
	glPopMatrix();

	if (frame >= 200) {
		if (lkn::InputManager::getInstance()->keyPless('w')) {
			alSourcePlay(select_music->source);
			title_count++;
		}
		if (lkn::InputManager::getInstance()->keyPless('s')) {
			alSourcePlay(select_music->source);
			title_count++;
		}
		title_count = (TITLE_MAX + title_count) % TITLE_MAX;

		glBlendFunc(
			GL_ONE,
			GL_ONE
			);
		float hajimekara = (1 - title_count)*0.3f + 0.1f;
		float owari = title_count * 0.3f + 0.1f;
		glDisable(GL_TEXTURE);
		glColor4f(hajimekara, hajimekara, hajimekara, 1);
		glBegin(GL_QUADS);
		{
			glVertex2f(-70.f, -140.f);
			glVertex2f(70.f, -140.f);
			glVertex2f(70.f, -210.f);
			glVertex2f(-70.f, -210.f);
		}
		glColor4f(owari, owari, owari, 1);
		{
			glVertex2f(-70.f, -212.f);
			glVertex2f(70.f, -212.f);
			glVertex2f(70.f, -282.f);
			glVertex2f(-70.f, -282.f);
		}
		glEnd();
		glDisable(GL_BLEND);
		glColor3f(0.3f, 0.3f, 0.3f);
		font->ChangeSize(lkn::TYPE_NORMAL);
		font->DrawStringW(-67, -200, L" ‚Í‚¶‚ß‚©‚ç");
		font->DrawStringW(-67, -270, L" ‚d‚w‚h‚s");

		if (lkn::InputManager::getInstance()->keyPless(0x0d)) {
			if (title_count == TITLE_START) {
				alSourcePlay(decision_music->source);
				alSourceStop(opening_music->source);
				title_init = 0;
				func = farm;
			}
			else if (title_count == TITLE_EXIT) {
				alSourcePlay(decision_music->source);
				exit(0);
			}
		}
	}
}
