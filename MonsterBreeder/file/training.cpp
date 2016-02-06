#include"training.h"
#include"../GL/freeglut.h"
#include"../game/monster.h"
#include"almighty.h"

#include<math.h>
#include<time.h>

void success();
void failure();
void parameter_up();
void(*result)();

extern game::Suezo* suezo;
float training_frame;
bool training_init = 0;
float training_movie;

void training() {
	if (training_init == 0) {
		training_frame = 0;
		result = NULL;
		srand(time(NULL));

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

	if (lkn::InputManager::getInstance()->keyPless(0x0d)) {////Enter Dicision
		if (result == NULL) {
			if (rand() % 20 > 19) {
				result = success;
			}
			else {
				result = failure;
			}
		}
		else if (result == success) {
			result = parameter_up;
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

	glColor4f(0, 0, 0, 1);
	glBegin(GL_QUADS);
	{
		glVertex2f(70, 70);
		glVertex2f(230, 70);
		glVertex2f(230, 230);
		glVertex2f(70, 230);
	}
	glEnd();
	glColor3f(1, 0.8f, 0.2f);
	max_font->DrawStringW(100, 130, L"成功！！");

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