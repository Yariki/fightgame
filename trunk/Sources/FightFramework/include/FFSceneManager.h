#ifndef __FFSCENEMANAGER_H__
#define __FFSCENEMANAGER_H__

#include "FFInclude.h"


template<class T>
class FFSceneManager
{
protected:
	std::vector<T> _listScene;

public:
	FFSceneManager();
	virtual ~FFSceneManager();

public:
	bool IsPresentObjectOfType(string type);
	T GetObjectType(string type);
	void AddObjectType(T obj) {_listScene.push_back(obj);}


};

template<class T>
FFSceneManager<T>::FFSceneManager()
{

}

template<class T>
FFSceneManager<T>::~FFSceneManager()
{
	for(size_t i = 0; i < _listScene.size(); i++)
	{
		delete _listScene.at(i);
	}
	_listScene.clear();
}

template<class T>
bool FFSceneManager<T>::IsPresentObjectOfType(string type)
{
	bool res = false;
	for(size_t i = 0; i < _listScene.size(); i++)
	{
		string typeName = typeid(*(_listScene.at(i))).name();
		if(!typeName.compare(type))
		{
			res = true;
			break;
		}
	}
	return res;
}

template<class T>
T FFSceneManager<T>::GetObjectType(string type)
{
	T res = NULL;
	for(size_t i = 0; i < _listScene.size(); i++)
	{
		string typeName = typeid(*(_listScene.at(i))).name();
		if(!typeName.compare(type))
		{
			res = _listScene.at(i);
			break;
		}
	}
	return res;
}



#endif //__FFSCENEMANAGER_H__