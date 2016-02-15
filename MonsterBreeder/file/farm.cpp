#define _CRT_SECURE_NO_WARNINGS

#include"farm.h"
#include"../game/monster.h"
#include"../game/message_box.h"
#include"training.h"
#include"../game/player.h"

#define _USE_MATH_DEFINES
#include<math.h>
#include<time.h>
#include<string.h>

void rest();
void start_mask();
void main_manu();
void training_mode();
void(*farm_scene)();

void rest_message();
void training_message();
void yes_message();
void battle_message();
void start_message();
void hayaku_battle_message();
void battle_mada_message();
void(*message)();

void status();
void(*status_mask)();

void field();

int mask_movie;

int farm_command;
bool farm_init = 0;
int farm_frame;
int mask_frame;
int angle;

bool rest_init = false;
int rest_count;
int rest_frame;
float mask_color;

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
extern game::Monster* monster;

extern game::MyMessageBox* message_box;

extern game::Player* player;

extern lkn::Image* status_mask_image;
extern lkn::Sound* rest_music;

int nen;
int getu;
int syu;

void farm() {
	glEnable(
		GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	if (farm_init == 0) {
		farm_scene = start_mask;
		message = start_message;

		farm_command = 0;
		farm_frame = 0;
		mask_frame = 0;
		angle = 0;

		if (monster->fatigue > 100) {
			monster->fatigue = 100;
		}
		if (monster->fatigue < 0) {
			monster->fatigue = 0;
		}

		alSourcei(
			spring_music->source,     // ALuint source
			AL_LOOPING, // ALenum param
			AL_TRUE);   // ALint value
		farm_init = 1;
		alSourcePlay(spring_music->source);

		monster->pos.x = 0.f;
		monster->pos.y = 0.f;
		monster->pos.z = -4500.f;

		eye->y = 1200;
		eye->x = 1400;
		eye->z = 2000;

		target->x = monster->pos.x;
		target->z = monster->pos.z;

		colt_flag = false;
		battle_flag = false;
		srand(time(NULL));

		nen = 1000 + (player->nengetu / 48);
		getu = 1 + (player->nengetu - (48 * (nen - 1000))) / 4;
		syu = 1 + (player->nengetu - (48 * (nen - 1000)) - (4 * (getu - 1)));

	}
	mask_frame++;
	field();


	glEnable(
		GL_CULL_FACE);
	if (mask_frame < 220 || rest_init == true) {
	}
	else {
		farm_frame++;
		//glTranslatef(sin(angle * M_PI / 180)*farm_frame, 0, cos(angle * M_PI / 180)*farm_frame);
		if (farm_frame % 70 >= 30) {
			if (-farm_x + 200 < (monster->pos.x + sin(angle* M_PI / 180) * 500 / (100.0f + monster->fatigue)) &&
				(monster->pos.x + sin(angle* M_PI / 180) * 500 / (100.0f + monster->fatigue)) < farm_x - 200 &&
				-farm_z + 200 < (monster->pos.z + cos(angle* M_PI / 180) * 500 / (100.0f + monster->fatigue)) &&
				(monster->pos.z + cos(angle* M_PI / 180) * 500 / (100.0f + monster->fatigue)) < farm_z - 200) {
				monster->pos.x += sin(angle* M_PI / 180) * 500 / (100.0f + monster->fatigue);
				monster->pos.z += cos(angle* M_PI / 180) * 500 / (100.0f + monster->fatigue);
			}
			else {
				angle += 90;
			}
		}

		target->x = monster->pos.x;
		target->z = monster->pos.z;
		if (farm_frame % 70 == 69) {
			angle += (rand() % 40) - 20;
		}

	}
	//printf("angle = %d  frame = %d", angle, farm_frame);
	glPushMatrix();
	glTranslatef(monster->pos.x, monster->pos.y - 100, monster->pos.z);
	glRotatef(angle, 0, 1, 0);


	///////////////////////////////////////モノリス

	//glColor4f(0, 0, 0, 1);
	//monorisu->Draw();

	/////////////////////////////////////スエゾー

	glColor4f(1, 1, 0, 1);
	monster->Draw();

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
	font->ChangeSize(lkn::TYPE_NORMAL);
	font->DrawStringW(20, 257, L" %d年", nen);
	font->DrawStringW(16, 229, L" %2d月%d週", getu, syu);

	farm_scene();

	if (message != NULL && mask_frame > 200) {
		message();
	}

	glDisable(
		GL_CULL_FACE);

	glColor3f(0, 0, 0);
	min_font->ChangeSize(lkn::TYPE_MIN);
	min_font->DrawStringW(100, 285, L"w:↑　s:↓　Enter:決定　Space:Cancel");


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

void rest() {
	if (rest_init == false) {
		alSourcePlay(rest_music->source);

		rest_frame = 0;
		rest_count = 0;
		rest_init = true;
		mask_color = 0.f;

		angle = 0;
		monster->pos.x = 0;
		monster->pos.z = -4500.f;
		target->x = 0;
		target->z = -4500.f;
	}
	if (rest_frame * 2 <= 450) {
		farm_movie = 450 - (rest_frame * 2);
	}
	rest_frame++;
	if (rest_frame > 230) {
		mask_color += 0.01f;
	}
	if (rest_frame > 400) {
		farm_init = 0;
		rest_init = 0;
		player->nengetu++;
		monster->age++;
		monster->fatigue -= 40;
	}
	glEnable(GL_BLEND);
	glBlendFunc(
		GL_SRC_ALPHA,
		GL_ONE_MINUS_SRC_ALPHA
		);
	glColor4f(0, 0, 0, mask_color);
	glBegin(GL_QUADS);
	{
		glVertex2f(0, 300);
		glVertex2f(0, 0);
		glVertex2f(300, 0);
		glVertex2f(300, 300);
	}
	glEnd();
	glDisable(GL_BLEND);

}

void main_manu() {

	glColor4f(0.5f, 0.5f, 0.5f, 0.5f);
	glBegin(GL_QUADS);
	{
		glVertex2f(235, 142);
		glVertex2f(280, 142);
		glVertex2f(280, 250);
		glVertex2f(235, 250);
	}
	glColor4f(1, 1, 1, 0.5f);
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
		//glVertex2f(235.3f, 115); glVertex2f(280, 115);
		//glVertex2f(235.3f, 88); glVertex2f(280, 88);
	}
	glEnd();

	glDisable(GL_BLEND);

	glColor3f(1, 1, 1);
	font->ChangeSize(lkn::TYPE_NORMAL);
	font->DrawStringW(243, 229, L" 育成");
	font->DrawStringW(243, 202, L" 休養");
	font->DrawStringW(243, 175, L" 大会");
	font->DrawStringW(228, 148, L" パラメータ");
	//font->DrawStringW(233, 121, L" ファイル");
	//font->DrawStringW(233, 94, L" パークへ");


	if (status_mask != NULL) {
		status_mask();

		if (lkn::InputManager::getInstance()->keyPless(0x20)) {////Space Cancel
			alSourcePlay(cancel_music->source);
			status_mask = NULL;
		}
	}
	else if (message == start_message) {
		if (lkn::InputManager::getInstance()->keyPless(0x0d)) {////Space Cancel
			alSourcePlay(decision_music->source);
			message = NULL;
		}
	}
	else if (message == hayaku_battle_message || message == battle_mada_message) {
		if (lkn::InputManager::getInstance()->keyPless(0x0d)) {////Space Cancel
			alSourcePlay(decision_music->source);
			message = NULL;
		}
	}
	else {
		if (lkn::InputManager::getInstance()->keyPless('w')) {////up select
			alSourcePlay(select_music->source);
			if (message == NULL) {
				farm_command--;
			}
			else if (message == battle_message || message == rest_message) {
				farm_yes_no--;
			}
		}
		if (lkn::InputManager::getInstance()->keyPless('s')) {////down select
			alSourcePlay(select_music->source);
			if (message == NULL) {
				farm_command++;
			}
			else if (message == battle_message || message == rest_message) {
				farm_yes_no++;
			}
		}

		farm_command = (FARM_MAX + farm_command) % FARM_MAX;
		farm_yes_no = (lkn::YES_NO_MAX + farm_yes_no) % lkn::YES_NO_MAX;

		if (lkn::InputManager::getInstance()->keyPless(0x0d)) {////Enter Dicision
			alSourcePlay(decision_music->source);
			
			if (farm_command == FARM_BATTLE) {
				if (player->nengetu < 23) {
					message = battle_mada_message;
				}
				else if (message == NULL) {
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
					alSourceStop(spring_music->source);
					farm_init = 0;
					message = NULL;
					func = battle;
				}
			}
			else if (farm_command == FARM_PARAMETER) {
				status_mask = status;
			}
			else if(player->nengetu == 23) {
				message = hayaku_battle_message;
			}
			else if (farm_command == FARM_TRAINING) {
				farm_yes_no = 0;
				farm_scene = training_mode;
			}
			else if (farm_command == FARM_REST) {
				if (message == NULL) {
					farm_yes_no = 0;
					message = rest_message;
				}
				else if (message == rest_message) {
					if (farm_yes_no == lkn::YES) {
						message = NULL;
						farm_scene = rest;
						alSourcePause(spring_music->source);
					}
					else if (farm_yes_no == lkn::NO) {
						message = NULL;
					}
				}
			}
			
		}

		if (lkn::InputManager::getInstance()->keyPless(0x20)) {////Space Cancel
			alSourcePlay(cancel_music->source);
			message = NULL;
		}

	}
	
}

void start_mask() {
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

	glColor4f(0, 0, 0, 1);
	glBegin(GL_QUADS);
	{
		glVertex2f(0, 0);
		glVertex2f(300, 0);
		glVertex2f(300, 300);
		glVertex2f(0, 300);
	}
	glEnd();

	if (mask_frame <= 70) {
		mask_movie = mask_frame;
	}
	else if (mask_frame >= 130) {
		mask_movie = 200 - mask_frame;
	}
	glColor3f(1, 1, 1);
	font->ChangeSize(lkn::TYPE_NORMAL);
	font->DrawStringW(-12 + (mask_movie / 2), 229, L" %4d年", nen);

	font->DrawStringW(308 - (mask_movie*1.5f), 79, L" %2d月 %d週", getu, syu);

	glColor3f(1, 0, 0);
	glLineWidth(5);
	glBegin(GL_LINES);
	{
		glVertex2f(0, 220); glVertex2f(mask_movie, 220);
		glVertex2f(280 - mask_movie, 70); glVertex2f(300, 70);
	}
	glEnd();
	if (lkn::InputManager::getInstance()->keyPless(0x0d)) {
		mask_frame = 200;
	}
	if (mask_frame == 200) {
		farm_scene = main_manu;
	}
}

void training_mode() {
	glColor4f(0.5f, 0.5f, 0.5f, 0.5f);
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

	glColor4f(1, 1, 1, 0.5f);
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
				farm_yes_no = 0;
			}
		}
		
		else if (message == yes_message) {
			farm_init = 0;
			message = NULL;
			alSourcePause(spring_music->source);
			func = training;
		}
	}

	if (lkn::InputManager::getInstance()->keyPless(0x20)) {////Space Cancel
		alSourcePlay(cancel_music->source);
		if (message != NULL) {
			message = NULL;
		}
		else if (farm_scene == training_mode) {
			farm_yes_no = 0;
			farm_scene = main_manu;
		}
	}
}

