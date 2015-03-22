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

const int CHIP_SIZE = 32;
const int CUTTING_SIZE = 32;
const int CUTTING_MAP_SIZE = 7;
const int MAP_SIZE = 16;
int Map[MAP_SIZE][MAP_SIZE];


// 
// メインプログラム
// 
int main() {
  AppEnv env(Window::WIDTH, Window::HEIGHT, false, true);
  
  std::ifstream load("res/map.prn");

  for (int i = 0; i < MAP_SIZE; i++){
	  for (int j = 0; j < MAP_SIZE; j++){
		  load >> Map[i][j];
	  }
  }

  const Texture texture("res/map.png");
  const Color color(1, 1, 1);

  while (env.isOpen()) {
    env.setupDraw();
    
    
	for (int i = 0; i < MAP_SIZE; i++){
		for (int j = 0; j < MAP_SIZE; j++){
			auto index = Map[i][j];
			auto cutting_x = index % CUTTING_MAP_SIZE * CUTTING_SIZE;
			auto cutting_y = index / CUTTING_MAP_SIZE * CUTTING_SIZE;
			drawTextureBox(-Window::WIDTH*.5f + j * CHIP_SIZE, Window::HEIGHT*.5f - CHIP_SIZE - i * CHIP_SIZE, CHIP_SIZE, CHIP_SIZE,
				cutting_x, cutting_y, CUTTING_SIZE, CUTTING_SIZE, texture, color);
		}
	}

    env.update();
  }
}
