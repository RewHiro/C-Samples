#pragma once
#include "lib\vector.hpp"
namespace Collision{

	static bool PointCenterRect(Vec2f& point,Vec2f& rect_pos,Vec2f& rect_size){
		if (!(point.x() > rect_pos.x() - rect_size.x()*.5f && point.x() < rect_pos.x() + rect_size.x()*.5f))return false;
		if (!(point.y() > rect_pos.y() - rect_size.y()*.5f && point.y() < rect_pos.y() + rect_size.y()*.5f))return false;
		return true;
	}

	static bool PointRect(Vec2f& point, Vec2f& rect_pos, Vec2f& rect_size){
		if (!(point.x() > rect_pos.x() && point.x() < rect_pos.x() + rect_size.x()))return false;
		if (!(point.y() > rect_pos.y() && point.y() < rect_pos.y() + rect_size.y()))return false;
		return true;
	}
};