void battle_message() {
	message_box->Draw(game::MESSAGE_TYPE_COLT, L"大会に出る？");
	glEnable(GL_BLEND);
	glBlendFunc(
		GL_SRC_ALPHA,
		GL_ONE_MINUS_SRC_ALPHA
		);

	glColor4f(0.5f, 0.5f, 0.5f, 0.5f);
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

	glColor4f(1, 1, 1, 0.5f);
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
	message_box->Draw(game::MESSAGE_TYPE_COLT, L"それじゃあトレーニングを\nはじめようか？");
	glEnable(GL_BLEND);
	glBlendFunc(
		GL_SRC_ALPHA,
		GL_ONE_MINUS_SRC_ALPHA
		);

	glColor4f(0.5f, 0.5f, 0.5f, 0.5f);
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

	glColor4f(1, 1, 1, 0.5f);
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

void rest_message() {
	message_box->Draw(game::MESSAGE_TYPE_COLT, L"今週は%sを\n休ませるんだね？",monster->name);
	glEnable(GL_BLEND);
	glBlendFunc(
		GL_SRC_ALPHA,
		GL_ONE_MINUS_SRC_ALPHA
		);

	glColor4f(0.5f, 0.5f, 0.5f, 0.5f);
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

	glColor4f(1, 1, 1, 0.5f);
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
	message_box->Draw(game::MESSAGE_TYPE_COLT, L"それじゃあ頑張ろうね！");
}

void hayaku_battle_message() {
	message_box->Draw(game::MESSAGE_TYPE_COLT_KOMARIGAO, L"今週は大事な大会だよ...？");
}

void battle_mada_message() {
	message_box->Draw(game::MESSAGE_TYPE_COLT_KOMARIGAO, L"大会は6月4週だよ...？");
}

void start_message() {
	if (monster->fatigue <= 5) {
		message_box->Draw(game::MESSAGE_TYPE_COLT, L"%sはすっごく元気だよ！！", monster->name);
	}
	else if (monster->fatigue <= 25) {
		message_box->Draw(game::MESSAGE_TYPE_COLT, L"%sは元気だよ！", monster->name);
	}
	else if (monster->fatigue <= 45) {
		message_box->Draw(game::MESSAGE_TYPE_COLT, L"%sは元気みたい。", monster->name);
	}
	else if (monster->fatigue <= 65) {
		message_box->Draw(game::MESSAGE_TYPE_COLT_KOMARIGAO, L"%sは\n少し疲れているみたい・・・", monster->name);
	}
	else if (monster->fatigue <= 85) {
		message_box->Draw(game::MESSAGE_TYPE_COLT_KOMARIGAO, L"%sは\n疲れているみたい・・・", monster->name);
	}
	else {
		message_box->Draw(game::MESSAGE_TYPE_COLT_KOMARIGAO, L"%sは\nすっごく疲れているみたい・・・\n休ませてあげようよ・・・", monster->name);
	}
}


void status() {
	glEnable(GL_BLEND);
	glBlendFunc(
		GL_SRC_ALPHA,
		GL_ONE_MINUS_SRC_ALPHA
		);
	glColor4f(0, 0, 0, 0.3f);
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
		glTexCoord2f(0, 0);
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
		monster->Draw();

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
	font->DrawStringW(46, 220, parameter_name[0]);
	font->DrawStringW(46, 190, parameter_name[1]);
	font->DrawStringW(41, 160, parameter_name[2]);
	font->DrawStringW(51, 130, parameter_name[3]);
	font->DrawStringW(51, 100, parameter_name[4]);
	font->DrawStringW(46, 70, parameter_name[5]);

	font->DrawStringW(81, 220, L"Lv.%2d　　　　　　　　　　　%3d", (monster->HP / 50) + 1, monster->HP);
	font->DrawStringW(81, 190, L"Lv.%2d　　　　　　　　　　　%3d", (monster->power_point / 50) + 1, monster->power_point);
	font->DrawStringW(81, 160, L"Lv.%2d　　　　　　　　　　　%3d", (monster->intelligence_point / 50) + 1, monster->intelligence_point);
	font->DrawStringW(81, 130, L"Lv.%2d　　　　　　　　　　　%3d", (monster->hit_probability_point / 50) + 1, monster->hit_probability_point);
	font->DrawStringW(81, 100, L"Lv.%2d　　　　　　　　　　　%3d", (monster->dodge_point / 50) + 1, monster->dodge_point);
	font->DrawStringW(81, 70, L"Lv.%2d　　　　　　　　　　　%3d", (monster->strong_point / 50) + 1, monster->strong_point);

#define GAUGE(a) 107 + (((213 - 107) / 999.0f) * a)
	glBegin(GL_QUADS);
	glColor4f(1, 1, 0.5f, 1);//ライフ
	{
		glVertex2f(107, 235);
		glVertex2f(107, 219);
		glVertex2f(GAUGE(monster->HP), 219);
		glVertex2f(GAUGE(monster->HP), 235);
	}
	glColor4f(1, 0, 0.25f, 1);//ちから
	{
		glVertex2f(107, 205);
		glVertex2f(107, 189);
		glVertex2f(GAUGE(monster->power_point), 189);
		glVertex2f(GAUGE(monster->power_point), 205);
	}
	glColor4f(0, 1, 0.4f, 1);//かしこさ
	{
		glVertex2f(107, 175);
		glVertex2f(107, 159);
		glVertex2f(GAUGE(monster->intelligence_point), 159);
		glVertex2f(GAUGE(monster->intelligence_point), 175);
	}
	glColor4f(1, 0, 1, 1);//命中
	{
		glVertex2f(107, 145);
		glVertex2f(107, 129);
		glVertex2f(GAUGE(monster->hit_probability_point), 129);
		glVertex2f(GAUGE(monster->hit_probability_point), 145);
	}
	glColor4f(0, 1, 1, 1);//回避
	{
		glVertex2f(107, 115);
		glVertex2f(107, 99);
		glVertex2f(GAUGE(monster->dodge_point), 99);
		glVertex2f(GAUGE(monster->dodge_point), 115);
	}
	glColor4f(0, 0.5f, 1, 1);//丈夫さ
	{
		glVertex2f(107, 85);
		glVertex2f(107, 69);
		glVertex2f(GAUGE(monster->strong_point), 69);
		glVertex2f(GAUGE(monster->strong_point), 85);
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
	font->DrawStringW(81, 25, monster->name);
	int month = monster->age / 4;
	int year = month / 12;
	month -= (year * 12);
	font->DrawStringW(201, 25, L"%2d歳  %2dカ月", year, month);

	min_font->ChangeSize(lkn::TYPE_MIN);
	min_font->DrawStringW(71, 48, L"NAME");
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

	if (farm_frame * 2 < 450 && rest_init == false) {
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
