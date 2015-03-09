#pragma once
#include "lib\vector.hpp"
#include "Window.h"
#include "Object.h"
#include <memory>
#include <iostream>



//�@HACK�F�؂�ւ��ƒǐՂ̏������قȂ��Ă���B
class Camera{

	enum class State{
		FOLLOWING, //�@�ǐՒ�
		SWITCHING, //�@�؂�ւ���
	};
	State state = State::FOLLOWING;
	Vec2f pos = Vec2f(Window::WIDTH * 0.5f,Window::HEIGHT * 0.5f);
	Vec2f size = Vec2f(Window::WIDTH * 0.5f, Window::HEIGHT * 0.5f);

	//�@(0,0)����_�������̂ŃJ�����̃|�W�V������Window�̃T�C�Y�̔�����ݒ肷��  
	//�@������Window�̔���
	//�@����͔w�i�̃T�C�Y-Window�̃T�C�Y�łł�B���̂Ƃ��ɃJ�����̃|�W�V�����𑫂��Ȃ��Ɛ���ɓ����Ȃ��B
	const Vec2f INFIMUM = Vec2f(Window::WIDTH * 0.5f, Window::HEIGHT * 0.5f);
	const Vec2f SUPREMUM = Vec2f(1024 - Window::WIDTH*0.5f, 512 - Window::HEIGHT * 0.5f);

	struct Rect{
		const float left = 200.0f;
		const float right = 400.0f;
		const float botoom = 100.0f;
		const float top = 300.0f;
	};

	Rect START_SCROLL;

	std::weak_ptr<Object>look_at_object;
	int switching_count = 0;

public:

	//�@�؂�ւ���
	//�@LookAt�����s����Ƃ��͂��̏������s���Ă�������
	void TurnSwitch(){
		state = State::SWITCHING;
	}

	Camera() = default;

	void Update(){
		if(state == State::FOLLOWING){
			Vec2f delta = (look_at_object.lock()->Position())-(pos - size);

			if (delta.x() > START_SCROLL.right){
				pos.x() += 0.01f * delta.x();
			}
			else if (delta.x() < START_SCROLL.left){
				pos.x() += -0.01f * (delta.x() + START_SCROLL.right - START_SCROLL.left + 50.0f);
			}
			if (delta.y() > START_SCROLL.top){
				pos.y() += 0.01f * delta.y();
			}
			else if (delta.y() < START_SCROLL.botoom){
				pos.y() -= 0.01f * (delta.y() + START_SCROLL.top - START_SCROLL.botoom + 50.0f);
			}
		}
		else {
			switching_count++;
			Vec2f delta = (look_at_object.lock()->Position()) - pos;
			pos += delta * 0.1f;
			if (switching_count > 30){
				state = State::FOLLOWING;
				switching_count = 0;
			}
		}

		pos.x() = std::max(pos.x(), INFIMUM.x());
		pos.x() = std::min(pos.x(), SUPREMUM.x());
		pos.y() = std::max(pos.y(), INFIMUM.y());
		pos.y() = std::min(pos.y(), SUPREMUM.y());
	}

	void LookAt(std::weak_ptr<Object>object){
		look_at_object = object;
	}

	//�@�|�W�V�������擾
	Vec2f Position()const{ return pos; }

private:
	//�@�ǐ�
	void Follow(){
		if (state != State::FOLLOWING)return;

		//�@(0,0)����̋������������̂�-size������)
		Vec2f delta = (look_at_object.lock()->Position()) - (pos - size);

		//�@�������قȂ�ƃX�N���[�����x���㉺����̂łȂ�ׂ������悤�ɐݒ肷��
		if (delta.x() > START_SCROLL.right){
			pos.x() += 0.01f * delta.x();
		}
		else if (delta.x() < START_SCROLL.left){
			pos.x() += -0.01f * (delta.x() + START_SCROLL.right - START_SCROLL.left + 50.0f);
		}
		if (delta.y() > START_SCROLL.top){
			pos.y() += 0.01f * delta.y();
		}
		else if (delta.y() < START_SCROLL.botoom){
			pos.y() -= 0.01f * (delta.y() + START_SCROLL.top - START_SCROLL.botoom + 50.0f);
		}
	}

	//�@�؂�ւ���
	void Switch(){
		if (state != State::SWITCHING)return;

		switching_count++;
		Vec2f delta = (look_at_object.lock()->Position()) - pos;
		pos += delta * 0.1f;

		if (switching_count < 30)return;
		state = State::FOLLOWING;
		switching_count = 0;	
	}
};