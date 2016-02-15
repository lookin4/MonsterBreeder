#include"battle.h"
#include"../game/monster.h"
#include"../lkn_library/image.h"

int battle_distance;
int battle_frame;
bool battle_init = 0;

float p1_HP_MAX;
float p1_HP;

float p2_HP_MAX;
float p2_HP;

int p1_x_pos;
int p2_x_pos;

int p1_y_pos;
int p2_y_pos;

float p1_guts = 50;
float p2_guts = 50;

int p1_y_angle = 50;
int p2_y_angle = -50;

int p1_z_angle = 0;
int p2_z_angle = 0;

int p1_meityu = 0;
int p2_meityu = 0;

int time;

bool enemy_near_frag;
bool enemy_far_frag;
bool enemy_stay_frag;
int enemy_distanse;

extern game::MyMessageBox* message_box;

void sippo(game::Monster &_monster);
void tuba(game::Monster &_monster);
void taore(game::Monster &_monster);
void biimu(game::Monster &_monster);
void(*waza_movie)(game::Monster &_monster);

void(*enemy_waza_movie)(game::Monster &_monster);

bool dead_flag;

void ending();

void won();
void lose();
void(*e_message)();

extern game::Suezo* suezo;
extern game::Monorisu* monorisu;


extern game::Monster* monster;
extern game::Monster* enemy;

extern lkn::Image* wazanasi_image;
extern lkn::Image* tuba_waza_image;
extern lkn::Image* biimu_waza2_image;
extern lkn::Image* biimu_waza1_image;

extern lkn::Sound* ending_music;


int waza_init = 0;

int b_frame = 0;
int b_type = 0;
int b_angle;
int b_judge;

