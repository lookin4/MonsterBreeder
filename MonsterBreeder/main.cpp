#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>
//#include "glut.h"
#include "lkn_library\input_manager.h"
#include "lkn_library\sound.h"
#include "lkn_library\image.h"
#include "lkn_library\font.h"
#include "lkn_library\vector3.h"
#include "file\almighty.h"
#include "game\monster.h"
#include"game\message_box.h"

//#pragma comment(lib, "glut32.lib")

///////////////////////////Font
lkn::GLFONT* font;
lkn::GLFONT* min_font;
lkn::GLFONT* max_font;

///////////////////////////音楽
lkn::Sound* opening_music;
lkn::Sound* decision_music;
lkn::Sound* cancel_music;
lkn::Sound* select_music;
lkn::Sound* spring_music;

lkn::Sound* battle_music;
lkn::Sound* battle_lose_music;

///////////////////////////画像
lkn::Image* title_image;
lkn::Image* title_background_image;

lkn::Image* sibahu_image;
lkn::Image* sibahu2_image;
lkn::Image* farm_background_image;
lkn::Image* farm_sky_image;
lkn::Image* koya_kabe_image;
lkn::Image* koya_tobira_image;

lkn::Image* waku_image;

lkn::Image* battle_gauge_image;
lkn::Image* battle_background_image;
lkn::Image* battle_selectbar_image;

lkn::Image* message_box_image;
lkn::Image* koruto_image;

lkn::Image* no_image;

lkn::Image* suezo_eye_image;

lkn::Image* status_mask_image;



lkn::Vec3* eye;
lkn::Vec3* target;

game::Suezo* suezo;
game::Monorisu* monorisu;

game::MyMessageBox* message_box;


int frame = 0;
//----------------------------------------------------
// 関数プロトタイプ（後に呼び出す関数名と引数の宣言）
//----------------------------------------------------
void init(void);
void display(void);
void timer(int value);
void keyboard(unsigned char key, int _x, int _y);
void keyboardUp(unsigned char key, int _x, int _y);

void title();
void farm();
void battle();

void(*func)(void);
//----------------------------------------------------
// メイン関数
//----------------------------------------------------
int main(int argc, char *argv[]) {
	glutInit(
		&argc,   //int *argcp,
		argv     //char **argv
		);
	glutInitWindowSize(1520, 793);
	glutCreateWindow("MonsterBreeder！"); //const char *title
	glutDisplayFunc(display);  //void (GLUTCALLBACK *func)(void)



	glutKeyboardFunc(keyboard); //void (GLUTCALLBACK *func)(unsigned char key, int x, int y)
	glutKeyboardUpFunc(keyboardUp); //void (GLUTCALLBACK *func)(unsigned char key, int x, int y)
	glutIgnoreKeyRepeat(GL_TRUE);//(int ignore)
	glutTimerFunc(
		0,       //unsigned int millis,タイマー起動までの時間(ミリ秒)
		timer,   //void (GLUTCALLBACK *func)(int value),タイマー起動でどのコールバック関数を呼ぶか
		0        //int value　(関数への引数)
		);


	init();

	glutMainLoop();

}

// 60fps ( 1/60 秒 ) ごとに実行される関数 
void timer(int value) {

	glutPostRedisplay();

	// 1000ミリ秒で 1 秒
	glutTimerFunc(1000 / 60, timer, 0);

}


