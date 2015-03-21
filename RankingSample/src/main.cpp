//
// アプリ雛形
//

#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "lib\random.hpp"
#include <random>
#include <fstream>
#include <array>

enum Window {
  WIDTH  = 600,
  HEIGHT = 800
};



const Color color(1, 1, 1);

const int SUPREMUM = 50;
const int INFIMUM = 2;

const float START_SCORE_POS = 300.0f;
const float START_SORT_POS = START_SCORE_POS - 100;
const float OFFSET = 60.0f;

void PointDraw(
	float y,
	int point,
	const Texture& score_texture,
	const Texture& one_point_texture,
	const Texture& ten_point_texture
	)
{
	auto x = -Window::WIDTH*.5f + score_texture.width();

	auto one_point = point % 10;
	auto ten_point = point / 10;

	while(ten_point  > 0){
		drawTextureBox(x, y, 60, 60,
			0, 0, 80, 80,
			ten_point_texture, color);
		x += 30;
		ten_point--;
	}

	while(one_point > 0){
		drawTextureBox(x, y, 40, 40,
			0, 0, 80, 80,
			one_point_texture, color);
		x += 20;
		one_point--;
	}
}


// 
// メインプログラム
// 
int main() {
  AppEnv env(Window::WIDTH, Window::HEIGHT, false, true);

  const Texture one_point_texture("res/miku_point_1.png");
  const Texture ten_point_texture("res/miku_point.png");
  const Texture rank_texture("res/rank.png");
  const Texture score_texture("res/score.png");


  Random random;
  random.setSeed(std::random_device()());

  int score = random.fromFirstToLast(INFIMUM, SUPREMUM);

  std::array<int, 11>score_array;

  std::ifstream load("res/score.txt");
  for (int i = 0; i < score_array.size()-1; i++){
	  load >> score_array.at(i);
  }
  score_array.at(score_array.size() - 1) = score;

  for (int i = 0; i < score_array.size(); i++){
	  for (int j = i+1; j < score_array.size(); j++){
		  if (score_array.at(i) > score_array.at(j))continue; 
		  std::swap(score_array.at(i), score_array.at(j));
	  }
  }

  while (env.isOpen()) {
    env.setupDraw();

	if(env.isPushButton(Mouse::LEFT)){
		score = random.fromFirstToLast(INFIMUM, SUPREMUM);
		std::ifstream load("res/score.txt");
		for (int i = 0; i < score_array.size() - 1; i++){
			load >> score_array.at(i);
		}
		score_array.at(score_array.size() - 1) = score;

		for (int i = 0; i < score_array.size(); i++){
			for (int j = i + 1; j < score_array.size(); j++){
				if (score_array.at(i) > score_array.at(j))continue;
				std::swap(score_array.at(i), score_array.at(j));
			}
		}
	}

	drawTextureBox(-Window::WIDTH*.5f, 300, score_texture.width(), score_texture.height(),
		0, 0, score_texture.width(), score_texture.height(),
		score_texture, color);
    
	PointDraw(START_SCORE_POS, score, score_texture, one_point_texture, ten_point_texture);
    
	for (int i = 0; i < score_array.size()-1; i++){
		PointDraw(START_SORT_POS - i * OFFSET, score_array.at(i), score_texture, one_point_texture, ten_point_texture);
	}

	for (int i = 0; i < score_array.size() - 1; i++){
		if (score != score_array.at(i))continue;
		drawTextureBox(-Window::WIDTH*.5f, START_SORT_POS - i * OFFSET, rank_texture.width(), rank_texture.height(),
			0, 0, rank_texture.width(), rank_texture.height(),
			rank_texture, color);
		break;
	}


    env.update();
  }
}
