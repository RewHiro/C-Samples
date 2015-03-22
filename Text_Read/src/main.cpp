//
// アプリ雛形
//

#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include <fstream>

enum Window {
  WIDTH  = 512,
  HEIGHT = 512
};

class Object{
	const Texture texture;
	Color color;
public:

	Object(std::string res_name):
		texture(Texture(res_name)),
		color(Color(1,1,1))
	{
	}

	void Draw(){
		drawTextureBox(0, 0, 128, 128,
			0, 0, texture.width(), texture.height(),
			texture, color);
	}
};

// 
// メインプログラム
// 
int main() {
  AppEnv env(Window::WIDTH, Window::HEIGHT, false, true);
  
  std::fstream load("res/data.txt");
  std::string res_name;

  load >> res_name;

  Object player(res_name);


  while (env.isOpen()) {
    env.setupDraw();
    
	player.Draw();
    
    env.update();
  }
}
