#include"battle.h"
#include"../game/monster.h"

int battle_distance;
int battle_frame;
bool battle_init = 0;

float p1_HP_MAX;
float p1_HP;

float p2_HP_MAX;
float p2_HP;

bool dead_flag;

bool bakkunakkuru;
float bakkunakkuru_count = 30;

extern game::Suezo* suezo;
extern game::Monorisu* monorisu;


extern game::Monster* monster;


void battle() {
	if (battle_init == 0) {

		p1_HP_MAX = 817;
		p1_HP = p1_HP_MAX;

		p2_HP_MAX = 652;
		p2_HP = p2_HP_MAX;

		bakkunakkuru = false;

		dead_flag = false;
		battle_distance = 200;
		battle_init = 1;
		alSourcePlay(battle_music->source);
		eye->y = 1000;
		eye->x = 0;
		eye->z = 2000;

		target->y = 0;
		target->x = 0;
		target->z = 0;

		battle_frame = 0;
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

	glPushMatrix();
	glDisable(GL_TEXTURE_2D);
	glTranslatef(250 + (battle_distance / 0.6f), 0, 0);
	glRotatef(-20, 1, 0, 0);
	glRotatef(-50, 0, 1, 0);
	glScalef(0.7f, 0.7f, 0.7f);
	glColor4f(1, 1, 0, 1);

	suezo->Draw();

	glPopMatrix();

	glPushMatrix();
	glDisable(GL_TEXTURE_2D);
	glTranslatef(-250 - (battle_distance / 0.6f), 0, 0);
	glRotatef(-20, 1, 0, 0);
	glRotatef(50, 0, 1, 0);
	glScalef(0.7f, 0.7f, 0.7f);
	glColor4f(0, 0, 0, 1);

	monster->Draw();

	glPopMatrix();
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

	if (bakkunakkuru == true) {
		if (bakkunakkuru_count > 0) {
			bakkunakkuru_count--;
			font->ChangeSize(lkn::TYPE_NORMAL);
			font->DrawStringW(209, 200, L" Damage!!");
			glColor3f(1, 0, 0);
			max_font->ChangeSize(lkn::TYPE_MAX);
			max_font->DrawStringW(187, 130, L" 80");
		}
		else {
			bakkunakkuru_count = 30;
			bakkunakkuru = false;
		}
	}


	glColor3f(1, 1, 1);

	font->ChangeSize(lkn::TYPE_NORMAL);
	font->DrawStringW(119, 55, L" ");//Ç»Ç∫Ç©àÍî≠ñ⁄Ç∏ÇÍÇÈÇÃÇ≈ãÛï`âÊ
	int p1_percentage = 50;
	int p2_percentage = 50;

	font->DrawStringW(119, 55, L" %2d", p1_percentage);
	font->DrawStringW(156, 55, L" %2d", p2_percentage);

	font->DrawStringW(73, 269, L" %3.0f/%3.0f", p1_HP, p1_HP_MAX);
	font->DrawStringW(185, 269, L" %3.0f/%3.0f", p2_HP, p2_HP_MAX);


	int p1_guts = 67;
	int p2_guts = 50;
	font->DrawStringW(119, 30, L" %2d", p1_guts);
	font->DrawStringW(162, 30, L" %2d", p2_guts);

	int time = 99 - (battle_frame / 60);
	font->DrawStringW(141, 242, L" %2d", time);

	font->DrawStringW(138, 55, L" Hit");
	font->DrawStringW(136, 30, L" Guts");

	wchar_t p1_name[] = {
		L"Ç¥Ç´"
	};
	wchar_t p2_name[] = {
		L"Ç∑Ç¶Ç´Ç∑Ç¶ÇºÅ["
	};
	int p1_size = sizeof(p1_name) / sizeof(p1_name[0]);
	int p2_size = sizeof(p2_name) / sizeof(p2_name[0]);

	glPushMatrix();
	{
		int p1_translate = (8 - (p1_size - 1)) * 5;
		glTranslatef(p1_translate, 0, 0);
		font->DrawStringW(28, 229, L" %s", p1_name);
	}
	glPopMatrix();

	glPushMatrix();
	{
		int p2_translate = (8 - (p2_size - 1)) * 5;
		glTranslatef(p2_translate, 0, 0);
		font->DrawStringW(184, 229, L" %s", p2_name);
	}
	glPopMatrix();

	wchar_t p1_skill[] = {
		L"ÉoÉbÉNÉiÉbÉNÉã"
	};
	wchar_t p2_skill[] = {
		L"Ç¬ÇŒÇÕÇ´"
	};
	int p1_skill_size = sizeof(p1_skill) / sizeof(p1_skill[0]);
	int p2_skill_size = sizeof(p2_skill) / sizeof(p2_skill[0]);
	glPushMatrix();
	{
		int p1_translate = (8 - (p1_skill_size - 1)) * 5;
		glTranslatef(p1_translate, 0, 0);
		font->DrawStringW(27, 79, L" %s", p1_skill);
	}
	glPopMatrix();

	glPushMatrix();
	{
		int p2_translate = (8 - (p2_skill_size - 1)) * 5;
		glTranslatef(p2_translate, 0, 0);
		font->DrawStringW(185, 79, L" %s", p2_skill);
	}
	glPopMatrix();


	min_font->ChangeSize(lkn::TYPE_MIN);
	min_font->DrawStringW(114, 79, L" %2d", 26);
	min_font->DrawStringW(172, 79, L" %2d", 10);

	min_font->DrawStringW(130, 55, L" Åì");
	min_font->DrawStringW(167, 55, L" Åì");
	//ãZBox
	glColor4f(1, 1, 1, 1);
	glBegin(GL_QUADS);
	{
		glVertex2f(28.7f, 35);
		glVertex2f(28.7f, 64);
		glVertex2f(50, 64);
		glVertex2f(50, 35);
	}
	{
		glVertex2f(50.6f, 35);
		glVertex2f(50.6f, 64);
		glVertex2f(72, 64);
		glVertex2f(72, 35);
	}
	{
		glVertex2f(72.7f, 35);
		glVertex2f(72.7f, 64);
		glVertex2f(94, 64);
		glVertex2f(94, 35);
	}
	{
		glVertex2f(94.6f, 35);
		glVertex2f(94.6f, 64);
		glVertex2f(116, 64);
		glVertex2f(116, 35);
	}


	{
		glVertex2f(184, 35);
		glVertex2f(184, 64);
		glVertex2f(205.4f, 64);
		glVertex2f(205.4f, 35);
	}
	{
		glVertex2f(206, 35);
		glVertex2f(206, 64);
		glVertex2f(227.3f, 64);
		glVertex2f(227.3f, 35);
	}
	{
		glVertex2f(228, 35);
		glVertex2f(228, 64);
		glVertex2f(249.4f, 64);
		glVertex2f(249.4f, 35);
	}
	{
		glVertex2f(250, 35);
		glVertex2f(250, 64);
		glVertex2f(271.3f, 64);
		glVertex2f(271.3f, 35);
	}



	glEnd();
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

	if (0 < time && 0 < p1_HP && 0 < p2_HP) {
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
		if (lkn::InputManager::getInstance()->keyPless('f')) {
			p2_HP -= 80;
			bakkunakkuru = true;
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

		if (lkn::InputManager::getInstance()->keyPlessAndHold('q')) {
			if (!(lkn::InputManager::getInstance()->keyRelease('q'))) {
				if (p1_HP < p1_HP_MAX)
					p1_HP++;
			}
		}
		if (lkn::InputManager::getInstance()->keyPlessAndHold('e')) {
			if (!(lkn::InputManager::getInstance()->keyRelease('e'))) {
				if (0 < p1_HP)
					p1_HP--;
			}
		}

		if (lkn::InputManager::getInstance()->keyPlessAndHold('p')) {
			if (!(lkn::InputManager::getInstance()->keyRelease('p'))) {
				if (p2_HP < p2_HP_MAX)
					p2_HP++;
			}
		}
		if (lkn::InputManager::getInstance()->keyPlessAndHold('i')) {
			if (!(lkn::InputManager::getInstance()->keyRelease('i'))) {
				if (0 < p2_HP)
					p2_HP--;
			}
		}

		if (lkn::InputManager::getInstance()->keyPless(0x0d)) {
			p1_HP = 0.f;
		}

		battle_frame++;
	}
	else {
		if (dead_flag == false) {
			alSourcePlay(battle_lose_music->source);
			dead_flag = true;
		}
		max_font->ChangeSize(lkn::TYPE_MAX);
		glColor3f(1, 0, 0);
		if (p1_HP == 0) {
			max_font->DrawStringW(65, 125, L" ÇkÇnÇrÇd...");
		}
		if (p2_HP == 0) {
			max_font->DrawStringW(65, 125, L" ÇvÇhÇmÅIÅI");
		}
		alSourceStop(battle_music->source);
		if (lkn::InputManager::getInstance()->keyPless(0x0d)) {
			alSourceStop(battle_lose_music->source);
			battle_init = false;
			func = title;
		}
	}

}