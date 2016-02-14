#ifndef GAME_MESSAGE_BOX_H
#define GAME_MESSAGE_BOX_H

#include"../file/almighty.h"
#include <stdarg.h>

extern lkn::Image* message_box_image;
extern lkn::Image* koruto_image;
extern lkn::Image* koruto_komarigao_image;

namespace game {

	enum {
		MESSAGE_TYPE_COLT = 1,
        MESSAGE_TYPE_COLT_KOMARIGAO
	};

	class MyMessageBox {
	public:
		MyMessageBox(){}
		~MyMessageBox() {}

		void Draw(int type,wchar_t* format,...);

	};


}

#endif