#pragma once
#include "lib\vector.hpp"
#include "Window.h"
class Camera{
	Vec2f pos = test;
	Vec2f size = Vec2f(Window::WIDTH * 0.5f, Window::HEIGHT / 0.5f);
	Vec2f look_at_pos;
	//　(0,0)を基点したいのでカメラのポジションをWindowのサイズの半分を設定する  
	//　下限はWindowの半分
	//　上限は背景のサイズ-Windowのサイズででる。このときにカメラのポジションを足さないと正常に動かない。
	const Vec2f INFIMUM = Vec2f(Window::WIDTH * 0.5f, Window::HEIGHT * 0.5f);
	const Vec2f SUPREMUM = Vec2f(1024 - Window::WIDTH*0.5f, 512 - Window::HEIGHT * 0.5f);

	const Vec2f o = Vec2f(400, -HEIGHT / 2 + 100);
	const Vec2f i = Vec2f(200, -HEIGHT / 2 + 50);

public:

	Camera() = default;

	void Update(){
		//Vec2f delta = (look_at_pos + Vec2f(64,64)) - (pos);
		Vec2f delta = (look_at_pos)-(pos - test);

		//pos += 0.1f * delta;

		DOUT << delta << std::endl;

		if (delta.x() > o.x()){
			pos.x() += 0.01f * delta.x();
			//DOUT << delta << std::endl;
		}
		else if (delta.x() < i.x()){
			pos.x() += -0.01f * (delta.x() + 250.0f);
			//DOUT << delta << std::endl;
		}

		//if(delta.y() > o.y()){
		//	pos.y() += 0.1f * (look_at_pos.y() - pos.y());
		//}
		//else if(delta.y() < i.y()){
		//	pos.y() += 0.1f * (look_at_pos.y() - pos.y());
		//}


		pos.x() = std::max(pos.x(), INFIMUM.x());
		pos.x() = std::min(pos.x(), SUPREMUM.x());
		pos.y() = std::max(pos.y(), INFIMUM.y());
		pos.y() = std::min(pos.y(), SUPREMUM.y());
	}

	void LookAt(const Vec2f& look_at){
		look_at_pos = look_at;
	}

	//　ポジションを取得
	Vec2f Position()const{ return pos; }
};