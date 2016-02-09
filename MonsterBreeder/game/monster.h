#ifndef GAME_MONSTER_H
#define GAME_MONSTER_H
#include "../lkn_library/vector3.h"

namespace game {

	enum {
		TYPE_HP,//ライフ
		TYPE_POWER,//ちから
		TYPE_INTELLIGENCE,//かしこさ
		TIPE_HIT_PROBABILITY,//命中
		TYPE_DODGE,//回避
		TYPE_STRONG//丈夫さ
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

		unsigned short age;//年齢
		unsigned short life;//寿命
		char personality_type;//性格
		unsigned char body_type;//体型
		unsigned char loyalty;//忠誠度
		unsigned char fatigue;//疲労度
		unsigned char stress;//ストレス
		unsigned char speed;//移動速度
		unsigned char re_guts;//ガッツ回復

		unsigned short HP;//ライフ
		unsigned short power_point;//ちから
		unsigned short intelligence_point;//かしこさ
		unsigned short hit_probability_point;//命中
		unsigned short dodge_point;//回避
		unsigned short strong_point;//丈夫さ


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