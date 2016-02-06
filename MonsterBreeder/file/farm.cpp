#define _CRT_SECURE_NO_WARNINGS

#include"farm.h"
#include"../game/monster.h"
#include"../game/message_box.h"
#include"training.h"

#define _USE_MATH_DEFINES
#include<math.h>
#include<time.h>
#include<string.h>

void main_manu();
void training_mode();
void(*farm_scene)();

void training_message();
void yes_message();
void battle_message();
void(*message)();

void status();
void(*status_mask)();

void field();


int farm_command;
bool farm_init = 0;
int farm_frame;
int angle;

int training_command;

int farm_movie;

int farm_yes_no = 0;

float farm_x = 5000.f;
float farm_y = 3500.f;
float farm_z = 5000.f;
bool colt_flag;
bool battle_flag;


extern game::Suezo* suezo;
extern game::Monorisu* monorisu;

extern game::MyMessageBox* message_box;

extern lkn::Image* status_mask_image;


void farm() {
	glEnable(
		GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	if (farm_init == 0) {
		farm_scene = main_manu;
		message = NULL;

		farm_command = 0;
		farm_frame = 0;
		angle = 0;

		suezo->pos.x = 0.f;
		suezo->pos.y = 0.f;
		suezo->pos.z = -4500.f;

		farm_init = 1;
		alSourcePlay(spring_music->source);
		eye->y = 1200;
		eye->x = 1400;
		eye->z = 2000;
		colt_flag = false;
		battle_flag = false;
		srand(time(NULL));

		//////////////////////////////
		wcscpy(suezo->name,L"すえきすえぞー");
		suezo->HP = 90;
		suezo->power_point = 100;
		suezo->intelligence_point = 180;
		suezo->hit_probability_point = 170;
		suezo->dodge_point = 120;
		suezo->strong_point = 80;
		//////////////////////////////
	}
	farm_frame++;
	
	field();

	glEnable(
		GL_CULL_FACE);

	//glTranslatef(sin(angle * M_PI / 180)*farm_frame, 0, cos(angle * M_PI / 180)*farm_frame);
	if (farm_frame % 70 >= 30) {
		if (-farm_x + 200 < (suezo->pos.x + sin(angle* M_PI / 180) * 500 / 100.0f) &&
			(suezo->pos.x + sin(angle* M_PI / 180) * 500 / 100.0f) < farm_x - 200 &&
			-farm_z + 200 < (suezo->pos.z + cos(angle* M_PI / 180) * 500 / 100.0f) &&
			(suezo->pos.z + cos(angle* M_PI / 180) * 500 / 100.0f) < farm_z - 200) {
			suezo->pos.x += sin(angle* M_PI / 180) * 500 / 100.0f;
			suezo->pos.z += cos(angle* M_PI / 180) * 500 / 100.0f;
		}
		else {
			angle += 90;
		}
	}

	target->x = suezo->pos.x;
	target->z = suezo->pos.z;
	if (farm_frame % 70 == 69) {
		angle += (rand() % 40) - 20;
	}


	//printf("angle = %d  frame = %d", angle, farm_frame);
	glPushMatrix();
	glTranslatef(suezo->pos.x, suezo->pos.y - 100, suezo->pos.z);
	glRotatef(angle, 0, 1, 0);


	///////////////////////////////////////モノリス

	//glColor4f(0, 0, 0, 1);
	//monorisu->Draw();

	/////////////////////////////////////スエゾー

	glColor4f(1, 1, 0, 1);
	suezo->Draw();

	glPopMatrix();

	glDisable(GL_DEPTH_TEST);


	glDisable(GL_TEXTURE_2D);
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

	glEnable(GL_BLEND);
	glBlendFunc(
		GL_SRC_ALPHA,
		GL_ONE_MINUS_SRC_ALPHA
		);

	glBegin(GL_QUADS);
	glColor4f(0.5f, 0.5f, 0.5f, 0.5f);
	{
		glVertex2f(10, 210);
		glVertex2f(70, 210);
		glVertex2f(70, 290);
		glVertex2f(10, 290);
	}
	glEnd();

	waku_image->changeImage();

	glColor4f(0.7f, 0.7f, 0.7f, 1);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0.f, 0.f);
		glVertex2f(10, 210);
		glTexCoord2f(0.f, 1.f);
		glVertex2f(70, 210);
		glTexCoord2f(1.f, 1.f);
		glVertex2f(70, 290);
		glTexCoord2f(1.f, 0.f);
		glVertex2f(10, 290);
	}
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glColor3f(1, 1, 1);
	int nen = 1000;
	int getu = 4;
	int syu = 1;
	font->DrawStringW(20, 257, L" %d年", nen);
	font->DrawStringW(16, 229, L" %2d月%d週", getu, syu);

	farm_scene();

	if (message != NULL) {
		message();
	}

	glDisable(
		GL_CULL_FACE);

}

