#pragma once
#include "lib\vector.hpp"
#include "Window.h"
#include "Object.h"
#include <memory>
#include <iostream>
class Camera{

	enum class State{
		FOLLOWING,
		SWITCHING,
	};
	State state = State::FOLLOWING;
	Vec2f pos = test;
	Vec2f size = Vec2f(Window::WIDTH * 0.5f, Window::HEIGHT / 0.5f);
	Vec2f look_at_pos;
	//　(0,0)を基点したいのでカメラのポジションをWindowのサイズの半分を設定する  
	//　下限はWindowの半分
	//　上限は背景のサイズ-Windowのサイズででる。このときにカメラのポジションを足さないと正常に動かない。
	const Vec2f INFIMUM = Vec2f(Window::WIDTH * 0.5f, Window::HEIGHT * 0.5f);
	const Vec2f SUPREMUM = Vec2f(1024 - Window::WIDTH*0.5f, 512 - Window::HEIGHT * 0.5f);

	const Vec2f o = Vec2f(400, 300);
	const Vec2f i = Vec2f(200, 100);

	std::weak_ptr<Object>look_at_object;
	int count = 0;

public:

	void Set(){
		state = State::SWITCHING;
	}
	Camera() = default;

	void Update(){
		if(state == State::FOLLOWING){
			Vec2f delta = (look_at_object.lock()->Position())-(pos - test);

			DOUT << pos << std::endl;

			if (delta.x() > o.x()){
				pos.x() += 0.01f * delta.x();
			}
			else if (delta.x() < i.x()){
				pos.x() += -0.01f * (delta.x() + 250.0f);
			}
			if(delta.y() > o.y()){
				pos.y() += 0.01f * delta.y();
			}
			else if(delta.y() < i.y()){
				pos.y() -= 0.01f * (delta.y() + 250.0f);
			}
		}
		else {
			count++;
			Vec2f delta = (look_at_object.lock()->Position()) - pos;
			pos += delta * 0.1f;
			if(count > 30){
				state = State::FOLLOWING;
				count = 0;
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

	//　ポジションを取得
	Vec2f Position()const{ return pos; }
};