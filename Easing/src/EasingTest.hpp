#pragma once
#include "lib\defines.hpp"
#include <functional>
#include <unordered_map>

//参考URL：http://blog.livedoor.jp/tek_nishi/archives/8145673.html

//　イージングの種類
enum class EaseType{
	//　等速
	LINEAR,

	// ○次の○の数字が増加すると緩急が強くなる
	//　二次関数(Quadratic)
	IN_QUAD, //だんだん速くなる
	OUT_QUAD, //だんだん遅くなる
	INOUT_QUAD, //最初遅く、中間で速くなり、最後に遅くなる

	//　三次関数(Cubic)
	IN_CUBIC,
	OUT_CUBIC,
	INOUT_CUBIC,

	//　四次関数(Quartic)
	IN_QUART,
	OUT_QUART,
	INOUT_QUART,

	// 五次関数(Quintic)
	IN_QUINT,
	OUT_QUINT,
	INOUT_QUINT,

	//　使用用途：バネや振り子の動き
	//　三角関数Sin()
	IN_SINE,
	OUT_SINE,
	INOUT_SINE,

	//　緩急が激しい
	//　指数関数(Exponential)
	IN_EXPO,
	OUT_EXPO,
	INOUT_EXPO,

	//　円(Circular)
	IN_CIRC,
	OUT_CIRC,
	INOUT_CIRC,

	//　行き過ぎて、少し戻る
	//　Back
	IN_BACK,
	OUT_BACK,
	INOUT_BACK,

	//　バネの動き
	//　Elastic
	IN_ELASTIC,
	OUT_ELASTIC,
	INOUT_ELASTIC,

	//　目的に到達したら跳ねる
	//　Bounce
	IN_BOUNCE,
	OUT_BOUNCE,
	INOUT_BOUNCE,
};

//　イージング機能
template <typename T>
class Easing{

	//　t:経過時間(current time)
	//　b:初期値(beginning value)
	//　c:初期値からの差(change in value)
	//　d:終了時間(duration)

	using ease_func = std::function < T(float, const T&, const T&, const float) > ;
	ease_func ease_update;
	float current_time = 0.0f;
	T save;