//----------------------------------------------------
// 初期設定の関数
//----------------------------------------------------
void init(void) {
	eye = new lkn::Vec3(0, 0, 1000);
	target = new lkn::Vec3(0, 0, 0);
	lkn::Sound::init();
	opening_music = new lkn::Sound("sound/title_music.wav");
	decision_music = new lkn::Sound("sound/kettei_music.wav");
	cancel_music = new lkn::Sound("sound/cancel.wav");
	select_music = new lkn::Sound("sound/select_music.wav");
	spring_music = new lkn::Sound("sound/spring_music.wav");

	battle_music = new lkn::Sound("sound/battle_music3.wav");
	battle_lose_music = new lkn::Sound("sound/battle_lose.wav");

	title_image = new lkn::Image("image/title2.bmp", lkn::IMAGE_TYPE_RGBA_W);
	title_background_image = new lkn::Image("image/title_background.bmp", lkn::IMAGE_TYPE_RGB);

	sibahu_image = new lkn::Image("image/sibahu.bmp", lkn::IMAGE_TYPE_RGB);
	sibahu2_image = new lkn::Image("image/sibahu2.bmp", lkn::IMAGE_TYPE_RGB);
	farm_background_image = new lkn::Image("image/farm_background.bmp", lkn::IMAGE_TYPE_RGB);
	farm_sky_image = new lkn::Image("image/sora2.bmp", lkn::IMAGE_TYPE_RGB);
	koya_kabe_image = new lkn::Image("image/koya_kabe.bmp", lkn::IMAGE_TYPE_RGB);
	koya_tobira_image = new lkn::Image("image/tobira.bmp", lkn::IMAGE_TYPE_RGB);

	waku_image = new lkn::Image("image/waku.bmp", lkn::IMAGE_TYPE_RGBA_W);

	battle_gauge_image = new lkn::Image("image/battle_gauge.bmp", lkn::IMAGE_TYPE_RGBA_W);
	battle_background_image = new lkn::Image("image/battle_background.bmp", lkn::IMAGE_TYPE_RGB);
	battle_selectbar_image = new lkn::Image("image/battle_selectbar.bmp", lkn::IMAGE_TYPE_RGBA_W);

	koruto_image = new lkn::Image("image/koruto.bmp", lkn::IMAGE_TYPE_RGBA_W);
	message_box_image = new lkn::Image("image/message_box.bmp", lkn::IMAGE_TYPE_RGBA_B);

	no_image = new lkn::Image("image/no_image.bmp", lkn::IMAGE_TYPE_RGB);

	suezo_eye_image = new lkn::Image("image/suezo_me.bmp", lkn::IMAGE_TYPE_RGB);

	status_mask_image = new lkn::Image("image/monster_data.bmp", lkn::IMAGE_TYPE_RGB);

	font = new lkn::GLFONT(L"ＭＳ明朝", 50, lkn::TYPE_NORMAL);
	min_font = new lkn::GLFONT(L"ＭＳ明朝", 35, lkn::TYPE_MIN);
	max_font = new lkn::GLFONT(L"ＭＳ明朝", 200, lkn::TYPE_MAX);

	suezo = new game::Suezo();
	monorisu = new game::Monorisu();

	message_box = new game::MyMessageBox();

	func = title;
}
//----------------------------------------------------
// 描画の関数
//----------------------------------------------------
void display(void) {

	glClearColor(0.0, 0.0, 0.0, 1);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);          /* 投影変換行列の設定 */
	glLoadIdentity();                     /* 変換行列の初期化 */
	gluPerspective(45.0f, 1, 0.1f, 10000); //透視投影法の視体積gluPerspactive(th, w/h, near, far);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		// 視点の位置x,y,z;
		eye->x, eye->y, eye->z,

		// 視界の中心位置の参照点座標x,y,z
		target->x, target->y, target->z,

		//視界の上方向のベクトルx,y,z
		0, 1, 0);
	frame++;
	func();

	glFlush();
	
}

void keyboard(unsigned char _key, int _x, int _y) {
	if (lkn::InputManager::getInstance()->keys[_key] == lkn::KEY_PLESS) {
		return;
	}
	lkn::InputManager::getInstance()->keys[_key] = lkn::KEY_DOWN;
}

void keyboardUp(unsigned char _key, int x, int y) {

	lkn::InputManager::getInstance()->keys[_key] = lkn::KEY_RELEASE;
}

