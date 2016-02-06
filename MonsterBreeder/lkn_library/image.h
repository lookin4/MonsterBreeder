#ifndef LKN_IMAGE_H
#define LKN_IMAGE_H

#include<windows.h>
//#include"../glut.h"
#include "../GL/freeglut.h"

namespace lkn {

	enum {
		IMAGE_TYPE_RGB,
		IMAGE_TYPE_RGBA_W,
		IMAGE_TYPE_RGBA_B
	};

	struct RGB {
		unsigned char r, g, b;
	};

	struct RGBA {
		unsigned char r, g, b,a;
	};

	class Image{
	public:

		Image(char*filename,int image_type);

		BITMAPFILEHEADER bf;
		BITMAPINFOHEADER bi;
		RGB* pixels;

		GLuint image_id;

		void changeImage();

	private:

		void loadImage(char*filename);
		void loadImageAlphaW(char*filename);
		void loadImageAlphaB(char*filename);

		Image() {}

		unsigned char *w_data;

	};

}

#endif