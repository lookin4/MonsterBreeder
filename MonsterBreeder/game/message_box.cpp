#include"message_box.h"

namespace game {

	void MyMessageBox::Draw(int type, int message_num, ...) {

		glEnable(GL_BLEND);
		glBlendFunc(
			GL_SRC_ALPHA,
			GL_ONE_MINUS_SRC_ALPHA
			);

		glColor4f(0, 0, 0, 0.5f);
		glBegin(GL_QUADS);
		{
			glVertex2f(29, 4);
			glVertex2f(271, 4);
			glVertex2f(271, 86);
			glVertex2f(29, 86);
		}
		glEnd();

		message_box_image->changeImage();

		glColor4f(0.7f, 0.7f, 0.7f, 1);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.f, 0.f);
			glVertex2f(30, 85);
			glTexCoord2f(0.f, 1.f);
			glVertex2f(30, 5);
			glTexCoord2f(1.f, 1.f);
			glVertex2f(270, 5);
			glTexCoord2f(1.f, 0.f);
			glVertex2f(270, 85);
		}
		glEnd();
		if (type == MESSAGE_TYPE_COLT) {
			koruto_image->changeImage();
		}
		glColor4f(1, 1, 1, 1);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.f, 0.f);
			glVertex2f(35, 110);
			glTexCoord2f(0.f, 1.f);
			glVertex2f(35, 5);
			glTexCoord2f(1.f, 1.f);
			glVertex2f(85, 5);
			glTexCoord2f(1.f, 0.f);
			glVertex2f(85, 110);
		}
		glEnd();

		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);

		va_list args;
		wchar_t* value;
		int count;

		if (message_num < 1) return;

		va_start(args, message_num);

		for (count = 0; count < message_num; count++) {
			value = va_arg(args, wchar_t*);
			font->DrawStringW(88, 60-(count * 22),  value);
		}

		va_end(args);

		

	}

}
