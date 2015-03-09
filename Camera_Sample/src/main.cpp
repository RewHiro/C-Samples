//
// アプリ雛形
//

#include "lib/appEnv.hpp"
#include "Camera.h"
#include "Character.h"
#include "BackGround.h"
#include "lib\font.hpp"
#include <memory>

// 
// メインプログラム
// 

int main() {
	// アプリウインドウの準備
	AppEnv app_env(Window::WIDTH, Window::HEIGHT,
		false, true);
	auto meiryo = Font("res/meiryo.ttc");
	meiryo.size(30);

	const Texture PLAYER_TEXTURE = Texture("res/player.png");
	const Texture BG_TEXTURE = Texture("res/bg.png");
	const Texture ENMEY_TEXTURE = Texture("res/enemy.png");

	Camera camera;

	std::shared_ptr<Object>player = 
		std::make_shared<Character>(
			app_env, 
			Vec2f(0 , 0), 
			Vec2f(PLAYER_TEXTURE.width(),PLAYER_TEXTURE.height()),
			PLAYER_TEXTURE,
			camera
			);

	std::shared_ptr<Object>enemy =
		std::make_shared<Character>(
		app_env,
		Vec2f(800, 0),
		Vec2f(ENMEY_TEXTURE.width(),ENMEY_TEXTURE.height()),
		ENMEY_TEXTURE,
		camera
		);

	std::shared_ptr<Object>background = 
		std::make_shared<BackGround>(
		Vec2f(0, 0), 
		BG_TEXTURE, 
		camera
		);

	//　Ojectの箱を作る
	std::shared_ptr<Object>object_box = player;

	player->Name() = "player";
	enemy->Name() = "enemy";

	std::string switching_ui = "Aで切り替え";
	std::string look_at_ui = "↓";

	camera.LookAt(player);
	while (app_env.isOpen()) {

		//　カメラの切り替え
		if (app_env.isPushKey('A')){
			camera.TurnSwitch();
			if (object_box->Name() == "player"){
				object_box = enemy;
				camera.LookAt(enemy);
			}
			else{
				object_box = player;
				camera.LookAt(player);
			}

		}

		//　計算処理更新
		camera.Update();
		background->Update();
		object_box->Update();

		// 描画準備
		app_env.setupDraw();

		background->Draw();
		player->Draw();
		enemy->Draw();
		meiryo.draw(switching_ui, Vec2f(-Window::WIDTH * 0.5f, HEIGHT * 0.5f - meiryo.drawSize(switching_ui).y()), Color(1, 0, 0));
		
		auto screen_pos = Vec2f(object_box->Position().x() + object_box->Size().x() * 0.4f, object_box->Position().y() + object_box->Size().y()) - camera.Position();
		meiryo.draw(look_at_ui, screen_pos, Color(1, 0, 0));

		// 画面更新
		app_env.update();
	}
}