void battle() {
	if (battle_init == 0) {


		p1_HP_MAX = monster->HP;
		p1_HP = p1_HP_MAX;

		p2_HP_MAX = enemy->HP;
		p2_HP = p2_HP_MAX;

		dead_flag = false;
		battle_distance = 10;
		battle_init = 1;

		alSourcei(
			battle_music->source,     // ALuint source
			AL_LOOPING, // ALenum param
			AL_TRUE);   // ALint value
		alSourcePlay(battle_music->source);

		eye->y = 1000;
		eye->x = 0;
		eye->z = 2000;

		target->y = 0;
		target->x = 0;
		target->z = 0;

		p1_x_pos = -250;
		p2_x_pos = 250;

		p1_y_pos = 0;
		p2_y_pos = 0;

		p1_y_angle = 50;
		p2_y_angle = -50;

		enemy_near_frag = false;
		enemy_far_frag = false;
		enemy_stay_frag = false;
		enemy_distanse = 30;

		battle_frame = 0;

		waza_movie = NULL;
		enemy_waza_movie = NULL;
	}

	glMatrixMode(GL_PROJECTION);          /* ìäâeïœä∑çsóÒÇÃê›íË */
	glLoadIdentity();                     /* ïœä∑çsóÒÇÃèâä˙âª */
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



	glEnable(GL_BLEND);
	glBlendFunc(
		GL_SRC_ALPHA,
		GL_ONE_MINUS_SRC_ALPHA
		);


	battle_background_image->changeImage();

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

	glDisable(GL_TEXTURE_2D);

	glColor4f(0.3f, 0.3f, 0.3f, 0.5f);
	glBegin(GL_QUADS);
	//â∫ÉQÅ[ÉW
	{
		glVertex2f(24, 30);
		glVertex2f(24, 100);
		glVertex2f(125, 100);
		glVertex2f(125, 30);
	}

	{
		glVertex2f(175, 30);
		glVertex2f(175, 100);
		glVertex2f(276, 100);
		glVertex2f(276, 30);
	}
	//è„ÉQÅ[ÉW
	{
		glVertex2f(28, 220);
		glVertex2f(28, 250);
		glVertex2f(118, 250);
		glVertex2f(118, 220);
	}

	{
		glVertex2f(182, 220);
		glVertex2f(182, 250);
		glVertex2f(272, 250);
		glVertex2f(272, 220);
	}

	if (p1_HP < 0) {
		p1_HP = 0;
	}
	if (p2_HP < 0) {
		p2_HP = 0;
	}

	//HPÉQÅ[ÉW
	if ((p1_HP / p1_HP_MAX) > 0.5f) {
		glColor4f(0, 0.7f, 1, 1);
	}
	else if ((p1_HP / p1_HP_MAX) > 0.3f) {
		glColor4f(0, 1, 0.5f, 1);
	}
	else {
		glColor4f(1, 1, 0, 1);
	}
	{
		float p1_hp_gauge = 33.5f + (116.5f - 33.5f)*(1 - (p1_HP / p1_HP_MAX));
		glVertex2f(p1_hp_gauge, 260);
		glVertex2f(p1_hp_gauge, 275);
		glVertex2f(116.5f, 275);
		glVertex2f(116.5f, 260);
	}

	if ((p2_HP / p2_HP_MAX) > 0.5f) {
		glColor4f(0, 0.7f, 1, 1);
	}
	else if ((p2_HP / p2_HP_MAX) > 0.3f) {
		glColor4f(0, 1, 0.5f, 1);
	}
	else {
		glColor4f(1, 1, 0, 1);
	}
	{
		float p2_hp_gauge = 267.0f - (267.0f - 184.0f)*(1 - (p2_HP / p2_HP_MAX));
		glVertex2f(184, 260);
		glVertex2f(184, 275);
		glVertex2f(p2_hp_gauge, 275);
		glVertex2f(p2_hp_gauge, 260);
	}
	glEnd();





	battle_gauge_image->changeImage();

	glColor4f(1, 1, 1, 1);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0.f, 0.f);
		glVertex2f(20, 290);
		glTexCoord2f(0.f, 1.f);
		glVertex2f(20, 210);
		glTexCoord2f(1.f, 1.f);
		glVertex2f(280, 210);
		glTexCoord2f(1.f, 0.f);
		glVertex2f(280, 290);
	}
	glEnd();

	battle_selectbar_image->changeImage();

	glColor4f(1, 1, 1, 1);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0.f, 0.f);
		glVertex2f(10, 80);
		glTexCoord2f(0.f, 1.f);
		glVertex2f(10, 10);
		glTexCoord2f(1.f, 1.f);
		glVertex2f(290, 10);
		glTexCoord2f(1.f, 0.f);
		glVertex2f(290, 80);
	}
	glEnd();


	glMatrixMode(GL_PROJECTION);          /* ìäâeïœä∑çsóÒÇÃê›íË */
	glLoadIdentity();                     /* ïœä∑çsóÒÇÃèâä˙âª */
	gluPerspective(45.0f, 1, 0.1f, 10000); //ìßéãìäâeñ@ÇÃéãëÃêœgluPerspactive(th, w/h, near, far);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		// éãì_ÇÃà íux,y,z;
		eye->x, eye->y, eye->z,

		// éãäEÇÃíÜêSà íuÇÃéQè∆ì_ç¿ïWx,y,z
		target->x, target->y, target->z,

		//éãäEÇÃè„ï˚å¸ÇÃÉxÉNÉgÉãx,y,z
		0, 1, 0);

	//////////////////////////////////////////////////////////////////////////////////////////////////
	glEnable(GL_CULL_FACE);
	glPushMatrix();
	glDisable(GL_TEXTURE_2D);
	glTranslatef(p2_x_pos + (battle_distance / 0.6f), p2_y_pos, 0);
	glRotatef(-20, 1, 0, 0);
	glRotatef(p2_y_angle, 0, 1, 0);
	glRotatef(p2_z_angle, 0, 0, 1);
	glScalef(0.7f, 0.7f, 0.7f);
	glColor4f(0, 0, 0, 1);

	enemy->Draw();

	glPopMatrix();

	glPushMatrix();
	glDisable(GL_TEXTURE_2D);
	glTranslatef(p1_x_pos - (battle_distance / 0.6f), p1_y_pos, 0);
	glRotatef(-20, 1, 0, 0);
	glRotatef(p1_y_angle, 0, 1, 0);
	glRotatef(p1_z_angle, 0, 0, 1);
	glScalef(0.7f, 0.7f, 0.7f);
	glColor4f(1, 1, 0, 1);

	monster->Draw();

	glPopMatrix();
	glDisable(GL_CULL_FACE);
	/////////////////////////////////////////////////////////////////////////////////////////////////


	glDisable(GL_TEXTURE_2D);

	glDisable(GL_BLEND);
	glMatrixMode(GL_PROJECTION);          /* ìäâeïœä∑çsóÒÇÃê›íË */
	glLoadIdentity();                     /* ïœä∑çsóÒÇÃèâä˙âª */
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


	glColor3f(1, 1, 1);

	font->ChangeSize(lkn::TYPE_NORMAL);
	font->DrawStringW(119, 55, L" ");//Ç»Ç∫Ç©àÍî≠ñ⁄Ç∏ÇÍÇÈÇÃÇ≈ãÛï`âÊ

	font->DrawStringW(73, 269, L" %3.0f/%3.0f", p1_HP, p1_HP_MAX);
	font->DrawStringW(185, 269, L" %3.0f/%3.0f", p2_HP, p2_HP_MAX);
	if (dead_flag == false) {
		if (p1_guts < 99) {
			p1_guts += 0.004f*(10 - monster->re_guts);
		}
		if (p2_guts < 99) {
			p2_guts += 0.004f*(10 - enemy->re_guts);
		}

		font->DrawStringW(119, 30, L" %2.0f", p1_guts);
		font->DrawStringW(162, 30, L" %2.0f", p2_guts);

		time = 60 - (battle_frame / 60);
		if (time < 0) {
			time = 0;
		}
	}
	font->DrawStringW(141, 242, L" %2d", time);

	font->DrawStringW(138, 55, L" Hit");
	font->DrawStringW(136, 30, L" Guts");


	int p1_size = wcslen(monster->name);
	int p2_size = wcslen(enemy->name);

	glPushMatrix();
	{
		int p1_translate = (8 - (p1_size - 1)) * 5;
		glTranslatef(p1_translate, 0, 0);
		font->DrawStringW(23, 229, L" %s", monster->name);
	}
	glPopMatrix();

	glPushMatrix();
	{
		int p2_translate = (8 - (p2_size - 1)) * 5;
		glTranslatef(p2_translate, 0, 0);
		font->DrawStringW(179, 229, L" %s", enemy->name);
	}
	glPopMatrix();


	if (dead_flag == false) {
		font->ChangeSize(lkn::TYPE_NORMAL);
		glPushMatrix();
		{
			for (int i = 0; i < monster->waza.size(); i++) {
				if ((battle_distance / 67) == monster->waza[i]->distance) {
					int p1_skill_size = wcslen(monster->waza[i]->name);
					int p1_translate = (8 - (p1_skill_size - 1)) * 5;
					glPushMatrix();
					glTranslatef(p1_translate, 0, 0);
					font->DrawStringW(22, 79, L" %s", monster->waza[i]->name);
					glPopMatrix();
					if (waza_movie == NULL) {
						p1_meityu = ((monster->hit_probability_point / 50) / ((enemy->dodge_point / 50) * 2 + 1)) + (monster->waza[i]->hit_probability * (p1_guts / p2_guts));
					}
					if (p1_meityu > 100) {
						p1_meityu = 99;
					}
					else if (p1_meityu < 1) {
						p1_meityu = 1;
					}
					font->DrawStringW(119, 55, L" %2d", p1_meityu);
					min_font->ChangeSize(lkn::TYPE_MIN);
					min_font->DrawStringW(114, 79, L" %2d", monster->waza[i]->guts);
				}
			}
		}
		glPopMatrix();

		font->ChangeSize(lkn::TYPE_NORMAL);
		glPushMatrix();
		{
			for (int i = 0; i < enemy->waza.size(); i++) {
				if ((battle_distance / 67) == enemy->waza[i]->distance) {
					int p2_skill_size = wcslen(enemy->waza[i]->name);
					int p2_translate = (8 - (p2_skill_size - 1)) * 5;
					glPushMatrix();
					glTranslatef(p2_translate, 0, 0);
					font->DrawStringW(180, 79, L" %s", enemy->waza[i]->name);
					glPopMatrix();
					if (enemy_waza_movie == NULL) {
						p2_meityu = ((enemy->hit_probability_point / 50) / ((monster->dodge_point / 50) * 2 + 1)) + (enemy->waza[i]->hit_probability * (p2_guts / p1_guts));
					}
					if (p2_meityu > 100) {
						p2_meityu = 99;
					}
					else if (p1_meityu < 1) {
						p2_meityu = 1;
					}
					font->DrawStringW(156, 55, L" %2d", p2_meityu);
					min_font->ChangeSize(lkn::TYPE_MIN);
					min_font->DrawStringW(172, 79, L" %2d", enemy->waza[i]->guts);
				}
			}
		}
		glPopMatrix();
	}
	min_font->ChangeSize(lkn::TYPE_MIN);
	min_font->DrawStringW(130, 55, L" Åì");
	min_font->DrawStringW(167, 55, L" Åì");
	//ãZBox
	//glEnable(GL_TEXTURE_2D);
	glColor4f(1, 1, 1, 1);

	if (waza_movie == NULL && enemy_waza_movie == NULL) {
		for (int i = 0; i < monster->waza.size(); i++) {
			if (monster->waza[i]->distance == game::D_FAR) {
				monster->waza[i]->image->changeImage();
				break;
			}
			else {
				wazanasi_image->changeImage();
			}
		}
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.f, 0.f);
			glVertex2f(28.7f, 64);
			glTexCoord2f(0.f, 1.f);
			glVertex2f(28.7f, 35);
			glTexCoord2f(1.f, 1.f);
			glVertex2f(50, 35);
			glTexCoord2f(1.f, 0.f);
			glVertex2f(50, 64);
		}
		glEnd();
		for (int i = 0; i < monster->waza.size(); i++) {
			if (monster->waza[i]->distance == game::D_MIDDLE_FAR) {
				monster->waza[i]->image->changeImage();
				break;
			}
			else {
				wazanasi_image->changeImage();
			}
		}
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.f, 0.f);
			glVertex2f(50.6f, 64);
			glTexCoord2f(0.f, 1.f);
			glVertex2f(50.6f, 35);
			glTexCoord2f(1.f, 1.f);
			glVertex2f(72, 35);
			glTexCoord2f(1.f, 0.f);
			glVertex2f(72, 64);
		}
		glEnd();
		for (int i = 0; i < monster->waza.size(); i++) {
			if (monster->waza[i]->distance == game::D_MIDDLE_NEAR) {
				monster->waza[i]->image->changeImage();
				break;
			}
			else {
				wazanasi_image->changeImage();
			}
		}
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.f, 0.f);
			glVertex2f(72.7f, 64);
			glTexCoord2f(0.f, 1.f);
			glVertex2f(72.7f, 35);
			glTexCoord2f(1.f, 1.f);
			glVertex2f(94, 35);
			glTexCoord2f(1.f, 0.f);
			glVertex2f(94, 64);
		}
		glEnd();
		for (int i = 0; i < monster->waza.size(); i++) {
			if (monster->waza[i]->distance == game::D_NEAR) {
				monster->waza[i]->image->changeImage();
				break;
			}
			else {
				wazanasi_image->changeImage();
			}
		}
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.f, 0.f);
			glVertex2f(94.6f, 64);
			glTexCoord2f(0.f, 1.f);
			glVertex2f(94.6f, 35);
			glTexCoord2f(1.f, 1.f);
			glVertex2f(116, 35);
			glTexCoord2f(1.f, 0.f);
			glVertex2f(116, 64);
		}
		glEnd();

		for (int i = 0; i < enemy->waza.size(); i++) {
			if (enemy->waza[i]->distance == game::D_NEAR) {
				enemy->waza[i]->image->changeImage();
				break;
			}
			else {
				wazanasi_image->changeImage();
			}
		}
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.f, 0.f);
			glVertex2f(184, 64);
			glTexCoord2f(0.f, 1.f);
			glVertex2f(184, 35);
			glTexCoord2f(1.f, 1.f);
			glVertex2f(205.4f, 35);
			glTexCoord2f(1.f, 0.f);
			glVertex2f(205.4f, 64);
		}
		glEnd();
		for (int i = 0; i < enemy->waza.size(); i++) {
			if (enemy->waza[i]->distance == game::D_MIDDLE_NEAR) {
				enemy->waza[i]->image->changeImage();
				break;
			}
			else {
				wazanasi_image->changeImage();
			}
		}
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.f, 0.f);
			glVertex2f(206, 64);
			glTexCoord2f(0.f, 1.f);
			glVertex2f(206, 35);
			glTexCoord2f(1.f, 1.f);
			glVertex2f(227.3f, 35);
			glTexCoord2f(1.f, 0.f);
			glVertex2f(227.3f, 64);
		}
		glEnd();
		for (int i = 0; i < enemy->waza.size(); i++) {
			if (enemy->waza[i]->distance == game::D_MIDDLE_FAR) {
				enemy->waza[i]->image->changeImage();
				break;
			}
			else {
				wazanasi_image->changeImage();
			}
		}
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.f, 0.f);
			glVertex2f(228, 64);
			glTexCoord2f(0.f, 1.f);
			glVertex2f(228, 35);
			glTexCoord2f(1.f, 1.f);
			glVertex2f(249.4f, 35);
			glTexCoord2f(1.f, 0.f);
			glVertex2f(249.4f, 64);
		}
		glEnd();
		for (int i = 0; i < enemy->waza.size(); i++) {
			if (enemy->waza[i]->distance == game::D_FAR) {
				enemy->waza[i]->image->changeImage();
				break;
			}
			else {
				wazanasi_image->changeImage();
			}
		}
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.f, 0.f);
			glVertex2f(250, 64);
			glTexCoord2f(0.f, 1.f);
			glVertex2f(250, 35);
			glTexCoord2f(1.f, 1.f);
			glVertex2f(271.3f, 35);
			glTexCoord2f(1.f, 0.f);
			glVertex2f(271.3f, 64);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);



	//ãóó£
	glColor4f(0, 1, 1, 1);
	glPushMatrix();
	{
		glTranslatef(-(battle_distance / 3.f), 0, 0);
		glBegin(GL_QUADS);
		{
			glVertex2f(113, 65);
			glVertex2f(113, 72);
			glVertex2f(119, 72);
			glVertex2f(119, 65);
		}
		glEnd();
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef((battle_distance / 3.f), 0, 0);
		glBegin(GL_QUADS);
		{
			glVertex2f(181, 65);
			glVertex2f(181, 72);
			glVertex2f(187, 72);
			glVertex2f(187, 65);
		}
		glEnd();
	}
	glPopMatrix();

	//ãZÇÃòg
	//ÇPP
	glLineWidth(4);
	glBegin(GL_LINES);
	if (battle_distance < 67) {
		glColor3f(1, 0, 0);
		{
			glVertex2f(27, 71); glVertex2f(94, 71);
			glVertex2f(94.2f, 72); glVertex2f(94.2f, 33);
			glVertex2f(116, 70.5f); glVertex2f(116, 33);
			glVertex2f(94.2f, 33.5f); glVertex2f(116, 33.5f);
		}
	}
	else if (battle_distance < 134) {
		glColor3f(1, 1, 0);
		{
			glVertex2f(27, 71); glVertex2f(72.2f, 71);
			glVertex2f(94.2f, 71); glVertex2f(116, 71);
			glVertex2f(72.2f, 72); glVertex2f(72.2f, 33);
			glVertex2f(94.2f, 72); glVertex2f(94.2f, 33);
			glVertex2f(94.2f, 33.5f); glVertex2f(72.2f, 33.5f);
		}
	}
	else if (battle_distance < 201) {
		glColor3f(0.5f, 1, 0);
		{
			glVertex2f(27, 71); glVertex2f(50.2f, 71);
			glVertex2f(72.2f, 71); glVertex2f(116, 71);
			glVertex2f(50.2f, 72); glVertex2f(50.2f, 33);
			glVertex2f(72.2f, 72); glVertex2f(72.2f, 33);
			glVertex2f(72.2f, 33.5f); glVertex2f(50.2f, 33.5f);
		}
	}
	else if (battle_distance < 268) {
		glColor3f(0, 0.5f, 1);
		{
			glVertex2f(27, 71); glVertex2f(28.2f, 71);
			glVertex2f(50.2f, 71); glVertex2f(116, 71);
			glVertex2f(28.2f, 72); glVertex2f(28.2f, 33);
			glVertex2f(50.2f, 72); glVertex2f(50.2f, 33);
			glVertex2f(50.2f, 33.5f); glVertex2f(28.2f, 33.5f);
		}
	}
	if (battle_distance < 268) {
		{
			glVertex2f(27, 99); glVertex2f(116, 99);
			glVertex2f(116, 70.5f); glVertex2f(116, 100);
			glVertex2f(27, 100); glVertex2f(27, 70.5f);
		}
	}

	//2P
	if (battle_distance < 67) {
		glColor3f(1, 0, 0);
		{
			glVertex2f(273, 71); glVertex2f(206, 71);
			glVertex2f(205.8f, 72); glVertex2f(205.8f, 33);
			glVertex2f(184, 70.5f); glVertex2f(184, 33);
			glVertex2f(205.8f, 33.5f); glVertex2f(184, 33.5f);
		}
	}
	else if (battle_distance < 134) {
		glColor3f(1, 1, 0);
		{
			glVertex2f(273, 71); glVertex2f(227.8f, 71);
			glVertex2f(205.8f, 71); glVertex2f(184, 71);
			glVertex2f(227.8f, 72); glVertex2f(227.8f, 33);
			glVertex2f(205.8f, 72); glVertex2f(205.8f, 33);
			glVertex2f(205.8f, 33.5f); glVertex2f(227.8f, 33.5f);
		}
	}
	else if (battle_distance < 201) {
		glColor3f(0.5f, 1, 0);
		{
			glVertex2f(273, 71); glVertex2f(249.8f, 71);
			glVertex2f(227.8f, 71); glVertex2f(184, 71);
			glVertex2f(249.8f, 72); glVertex2f(249.8f, 33);
			glVertex2f(227.8f, 72); glVertex2f(227.8f, 33);
			glVertex2f(227.8f, 33.5f); glVertex2f(249.8f, 33.5f);
		}
	}
	else if (battle_distance < 268) {
		glColor3f(0, 0.5f, 1);
		{
			glVertex2f(273, 71); glVertex2f(271.8f, 71);
			glVertex2f(249.8f, 71); glVertex2f(184, 71);
			glVertex2f(271.8f, 72); glVertex2f(271.8f, 33);
			glVertex2f(249.8f, 72); glVertex2f(249.8f, 33);
			glVertex2f(249.8f, 33.5f); glVertex2f(271.8f, 33.5f);
		}
	}
	if (battle_distance < 268) {
		{
			glVertex2f(273, 99); glVertex2f(184, 99);
			glVertex2f(184, 70.5f); glVertex2f(184, 100);
			glVertex2f(273, 100); glVertex2f(273, 70.5f);
		}
	}
	glEnd();
	glLineWidth(0);
	if (waza_movie != NULL && enemy_waza_movie == NULL) {
		waza_movie(*monster);
		battle_frame++;
	}
	else if (enemy_waza_movie != NULL) {
		enemy_waza_movie(*enemy);
		battle_frame++;
	}
	else if (0 < time && 0 < p1_HP && 0 < p2_HP) {
		if (enemy_distanse < 0) {
			if (rand() % 100 < 30) {
				enemy_far_frag = 1;
				enemy_near_frag = 0;
				enemy_stay_frag = 0;
				enemy_distanse = 30;
			}
			else if (rand() % 100 < 60) {
				enemy_far_frag = 0;
				enemy_near_frag = 1;
				enemy_stay_frag = 0;
				enemy_distanse = 30;
			}
			else {
				enemy_far_frag = 0;
				enemy_near_frag = 0;
				enemy_stay_frag = 1;
				enemy_distanse = 30;
			}
		}
		if (enemy_far_frag == true) {
			if (battle_distance <= 268)
				battle_distance += 0.8f;
		}
		else if (enemy_near_frag == true) {
			if (0 <= battle_distance)
				battle_distance -= 0.8f;
		}
		if (rand() % 1000 < 5) {
			for (int i = 0; i < enemy->waza.size(); i++) {
				if ((battle_distance / 67) == enemy->waza[i]->distance) {
					if (enemy->waza[i]->guts <= p2_guts) {
						if (enemy->waza[i]->w_type == game::SIPPO) {
							enemy_waza_movie = sippo;
						}
						else if (enemy->waza[i]->w_type == game::TUBA) {
							enemy_waza_movie = tuba;
						}
						else if (enemy->waza[i]->w_type == game::BIIMU) {
							enemy_waza_movie = biimu;
						}
						else if (enemy->waza[i]->w_type == game::TAORE) {
							enemy_waza_movie = taore;
						}
					}
				}
			}
		}

		if (lkn::InputManager::getInstance()->keyPlessAndHold('a')) {
			if (!(lkn::InputManager::getInstance()->keyRelease('a'))) {
				if (battle_distance <= 268)
					battle_distance++;
			}
		}
		if (lkn::InputManager::getInstance()->keyPlessAndHold('d')) {
			if (!(lkn::InputManager::getInstance()->keyRelease('d'))) {
				if (0 <= battle_distance)
					battle_distance--;
			}
		}
		if (lkn::InputManager::getInstance()->keyPlessAndHold(';')) {
			if (!(lkn::InputManager::getInstance()->keyRelease(';'))) {
				if (battle_distance <= 268)
					battle_distance++;
			}
		}
		if (lkn::InputManager::getInstance()->keyPlessAndHold('k')) {
			if (!(lkn::InputManager::getInstance()->keyRelease('k'))) {
				if (0 <= battle_distance)
					battle_distance--;
			}
		}

		if (lkn::InputManager::getInstance()->keyPless(0x0d)) {
			for (int i = 0; i < monster->waza.size(); i++) {
				if ((battle_distance / 67) == monster->waza[i]->distance) {
					if (monster->waza[i]->guts <= p1_guts) {
						if (monster->waza[i]->w_type == game::SIPPO) {
							waza_movie = sippo;
						}
						else if (monster->waza[i]->w_type == game::TUBA) {
							waza_movie = tuba;
						}
						else if (monster->waza[i]->w_type == game::BIIMU) {
							waza_movie = biimu;
						}
						else if (monster->waza[i]->w_type == game::TAORE) {
							waza_movie = taore;
						}
					}
				}
			}
		}
		battle_frame++;
	}
	else {
		if (dead_flag == false) {
			if (p2_HP == 0 || (p1_HP / p1_HP_MAX) > (p2_HP / p2_HP_MAX)) {
				alSourcePlay(battle_win_music->source);
			}
			else {
				alSourcePlay(battle_lose_music->source);
			}

			dead_flag = true;
		}
		max_font->ChangeSize(lkn::TYPE_MAX);
		glColor3f(1, 0, 0);
		if (p1_HP == 0 || (p1_HP / p1_HP_MAX) < (p2_HP / p2_HP_MAX)) {
			max_font->DrawStringW(65, 125, L" ÇkÇnÇrÇd...");
		}
		else if (p2_HP == 0 || (p2_HP / p2_HP_MAX) < (p1_HP / p1_HP_MAX)) {
			max_font->DrawStringW(65, 125, L" ÇvÇhÇmÅIÅI");
		}
		else {
			max_font->DrawStringW(65, 125, L" ÇcÇqÇ`Çv...");
		}
		alSourceStop(battle_music->source);
		if (lkn::InputManager::getInstance()->keyPless(0x0d)) {
			alSourceStop(battle_lose_music->source);
			alSourceStop(battle_win_music->source);
			battle_init = false;
			func = ending;
		}
	}

	enemy_distanse--;

	glColor3f(0, 0, 0);
	min_font->ChangeSize(lkn::TYPE_MIN);
	min_font->DrawStringW(20, 285, L" a:Å©Å@d:Å®Å@Enter:åàíË");

}

