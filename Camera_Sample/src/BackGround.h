#pragma once
#include "Object.h"
class BackGround : public Object{
	const Texture& texture;
	Camera& camera;
public:
	BackGround(
		const Vec2f& pos,
		const Texture& texture,
		Camera& camera):
		Object(pos,Vec2f(0,0)),
		texture(texture),
		camera(camera)
	{}

	void Update(){
	}

	void Draw()final{
		auto screen_pos = pos - camera.Position();
		drawTextureBox(screen_pos.x(), screen_pos.y(),
			texture.width(), texture.height(),
			0, 0,
			texture.width(), texture.height(),
			texture,
			Color(1, 1, 1));
	}
};