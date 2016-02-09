#include"training.h"
#include"../GL/freeglut.h"
#include"../game/monster.h"
#include"../game/player.h"
#include"almighty.h"

#include<stdio.h>
#include<math.h>
#include<time.h>

void success();
void failure();
void parameter_up();
void(*result)();


void light_parameter_up(int type, unsigned short& para);
void (*l_para)(int type, unsigned short& para);

void heavy_parameter_up(int type1, int type2, int type3, unsigned short &para1, unsigned short &para2, unsigned short &para3);
void(*h_para)(int type1, int type2, int type3, unsigned short &para1,unsigned short &para2, unsigned short &para3);

extern game::MyMessageBox* message_box;
extern lkn::Image* status_mask_image;
extern game::Suezo* suezo;
extern game::Monster* monster;
extern game::Player* player;
extern lkn::Sound* training_music;


extern int training_command;

float training_frame;
bool training_init = 0;
float training_movie;

bool up_init = 0;
int up_para;
int super_up_para;
int down_para;

lkn::RGB parameter_color[6] = {
	1, 1, 0.5f,
	1, 0, 0.25f,
	0, 1, 0.4f,
	1, 0, 1,
	0, 1, 1,
	0, 0.5f, 1
};

void training() {
	if (training_init == 0) {
		alSourcePlay(training_music->source);

		training_frame = 0;
		result = NULL;
		l_para = NULL;
		h_para = NULL;
		srand(time(NULL));
		up_init = 0;
		training_init = 1;
	}
	training_frame += 0.1f;
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

	glColor4f(1, 0.3f, 0.3f, 1);
	max_font->ChangeSize(lkn::TYPE_MAX);
	if (result == NULL) {
		training_movie = sin(training_frame) * 10;
	}
	max_font->DrawStringW(30, training_movie + 150, L"トレーニング");
	max_font->DrawStringW(30, training_movie + 80, L"       中...");

	if (result != NULL) {
		result();
	}

	if (l_para != NULL) {
		if (training_command == 0) {
			l_para(game::TYPE_POWER, monster->power_point);
		}
		else if(training_command == 1) {
			l_para(game::TIPE_HIT_PROBABILITY, monster->hit_probability_point);
		}
		else if (training_command == 2) {
			l_para(game::TYPE_INTELLIGENCE, monster->intelligence_point);
		}
		else if (training_command == 3) {
			l_para(game::TYPE_DODGE, monster->dodge_point);
		}
		else if (training_command == 4) {
			l_para(game::TYPE_HP, monster->HP);
		}
		else if (training_command == 5) {
			l_para(game::TYPE_STRONG, monster->strong_point);
		}
	}

	if (h_para != NULL) {
		if (training_command == 6) {
			h_para(game::TYPE_POWER, game::TYPE_HP, game::TYPE_DODGE, monster->power_point, monster->HP,monster->dodge_point);
		}
		else if (training_command == 7) {
			h_para(game::TYPE_DODGE, game::TYPE_INTELLIGENCE, game::TYPE_POWER, monster->dodge_point, monster->intelligence_point, monster->power_point);
		}
		else if (training_command == 8) {
			h_para(game::TYPE_INTELLIGENCE, game::TIPE_HIT_PROBABILITY, game::TYPE_STRONG, monster->intelligence_point, monster->hit_probability_point, monster->strong_point);
		}
		else if (training_command == 9) {
			h_para(game::TYPE_STRONG, game::TYPE_HP, game::TYPE_INTELLIGENCE, monster->strong_point, monster->HP, monster->intelligence_point);
		}
	}

	if (lkn::InputManager::getInstance()->keyPless(0x0d)) {////Enter Dicision
		if (result == NULL) {
			if (rand() % 20 >= 0) {
				result = success;
			}
			else {
				result = failure;
			}
		}
		else if (result == success) {
			if (l_para == NULL && h_para == NULL) {
				if (training_command < 6) {
					l_para = light_parameter_up;
				}
				else {
					h_para = heavy_parameter_up;
				}
			}
			else {
				result = NULL;
				l_para = NULL;
				h_para = NULL;
				up_init = 0;
				player->nengetu++;
				monster->age++;
				alSourceStop(training_music->source);

				func = farm;
			}
		}
		else if (result == failure) {
			
		}
	}
}

void success() {
	glEnable(GL_BLEND);
	glBlendFunc(
		GL_SRC_ALPHA,
		GL_ONE_MINUS_SRC_ALPHA
		);

	glColor4f(0, 0, 0, 0.3f);
	glBegin(GL_QUADS);
	{
		glVertex2f(0, 70);
		glVertex2f(300, 70);
		glVertex2f(300, 230);
		glVertex2f(0, 230);
	}
	glEnd();
	glColor3f(1, 0.8f, 0.2f);
	max_font->DrawStringW(100, 130, L"成功！！");

	

	glDisable(GL_BLEND);

}