void sippo(game::Monster &_monster) {
	if (waza_init == false) {
		waza_init = true;
		b_frame = 0;
		int percentage;
		if (_monster.type == game::PLAYER) {
			b_type = 1;
			p1_guts -= _monster.waza[1]->guts;
			percentage = p1_meityu;
		}
		else if (_monster.type == game::ENEMY) {
			b_type = -1;
			p2_guts -= _monster.waza[1]->guts;
			percentage = p2_meityu;
		}
		b_angle = 0;
		if (rand() % 100 < percentage) {
			b_judge = true;
		}
		else {
			b_judge = false;
		}
	}

	if (b_type == 1) {
		p1_guts -= 0.004f*(10 - _monster.re_guts);
	}
	else if (b_type == -1) {
		p2_guts -= 0.004f*(10 - _monster.re_guts);
	}
	if (b_frame < 40) {
		if (b_type == 1) {
			p1_x_pos += 4;
		}
		else if (b_type == -1) {
			p2_x_pos -= 4;
		}
	}
	else if (b_frame < 76) {
		if (b_type == 1) {
			p1_y_angle -= 10;
		}
		else if (b_type == -1) {
			p2_y_angle += 10;
		}
	}
	else if (b_frame < 116) {
		if (b_type == 1) {
			p1_x_pos -= 4;
		}
		else if (b_type == -1) {
			p2_x_pos += 4;
		}
	}
	else if (b_frame < (116 + _monster.waza[1]->damage)) {
		font->ChangeSize(lkn::TYPE_NORMAL);
		if (b_judge == true) {
			if (b_type == 1) {
				glColor3f(1, 0, 0);
				font->DrawStringW(200, 200, L" DAMAGE!!");
				max_font->ChangeSize(lkn::TYPE_MAX);
				max_font->DrawStringW(180, 120, L" %d", _monster.waza[1]->damage);
				p2_HP -= 1;
			}
			else if (b_type == -1) {
				glColor3f(1, 0, 0);
				font->DrawStringW(50, 200, L" DAMAGE!!");
				max_font->ChangeSize(lkn::TYPE_MAX);
				max_font->DrawStringW(30, 120, L" %d", _monster.waza[1]->damage);
				p1_HP -= 1;
			}
		}
		else if (b_judge == false) {
			if (b_type == 1) {
				glColor3f(0.3f, 0, 1);
				max_font->ChangeSize(lkn::TYPE_MAX);
				max_font->DrawStringW(160, 120, L" MISS!!");
			}
			else if (b_type == -1) {
				glColor3f(0.3f, 0, 1);
				max_font->ChangeSize(lkn::TYPE_MAX);
				max_font->DrawStringW(10, 120, L" MISS!!");
			}
		}
	}
	else {
		waza_init = false;
		if (b_type == 1) {
			waza_movie = NULL;
		}
		else if (b_type == -1) {
			enemy_waza_movie = NULL;
		}
	}
	b_frame++;
}
void tuba(game::Monster &_monster) {
	if (waza_init == false) {
		waza_init = true;
		b_frame = 0;
		int percentage;
		if (_monster.type == game::PLAYER) {
			b_type = 1;
			p1_guts -= _monster.waza[0]->guts;
			percentage = p1_meityu;
		}
		else if (_monster.type == game::ENEMY) {
			b_type = -1;
			p2_guts -= _monster.waza[0]->guts;
			percentage = p2_meityu;
		}
		b_angle = 0;
		if (rand() % 100 < percentage) {
			b_judge = true;
		}
		else {
			b_judge = false;
		}
	}

	if (b_type == 1) {
		p1_guts -= 0.004f*(10 - _monster.re_guts);
	}
	else if (b_type == -1) {
		p2_guts -= 0.004f*(10 - _monster.re_guts);
	}
	if (b_frame < 50) {
		glEnable(GL_BLEND);
		glBlendFunc(
			GL_SRC_ALPHA,
			GL_ONE_MINUS_SRC_ALPHA
			);
		tuba_waza_image->changeImage();
		glPushMatrix();
		if (b_type == 1) {
			glTranslatef(b_frame * 2, 0, 0);
			glColor3f(1, 1, 1);
			glBegin(GL_QUADS);
			{
				glTexCoord2f(0.f, 0.f);
				glVertex2f(100, 155);
				glTexCoord2f(0.f, 1.f);
				glVertex2f(100, 135);
				glTexCoord2f(1.f, 1.f);
				glVertex2f(120, 135);
				glTexCoord2f(1.f, 0.f);
				glVertex2f(120, 155);
			}
			glEnd();
		}
		else if (b_type == -1) {
			glTranslatef(-(b_frame * 2), 0, 0);
			glColor3f(1, 1, 1);
			glBegin(GL_QUADS);
			{
				glTexCoord2f(0.f, 0.f);
				glVertex2f(200, 155);
				glTexCoord2f(0.f, 1.f);
				glVertex2f(200, 135);
				glTexCoord2f(1.f, 1.f);
				glVertex2f(180, 135);
				glTexCoord2f(1.f, 0.f);
				glVertex2f(180, 155);
			}
			glEnd();
		}
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	}

	else if (b_frame < (50 + _monster.waza[0]->damage)) {
		font->ChangeSize(lkn::TYPE_NORMAL);
		if (b_judge == true) {
			if (b_type == 1) {
				glColor3f(1, 0, 0);
				font->DrawStringW(200, 200, L" DAMAGE!!");
				max_font->ChangeSize(lkn::TYPE_MAX);
				max_font->DrawStringW(180, 120, L" %d", _monster.waza[0]->damage);
				p2_HP -= 1;
			}
			else if (b_type == -1) {
				glColor3f(1, 0, 0);
				font->DrawStringW(50, 200, L" DAMAGE!!");
				max_font->ChangeSize(lkn::TYPE_MAX);
				max_font->DrawStringW(30, 120, L" %d", _monster.waza[0]->damage);
				p1_HP -= 1;
			}
		}
		else if (b_judge == false) {
			if (b_type == 1) {
				glColor3f(0.3f, 0, 1);
				max_font->ChangeSize(lkn::TYPE_MAX);
				max_font->DrawStringW(160, 120, L" MISS!!");
			}
			else if (b_type == -1) {
				glColor3f(0.3f, 0, 1);
				max_font->ChangeSize(lkn::TYPE_MAX);
				max_font->DrawStringW(10, 120, L" MISS!!");
			}
		}
	}
	else {
		waza_init = false;
		if (b_type == 1) {
			waza_movie = NULL;
		}
		else if (b_type == -1) {
			enemy_waza_movie = NULL;
		}
	}
	b_frame++;
}
void taore(game::Monster &_monster) {
	if (waza_init == false) {
		waza_init = true;
		b_frame = 0;
		int percentage;
		if (_monster.type == game::PLAYER) {
			b_type = 1;
			p1_guts -= _monster.waza[1]->guts;
			percentage = p1_meityu;
		}
		else if (_monster.type == game::ENEMY) {
			b_type = -1;
			p2_guts -= _monster.waza[1]->guts;
			percentage = p2_meityu;
		}
		b_angle = 0;
		if (rand() % 100 < percentage) {
			b_judge = true;
		}
		else {
			b_judge = false;
		}
	}

	if (b_type == 1) {
		p1_guts -= 0.004f*(10 - _monster.re_guts);
	}
	else if (b_type == -1) {
		p2_guts -= 0.004f*(10 - _monster.re_guts);
	}
	if (b_frame < 40) {
		if (b_type == 1) {
			p1_x_pos += 5;
		}
		else if (b_type == -1) {
			p2_x_pos -= 5;
		}
	}
	else if (b_frame < 58) {
		if (b_type == 1) {
			p1_z_angle -= 5;
			p1_y_pos += 10;
		}
		else if (b_type == -1) {
			p2_z_angle += 5;
			p2_y_pos += 10;
		}
	}
	else if (b_frame < 76) {
		if (b_type == 1) {
			p1_y_pos -= 15;
		}
		else if (b_type == -1) {
			p2_y_pos -= 15;
		}
	}
	else if (b_frame < 94) {
		if (b_type == 1) {
			p1_y_pos += 5;
			p1_z_angle += 5;
		}
		else if (b_type == -1) {
			p2_y_pos += 5;
			p2_z_angle -= 5;
		}
	}
	else if (b_frame < 134) {
		if (b_type == 1) {
			p1_x_pos -= 5;
		}
		else if (b_type == -1) {
			p2_x_pos += 5;
		}
	}
	else if (b_frame < (134 + _monster.waza[1]->damage)) {
		font->ChangeSize(lkn::TYPE_NORMAL);
		if (b_judge == true) {
			if (b_type == 1) {
				glColor3f(1, 0, 0);
				font->DrawStringW(200, 200, L" DAMAGE!!");
				max_font->ChangeSize(lkn::TYPE_MAX);
				max_font->DrawStringW(180, 120, L" %d", _monster.waza[1]->damage);
				p2_HP -= 1;
			}
			else if (b_type == -1) {
				glColor3f(1, 0, 0);
				font->DrawStringW(50, 200, L" DAMAGE!!");
				max_font->ChangeSize(lkn::TYPE_MAX);
				max_font->DrawStringW(30, 120, L" %d", _monster.waza[1]->damage);
				p1_HP -= 1;
			}
		}
		else if (b_judge == false) {
			if (b_type == 1) {
				glColor3f(0.3f, 0, 1);
				max_font->ChangeSize(lkn::TYPE_MAX);
				max_font->DrawStringW(160, 120, L" MISS!!");
			}
			else if (b_type == -1) {
				glColor3f(0.3f, 0, 1);
				max_font->ChangeSize(lkn::TYPE_MAX);
				max_font->DrawStringW(10, 120, L" MISS!!");
			}
		}
	}
	else {
		waza_init = false;
		if (b_type == 1) {
			waza_movie = NULL;
		}
		else if (b_type == -1) {
			enemy_waza_movie = NULL;
		}
	}
	b_frame++;
}
void biimu(game::Monster &_monster) {
	if (waza_init == false) {
		waza_init = true;
		b_frame = 0;
		int percentage;
		if (_monster.type == game::PLAYER) {
			b_type = 1;
			p1_guts -= _monster.waza[0]->guts;
			percentage = p1_meityu;
		}
		else if (_monster.type == game::ENEMY) {
			b_type = -1;
			p2_guts -= _monster.waza[0]->guts;
			percentage = p2_meityu;
		}
		b_angle = 0;
		if (rand() % 100 < percentage) {
			b_judge = true;
		}
		else {
			b_judge = false;
		}
	}

	if (b_type == 1) {
		p1_guts -= 0.004f*(10 - _monster.re_guts);
	}
	else if (b_type == -1) {
		p2_guts -= 0.004f*(10 - _monster.re_guts);
	}
	if (b_frame < 70) {
		glEnable(GL_BLEND);
		glBlendFunc(
			GL_SRC_ALPHA,
			GL_ONE_MINUS_SRC_ALPHA
			);
		biimu_waza2_image->changeImage();
		glPushMatrix();
		if (b_type == 1) {
			glColor3f(1, 1, 1);
			glBegin(GL_QUADS);
			{
				glTexCoord2f(0.f, 0.f);
				glVertex2f(70, 225);
				glTexCoord2f(0.f, 1.f);
				glVertex2f(70, 85);
				glTexCoord2f(1.f, 1.f);
				glVertex2f(80 + b_frame * 4, 85);
				glTexCoord2f(1.f, 0.f);
				glVertex2f(80 + b_frame * 4, 225);
			}
			glEnd();
			biimu_waza1_image->changeImage();
			glColor3f(1, 1, 1);
			glBegin(GL_QUADS);
			{
				glTexCoord2f(0.f, 0.f);
				glVertex2f(50, 225);
				glTexCoord2f(0.f, 1.f);
				glVertex2f(50, 85);
				glTexCoord2f(1.f, 1.f);
				glVertex2f(80, 85);
				glTexCoord2f(1.f, 0.f);
				glVertex2f(80, 225);
			}
			glEnd();
		}
		else if (b_type == -1) {
			glColor3f(1, 1, 1);
			glBegin(GL_QUADS);
			{
				glTexCoord2f(0.f, 0.f);
				glVertex2f(230, 225);
				glTexCoord2f(0.f, 1.f);
				glVertex2f(230, 85);
				glTexCoord2f(1.f, 1.f);
				glVertex2f(220 - b_frame * 4, 85);
				glTexCoord2f(1.f, 0.f);
				glVertex2f(220 - b_frame * 4, 225);
			}
			glEnd();
			biimu_waza1_image->changeImage();
			glColor3f(1, 1, 1);
			glBegin(GL_QUADS);
			{
				glTexCoord2f(0.f, 0.f);
				glVertex2f(250, 225);
				glTexCoord2f(0.f, 1.f);
				glVertex2f(250, 85);
				glTexCoord2f(1.f, 1.f);
				glVertex2f(220, 85);
				glTexCoord2f(1.f, 0.f);
				glVertex2f(220, 225);
			}
			glEnd();
		}
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	}

	else if (b_frame < (70 + _monster.waza[0]->damage)) {
		font->ChangeSize(lkn::TYPE_NORMAL);
		if (b_judge == true) {
			if (b_type == 1) {
				glColor3f(1, 0, 0);
				font->DrawStringW(200, 200, L" DAMAGE!!");
				max_font->ChangeSize(lkn::TYPE_MAX);
				max_font->DrawStringW(180, 120, L" %d", _monster.waza[0]->damage);
				p2_HP -= 1;
			}
			else if (b_type == -1) {
				glColor3f(1, 0, 0);
				font->DrawStringW(50, 200, L" DAMAGE!!");
				max_font->ChangeSize(lkn::TYPE_MAX);
				max_font->DrawStringW(30, 120, L" %d", _monster.waza[0]->damage);
				p1_HP -= 1;
			}
		}
		else if (b_judge == false) {
			if (b_type == 1) {
				glColor3f(0.3f, 0, 1);
				max_font->ChangeSize(lkn::TYPE_MAX);
				max_font->DrawStringW(160, 120, L" MISS!!");
			}
			else if (b_type == -1) {
				glColor3f(0.3f, 0, 1);
				max_font->ChangeSize(lkn::TYPE_MAX);
				max_font->DrawStringW(10, 120, L" MISS!!");
			}
		}
	}
	else {
		waza_init = false;
		if (b_type == 1) {
			waza_movie = NULL;
		}
		else if (b_type == -1) {
			enemy_waza_movie = NULL;
		}
	}
	b_frame++;
}

