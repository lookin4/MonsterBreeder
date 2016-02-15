#define _CRT_SECURE_NO_WARNINGS

#include"../GL/freeglut.h"
#include"../lkn_library/sound.h"
#include"../lkn_library/input_manager.h"
#include"../lkn_library/image.h"
#include"../game/monster.h"
#include"../game/player.h"
#include"almighty.h"
#include"title.h"


void opening();

extern game::Monster* monster;
extern game::Suezo* suezo;

extern game::Monster* enemy;
extern game::Monorisu* monorisu;

extern game::Player* player;

extern lkn::Sound* init_music;


extern lkn::Image* tuba_image;
extern lkn::Image* sippo_image;
extern lkn::Image* taore_image;
extern lkn::Image* biimu_image;

extern lkn::Image* init_image;


extern game::MyMessageBox* message_box;

int title_count = 0;
bool title_init = 0;
int title_movie;

int opening_init = 0;

void hajimemasite();
void kyuudakedo();
void sokode();
void tasukete();
void yorosikune();

void(*o_message)();

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

		opening_init = 0;

		player->nengetu = 12;

		wcscpy(suezo->waza[0]->name, L"つばはき");
		wcscpy(suezo->waza[1]->name, L"しっぽアタック");
		wcscpy(monorisu->waza[0]->name, L"ビーム");
		wcscpy(monorisu->waza[1]->name, L"たおれこみ");

		suezo->waza[0]->image = tuba_image;
		suezo->waza[1]->image = sippo_image;
		monorisu->waza[0]->image = biimu_image;
		monorisu->waza[1]->image = taore_image;

		wcscpy(suezo->name, L"すえぞー");
		wcscpy(monorisu->name, L"ものりす");


		monster = suezo;

		enemy = monorisu;

		monster->type = game::PLAYER;
		enemy->type = game::ENEMY;

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
		font->DrawStringW(-67, -200, L" はじめから");
		font->DrawStringW(-67, -270, L" ＥＸＩＴ");

		if (lkn::InputManager::getInstance()->keyPless(0x0d)) {
			if (title_count == TITLE_START) {
				alSourcePlay(decision_music->source);
				alSourceStop(opening_music->source);
				title_init = 0;
				func = opening;
			}
			else if (title_count == TITLE_EXIT) {
				alSourcePlay(decision_music->source);
				exit(0);
			}
		}
	}

	glMatrixMode(GL_PROJECTION);          /* 投影変換行列の設定 */
	glLoadIdentity();                     /* 変換行列の初期化 */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(
		0,//GLdouble left,
		300,//GLdouble right,
		0,//GLdouble bottom,
		300,//GLdouble top,
		1,//GLdouble zNear, 
		-1//GLdouble zFar
		);

	glColor3f(0, 0, 0);
	min_font->ChangeSize(lkn::TYPE_MIN);
	min_font->DrawStringW(10, 285, L"w:↑　s:↓　Enter:決定");
}



void opening() {
	if (opening_init == 0) {
		opening_init = 1;
		alSourcePlay(init_music->source);
	}
	glMatrixMode(GL_PROJECTION);          /* 投影変換行列の設定 */
	glLoadIdentity();                     /* 変換行列の初期化 */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(
		0,//GLdouble left,
		300,//GLdouble right,
		0,//GLdouble bottom,
		300,//GLdouble top,
		1,//GLdouble zNear, 
		-1//GLdouble zFar
		);


	init_image->changeImage();

	glColor4f(1, 1, 1, 1);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0.f, 0.f);
		glVertex2f(0, 300);
		glTexCoord2f(0.f, 1.f);
		glVertex2f(0, 0);
		glTexCoord2f(1.f, 1.f);
		glVertex2f(300, 0);
		glTexCoord2f(1.f, 0.f);
		glVertex2f(300, 300);
	}
	glEnd();

	if (o_message != NULL) {
		o_message();
	}
	else {
		glColor3f(0.7f, 0.5f, 0);
		max_font->ChangeSize(lkn::TYPE_MAX);
		max_font->DrawStringW(10, 160, L"はじめの出会い");
		font->ChangeSize(lkn::TYPE_NORMAL);
		glColor3f(1, 0, 0);
		font->DrawStringW(100, 110, L"～ファームを救え！～");
	}

	glDisable(GL_TEXTURE_2D);

    font->ChangeSize(lkn::TYPE_NORMAL);

	if (lkn::InputManager::getInstance()->keyPless(0x0d)) {

		if (o_message == NULL) {
			o_message = hajimemasite;
		}
		else if(o_message == hajimemasite) {
			o_message = kyuudakedo;
		}
		else if (o_message == kyuudakedo) {
			o_message = sokode;
		}
		else if (o_message == sokode) {
			o_message = tasukete;
		}
		else if (o_message == tasukete) {
			o_message = yorosikune;
		}
		else if (o_message == yorosikune) {
			o_message = NULL;
			alSourceStop(init_music->source);
			func = farm;
		}
	}

	glColor3f(0, 0, 0);
	min_font->ChangeSize(lkn::TYPE_MIN);
	min_font->DrawStringW(10, 285, L"　　　　　　Enter:決定");

}

void hajimemasite() {
	message_box->Draw(game::MESSAGE_TYPE_COLT, L"はじめまして！\n私はこのファームのブリーダー助手を\n務める、コルトと言います。");
}
void kyuudakedo() {
	message_box->Draw(game::MESSAGE_TYPE_COLT_KOMARIGAO, L"急なんだけど、このファームは今\n経営難に陥っているの。");
}
void sokode() {
	message_box->Draw(game::MESSAGE_TYPE_COLT_KOMARIGAO, L"そこで協会にお願いしてあなたを\n派遣してもらったんだけど\n");
}
void tasukete() {
	message_box->Draw(game::MESSAGE_TYPE_COLT_KOMARIGAO, L"今度6月4週に開かれる\n大会で勝たないといけないの...");
}

void yorosikune() {
	message_box->Draw(game::MESSAGE_TYPE_COLT, L"大会で勝つ為に\n一緒にモンスターを育てて\n頑張ろうね！");
}