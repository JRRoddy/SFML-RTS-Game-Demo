#pragma once
#include "string"


template<class MenuToBindElements, typename binding =  void((MenuToBindElements::* )())>
class UiActionBinder {
    
public:
    
	UiActionBinder() {};
	~UiActionBinder() {};
	void addBinding(std::string elementId, void((MenuToBindElements::*action)())){

		m_elementIdToAction.insert({ elementId, action });

	}

	binding getActionBinding(std::string & id ){

		return m_elementIdToAction[id];

	}

private:
	std::map<std::string, void((MenuToBindElements::*)())> m_elementIdToAction;
	

};