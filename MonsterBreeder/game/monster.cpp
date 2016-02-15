
#include"../GL/freeglut.h"
#include"monster.h"
#include"../lkn_library/image.h"

extern lkn::Image* suezo_eye_image;

wchar_t parameter_name[6][16] = {
	L"ライフ\0",
	L"ちから\0",
	L"かしこさ\0",
	L"命中\0",
	L"回避\0",
	L"丈夫さ\0",
};


namespace game {
	void Suezo::Draw() {
		glColor3f(1, 1, 0);
		glBegin(GL_QUADS);
		{
			glVertex3f(-50.f, -50.f, -150);
			glVertex3f(50.f, -50.f, -150);
			glVertex3f(50.f, -350.f, -150);
			glVertex3f(-50.f, -350.f, -150);
		}
		{
			glVertex3f(-50.f, -50.f, -50.f);
			glVertex3f(-50.f, -50.f, -150);
			glVertex3f(-50.f, -350.f, -150);
			glVertex3f(-50.f, -350.f, -50.f);
		}
		{
			glVertex3f(50.f, -50.f, -50.f);
			glVertex3f(50.f, -350.f, -50.f);
			glVertex3f(50.f, -350.f, -150);
			glVertex3f(50.f, -50.f, -150);
		}
		{
			glVertex3f(-50.f, -50.f, -50.f);
			glVertex3f(-50.f, -350.f, -50.f);
			glVertex3f(50.f, -350.f, -50.f);
			glVertex3f(50.f, -50.f, -50.f);
		}
		{
			glVertex3f(-50.f, -350.f, -50.f);
			glVertex3f(-50.f, -350.f, -150);
			glVertex3f(50.f, -350.f, -150);
			glVertex3f(50.f, -350.f, -50.f);
		}
		{
			glVertex3f(-50.f, -50.f, -50.f);
			glVertex3f(50.f, -50.f, -50.f);
			glVertex3f(50.f, -50.f, -150);
			glVertex3f(-50.f, -50.f, -150);
		}
		glEnd();
		glPushMatrix();
		{
			glTranslatef(0, -30, 10);
			glRotatef(20, 1, 0, 0);

			glBegin(GL_QUADS);//スエゾーべたがき//頭
							  //口
			{
				glVertex3f(-150.f, 0.f, 150);
				glVertex3f(-150.f, -100.f, 150);
				glVertex3f(150.f, -100.f, 150);
				glVertex3f(150.f, 0.f, 150);
			}
			{
				glVertex3f(-150.f, 0.f, -150);
				glVertex3f(-150.f, -100.f, -150);
				glVertex3f(-150.f, -100.f, 150);
				glVertex3f(-150.f, 0.f, 150);
			}
			{
				glVertex3f(150.f, 0.f, -150);
				glVertex3f(150.f, 0.f, 150);
				glVertex3f(150.f, -100.f, 150);
				glVertex3f(150.f, -100.f, -150);
			}
			{
				glVertex3f(-150.f, 0.f, -150);
				glVertex3f(150.f, 0.f, -150);
				glVertex3f(150.f, -100.f, -150);
				glVertex3f(-150.f, -100.f, -150);
			}
			{
				glVertex3f(-150.f, -100.f, -150);
				glVertex3f(150.f, -100.f, -150);
				glVertex3f(150.f, -100.f, 150);
				glVertex3f(-150.f, -100.f, 150);
			}
			glColor4f(1, 0, 0, 1);
			{
				glVertex3f(-150.f, 0.f, -150);
				glVertex3f(-150.f, 0.f, 150);
				glVertex3f(150.f, 0.f, 150);
				glVertex3f(150.f, 0.f, -150);
			}
			glEnd();
		}
		glPopMatrix();
		//atama



		glColor4f(1, 1, 0, 1);
		glBegin(GL_QUADS);
		/*{
			glVertex3f(-150.f, 0.f, 150);
			glVertex3f(150.f, 0.f, 150);
			glVertex3f(150.f, 300.f, 150);
			glVertex3f(-150.f, 300.f, 150);
		}*/
		{
			glVertex3f(-150.f, 0.f, -150);
			glVertex3f(-150.f, 0.f, 150);
			glVertex3f(-150.f, 300.f, 150);
			glVertex3f(-150.f, 300.f, -150);
		}
		{
			glVertex3f(150.f, 0.f, -150);
			glVertex3f(150.f, 300.f, -150);
			glVertex3f(150.f, 300.f, 150);
			glVertex3f(150.f, 0.f, 150);
		}
		{
			glVertex3f(-150.f, 0.f, -150);
			glVertex3f(-150.f, 300.f, -150);
			glVertex3f(150.f, 300.f, -150);
			glVertex3f(150.f, 0.f, -150);
		}
		{
			glVertex3f(-150.f, 300.f, -150);
			glVertex3f(-150.f, 300.f, 150);
			glVertex3f(150.f, 300.f, 150);
			glVertex3f(150.f, 300.f, -150);
		}
		{
			glVertex3f(-150.f, 0.f, -150);
			glVertex3f(150.f, 0.f, -150);
			glVertex3f(150.f, 0.f, 150);
			glVertex3f(-150.f, 0.f, 150);
		}
		glEnd();

		suezo_eye_image->changeImage();
		glColor4f(1, 1, 1, 1);
		glBegin(GL_QUADS);//モンスター
		{
			glTexCoord2f(0.f, 0.f);
			glVertex3f(-150.f, 300.f, 150);
			glTexCoord2f(0.f, 1.f);
			glVertex3f(-150.f, 0.f, 150);
			glTexCoord2f(1.f, 1.f);
			glVertex3f(150.f, 0.f, 150);
			glTexCoord2f(1.f, 0.f);
			glVertex3f(150.f, 300.f, 150);
		}
		glEnd();
	}



	void Monorisu::Draw() {

		glColor3f(0, 0, 0);
		glBegin(GL_QUADS);
		{
			glVertex3f(-150.f, 350.f, -50);
			glVertex3f(150.f, 350.f, -50);
			glVertex3f(150.f, -350.f, -50);
			glVertex3f(-150.f, -350.f, -50);
		}
		{
			glVertex3f(-150.f, 350.f, 50);
			glVertex3f(-150.f, 350.f, -50);
			glVertex3f(-150.f, -350.f, -50);
			glVertex3f(-150.f, -350.f, 50);
		}
		{
			glVertex3f(150.f, 350.f, 50);
			glVertex3f(150.f, -350.f, 50);
			glVertex3f(150.f, -350.f, -50);
			glVertex3f(150.f, 350.f, -50);
		}
		{
			glVertex3f(-150.f, 350.f, 50);
			glVertex3f(-150.f, -350.f, 50);
			glVertex3f(150.f, -350.f, 50);
			glVertex3f(150.f, 350.f, 50);
		}
		{
			glVertex3f(-150.f, -350.f, 50);
			glVertex3f(-150.f, -350.f, -50);
			glVertex3f(150.f, -350.f, -50);
			glVertex3f(150.f, -350.f, 50);
		}
		{
			glVertex3f(-150.f, 350.f, 50);
			glVertex3f(150.f, 350.f, 50);
			glVertex3f(150.f, 350.f, -50);
			glVertex3f(-150.f, 350.f, -50);
		}
		glEnd();
	}
}