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

extern int training_command;

float training_frame;
bool training_init = 0;
float training_movie;

bool up_init = 0;
int up_para;

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
				printf("12");
				result = NULL;
				l_para = NULL;
				h_para = NULL;
				up_init = 0;
				player->nengetu++;
				monster->age++;

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
}

void light_parameter_up(int type, unsigned short& para) {
	
	if (up_init == 0) {
		up_init = 1;

		up_para = 7 + (rand() % 5-2);
		para += up_para;
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