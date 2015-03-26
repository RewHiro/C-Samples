//
// アプリ雛形
//

#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "picojson.h"
#include <fstream>
#include <string>

enum Window {
  WIDTH  = 512,
  HEIGHT = 512
};

class Object{
	const Texture texture;
	Color color;
	Vec2f pos;
	Vec2f size;
	Vec2f speed;
public:

	Object(
		const std::string& res_name,
		const Color& color,
		const Vec2f& pos,
		const Vec2f& size,
		const Vec2f& speed
		):
		texture(Texture(res_name)),
		color(color),
		pos(pos),
		size(size),
		speed(speed)
	{
	}

	void Update(AppEnv& env){
		if(env.isPressKey(GLFW_KEY_LEFT)){
			pos.x() += -speed.x();
		}
		if (env.isPressKey(GLFW_KEY_RIGHT)){
			pos.x() += speed.x();
		}
		if (env.isPressKey(GLFW_KEY_UP)){
			pos.y() += speed.y();
		}
		if (env.isPressKey(GLFW_KEY_DOWN)){
			pos.y() += -speed.y();
		}
	}

	void Draw(){
		drawTextureBox(pos.x(), pos.y(), size.x(), size.y(),
			0, 0, texture.width(), texture.height(),
			texture, color);
	}
};

// 
// メインプログラム
// 
int main() {
  AppEnv env(Window::WIDTH, Window::HEIGHT, false, true);
  std::string name = "player";

  std::ifstream load("res/data.json");
  std::stringstream palam_str;
  palam_str << load.rdbuf();

  picojson::value json;
  picojson::parse(json, palam_str.str());
  picojson::object& player_data = json.get<picojson::object>()[name].get<picojson::object>();



  auto path = player_data["texture"].get<std::string>();
  
  auto pos = Vec2f(
	  player_data["pos"].get<picojson::object>()["x"].get<double>(),
	  player_data["pos"].get<picojson::object>()["y"].get<double>()
	  );

  auto size = Vec2f(
	  player_data["size"].get<picojson::object>()["x"].get<double>(),
	  player_data["size"].get<picojson::object>()["y"].get<double>()
	  );

  auto color = Color(
	  player_data["color"].get<picojson::object>()["red"].get<double>(),
	  player_data["color"].get<picojson::object>()["green"].get<double>(),
	  player_data["color"].get<picojson::object>()["blue"].get<double>()
	  );

  auto speed = Vec2f(
	  player_data["speed"].get<picojson::object>()["x"].get<double>(),
	  player_data["speed"].get<picojson::object>()["y"].get<double>()
	  );



  Object player(
	  path,
	  color,
	  pos,
	  size,
	  speed
	  );


  while (env.isOpen()) {

	player.Update(env);
    env.setupDraw();
    
	player.Draw();
    
    env.update();
  }
}
