//
// アプリ雛形
//

#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include <array>

enum Window {
  WIDTH  = 256,
  HEIGHT = 512
};


class Bullet{
	Vec2f pos;
	Vec2f size;
	Color color;
	bool is_active = false;
public:
	Bullet() = default;

	void Shot(const Vec2f& pos, const Vec2f& size, const Color& color){
		this->pos = pos;
		this->size = size;
		this->color = color;
		is_active = !is_active;
	}

	void Update(){
		if (!is_active)return;
		pos.y() += 3;
		if (pos.y() - size.y() < Window::HEIGHT *.5f)return;
		is_active = !is_active;
	}

	void Draw(){
		if (!is_active)return;
		drawFillCircle(pos.x(), pos.y(), 
			size.x(), size.y(), 
			20, color);
	}

	bool IsActive()const{ return is_active; }
};

// 
// メインプログラム
// 
int main() {
  AppEnv env(Window::WIDTH, Window::HEIGHT, false, true);
  

  std::array<Bullet, 10>bullets;
  while (env.isOpen()) {
    if(env.isPushButton(Mouse::LEFT)){
		for(auto& bullet : bullets){
			if (bullet.IsActive())continue;
			bullet.Shot(Vec2f(0,-Window::HEIGHT*.5f),Vec2f(5,5),Color(1,1,1));
			break;
		}
	}
	for (auto& bullet : bullets){
		bullet.Update();
	}

    env.setupDraw();
	for (auto& bullet : bullets){
		bullet.Draw();
	}
    env.update();
  }
}