wchar_t training_menu[10][16] = {
	L" ドミノ倒し",
	L"  しゃてき",
	L"   猛勉強",
	L"  巨石よけ",
	L"  走りこみ",
	L"  丸太うけ",
	L"  重り引き",
	L"  変動ゆか",
	L"  めいそう",
	L"   プール"
};

wchar_t training_menu2[10][32] = {
	L"ちから↑",
	L"命中↑",
	L"かしこさ↑",
	L"回避↑",
	L"ライフ↑",
	L"丈夫さ↑",
	L"ちから↑↑　ライフ↑",
	L"回避↑↑　　かしこさ↑",
	L"かしこさ↑↑命中↑",
	L"丈夫さ↑↑　ライフ↑"
};

wchar_t training_menu3[10][32] = {
	L"　　　　　　疲労↑",
	L"　　　　　　疲労↑",
	L"　　　　　　疲労↑",
	L"　　　　　　疲労↑",
	L"　　　　　　疲労↑",
	L"　　　　　　疲労↑",
	L"回避↓　　　疲労↑↑",
	L"ちから↓　　疲労↑↑",
	L"丈夫さ↓　　疲労↑↑",
	L"かしこさ↓　疲労↑↑"
};

void main_manu() {
	glColor4f(0.7f, 0.7f, 0.7f, 0.5f);
	glBegin(GL_QUADS);
	{
		glVertex2f(235, 88);
		glVertex2f(280, 88);
		glVertex2f(280, 250);
		glVertex2f(235, 250);
	}
	glColor4f(1, 1, 1, 0.7f);
	{
		glVertex2f(235, 223 - farm_command * 27);
		glVertex2f(280, 223 - farm_command * 27);
		glVertex2f(280, 250 - farm_command * 27);
		glVertex2f(235, 250 - farm_command * 27);
	}
	glEnd();

	glLineWidth(4);
	glColor4f(0, 0, 0, 1);
	glBegin(GL_LINES);
	{
		glVertex2f(235.3f, 223); glVertex2f(280, 223);
		glVertex2f(235.3f, 196); glVertex2f(280, 196);
		glVertex2f(235.3f, 169); glVertex2f(280, 169);
		glVertex2f(235.3f, 142); glVertex2f(280, 142);
		glVertex2f(235.3f, 115); glVertex2f(280, 115);
		glVertex2f(235.3f, 88); glVertex2f(280, 88);
	}
	glEnd();

	glDisable(GL_BLEND);

	glColor3f(1, 1, 1);
	font->ChangeSize(lkn::TYPE_NORMAL);
	font->DrawStringW(243, 229, L" 育成");
	font->DrawStringW(243, 202, L" 休養");
	font->DrawStringW(243, 175, L" 大会");
	font->DrawStringW(233, 148, L" アイテム");
	font->DrawStringW(233, 121, L" ファイル");
	font->DrawStringW(233, 94, L" パークへ");


	if (status_mask != NULL) {
		status_mask();

		if (lkn::InputManager::getInstance()->keyPless(0x20)) {////Space Cancel
			alSourcePlay(cancel_music->source);
			status_mask = NULL;
		}
	}
	else {
		if (lkn::InputManager::getInstance()->keyPless('w')) {////up select
			alSourcePlay(select_music->source);
			if (message == NULL) {
				farm_command--;
			}
			else if (message == battle_message) {
				farm_yes_no--;
			}
		}
		if (lkn::InputManager::getInstance()->keyPless('s')) {////down select
			alSourcePlay(select_music->source);
			if (message == NULL) {
				farm_command++;
			}
			else if (message == battle_message) {
				farm_yes_no++;
			}
		}

		farm_command = (FARM_MAX + farm_command) % FARM_MAX;
		farm_yes_no = (lkn::YES_NO_MAX + farm_yes_no) % lkn::YES_NO_MAX;

		if (lkn::InputManager::getInstance()->keyPless(0x0d)) {////Enter Dicision
			alSourcePlay(decision_music->source);
			if (farm_command == FARM_BATTLE) {
				if (message == NULL) {
					farm_yes_no = 0;
					message = battle_message;
				}
				else if (message == battle_message) {
					if (farm_yes_no == lkn::YES) {
						message = yes_message;
					}
					else if (farm_yes_no == lkn::NO) {
						message = NULL;
					}
				}
				else if (message == yes_message) {
					farm_init = 0;
					message = NULL;
					func = battle;
				}
			}
			else if (farm_command == FARM_TRAINING) {
				farm_scene = training_mode;
			}
		}

		if (lkn::InputManager::getInstance()->keyPless(0x20)) {////Space Cancel
			alSourcePlay(cancel_music->source);
			message = NULL;
		}


		if (lkn::InputManager::getInstance()->keyPless('p')) {////up select
			alSourcePlay(decision_music->source);
			status_mask = status;
		}

	}
}

