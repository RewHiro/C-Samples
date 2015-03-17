#pragma once
#include <unordered_map>
#include <memory>
class Object;
class ObjectInfo
{
	using ObjectMap = std::unordered_multimap < std::string, std::shared_ptr<Object> >;
	ObjectMap object_map;
public:
	ObjectInfo() = default;

	void Add(std::string name,std::shared_ptr<Object>object){
		object_map.emplace(name, object);
	}

	ObjectMap::iterator Find(std::string name){
		return object_map.find(name);
	}
};

