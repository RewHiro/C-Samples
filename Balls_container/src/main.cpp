//
// アプリ雛形
//

#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "lib\random.hpp"
#include <random>
#include <vector>

// アプリのウインドウサイズ
enum Window {
	WIDTH = 512,
	HEIGHT = 512
};

//　重力の大きさ
const float GRAVITY_POWER = 1.0f;

//　ボールの定義
class Ball{

	Vec2f pos;
	Vec2f speed;
	Vec2f radius = Vec2f(10.0f, 10.0f);
	Color color;
	bool isActive = false;
public:
	Ball() = default;
	Ball(
		Vec2f& pos,
		Vec2f& speed,
		Color& color
		):
		pos(pos),
		speed(speed),
		color(color),
		isActive(true){}

	//　更新
	void Update(){
		if (!isActive)return;
		pos += speed;
		Bounce();
	}

	//　描画
	void Draw(){
		if (!isActive)return;
		drawFillCircle(pos.x(), pos.y(),
			radius.x(), radius.y(),
			10,
			color);
	}

	//　重力
	void Gravity(){
		speed.y() += -GRAVITY_POWER;
	}

private:


	//　壁に当たったら跳ね返す
	void Bounce(){
		if (pos.x() - radius.x() < -WIDTH*0.5f ||
			pos.x() + radius.x() > WIDTH*0.5f){
			pos.x() = std::max(pos.x(), -WIDTH * 0.5f + radius.x());
			pos.x() = std::min(pos.x(), WIDTH * 0.5f - radius.x());
			speed.x() *= -1;
		}
		if (pos.y() - radius.y() < -HEIGHT*0.5f ||
			pos.y() + radius.y() > HEIGHT*0.5f){
			pos.y() = std::max(pos.y(), -HEIGHT * 0.5f + radius.y());
			pos.y() = std::min(pos.y(), HEIGHT * 0.5f - radius.y());
			speed.y() *= -1;
		}
	}
};

//　ボールを管理する機能
class BallManager{

	AppEnv& app_env;

	//　乱数生成
	Random random;

	std::vector<Ball>balls;

	const Vec2f INIT_POS = Vec2f(200.0f, 200.0f);
	const float SPPED_POWER = 5.0f;

public:
	BallManager(AppEnv& app_env) :
		app_env(app_env)
	{
		random.setSeed(std::random_device()());
	}

	//　更新
	void Update()
	{
		Create();
		Gravity();
		for (auto& ball : balls){
			ball.Update();
		}
	}

	//　描画
	void Draw(){
		for (auto& ball : balls){
			ball.Draw();
		}
	}
private:
	//　重力処理
	void Gravity(){
		if (!app_env.isPressKey('G'))return;
		for (auto& ball : balls){
			ball.Gravity();
		}
	}

	//　ボールを生成
	Ball CreateBall(){
		auto pos = app_env.mousePosition();

		auto speed = Vec2f(
			random.fromFirstToLast(-SPPED_POWER, SPPED_POWER),
			random.fromFirstToLast(-SPPED_POWER, SPPED_POWER));
		
		auto color = Color(
			random.fromFirstToLast(0.1f, 1.0f),
			random.fromFirstToLast(0.1f, 1.0f),
			random.fromFirstToLast(0.1f, 1.0f));

		return Ball(pos, speed, color);
	}

	//　生成
	void Create(){
		if (!app_env.isPushButton(Mouse::LEFT))return;
		balls.emplace_back(CreateBall());
	}
};


// 
// メインプログラム
// 
int main() {
	// アプリウインドウの準備
	AppEnv app_env(Window::WIDTH, Window::HEIGHT,
		false, false);

	BallManager ball_manager(app_env);

	while (app_env.isOpen()) {

		ball_manager.Update();

		// 描画準備
		app_env.setupDraw();

		ball_manager.Draw();

		// 画面更新
		app_env.update();
	}
}