bool ending_init = false;

void ending() {
	if (ending_init == false) {
		ending_init = true;
		if (p2_HP == 0 || (p2_HP / p2_HP_MAX) < (p1_HP / p1_HP_MAX)) {
			e_message = won;
		}
		else {
			e_message = lose;
		}
		alSourcePlay(ending_music->source);
	}
	glMatrixMode(GL_PROJECTION);          /* ìäâeïœä∑çsóÒÇÃê›íË */
	glLoadIdentity();                     /* ïœä∑çsóÒÇÃèâä˙âª */
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

	glColor4f(0, 0, 0, 1);
	glBegin(GL_QUADS);
	{
		glVertex2f(0, 0);
		glVertex2f(300, 0);
		glVertex2f(300, 300);
		glVertex2f(0, 300);
	}
	glEnd();

	if (e_message != NULL) {
		e_message();
	}
	else if (p2_HP == 0 || (p2_HP / p2_HP_MAX) < (p1_HP / p1_HP_MAX)) {
		max_font->ChangeSize(lkn::TYPE_MAX);
		glColor3f(1, 0.5f, 0);
		max_font->DrawStringW(40, 130, L"HAPPY ENDÅIÅI");
	}
	else {
		max_font->ChangeSize(lkn::TYPE_MAX);
		glColor3f(0.5f, 0.2f, 0.2f);
		max_font->DrawStringW(60, 130, L"BAD END...");
	}
	if (lkn::InputManager::getInstance()->keyPless(0x0d)) {
		if (e_message == NULL) {
			ending_init = false;
			alSourceStop(ending_music->source);
			func = title;
		}
		e_message = NULL;
	}
	glColor3f(1, 1, 1);
	min_font->ChangeSize(lkn::TYPE_MIN);
	min_font->DrawStringW(20, 285, L"Å@Å@Å@Å@Å@Å@Enter:åàíË");

}

void won() {
	font->ChangeSize(lkn::TYPE_NORMAL);
	message_box->Draw(game::MESSAGE_TYPE_COLT, L"Ç‚Ç¡ÇΩÇÀÅI\nÇ±ÇÍÇ≈ÉtÉ@Å[ÉÄÇÕà¿ë◊ÇæÇÊÅI\nÇ±ÇÍÇ©ÇÁÇ‡ÇÊÇÎÇµÇ≠ÇÀÅI");
}

void lose() {
	font->ChangeSize(lkn::TYPE_NORMAL);
	message_box->Draw(game::MESSAGE_TYPE_COLT_KOMARIGAO, L"ïâÇØÇøÇ·Ç¡ÇΩÇÀ...\nÇ†ÇüÇ±ÇÍÇ©ÇÁÇ«Ç§ÇµÇÊÇ§...");
}