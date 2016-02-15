#ifndef GAME_MONSTER_H
#define GAME_MONSTER_H


#include "../lkn_library/vector3.h"
#include "../lkn_library/image.h"
#include <vector>

namespace game {

	enum {
		D_NEAR,
		D_MIDDLE_NEAR,
		D_MIDDLE_FAR,
		D_FAR
	};

	enum {
		WAZA_TIKARA,
		WAZA_KASIKOSA
	};

	enum {
		SIPPO,
		TUBA,
		TAORE,
		BIIMU
	};

	class Waza {
	public:

		Waza() {}
		Waza(const wchar_t* _name, int _distance, int _damage, int _hit_probability, int _type, int _guts,int _w_type) :
			distance(_distance),
			damage(_damage),
			hit_probability(_hit_probability),
			type(_type),
			guts(_guts),
			w_type(_w_type)
		{
			//wcscpy(name, _name);
		}
		~Waza() {}

		wchar_t name[16];
		int distance;
		int damage;
		int hit_probability;
		int type;
		int guts;
		int w_type;
		lkn::Image* image;

	};

	enum {
		TYPE_HP,//���C�t
		TYPE_POWER,//������
		TYPE_INTELLIGENCE,//��������
		TIPE_HIT_PROBABILITY,//����
		TYPE_DODGE,//���
		TYPE_STRONG//��v��
	};

	enum {
		PLAYER,
		ENEMY
	};

	class Monster {
	public:
		Monster() :
			pos(0, 0, 0),
			scl(1, 1, 1),
			rot(0, 0, 0),
			age(0),
			fatigue(0)
		{}
		~Monster() {}

		lkn::Vec3 pos;
		lkn::Vec3 scl;
		lkn::Vec3 rot;

		std::vector <Waza*> waza;

		wchar_t name[16];

		int type;
		unsigned short age;//�N��
		unsigned short life;//����
		char personality_type;//���i
		unsigned char body_type;//�̌^
		unsigned char loyalty;//�����x
		int fatigue;//��J�x
		unsigned char stress;//�X�g���X
		unsigned char speed;//�ړ����x
		unsigned char re_guts;//�K�b�c��

		short HP;//���C�t
		short power_point;//������
		short intelligence_point;//��������
		short hit_probability_point;//����
		short dodge_point;//���
		short strong_point;//��v��


		virtual void Draw() = 0;
	};

	class Suezo :public Monster {
	public:
		Suezo() 
		{
			HP = 80;
			power_point = 120;
			intelligence_point = 170;
			hit_probability_point = 130;
			dodge_point = 90;
			strong_point = 100;

			re_guts = 4;

			Waza* tuba = new Waza(L"�΂͂�", D_MIDDLE_NEAR, 20, 60, WAZA_KASIKOSA, 10,TUBA);
			Waza* sippo = new Waza(L"�����ۃA�^�b�N", D_NEAR, 25, 50, WAZA_TIKARA, 12,SIPPO);

			waza.push_back(tuba);
			waza.push_back(sippo);
		}
		~Suezo() {}

		//Waza* tuba;
		//Waza* sippo;

		virtual void Draw();
	};

	class Monorisu :public Monster {
	public:
		Monorisu() 
		{
			HP = 110;
			power_point = 130;
			intelligence_point = 140;
			hit_probability_point = 90;
			dodge_point = 10;
			strong_point = 220;
			re_guts = 6;

			Waza* biimu = new Waza(L"�r�[��", D_FAR, 50, 20, WAZA_KASIKOSA, 20,BIIMU);
			Waza* taore = new Waza(L"�����ꂱ��", D_NEAR, 35, 30, WAZA_TIKARA, 12,TAORE);

			waza.push_back(biimu);
			waza.push_back(taore);
		}
		~Monorisu() {}

		

		virtual void Draw();
	};

	

	

}

extern wchar_t parameter_name[6][16];

#endif