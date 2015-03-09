#pragma once
#include "lib\appEnv.hpp"
#include <algorithm>
#include <memory>

// ���N���X
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

	//�@�|�W�V�������擾
	Vec2f Position()const{return pos;}
	
	//�@�T�C�Y���擾
	Vec2f Size()const{ return size; }

	//�@���O���擾
	std::string& Name(){ return name; }

	//�@�X�V
	virtual void Update(){}

	//�@�`��
	virtual void Draw(){}
};