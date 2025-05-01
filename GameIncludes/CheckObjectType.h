#pragma once
#include "GameObject.h"
#ifndef CHECK_TYPE
#define CHECK_TYPE

// method of generically checking the type of an object 
// using a template passing in any object type and casting it 
// to the type argument passed into the template 
// this can the be checked for if it returns null pointer 
// very similar to the cast node in unreal 
template<class ObjectTypeToCheck, class Object>
ObjectTypeToCheck* CheckObjecType(Object* object) {

	//std::cout << "attempting dynamic cast from " << typeid(object).name() << "to " << typeid(ObjectTypeToCheck).name() << std::endl;
	return dynamic_cast<ObjectTypeToCheck*>(object);

}

#endif // !CHECK_TYPE





