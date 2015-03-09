#pragma once
#include "lib\appEnv.hpp"
#include <algorithm>
#include <memory>

// 基底クラス
class Object{
protected:
	Vec2f pos = Vec2f(0,0);
	Vec2f size = Vec2f(0,0);
	std::string name = "GameObject";

public:
	Object() = default;
	Object(const Vec2f& pos, const Vec2f& size):
	pos(pos),
	size(size)
	{}

	//　ポジションを取得
	Vec2f Position()const{return pos;}
	
	//　サイズを取得
	Vec2f Size()const{ return size; }

	//　名前を取得
	std::string& Name(){ return name; }

	//　更新
	virtual void Update(){}

	//　描画
	virtual void Draw(){}
};