void training_mode() {
	glColor4f(0.7f, 0.7f, 0.7f, 0.5f);
	glBegin(GL_QUADS);
	{
		glVertex2f(165, 115);
		glVertex2f(280, 115);
		glVertex2f(280, 250);
		glVertex2f(165, 250);
	}
	glColor4f(0.3f, 0.3f, 0.3f, 0.5f);
	{
		glVertex2f(25, 110);
		glVertex2f(140, 110);
		glVertex2f(140, 210);
		glVertex2f(25, 210);
	}

	glColor4f(1, 1, 1, 0.7f);
	if (training_command % 2 == 0) {
		{
			glVertex2f(165, 223 - (training_command / 2) * 27);
			glVertex2f(222, 223 - (training_command / 2) * 27);
			glVertex2f(222, 250 - (training_command / 2) * 27);
			glVertex2f(165, 250 - (training_command / 2) * 27);
		}
	}
	else {
		{
			glVertex2f(222, 223 - (training_command / 2) * 27);
			glVertex2f(280, 223 - (training_command / 2) * 27);
			glVertex2f(280, 250 - (training_command / 2) * 27);
			glVertex2f(222, 250 - (training_command / 2) * 27);
		}
	}
	glEnd();

	glLineWidth(4);
	glColor4f(0, 0, 0, 1);
	glBegin(GL_LINES);
	{
		glVertex2f(165, 223); glVertex2f(280, 223);
		glVertex2f(165, 196); glVertex2f(280, 196);
		glVertex2f(165, 169); glVertex2f(280, 169);
		glVertex2f(165, 142); glVertex2f(280, 142);
		glVertex2f(165, 115); glVertex2f(280, 115);

		glVertex2f(222, 250); glVertex2f(222, 115);
	}
	glEnd();

	glDisable(GL_BLEND);

	glColor3f(1, 1, 1);
	font->ChangeSize(lkn::TYPE_NORMAL);
	font->DrawStringW(164, 229, training_menu[0]);
	font->DrawStringW(223, 229, training_menu[1]);
	font->DrawStringW(164, 202, training_menu[2]);
	font->DrawStringW(223, 202, training_menu[3]);
	font->DrawStringW(164, 175, training_menu[4]);
	font->DrawStringW(223, 175, training_menu[5]);
	font->DrawStringW(164, 148, training_menu[6]);
	font->DrawStringW(223, 148, training_menu[7]);
	font->DrawStringW(164, 121, training_menu[8]);
	font->DrawStringW(223, 121, training_menu[9]);
	
	font->DrawStringW(51, 185, training_menu[training_command]);
	font->DrawStringW(31, 155, training_menu2[training_command]);
	font->DrawStringW(31, 125, training_menu3[training_command]);

	

	if (lkn::InputManager::getInstance()->keyPless('w')) {////up select
		alSourcePlay(select_music->source);
		if (message == NULL) {
			training_command -= 2;
		}
		else if (message == training_message) {
			farm_yes_no--;
		}
	}
	if (lkn::InputManager::getInstance()->keyPless('s')) {////down select
		alSourcePlay(select_music->source);
		if (message == NULL) {
			training_command += 2;
		}
		else if (message == training_message) {
			farm_yes_no++;
		}
	}

	if (lkn::InputManager::getInstance()->keyPless('a')) {////left select
		alSourcePlay(select_music->source);
		if (message == NULL) {
			training_command--;
		}
	}
	if (lkn::InputManager::getInstance()->keyPless('d')) {////right select
		alSourcePlay(select_music->source);
		if (message == NULL) {
			training_command++;
		}
	}
	training_command = (TRAINING_MAX + training_command) % TRAINING_MAX;
	farm_yes_no = (lkn::YES_NO_MAX + farm_yes_no) % lkn::YES_NO_MAX;

	if (lkn::InputManager::getInstance()->keyPless(0x0d)) {////Enter Dicision
		alSourcePlay(decision_music->source);
		if (message == NULL) {
			message = training_message;
		}
		else if (message == training_message) {
			if (farm_yes_no == lkn::YES) {
				message = yes_message;
			}
			else if (farm_yes_no == lkn::NO) {
				message = NULL;
			}
		}
		else if (message == yes_message) {
			farm_init = 0;
			message = NULL;
			func = training;
		}
	}

	if (lkn::InputManager::getInstance()->keyPless(0x20)) {////Space Cancel
		alSourcePlay(cancel_music->source);
		if (farm_scene == training_mode) {
			farm_scene = main_manu;
		}
	}
}

