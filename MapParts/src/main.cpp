//
// アプリ雛形
//

#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include <array>

enum Window {
  WIDTH  = 512,
  HEIGHT = 512
};


struct MapInfo{
	Vec2f pos;
	Vec2f size;
	int index;
};

struct MapCreate{
	Vec2f pos;
	Vec2f size;
};



std::array<MapCreate,4>map_create ={
	Vec2f(10,5),Vec2f(83,90),
	Vec2f(105, 5), Vec2f(140, 90),
	Vec2f(36, 109), Vec2f(107, 91),
	Vec2f(145, 109), Vec2f(107, 91),
};

std::array<MapInfo, 9>maps = {
	Vec2f(120, 0), Vec2f(83, 90), 0,
	Vec2f(-100, 100), Vec2f(83, 90), 0,
	Vec2f(50, -150), Vec2f(83, 90), 0,
	Vec2f(170, 160), Vec2f(83, 90), 0,
	Vec2f(80, 140), Vec2f(83, 90), 0,

	Vec2f(-200, -200), Vec2f(140, 90), 1,

	Vec2f(-50, -220), Vec2f(107, 91), 2,
	Vec2f(-220, -10), Vec2f(107, 91), 2,

	Vec2f(-10, -10), Vec2f(107, 91), 3
};

void Draw(
	const MapInfo& map_info,
	const Texture& texture){
	MapCreate& create = map_create[map_info.index];
	drawTextureBox(map_info.pos.x(), map_info.pos.y(), map_info.size.x(), map_info.size.y(),
		create.pos.x(), create.pos.y(), create.size.x(), create.size.y(),
		texture, Color(1, 1, 1));
}

// 
// メインプログラム
// 
int main() {
  AppEnv env(Window::WIDTH, Window::HEIGHT, false, true);
  
  env.bgColor(Color(0.1f, 0.9f, 0.1f));

  const Texture texture("res/parts.png");

  while (env.isOpen()) {
    env.setupDraw();
    
	for(auto& map : maps){
		Draw(map, texture);
	}
    
    env.update();
  }
}
