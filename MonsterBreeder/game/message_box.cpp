#define _CRT_NON_CONFORMING_WCSTOK
#define _CRT_SECURE_NO_WARNINGS

#include"message_box.h"
#include<stdio.h>
#include<vector>
#include<string>
#include<sstream>

std::vector<std::wstring> wsplit(const std::wstring &str, const wchar_t sep) {
	std::vector<std::wstring> v;
	std::wstringstream ss(str);
	std::wstring buffer;
	while (std::getline(ss, buffer, sep)) {
		v.push_back(buffer);
	}
	return v;
}

namespace game {

	void MyMessageBox::Draw(int type,wchar_t *format, ...) {

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

		glColor4f(1, 1, 1, 1);
		if (type != NULL) {

			if (type == MESSAGE_TYPE_COLT) {
				koruto_image->changeImage();
			}

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
		}

		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		wchar_t buf[256];

		wchar_t *tp;
		std::vector <std::wstring> message;
		std::vector <const wchar_t*> message2;
		va_list args;
		wchar_t* value;
		int count;
		if (format == NULL) return;

		va_start(args, format);
		vswprintf_s(buf, format, args);
		va_end(args);

		/*while ((tp = wcstok(format, L"\n")) != NULL) {
			message.push_back(tp);
			format = NULL;
		}*/
		
		message = wsplit(buf, L'\n');

		message2.push_back(message[0].c_str());
		message2.push_back(message[1].c_str());

		font->DrawStringW(88, 60, message2[1]);
		/*for (count = 0; count < message_num; count++) {
			value = va_arg(args, wchar_t*);
			font->DrawStringW(88, 60-(count * 22),  value);
		}*/


		

	}

}