void battle_message() {
	message_box->Draw(game::MESSAGE_TYPE_COLT, 1, L"大会に出る？");
	glEnable(GL_BLEND);
	glBlendFunc(
		GL_SRC_ALPHA,
		GL_ONE_MINUS_SRC_ALPHA
		);

	glColor4f(0.8f, 0.8f, 0.8f, 0.5f);
	glBegin(GL_QUADS);
	{
		glVertex2f(210, 45);
		glVertex2f(255, 45);
		glVertex2f(255, 72);
		glVertex2f(210, 72);
	}
	{
		glVertex2f(210, 17);
		glVertex2f(255, 17);
		glVertex2f(255, 44);
		glVertex2f(210, 44);
	}

	glColor4f(1, 1, 1, 0.7f);
	{
		glVertex2f(210, 45 - farm_yes_no * 28);
		glVertex2f(255, 45 - farm_yes_no * 28);
		glVertex2f(255, 72 - farm_yes_no * 28);
		glVertex2f(210, 72 - farm_yes_no * 28);
	}
	glEnd();
	glDisable(GL_BLEND);

	glColor4f(1, 1, 1, 1);
	font->DrawStringW(223, 51, L"はい");
	font->DrawStringW(218, 24, L"いいえ");
}

void training_message() {
	message_box->Draw(game::MESSAGE_TYPE_COLT, 2, L"それじゃあトレーニングを", L"はじめようか？");
	glEnable(GL_BLEND);
	glBlendFunc(
		GL_SRC_ALPHA,
		GL_ONE_MINUS_SRC_ALPHA
		);

	glColor4f(0.8f, 0.8f, 0.8f, 0.5f);
	glBegin(GL_QUADS);
	{
		glVertex2f(210, 45);
		glVertex2f(255, 45);
		glVertex2f(255, 72);
		glVertex2f(210, 72);
	}
	{
		glVertex2f(210, 17);
		glVertex2f(255, 17);
		glVertex2f(255, 44);
		glVertex2f(210, 44);
	}

	glColor4f(1, 1, 1, 0.7f);
	{
		glVertex2f(210, 45 - farm_yes_no * 28);
		glVertex2f(255, 45 - farm_yes_no * 28);
		glVertex2f(255, 72 - farm_yes_no * 28);
		glVertex2f(210, 72 - farm_yes_no * 28);
	}
	glEnd();
	glDisable(GL_BLEND);

	glColor4f(1, 1, 1, 1);
	font->DrawStringW(223, 51, L"はい");
	font->DrawStringW(218, 24, L"いいえ");
}

void yes_message() {
	message_box->Draw(game::MESSAGE_TYPE_COLT, 1, L"それじゃあ頑張ろうね！");
}


