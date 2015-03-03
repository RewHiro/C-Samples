//
// アプリ雛形
//

#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include <iostream>

// アプリのウインドウサイズ
enum Window {
  WIDTH  = 640,
  HEIGHT = 480
};

struct Camera{
	Vec2f pos = Vec2f(WIDTH * 0.5f,HEIGHT * 0.5);
	Vec2f size;
};

class Object{
	Vec2f pos;
	Vec2f size;
	const Vec2f SPEED_VALUE = Vec2f(5.0f, 5.0f);
	const Texture& texture;
	AppEnv& app_env;
	Camera& camera;

public:
	Object(
		AppEnv& app_env,
		const Vec2f& pos,
		const Vec2f& size,
		const Texture& texture,
		Camera& camera
		):
	app_env(app_env),
	pos(pos),
	size(size),
	texture(texture),
	camera(camera)
	{
	}

	Vec2f Position()const {
		return pos;
	}

	void Update(){
		Move();
	}

	void Draw(){ 
		auto screen_pos = pos + size * 0.5f - camera.pos;
		DOUT << camera.pos << std::endl;
		drawTextureBox(screen_pos.x(), screen_pos.y(),
			size.x(), size.y(),
			0, 0,
			texture.width(), texture.height(),
			texture,
			Color(1, 1, 1),
			0.0f, Vec2f(1, 1), Vec2f(size.x() * 0.5f,size.y() * 0.5f));
	}

private:

	void Move(){

		if(app_env.isPressKey(GLFW_KEY_UP)){
			pos.y() += SPEED_VALUE.y();
		}
		if (app_env.isPressKey(GLFW_KEY_DOWN)){
			pos.y() += -SPEED_VALUE.y();
		}
		if (app_env.isPressKey(GLFW_KEY_LEFT)){
			pos.x() += -SPEED_VALUE.x();
		}
		if (app_env.isPressKey(GLFW_KEY_RIGHT)){
			pos.x() += SPEED_VALUE.x();
		}
	}
};

// 
// メインプログラム
// 
int main() {
	// アプリウインドウの準備
	AppEnv app_env(Window::WIDTH, Window::HEIGHT,
		false, true);

	const Texture player_texture = Texture("res/player.png");

	Camera camera;

	Object player(app_env,Vec2f(0, 0), Vec2f(player_texture.width(), player_texture.height()),player_texture,camera);

	const Texture bg_texture = Texture("res/bg.png");
	Vec2f bg_start_pos = Vec2f(0, 0);

	while (app_env.isOpen()) {
    
	player.Update();

	camera.pos = player.Position() -Vec2f(-Window::WIDTH/2,-Window::HEIGHT/2);
    
	// 描画準備
    app_env.setupDraw();


	auto screen_pos = bg_start_pos - camera.pos;
	drawTextureBox(screen_pos.x(), screen_pos.y(),
		bg_texture.width(), bg_texture.height(),
		0, 0,
		bg_texture.width(), bg_texture.height(),
		bg_texture,
		Color(1, 1, 1));
	
	player.Draw();
    
    // 画面更新
    app_env.update();
	}
}
