#pragma once
#include "GameObject.h"
#ifndef CHECK_TYPE
#define CHECK_TYPE

template<class ObjectTypeToCheck, class Object>
ObjectTypeToCheck* CheckObjecType(Object* object) {

	//std::cout << "attempting dynamic cast from " << typeid(object).name() << "to " << typeid(ObjectTypeToCheck).name() << std::endl;
	return dynamic_cast<ObjectTypeToCheck*>(object);

}

#endif // !CHECK_TYPE