void status() {
	glEnable(GL_BLEND);
	glBlendFunc(
		GL_SRC_ALPHA,
		GL_ONE_MINUS_SRC_ALPHA
		);
	glColor4f(0, 0, 0,0.3f);
	glBegin(GL_QUADS);
	{
		glVertex2f(0, 300);
		glVertex2f(0, 0);
		glVertex2f(300, 0);
		glVertex2f(300, 300);
	}
	glEnd();
	glDisable(GL_BLEND);

	status_mask_image->changeImage();

	glColor4f(1, 1, 1, 1);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0,0);
		glVertex2f(10, 290);
		glTexCoord2f(0, 1);
		glVertex2f(10, 10);
		glTexCoord2f(1, 1);
		glVertex2f(290, 10);
		glTexCoord2f(1, 0);
		glVertex2f(290, 290);
	}
	glEnd();

	glPushMatrix();
	{
		glMatrixMode(GL_PROJECTION);          /* 投影変換行列の設定 */
		glLoadIdentity();                     /* 変換行列の初期化 */
		gluPerspective(45.0f, 1, 0.1f, 10000); //透視投影法の視体積gluPerspactive(th, w/h, near, far);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(
			// 視点の位置x,y,z;
			0, 0, 1000,

			// 視界の中心位置の参照点座標x,y,z
			0, 0, 0,

			//視界の上方向のベクトルx,y,z
			0, 1, 0);
		glColor4f(1, 1, 0, 1);
		glTranslatef(200, -150, 0);
		glRotatef(-8, 0, 1, 0);
		glScalef(0.4f, 0.4f, 0.4f);
		suezo->Draw();
		
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

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

	glEnable(GL_BLEND);
	glBlendFunc(
		GL_SRC_ALPHA,
		GL_ONE_MINUS_SRC_ALPHA
		);
	glColor4f(0, 0, 0, 1);
	glBegin(GL_QUADS);
	{
		glVertex2f(40, 242);
		glVertex2f(40, 62);
		glVertex2f(80, 62);
		glVertex2f(80, 242);
	}
	glColor4f(0, 0, 0, 0.3f);
	{
		glVertex2f(80, 242);
		glVertex2f(80, 62);
		glVertex2f(230, 62);
		glVertex2f(230, 242);
	}
	{
		glVertex2f(70, 59);
		glVertex2f(70, 42);
		glVertex2f(100, 42);
		glVertex2f(100, 59);
	}
	{
		glVertex2f(190, 59);
		glVertex2f(190, 42);
		glVertex2f(210, 42);
		glVertex2f(210, 59);
	}
	glEnd();
	glDisable(GL_BLEND);

	glColor3f(1, 1, 1);
	font->ChangeSize(lkn::TYPE_NORMAL);
	font->DrawStringW(41, 220, parameter_name[0]);
	font->DrawStringW(41, 190, parameter_name[1]);
	font->DrawStringW(41, 160, parameter_name[2]);
	font->DrawStringW(41, 130, parameter_name[3]);
	font->DrawStringW(41, 100, parameter_name[4]);
	font->DrawStringW(41, 70, parameter_name[5]);

	font->DrawStringW(81, 220, L"Lv.%2d　　　　　　　　　　　%3d",(suezo->HP / 50)+1, suezo->HP);
	font->DrawStringW(81, 190, L"Lv.%2d　　　　　　　　　　　%3d", (suezo->power_point / 50) + 1, suezo->power_point);
	font->DrawStringW(81, 160, L"Lv.%2d　　　　　　　　　　　%3d", (suezo->intelligence_point / 50) + 1, suezo->intelligence_point);
	font->DrawStringW(81, 130, L"Lv.%2d　　　　　　　　　　　%3d", (suezo->hit_probability_point / 50) + 1, suezo->hit_probability_point);
	font->DrawStringW(81, 100, L"Lv.%2d　　　　　　　　　　　%3d", (suezo->dodge_point / 50) + 1, suezo->dodge_point);
	font->DrawStringW(81, 70, L"Lv.%2d　　　　　　　　　　　%3d", (suezo->strong_point / 50) + 1, suezo->strong_point);

