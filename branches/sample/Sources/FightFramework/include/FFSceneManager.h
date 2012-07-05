#ifndef __FFSCENEMANAGER_H__
#define __FFSCENEMANAGER_H__

#include "FFInclude.h"


template<class T>
class FFSceneManager
{
protected:
	
    std::map<string,T> _listScene;
public:
	FFSceneManager();
	virtual ~FFSceneManager();

public:
	bool IsPresentObjectOfType(string type);
	T GetObjectType(string type);
	void AddObjectType(T obj) { _listScene.insert(pair<string,T>(typeid(*obj).name(),obj)); }


};

template<class T>
FFSceneManager<T>::FFSceneManager()
{

}

template<class T>
FFSceneManager<T>::~FFSceneManager()
{

    for(map<string,T>::iterator p = _listScene.begin();
        p != _listScene.end(); ++p)
        delete p->second;
	_listScene.clear();
}

template<class T>
bool FFSceneManager<T>::IsPresentObjectOfType(string type)
{
	bool res = false;
	
    if(_listScene.find(type) != _listScene.end())
        res = true;
	return res;
}

template<class T>
T FFSceneManager<T>::GetObjectType(string type)
{
	T res = NULL;
	
    res = _listScene[type];

	return res;
}



#endif //__FFSCENEMANAGER_H__