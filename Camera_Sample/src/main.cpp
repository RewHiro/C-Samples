//
// アプリ雛形
//

#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include <iostream>
#include <algorithm>

// アプリのウインドウサイズ
enum Window {
  WIDTH  = 640,
  HEIGHT = 480
};

const Vec2f test = Vec2f(WIDTH / 2, HEIGHT / 2);

class Camera{
	Vec2f pos = test;
	Vec2f size = Vec2f(Window::WIDTH * 0.5f,Window::HEIGHT / 0.5f);
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
		Vec2f delta = (look_at_pos) - (pos - test);

		//pos += 0.1f * delta;

		DOUT << delta << std::endl;

		if(delta.x() > o.x()){
			pos.x() += 0.01f * delta.x();
			//DOUT << delta << std::endl;
		}
		else if(delta.x() < i.x()){
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


class BG{
	const Texture& texture;
	Vec2f pos;
	const Camera& camera;

public:
	BG(
		const Vec2f& pos,
		const Texture& texture,
		const Camera& camera) :
		pos(pos),
		texture(texture),
		camera(camera){}

	Vec2f Position()const{
		return pos;
	}

	void Draw(){
		auto screen_pos = pos - camera.Position();
		drawTextureBox(screen_pos.x(), screen_pos.y(),
			texture.width(), texture.height(),
			0, 0,
			texture.width(), texture.height(),
			texture,
			Color(1, 1, 1));
	}

};

// 
// メインプログラム
// 
int main() {
	// アプリウインドウの準備
	AppEnv app_env(Window::WIDTH, Window::HEIGHT,
		false, true);

	const Texture PLAYER_TEXTURE = Texture("res/player.png");
	const Texture BG_TEXTURE = Texture("res/bg.png");
	const Texture ENMEY_TEXTURE = Texture("res/enemy.png");

	Camera camera;

	Object player(
		app_env, 
		Vec2f(0 , 0), 
		Vec2f(PLAYER_TEXTURE.width(),
		PLAYER_TEXTURE.height()),
		PLAYER_TEXTURE,
		camera);

	Object enemy(
		app_env,
		Vec2f(800.0f, 100.0f),
		Vec2f(ENMEY_TEXTURE.width(),
		ENMEY_TEXTURE.height()),
		ENMEY_TEXTURE,
		camera);

	BG bg(Vec2f(0 , 0), BG_TEXTURE, camera);

	bool isObject = true;


	while (app_env.isOpen()) {

		if(app_env.isPushKey('A')){
			isObject = !isObject;
		}

		if(isObject){
			player.Update();
			camera.LookAt(player.Position());
		}
		else {
			enemy.Update();
			camera.LookAt(enemy.Position());
		}
		
		camera.Update();

		// 描画準備
		app_env.setupDraw();

		bg.Draw();
	
		player.Draw();

		enemy.Draw();
    
		// 画面更新
		app_env.update();
	}
}