#define GAUGE(a) 107 + (((213 - 107) / 999.0f) * a)
	glBegin(GL_QUADS);
	glColor4f(1, 1, 0.5f, 1);//ライフ
	{
		glVertex2f(107, 235);
		glVertex2f(107, 219);
		glVertex2f(GAUGE(suezo->HP), 219);
		glVertex2f(GAUGE(suezo->HP), 235);
	}
	glColor4f(1, 0, 0.25f, 1);//ちから
	{
		glVertex2f(107, 205);
		glVertex2f(107, 189);
		glVertex2f(GAUGE(suezo->power_point), 189);
		glVertex2f(GAUGE(suezo->power_point), 205);
	}
	glColor4f(0, 1, 0.4f, 1);//かしこさ
	{
		glVertex2f(107, 175);
		glVertex2f(107, 159);
		glVertex2f(GAUGE(suezo->intelligence_point), 159);
		glVertex2f(GAUGE(suezo->intelligence_point), 175);
	}
	glColor4f(1, 0, 1, 1);//命中
	{
		glVertex2f(107, 145);
		glVertex2f(107, 129);
		glVertex2f(GAUGE(suezo->hit_probability_point), 129);
		glVertex2f(GAUGE(suezo->hit_probability_point), 145);
	}
	glColor4f(0, 1, 1, 1);//回避
	{
		glVertex2f(107, 115);
		glVertex2f(107, 99);
		glVertex2f(GAUGE(suezo->dodge_point), 99);
		glVertex2f(GAUGE(suezo->dodge_point), 115);
	}
	glColor4f(0, 0.5f, 1, 1);//丈夫さ
	{
		glVertex2f(107, 85);
		glVertex2f(107, 69);
		glVertex2f(GAUGE(suezo->strong_point), 69);
		glVertex2f(GAUGE(suezo->strong_point), 85);
	}

	////////////////////////////////////////////////////name,age
	glColor4f(1, 1, 1, 1);
	{
		glVertex2f(67, 48);
		glVertex2f(67, 15);
		glVertex2f(180, 15);
		glVertex2f(180, 48);
	}
	{
		glVertex2f(187, 48);
		glVertex2f(187, 15);
		glVertex2f(270, 15);
		glVertex2f(270, 48);
	}
	glColor4f(0.3f, 0.3f, 1, 1);
	{
		glVertex2f(68, 46);
		glVertex2f(68, 17);
		glVertex2f(179, 17);
		glVertex2f(179, 46);
	}
	{
		glVertex2f(188, 46);
		glVertex2f(188, 17);
		glVertex2f(269, 17);
		glVertex2f(269, 46);
	}

	glEnd();

	glColor3f(1, 1, 1);
	font->DrawStringW(81, 25, suezo->name);
	int month = suezo->age / 4;
	int year = month / 12;
	month -= (year * 12);
	font->DrawStringW(201, 25, L"%2d歳  %2dカ月",year,month);

	min_font->ChangeSize(lkn::TYPE_MIN);
	min_font->DrawStringW(71,48,L"NAME");
	min_font->DrawStringW(191, 48, L"AGE");

	glBegin(GL_LINES);
	{
		glColor3f(1, 1, 1);
		glVertex2f(40, 212); glVertex2f(80, 212);
		glVertex2f(40, 182); glVertex2f(80, 182);
		glVertex2f(40, 152); glVertex2f(80, 152);
		glVertex2f(40, 122); glVertex2f(80, 122);
		glVertex2f(40, 92); glVertex2f(80, 92);
		glColor3f(0, 0, 0);
		glVertex2f(80, 212); glVertex2f(230, 212);
		glVertex2f(80, 182); glVertex2f(230, 182);
		glVertex2f(80, 152); glVertex2f(230, 152);
		glVertex2f(80, 122); glVertex2f(230, 122);
		glVertex2f(80, 92); glVertex2f(230, 92);
	}
	glEnd();

}



