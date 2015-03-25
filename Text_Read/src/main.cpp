//
// アプリ雛形
//

#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include <fstream>
#include <string>

//　FIXME：float型で固定しているので整数型にキャストする場合に時間がかかる
float INIF(const std::string& session_name, const std::string& name, const std::string& filepath){
	std::ifstream load(filepath);
	if (load.fail())return .0f;
	std::string buf;
	std::string parameter;
	std::string session = "[]";
	session.insert(1, session_name);
	while (std::getline(load, buf)){
		//　コメントだったらとばす
		if (std::string::npos != buf.find('#'))continue;
		//　セッション名が異なったらとばす
		if (session != buf)continue;

		while (std::getline(load, buf)){
			if (buf.empty())break;
			//　コメントだったらとばす
			if (std::string::npos != buf.find('#'))continue;
			//　見つからなかったらとばす
			if (std::string::npos == buf.find(name))continue;
			//　完全一致しなかったらとばす(サイズで判定)
			std::string find = buf.substr(0, buf.find('=') - 1);
			if (name.length() != find.length())continue;
			parameter = buf.substr(buf.find('=') + 2);
			break;
		}
		break;
	}
	if (parameter.empty())return.0f;
	return std::stof(parameter);
}

int INII(const std::string& session_name, const std::string& name, const std::string& filepath){
	std::ifstream load(filepath);
	if (load.fail())return 0;
	std::string buf;
	std::string parameter;
	std::string session = "[]";
	session.insert(1, session_name);
	while (std::getline(load, buf)){
		//　コメントだったらとばす
		if (std::string::npos != buf.find('#'))continue;
		//　セッション名が異なったらとばす
		if (session != buf)continue;

		while (std::getline(load, buf)){
			if (buf.empty())break;
			//　コメントだったらとばす
			if (std::string::npos != buf.find('#'))continue;
			//　見つからなかったらとばす
			if (std::string::npos == buf.find(name))continue;
			//　完全一致しなかったらとばす(サイズで判定)
			std::string find = buf.substr(0, buf.find('=') - 1);
			if (name.length() != find.length())continue;
			parameter = buf.substr(buf.find('=') + 2);
			break;
		}
		break;
	}
	if (parameter.empty())return 0;
	return std::stoi(parameter);
}

std::string INIS(const std::string& session_name, const std::string& name, const std::string& filepath){
	std::ifstream load(filepath);
	if (load.fail())return std::string("");
	std::string buf;
	std::string parameter;
	std::string session = "[]";
	session.insert(1, session_name);
	while (std::getline(load, buf)){
		//　コメントだったらとばす
		if (std::string::npos != buf.find('#'))continue;
		//　セッション名が異なったらとばす
		if (session != buf)continue;

		while (std::getline(load, buf)){
			if (buf.empty())break;
			//　コメントだったらとばす
			if (std::string::npos != buf.find('#'))continue;
			//　見つからなかったらとばす
			if (std::string::npos == buf.find(name))continue;
			//　完全一致しなかったらとばす(サイズで判定)
			std::string find = buf.substr(0, buf.find('=') - 1);
			if (name.length() != find.length())continue;
			parameter = buf.substr(buf.find('=') + 2);
			break;
		}
		break;
	}
	if (parameter.empty())return std::string("");
	return parameter;
}

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


  std::string name = "enemy";

  auto path = INIS(name, "texture_path", "res/data.txt");
  
  auto pos = Vec2f(
	  INIF(name, "x", "res/data.txt"),
	  INIF(name, "y", "res/data.txt")
	  );

  auto size = Vec2f(
	  INIF(name, "size_x", "res/data.txt"),
	  INIF(name, "size_y", "res/data.txt")
	  );

  auto color = Color(
	  INIF(name, "red", "res/data.txt"),
	  INIF(name, "green", "res/data.txt"),
	  INIF(name, "blue", "res/data.txt")
	  );

  auto speed = Vec2f(
	  INIF(name, "speed_x", "res/data.txt"),
	  INIF(name, "speed_y", "res/data.txt")
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
