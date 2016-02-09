#ifndef GAME_MONSTER_H
#define GAME_MONSTER_H
#include "../lkn_library/vector3.h"

namespace game {

	enum {
		TYPE_HP,//���C�t
		TYPE_POWER,//������
		TYPE_INTELLIGENCE,//��������
		TIPE_HIT_PROBABILITY,//����
		TYPE_DODGE,//���
		TYPE_STRONG//��v��
	};



	class Monster {
	public:
		Monster() :
			pos(0, 0, 0),
			scl(1, 1, 1),
			rot(0, 0, 0),
			age(0)
		{}
		~Monster() {}

		lkn::Vec3 pos;
		lkn::Vec3 scl;
		lkn::Vec3 rot;

		wchar_t name[16];

		unsigned short age;//�N��
		unsigned short life;//����
		char personality_type;//���i
		unsigned char body_type;//�̌^
		unsigned char loyalty;//�����x
		unsigned char fatigue;//��J�x
		unsigned char stress;//�X�g���X
		unsigned char speed;//�ړ����x
		unsigned char re_guts;//�K�b�c��

		unsigned short HP;//���C�t
		unsigned short power_point;//������
		unsigned short intelligence_point;//��������
		unsigned short hit_probability_point;//����
		unsigned short dodge_point;//���
		unsigned short strong_point;//��v��


		virtual void Draw() = 0;
	};

	class Suezo :public Monster {
	public:
		Suezo() {}
		~Suezo() {}

		virtual void Draw();
	};

	class Monorisu :public Monster {
	public:
		Monorisu() {}
		~Monorisu() {}

		virtual void Draw();
	};

}

extern wchar_t parameter_name[6][16];

#endif