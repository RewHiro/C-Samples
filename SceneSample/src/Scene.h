#pragma once
#include "lib\texture.hpp"
#include "lib\graph.hpp"

enum Window {
	WIDTH = 256,
	HEIGHT = 256
};

class Scene
{
	const Color color = Color(1, 1, 1);
protected:
	const Texture bg_texture;
	const Texture chara_texture;
	const Texture text_texture;
public:
	Scene(
		std::string bg_texture,
		std::string chara_texture,
		std::string text_texture
		) :
		bg_texture(Texture(bg_texture)),
		chara_texture(Texture(chara_texture)),
		text_texture(Texture(text_texture))
	{
	}
	virtual ~Scene() = default;

	virtual void Draw(){
		drawTextureBox(-Window::HEIGHT*.5f, -Window::HEIGHT*.5f, bg_texture.width(), bg_texture.height(),
			0, 0, bg_texture.width(), bg_texture.height(),
			bg_texture, color);

		drawTextureBox(-Window::HEIGHT*.5f, -Window::HEIGHT*.5f, chara_texture.width(), chara_texture.height(),
			0, 0, chara_texture.width(), chara_texture.height(),
			chara_texture, color);

		drawTextureBox(-Window::HEIGHT*.5f, -Window::HEIGHT*.5f, text_texture.width(), text_texture.height(),
			0, 0, text_texture.width(), text_texture.height(),
			text_texture, color);
	}
};

