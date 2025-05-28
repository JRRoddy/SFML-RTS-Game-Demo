#pragma once
#include "string"
#include "GameObject.h"
// this is a template utility class that is usually used for binding a particualr 
// ui elelement string id to an associated method within a menu class by mapping its 
// string id to a method pointer to that method using an associative map container 

// here the template agruments define an object type for the particualr  menu class 
// we are using and then use the type name key word to define a type called binding 
// which simply declares the method pointer type that being what it returns and the class 
// type that the method pointer is associated to 
template<class MenuToBindElements, typename binding =  void((MenuToBindElements::* )())>
class UiActionBinder {
    
public:
    
	UiActionBinder() {};
	~UiActionBinder() {};
	// this method allows a particualr string id to be bound to a method pointer 
	// assosiated with a particualr menu class here we pass in the method pointer 
	// of the type we defined in  the template arguments for this util class 
	// and the element id we want it to be bound to storing them in an std::map 
	// for quick and easy access
	void addBinding(std::string elementId, void((MenuToBindElements::*action)())){

		m_elementIdToAction.insert({ elementId, action });

	}
	// return the binding type defined within the template arguments 
	// acccessing a binding that is assoctiaed with the particualr ui element 
	// string id 
	binding getActionBinding(std::string & id ){
		try {

			return m_elementIdToAction.at(id);
		}
		catch (...) {
			std::cout << "could not find ui action for id " << id << std::endl;
			return nullptr;
		}

	}

private:
	std::map<std::string, void((MenuToBindElements::*)())> m_elementIdToAction;
	

};