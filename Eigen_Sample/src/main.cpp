//
// アプリ雛形
//

#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include <fstream>
#include <iostream>

enum Window {
  WIDTH  = 512,
  HEIGHT = 512
};

const int CHIP_SIZE = 32;
const int CUTTING_SIZE = 32;
const int CUTTING_MAP_SIZE = 7;
const int MAP_SIZE = 16;
int Map[MAP_SIZE][MAP_SIZE];

const float MOVE_SPEED = 5.0f;
const float ROTATE_POWER = static_cast<float>(M_1_PI) *.1f;
const float SCALE_POWER = .05f;
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
  
  float rotate = .0f;
  Vec2f scale = Vec2f::Ones();
  Vec2f pos(-Window::WIDTH*.5f, Window::HEIGHT*.5f);





  while (env.isOpen()) {

	//　ローカル座標
	Eigen::Rotation2Df rotation(rotate);
	Eigen::DiagonalMatrix<float, 2>scaling = Eigen::Scaling(scale);
	Eigen::Translation<float, 2>translation = Eigen::Translation<float, 2>(pos);
	Eigen::Affine2f affine = scaling * rotation * translation;


	if(env.isPressKey('A')){
		pos.x() += -MOVE_SPEED;
	}
	if(env.isPressKey('D')){
		pos.x() += MOVE_SPEED;
	}
	if(env.isPressKey('W')){
		pos.y() += MOVE_SPEED;
	}
	if (env.isPressKey('S')){
		pos.y() += -MOVE_SPEED;
	}

	if(env.isPressKey(GLFW_KEY_LEFT)){
		rotate += -ROTATE_POWER;
	}
	if (env.isPressKey(GLFW_KEY_RIGHT)){
		rotate += ROTATE_POWER;
	}
	if (env.isPressKey(GLFW_KEY_UP)){
		scale.array() += SCALE_POWER;
	}
	if (env.isPressKey(GLFW_KEY_DOWN)){
		scale.array() += -SCALE_POWER;
	}
	

    env.setupDraw();


    
	for (int i = 0; i < MAP_SIZE; i++){
		for (int j = 0; j < MAP_SIZE; j++){
			auto index = Map[i][j];
			auto cutting_x = index % CUTTING_MAP_SIZE * CUTTING_SIZE;
			auto cutting_y = index / CUTTING_MAP_SIZE * CUTTING_SIZE;

			Vec2f pos = affine * Vec2f(j * CHIP_SIZE,-i * CHIP_SIZE - CHIP_SIZE);

			drawTextureBox(pos.x(), pos.y(), CHIP_SIZE, CHIP_SIZE,
				cutting_x, cutting_y, CUTTING_SIZE, CUTTING_SIZE, texture, color,
				rotate,scale,Vec2f::Zero());
		}
	}

    env.update();
  }
}