void heavy_parameter_up(int type1, int type2, int type3, unsigned short& para1, unsigned short& para2, unsigned short& para3) {
	if (up_init == 0) {
		up_init = 1;

		super_up_para = 10 + (rand() % 5 - 2);
		up_para = 5 + (rand() % 5 - 2);
		down_para = 3 + (rand() % 3 - 2);
		para1 += super_up_para;
		para2 += up_para;
		para3 -= down_para;
		if (para1 > 999) {
			super_up_para -= (para1 - 999);
			para1 = 999;
		}
		if (para2 > 999) {
			up_para -= (para2 - 999);
			para2 = 999;
		}
		if (para3 < 1) {
			down_para -= (1-para3);
			para3 = 1;
		}

	}

	status_mask_image->changeImage();

	glColor4f(1, 1, 1, 1);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0, 0);
		glVertex2f(70, 250);
		glTexCoord2f(0, 1);
		glVertex2f(70, 80);
		glTexCoord2f(1, 1);
		glVertex2f(230, 80);
		glTexCoord2f(1, 0);
		glVertex2f(230, 250);

	}
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glBlendFunc(
		GL_SRC_ALPHA,
		GL_ONE_MINUS_SRC_ALPHA
		);

	glColor4f(0.3f, 0.3f, 0.3f, 1);
	glBegin(GL_QUADS);
	{
		glVertex2f(85, 95);
		glVertex2f(125, 95);
		glVertex2f(125, 125);
		glVertex2f(85, 125);
	}
	{
		glVertex2f(85, 135);
		glVertex2f(125, 135);
		glVertex2f(125, 165);
		glVertex2f(85, 165);
	}
	{
		glVertex2f(85, 175);
		glVertex2f(125, 175);
		glVertex2f(125, 205);
		glVertex2f(85, 205);
	}
	glColor4f(0.3f, 0.3f, 0.3f, 0.3f);
	{
		glVertex2f(125, 95);
		glVertex2f(220, 95);
		glVertex2f(220, 125);
		glVertex2f(125, 125);
	}
	{
		glVertex2f(125, 135);
		glVertex2f(220, 135);
		glVertex2f(220, 165);
		glVertex2f(125, 165);
	}
	{
		glVertex2f(125, 175);
		glVertex2f(220, 175);
		glVertex2f(220, 205);
		glVertex2f(125, 205);
	}

	int parameter_length1 = 126 + (219 - 126) / 999.0f*para1;
	int parameter_length2 = 126 + (219 - 126) / 999.0f*para2;
	int parameter_length3 = 126 + (219 - 126) / 999.0f*para3;
	glColor4f(parameter_color[type1].r, parameter_color[type1].g, parameter_color[type1].b, 1);
	{
		glVertex2f(126, 182);
		glVertex2f(parameter_length1, 182);
		glVertex2f(parameter_length1, 198);
		glVertex2f(126, 198);
	}

	glColor4f(parameter_color[type2].r, parameter_color[type2].g, parameter_color[type2].b, 1);
	{
		glVertex2f(126, 142);
		glVertex2f(parameter_length2, 142);
		glVertex2f(parameter_length2, 158);
		glVertex2f(126, 158);
	}

	glColor4f(parameter_color[type3].r, parameter_color[type3].g, parameter_color[type3].b, 1);
	{
		glVertex2f(126, 102);
		glVertex2f(parameter_length3, 102);
		glVertex2f(parameter_length3, 118);
		glVertex2f(126, 118);
	}

	glColor4f(0, 0, 0, 0.4f);
	{
		glVertex2f(126, 138);
		glVertex2f(143, 138);
		glVertex2f(143, 162);
		glVertex2f(126, 162);
	}
	{
		glVertex2f(151, 138);
		glVertex2f(169, 138);
		glVertex2f(169, 162);
		glVertex2f(151, 162);
	}
	{
		glVertex2f(176, 138);
		glVertex2f(194, 138);
		glVertex2f(194, 162);
		glVertex2f(176, 162);
	}

	{
		glVertex2f(126, 98);
		glVertex2f(143, 98);
		glVertex2f(143, 122);
		glVertex2f(126, 122);
	}
	{
		glVertex2f(151, 98);
		glVertex2f(169, 98);
		glVertex2f(169, 122);
		glVertex2f(151, 122);
	}
	{
		glVertex2f(176, 98);
		glVertex2f(194, 98);
		glVertex2f(194, 122);
		glVertex2f(176, 122);
	}

	{
		glVertex2f(126, 178);
		glVertex2f(143, 178);
		glVertex2f(143, 202);
		glVertex2f(126, 202);
	}
	{
		glVertex2f(151, 178);
		glVertex2f(169, 178);
		glVertex2f(169, 202);
		glVertex2f(151, 202);
	}
	{
		glVertex2f(176, 178);
		glVertex2f(194, 178);
		glVertex2f(194, 202);
		glVertex2f(176, 202);
	}

	glEnd();

	glColor3f(1, 1, 1);
	font->ChangeSize(lkn::TYPE_NORMAL);
	glPushMatrix();
	{
		int name_value = wcslen(parameter_name[type1]);
		glTranslatef((4 - name_value) * 5, 0, 0);
		font->DrawStringW(86, 182, L"%s", parameter_name[type1]);
	}
	glPopMatrix();
	glPushMatrix();
	{
		int name_value = wcslen(parameter_name[type2]);
		glTranslatef((4 - name_value) * 5, 0, 0);
		font->DrawStringW(86, 142, L"%s", parameter_name[type2]);
	}
	glPopMatrix();
	glPushMatrix();
	{
		int name_value = wcslen(parameter_name[type3]);
		glTranslatef((4 - name_value) * 5, 0, 0);
		font->DrawStringW(86, 102, L"%s", parameter_name[type3]);
	}
	glPopMatrix();

	font->DrawStringW(128, 182, L"+%2d  %3d⇒%3d", super_up_para, para1 - super_up_para, para1);
	font->DrawStringW(128, 142, L"+%2d  %3d⇒%3d", up_para, para2 - up_para, para2);
	font->DrawStringW(128, 102, L"-%2d  %3d⇒%3d", down_para, para3 + down_para, para3);

	message_box->Draw(NULL, 0);
	font->DrawStringW(70, 60, L"「%s」が%d上がりました。", parameter_name[type1], super_up_para);
	font->DrawStringW(70, 40, L"「%s」が%d上がりました。", parameter_name[type2], up_para);
	font->DrawStringW(70, 20, L"「%s」が%d下がりました。", parameter_name[type3], down_para);


	glDisable(GL_BLEND);
}