void field() {
	glColor4f(1, 1, 1, 1);
	sibahu_image->changeImage();
	glBegin(GL_QUADS);//地面
	{
		glTexCoord2f(0.f, 0.f);
		glVertex3f(-farm_x, -500.f, -farm_z);
		glTexCoord2f(0.f, 1.f);
		glVertex3f(-farm_x, -500.f, farm_z);
		glTexCoord2f(1.f, 1.f);
		glVertex3f(farm_x, -500.f, farm_z);
		glTexCoord2f(1.f, 0.f);
		glVertex3f(farm_x, -500.f, -farm_z);
	}
	glEnd();

	farm_sky_image->changeImage();
	glBegin(GL_QUADS);//上面
	{
		glTexCoord2f(0.f, 0.f);
		glVertex3f(-farm_x, farm_y, -farm_z);
		glTexCoord2f(0.f, 1.f);
		glVertex3f(farm_x, farm_y, -farm_z);
		glTexCoord2f(1.f, 1.f);
		glVertex3f(farm_x, farm_y, farm_z);
		glTexCoord2f(1.f, 0.f);
		glVertex3f(-farm_x, farm_y, farm_z);
	}
	//左側面
	{
		glTexCoord2f(0.f, 0.f);
		glVertex3f(-farm_x, -500.f, farm_z);
		glTexCoord2f(0.f, 1.f);
		glVertex3f(-farm_x, -500.f, -farm_z);
		glTexCoord2f(1.f, 1.f);
		glVertex3f(-farm_x, farm_y, -farm_z);
		glTexCoord2f(1.f, 0.f);
		glVertex3f(-farm_x, farm_y, farm_z);
	}
	//右側面
	{
		glTexCoord2f(0.f, 0.f);
		glVertex3f(farm_x, -500.f, -farm_z);
		glTexCoord2f(0.f, 1.f);
		glVertex3f(farm_x, -500.f, farm_z);
		glTexCoord2f(1.f, 1.f);
		glVertex3f(farm_x, farm_y, farm_z);
		glTexCoord2f(1.f, 0.f);
		glVertex3f(farm_x, farm_y, -farm_z);
	}
	//奥側面
	{
		glTexCoord2f(0.f, 0.f);
		glVertex3f(-farm_x, -500.f, -farm_z);
		glTexCoord2f(0.f, 1.f);
		glVertex3f(farm_x, -500.f, -farm_z);
		glTexCoord2f(1.f, 1.f);
		glVertex3f(farm_x, farm_y, -farm_z);
		glTexCoord2f(1.f, 0.f);
		glVertex3f(-farm_x, farm_y, -farm_z);
	}
	//手前側面
	{
		glTexCoord2f(0.f, 0.f);
		glVertex3f(farm_x, -500.f, farm_z);
		glTexCoord2f(0.f, 1.f);
		glVertex3f(-farm_x, -500.f, farm_z);
		glTexCoord2f(1.f, 1.f);
		glVertex3f(-farm_x, farm_y, farm_z);
		glTexCoord2f(1.f, 0.f);
		glVertex3f(farm_x, farm_y, farm_z);
	}
	glEnd();

	glDisable(
		GL_CULL_FACE);

	float koya_ookisa = 700.f;
	float koya_tenjou = 900.f;
	float koya_okuyuki = -farm_z + 100.f;
	koya_kabe_image->changeImage();
	glBegin(GL_QUADS);//小屋奥側面
	{
		glTexCoord2f(0.f, 0.f);
		glVertex3f(-koya_ookisa, -500.f, koya_okuyuki);
		glTexCoord2f(0.f, 1.f);
		glVertex3f(koya_ookisa, -500.f, koya_okuyuki);
		glTexCoord2f(1.f, 1.f);
		glVertex3f(koya_ookisa, koya_tenjou, koya_okuyuki);
		glTexCoord2f(1.f, 0.f);
		glVertex3f(-koya_ookisa, koya_tenjou, koya_okuyuki);
	}
	//小屋右側面
	{
		glTexCoord2f(0.f, 0.f);
		glVertex3f(koya_ookisa, -500.f, koya_okuyuki);
		glTexCoord2f(0.f, 1.f);
		glVertex3f(koya_ookisa, -500.f, koya_okuyuki + koya_ookisa);
		glTexCoord2f(1.f, 1.f);
		glVertex3f(koya_ookisa, koya_tenjou, koya_okuyuki + koya_ookisa);
		glTexCoord2f(1.f, 0.f);
		glVertex3f(koya_ookisa, koya_tenjou, koya_okuyuki);
	}
	//小屋左側面
	{
		glTexCoord2f(0.f, 0.f);
		glVertex3f(-koya_ookisa, -500.f, koya_okuyuki + koya_ookisa);
		glTexCoord2f(0.f, 1.f);
		glVertex3f(-koya_ookisa, -500.f, koya_okuyuki);
		glTexCoord2f(1.f, 1.f);
		glVertex3f(-koya_ookisa, koya_tenjou, koya_okuyuki);
		glTexCoord2f(1.f, 0.f);
		glVertex3f(-koya_ookisa, koya_tenjou, koya_okuyuki + koya_ookisa);
	}
	//小屋天井
	{
		glTexCoord2f(0.f, 0.f);
		glVertex3f(-koya_ookisa, koya_tenjou, koya_okuyuki + koya_ookisa);
		glTexCoord2f(0.f, 1.f);
		glVertex3f(koya_ookisa, koya_tenjou, koya_okuyuki + koya_ookisa);
		glTexCoord2f(1.f, 1.f);
		glVertex3f(koya_ookisa, koya_tenjou, koya_okuyuki);
		glTexCoord2f(1.f, 0.f);
		glVertex3f(-koya_ookisa, koya_tenjou, koya_okuyuki);
	}

	//小屋手前
	{
		glTexCoord2f(0.f, 0.f);
		glVertex3f(-koya_ookisa, koya_tenjou - 200.f, koya_okuyuki + koya_ookisa);
		glTexCoord2f(0.f, 1.f);
		glVertex3f(koya_ookisa, koya_tenjou - 200.f, koya_okuyuki + koya_ookisa);
		glTexCoord2f(1.f, 1.f);
		glVertex3f(koya_ookisa, koya_tenjou, koya_okuyuki + koya_ookisa);
		glTexCoord2f(1.f, 0.f);
		glVertex3f(-koya_ookisa, koya_tenjou, koya_okuyuki + koya_ookisa);
	}
	{
		glTexCoord2f(0.f, 0.f);
		glVertex3f(-koya_ookisa, -500.f, koya_okuyuki + koya_ookisa);
		glTexCoord2f(0.f, 1.f);
		glVertex3f(-koya_ookisa + 250.f, -500.f, koya_okuyuki + koya_ookisa);
		glTexCoord2f(1.f, 1.f);
		glVertex3f(-koya_ookisa + 250.f, koya_tenjou - 200.f, koya_okuyuki + koya_ookisa);
		glTexCoord2f(1.f, 0.f);
		glVertex3f(-koya_ookisa, koya_tenjou - 200.f, koya_okuyuki + koya_ookisa);
	}
	{
		glTexCoord2f(0.f, 0.f);
		glVertex3f(koya_ookisa - 250.f, -500.f, koya_okuyuki + koya_ookisa);
		glTexCoord2f(0.f, 1.f);
		glVertex3f(koya_ookisa, -500.f, koya_okuyuki + koya_ookisa);
		glTexCoord2f(1.f, 1.f);
		glVertex3f(koya_ookisa, koya_tenjou - 200.f, koya_okuyuki + koya_ookisa);
		glTexCoord2f(1.f, 0.f);
		glVertex3f(koya_ookisa - 250.f, koya_tenjou - 200.f, koya_okuyuki + koya_ookisa);
	}
	glEnd();

	koya_tobira_image->changeImage();
	glBegin(GL_QUADS);//扉

	if (farm_frame * 2 < 450) {
		farm_movie = farm_frame * 2;
	}
	{
		glTexCoord2f(0.f, 0.f);
		glVertex3f(0 - farm_movie, -500.f, koya_okuyuki + koya_ookisa);
		glTexCoord2f(0.f, 1.f);
		glVertex3f(0 - farm_movie, koya_tenjou - 200.f, koya_okuyuki + koya_ookisa);
		glTexCoord2f(1.f, 1.f);
		glVertex3f(-koya_ookisa + 250.f, koya_tenjou - 200.f, koya_okuyuki + koya_ookisa);
		glTexCoord2f(1.f, 0.f);
		glVertex3f(-koya_ookisa + 250.f, -500.f, koya_okuyuki + koya_ookisa);
	}
	{
		glTexCoord2f(0.f, 0.f);
		glVertex3f(koya_ookisa - 250.f, -500.f, koya_okuyuki + koya_ookisa);
		glTexCoord2f(0.f, 1.f);
		glVertex3f(koya_ookisa - 250.f, koya_tenjou - 200.f, koya_okuyuki + koya_ookisa);
		glTexCoord2f(1.f, 1.f);
		glVertex3f(0 + farm_movie, koya_tenjou - 200.f, koya_okuyuki + koya_ookisa);
		glTexCoord2f(1.f, 0.f);
		glVertex3f(0 + farm_movie, -500.f, koya_okuyuki + koya_ookisa);
	}
	glEnd();
}
