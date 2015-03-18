//
// アプリ雛形
//

#include "lib/defines.hpp"
#include "lib/appEnv.hpp"

#include <iostream>
enum Window {
  WIDTH  = 512,
  HEIGHT = 512
};


enum class RasterType{
	PITCHING,
	ROLLING,
};

class RasterScroll{

	const RasterType type;
	Vec2f pos;
	Vec2f size;
	Vec2f cutting_size;
	const Texture& texture;
	Color color = Color(1, 1, 1);
	float swing_value;
	float radian = 0.0f;
	float cycle = 0;
	float shift_value;
	float swing_speed;
public:

	RasterScroll(
		const RasterType type,
		const Vec2f& pos,
		const Vec2f& size,
		const Texture& texture,
		const Vec2f& cutting_size,
		float swing_value = 25.0f,
		float shift_value = .04f,
		float swing_speed = .05f
		):
		type(type),
		pos(pos),
		size(size),
		texture(texture),
		cutting_size(cutting_size),
		swing_value(swing_value),
		shift_value(shift_value),
		swing_speed(swing_speed)
	{}

	void Draw(){
		radian = .0f;
		radian = cycle;
		if(type == RasterType::PITCHING){
			for (float i = 0; i < cutting_size.y(); i++){

				float x = std::sinf(radian)* swing_value;
				radian += shift_value;

				drawTextureBox(x + pos.x(), i + pos.y(), size.x(), size.y(),
					0, cutting_size.y() - i, cutting_size.x(), 1,
					texture, color);
			}
		}
		else{
			for (float i = 0; i < cutting_size.x(); i++){

				float y = std::sinf(radian)* swing_value;
				radian += shift_value;

				drawTextureBox(i + pos.x(), y + pos.y(), size.x(), size.y(),
					i, 0, 1, cutting_size.y(),
					texture, color);
			}
		}
		cycle += swing_speed;
	}
};

// 
// メインプログラム
// 
int main() {
  AppEnv env(Window::WIDTH, Window::HEIGHT, false, false);
  env.bgColor(Color(.5f, .5f, .5f));
  const Texture texture("res/miku.png");
  Color color(1, 1, 1);
  float radian = 0;
  float angle = 0;

  RasterScroll raster(RasterType::ROLLING,Vec2f(0, 0), Vec2f(1, 256), texture,Vec2f(256,256));

  while (env.isOpen()) {
    env.setupDraw();
	raster.Draw();
    env.update();
  }
}