void light_parameter_up(int type, unsigned short& para) {
	
	if (up_init == 0) {
		up_init = 1;

		up_para = 7 + (rand() % 5-2);
		para += up_para;
		if (para > 999) {
			up_para -= (para - 999);
			para = 999;
		}
	}

	status_mask_image->changeImage();

	glColor4f(1, 1, 1, 1);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0, 0);
		glVertex2f(70, 250);
		glTexCoord2f(0,1);
		glVertex2f(70, 80);
		glTexCoord2f(1, 1);
		glVertex2f(230, 80);
		glTexCoord2f(1, 0);
		glVertex2f(230, 250);
		
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glBlendFunc(
		GL_SRC_ALPHA,
		GL_ONE_MINUS_SRC_ALPHA
		);

	glColor4f(0.3f, 0.3f, 0.3f, 1);
	glBegin(GL_QUADS);
	{
		glVertex2f(85, 135);
		glVertex2f(125, 135);
		glVertex2f(125, 165);
		glVertex2f(85, 165);
	}
	glColor4f(0.3f, 0.3f, 0.3f, 0.3f);
	{
		glVertex2f(125, 135);
		glVertex2f(220, 135);
		glVertex2f(220, 165);
		glVertex2f(125, 165);
	}

	int parameter_length = 126 + (219 - 126) / 999.0f*para;
	glColor4f(parameter_color[type].r, parameter_color[type].g, parameter_color[type].b, 1);
	{
		glVertex2f(126, 142);
		glVertex2f(parameter_length, 142);
		glVertex2f(parameter_length, 158);
		glVertex2f(126, 158);
	}

	glColor4f(0, 0, 0, 0.4f);
	{
		glVertex2f(126, 138);
		glVertex2f(143, 138);
		glVertex2f(143, 162);
		glVertex2f(126, 162);
	}
	glColor4f(0, 0, 0, 0.4f);
	{
		glVertex2f(151, 138);
		glVertex2f(169, 138);
		glVertex2f(169, 162);
		glVertex2f(151, 162);
	}
	glColor4f(0, 0, 0, 0.4f);
	{
		glVertex2f(176, 138);
		glVertex2f(194, 138);
		glVertex2f(194, 162);
		glVertex2f(176, 162);
	}

	glEnd();

	glColor3f(1, 1, 1);
	font->ChangeSize(lkn::TYPE_NORMAL);
	glPushMatrix(); 
	{
		int name_value = wcslen(parameter_name[type]);
		glTranslatef((4 - name_value)*5,0,0);
		font->DrawStringW(86, 142, L"%s", parameter_name[type]);
	}
	glPopMatrix();

	font->DrawStringW(128, 142, L"+%2d  %3d⇒%3d",up_para,para - up_para,para);

	message_box->Draw(NULL,0);
	font->DrawStringW(70,60,L"「%s」が%d上がりました。", parameter_name[type],up_para);
	

	glDisable(GL_BLEND);
}

void failure() {
	glEnable(GL_BLEND);
	glBlendFunc(
		GL_SRC_ALPHA,
		GL_ONE_MINUS_SRC_ALPHA
		);

	glColor4f(0, 0, 0, 0.5f);
	glBegin(GL_QUADS);
	{
		glVertex2f(0, 70);
		glVertex2f(300, 70);
		glVertex2f(300, 230);
		glVertex2f(0, 230);
	}
	glEnd();
	glColor3f(0, 0.5f, 1);
	max_font->DrawStringW(100, 130, L"失敗...");

	glDisable(GL_BLEND);
}