	//　typeに対応した計算関数を返す
	ease_func CreateEase(const EaseType type){

		static 	std::unordered_map<EaseType, ease_func>ease_list = {
			{
				EaseType::LINEAR,
				[](float t, const T& b, const T& c, const float d){
					return c*t / d + b;
				}
			},
			{
				EaseType::IN_QUAD,
				[](float t, const T& b, const T& c, const float d){
					t /= d;
					return c*t*t + b;
				}
			},
			{
				EaseType::OUT_QUAD,
				[](float t, const T& b, const T& c, const float d){
					t /= d;
					return -c*t*(t - 2) + b;
				}
			},
			{
				EaseType::INOUT_QUAD,
				[](float t, const T& b, const T& c, const float d){
					t /= d / 2;
					if (t < 1)return static_cast<T>(c / 2 * t*t + b);
					--t;
					return static_cast<T>(-c / 2 * (t*(t - 2) - 1) + b);
				}
			},
			{
				EaseType::IN_CUBIC,
				[](float t, const T& b, const T& c, const float d){
					t /= d;
					return c*t*t*t + b;
				}
			},
			{
				EaseType::OUT_CUBIC,
				[](float t, const T& b, const T& c, const float d){
					t = t / d - 1;
					return c*(t*t*t + 1) + b;
				}
			},
			{
				EaseType::INOUT_CUBIC,
				[](float t, const T& b, const T& c, const float d){
					if ((t /= d / 2) < 1) return static_cast<T>(c / 2 * t*t*t + b);
					t -= 2;
					return static_cast<T>(c / 2 * (t*t*t + 2) + b);
				}
			},
			{
				EaseType::INOUT_CUBIC,
				[](float t, const T& b, const T& c, const float d){
					if ((t /= d / 2) < 1) return static_cast<T>(c / 2 * t*t*t + b);
					t -= 2;
					return static_cast<T>(c / 2 * (t*t*t + 2) + b);
				}
			},
			{
				EaseType::IN_QUART,
				[](float t, const T& b, const T& c, const float d){
					t /= d;
					return c*t*t*t*t + b;
				}
			},
			{
				EaseType::OUT_QUART,
				[](float t, const T& b, const T& c, const float d){
					t = t / d - 1;
					return -c * (t*t*t*t - 1) + b;
				}
			},
			{
				EaseType::INOUT_QUART,
				[](float t, const T& b, const T& c, const float d){
					if ((t /= d / 2) < 1) return static_cast<T>(c / 2 * t*t*t*t + b);
					t -= 2;
					return static_cast<T>(-c / 2 * (t*t*t*t - 2) + b);
				}
			},
			{
				EaseType::IN_QUINT,
				[](float t, const T& b, const T& c, const float d){
					t /= d;
					return c*t*t*t*t*t + b;
				}
			},
			{
				EaseType::OUT_QUINT,
				[](float t, const T& b, const T& c, const float d){
					t = t / d - 1;
					return c*(t*t*t*t*t + 1) + b;
				}
			},
			{
				EaseType::INOUT_QUINT,
				[](float t, const T& b, const T& c, const float d){
					if ((t /= d / 2) < 1) return static_cast<T>(c / 2 * t*t*t*t*t + b);
					t -= 2;
					return static_cast<T>(c / 2 * (t*t*t*t*t + 2) + b);
				}
			},
			{
				EaseType::IN_SINE,
				[](float t, const T& b, const T& c, const float d){
					return -c * std::cos(t / d * (M_PI / 2)) + c + b;
				}
			},
			{
				EaseType::OUT_SINE,
				[](float t, const T& b, const T& c, const float d){
					return c * std::sin(t / d * (M_PI / 2)) + b;
				}
			},
			{
				EaseType::INOUT_SINE,
				[](float t, const T& b, const T& c, const float d){
					return -c / 2 * (std::cos(M_PI*t / d) - 1) + b;
				}
			},
			{
				EaseType::IN_EXPO,
				[](float t, const T& b, const T& c, const float d){
					return (t == 0) ? b : c * std::pow(2, 10 * (t / d - 1)) + b;
				}
			},
			{
				EaseType::OUT_EXPO,
				[](float t, const T& b, const T& c, const float d){
					return (t == d) ? T(b + c) : c * (-std::pow(2, -10 * t / d) + 1) + b;
				}
			},
			{
				EaseType::INOUT_EXPO,
				[](float t, const T& b, const T& c, const float d){
					if (t == 0)         return static_cast<T>(b);
					if (t == d)         return static_cast<T>(b + c);
					if ((t /= d / 2) < 1) return static_cast<T>(c / 2 * std::pow(2, 10 * (t - 1)) + b);
					return static_cast<T>(c / 2 * (-std::pow(2, -10 * --t) + 2) + b);
				}
			},
			{
				EaseType::IN_CIRC,
				[](float t, const T& b, const T& c, const float d){
					t /= d;
					return c*t*t*t + b;
				}
			},
			{
				EaseType::OUT_CIRC,
				[](float t, const T& b, const T& c, const float d){
					t = t / d - 1;
					return c*(t*t*t + 1) + b;
				}
			},
			{
				EaseType::INOUT_CIRC,
				[](float t, const T& b, const T& c, const float d){
					if ((t /= d / 2) < 1) return static_cast<T>(c / 2 * t*t*t + b);
					t -= 2;
					return static_cast<T>(c / 2 * (t*t*t + 2) + b);
				}
			},
			{
				EaseType::IN_BACK,
				[](float t, const T& b, const T& c, const float d){
					float s = 1.70158f;
					t /= d;
					return c*t*t*((s + 1)*t - s) + b;
				}
			},
			{
				EaseType::OUT_BACK,
				[](float t, const T& b, const T& c, const float d){
					float s = 1.70158f;
					t = t/d-1;
					return c*(t*t*((s + 1)*t + s) + 1) + b;
				}
			},
			{
				EaseType::INOUT_BACK,
				[](float t, const T& b, const T& c, const float d){
					float s = 1.70158f * 1.525f;
					if ((t /= d / 2) < 1) return c / 2 * (t*t*((s + 1)*t - s)) + b;
					t -= 2;
					return c / 2 * (t*t*((s + 1)*t + s) + 2) + b;
				}
			},
			{
				EaseType::IN_ELASTIC,
				[](float t, const T& b, const T& c, const float d){
					if (t == 0)      return static_cast<T>(b);
					if ((t /= d) == 1) return static_cast<T>(b + c);
					float p = d*0.3f;

					T a(c);
					float s = p / 4;
					t -= 1;
					return static_cast<T>(-(a * std::pow(2, 10 * t) * std::sin((t*d - s)*(2 * M_PI) / p)) + b);
				}
			},
			{
				EaseType::OUT_ELASTIC,
				[](float t, const T& b, const T& c, const float d){
					if (t == 0)      return static_cast<T>(b);
					if ((t /= d) == 1) return static_cast<T>(b + c);
					float p = d*0.3f;

					T a(c);
					float s = p / 4;
					return static_cast<T>((a* std::pow(2, -10 * t) * std::sin((t*d - s)*(2 * M_PI) / p) + c + b));
				}
			},
			{
				EaseType::INOUT_ELASTIC,
				[](float t, const T& b, const T& c, const float d){
					if (t == 0) return static_cast<T>(b);
					if ((t /= d / 2) == 2) return static_cast<T>(b + c);
					float p = d*(0.3f*1.5f);

					T a(c);
					float s = p / 4;
					if (t < 1)
					{
						t -= 1;
						return static_cast<T>(-.5*(a * std::pow(2, 10 * t) * std::sin((t*d - s)*(2 * M_PI) / p)) + b);
					}
					t -= 1;
					return static_cast<T>(a * std::pow(2, -10 * t) * std::sin((t*d - s)*(2 * M_PI) / p)*0.5f + c + b);
				}
			},
			{
				EaseType::IN_BOUNCE,
				[](float t, const T& b, const T& c, const float d){
					return c - (ease_list.find(EaseType::OUT_BOUNCE)->second)(d - t, T(b * 0), c, d) + b;
				}
			},
			{
				EaseType::OUT_BOUNCE,
				[](float t, const T& b, const T& c, const float d){
					if ((t /= d) < (1 / 2.75f)) {
						return static_cast<T>(c*(7.5625*t*t) + b);
					}
					else if (t < (2 / 2.75f)) {
						t -= (1.5f / 2.75f);
						return static_cast<T>(c*(7.5625f*t*t + .75f) + b);
					}
					else if (t < (2.5f / 2.75f)) {
						t -= (2.25f / 2.75f);
						return static_cast<T>(c*(7.5625f*t*t + .9375f) + b);
					}
					else {
						t -= (2.625f / 2.75f);
						return static_cast<T>(c*(7.5625f*t*t + .984375f) + b);
					}
				}
			},
			{
				EaseType::INOUT_BOUNCE,
				[](float t, const T& b, const T& c, const float d){
					if (t < d / 2) return static_cast<T>((ease_list.find(EaseType::IN_BOUNCE)->second)(t * 2, T(b * 0), c, d) * .5f + b);
					else         return static_cast<T>((ease_list.find(EaseType::OUT_BOUNCE)->second)(t * 2 - d, T(b * 0), c, d) * .5f + c*.5f + b);
				}
			},
		};
		return ease_list.find(type)->second;
	}

public:
	explicit Easing(const EaseType type)
	{
		SetEaseType(type);
	}

	void SetEaseType(const EaseType type){
		current_time = 0;
		ease_update = CreateEase(type);
	}

	// b 開始値
	// target_value 最終値
	// d 持続時間
	// delay 遅らせる時間
	T operator()(const T& b, const T& target_value, const float d, const float delay = 0.0f){
		current_time += 1.0f/60.0f;

		//　目的地に着いたらずっとそこにいる
		if (current_time > d + delay)return ease_update(d, b, target_value - b, d);
		
		//　遅らせるまで最初の位置のまま
		if (current_time < delay)return ease_update(0, b, target_value - b, d);

		//　イージング開始
		return ease_update(current_time - delay, b, target_value - b, d);
	}

	// b 開始値
	// c 変位量
	// t 持続時間
	// delay 遅らせる時間
	T MoveTo(const T& b, const T& c, const float d, const float delay = 0.0f){
		current_time += 1.0f / 60.0f;
		//　目的地に着いたらずっとそこにいる
		if (current_time > d + delay)return ease_update(d, b, c, d);

		//　遅らせるまで最初の位置のまま
		if (current_time < delay)return ease_update(0, b, c, d);

		//　イージング開始
		return ease_update(current_time - delay, b, c, d);
	}

};