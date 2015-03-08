#pragma once
#include "lib\appEnv.hpp"
#include "Camera.h"
class Object{
	Vec2f pos;
	Vec2f size;
	const Vec2f SPEED_VALUE = Vec2f(5.0f, 5.0f);
	const Texture& texture;
	AppEnv& app_env;
	const Camera& camera;
	const Vec2f INFIMUM = Vec2f(0.0f, 0.0f);
	const Vec2f SUPREMUM = Vec2f(830.0f, 390.0f);

public:
	Object() = default;
	Object(
		AppEnv& app_env,
		const Vec2f& pos,
		const Vec2f& size,
		const Texture& texture,
		const Camera& camera
		) :
		app_env(app_env),
		pos(pos),
		size(size),
		texture(texture),
		camera(camera)
	{}

	Vec2f Position()const{
		return pos;
	}

	void Update(){
		Move();
	}

	void Draw(){
		auto screen_pos = pos + size * 0.5f - camera.Position();
		drawTextureBox(screen_pos.x(), screen_pos.y(),
			size.x(), size.y(),
			0, 0,
			texture.width(), texture.height(),
			texture,
			Color(1, 1, 1),
			0.0f, Vec2f(1, 1), Vec2f(size.x() * 0.5f, size.y() * 0.5f));
	}

private:

	void Move(){
		if (app_env.isPressKey(GLFW_KEY_UP)){
			pos.y() += SPEED_VALUE.y();
			LimitLine();
		}
		if (app_env.isPressKey(GLFW_KEY_DOWN)){
			pos.y() += -SPEED_VALUE.y();
			LimitLine();
		}
		if (app_env.isPressKey(GLFW_KEY_LEFT)){
			pos.x() += -SPEED_VALUE.x();
			LimitLine();
		}
		if (app_env.isPressKey(GLFW_KEY_RIGHT)){
			pos.x() += SPEED_VALUE.x();
			LimitLine();
		}
	}

	void LimitLine(){
		pos.x() = std::max(pos.x(), INFIMUM.x());
		pos.x() = std::min(pos.x(), SUPREMUM.x());

		pos.y() = std::max(pos.y(), INFIMUM.y());
		pos.y() = std::min(pos.y(), SUPREMUM.y());
	}
};