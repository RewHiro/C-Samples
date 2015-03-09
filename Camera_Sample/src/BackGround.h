#pragma once
#include "Object.h"
#include "Camera.h"

//Å@îwåi
class BackGround : public Object{
	const Texture& texture;
	Camera& camera;
public:

	enum class SIZE{
		WIDTH = 1024,
		HEIGHT = 512
	};

	BackGround(
		const Vec2f& pos,
		const Texture& texture,
		Camera& camera):
		Object(pos,Vec2f(1024,512)),
		texture(texture),
		camera(camera)
	{}

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