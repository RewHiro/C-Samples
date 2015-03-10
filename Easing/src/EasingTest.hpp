#pragma once
#include "lib\defines.hpp"
#include <functional>
#include <unordered_map>

//�Q�lURL�Fhttp://blog.livedoor.jp/tek_nishi/archives/8145673.html

//�@�C�[�W���O�̎��
enum class EaseType{
	//�@����
	LINEAR,

	// �����́��̐�������������Ɗɋ}�������Ȃ�
	//�@�񎟊֐�(Quadratic)
	IN_QUAD, //���񂾂񑬂��Ȃ�
	OUT_QUAD, //���񂾂�x���Ȃ�
	INOUT_QUAD, //�ŏ��x���A���Ԃő����Ȃ�A�Ō�ɒx���Ȃ�

	//�@�O���֐�(Cubic)
	IN_CUBIC,
	OUT_CUBIC,
	INOUT_CUBIC,

	//�@�l���֐�(Quartic)
	IN_QUART,
	OUT_QUART,
	INOUT_QUART,

	// �܎��֐�(Quintic)
	IN_QUINT,
	OUT_QUINT,
	INOUT_QUINT,

	//�@�g�p�p�r�F�o�l��U��q�̓���
	//�@�O�p�֐�Sin()
	IN_SINE,
	OUT_SINE,
	INOUT_SINE,

	//�@�ɋ}��������
	//�@�w���֐�(Exponential)
	IN_EXPO,
	OUT_EXPO,
	INOUT_EXPO,

	//�@�~(Circular)
	IN_CIRC,
	OUT_CIRC,
	INOUT_CIRC,

	//�@�s���߂��āA�����߂�
	//�@Back
	IN_BACK,
	OUT_BACK,
	INOUT_BACK,

	//�@�o�l�̓���
	//�@Elastic
	IN_ELASTIC,
	OUT_ELASTIC,
	INOUT_ELASTIC,

	//�@�ړI�ɓ��B�����璵�˂�
	//�@Bounce
	IN_BOUNCE,
	OUT_BOUNCE,
	INOUT_BOUNCE,
};

//�@�C�[�W���O�@�\
template <typename T>
class Easing{

	//�@t:�o�ߎ���(current time)
	//�@b:�����l(beginning value)
	//�@c:�����l����̍�(change in value)
	//�@d:�I������(duration)

	using ease_func = std::function < T(float, const T&, const T&, const float) > ;
	ease_func ease_update;
	float current_time = 0.0f;
	T save;

	//�@type�ɑΉ������v�Z�֐���Ԃ�
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

	// b �J�n�l
	// target_value �ŏI�l
	// d ��������
	// delay �x�点�鎞��
	T operator()(const T& b, const T& target_value, const float d, const float delay = 0.0f){
		current_time += 1.0f/60.0f;

		//�@�ړI�n�ɒ������炸���Ƃ����ɂ���
		if (current_time > d + delay)return ease_update(d, b, target_value - b, d);
		
		//�@�x�点��܂ōŏ��̈ʒu�̂܂�
		if (current_time < delay)return ease_update(0, b, target_value - b, d);

		//�@�C�[�W���O�J�n
		return ease_update(current_time - delay, b, target_value - b, d);
	}

	// b �J�n�l
	// c �ψʗ�
	// t ��������
	// delay �x�点�鎞��
	T MoveTo(const T& b, const T& c, const float d, const float delay = 0.0f){
		current_time += 1.0f / 60.0f;
		//�@�ړI�n�ɒ������炸���Ƃ����ɂ���
		if (current_time > d + delay)return ease_update(d, b, c, d);

		//�@�x�点��܂ōŏ��̈ʒu�̂܂�
		if (current_time < delay)return ease_update(0, b, c, d);

		//�@�C�[�W���O�J�n
		return ease_update(current_time - delay, b, c, d);
	}

};