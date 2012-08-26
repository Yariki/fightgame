#ifndef __FFPHYSICSWORLD_H__
#define __FFPHYSICSWORLD_H__

#include "FFInclude.h"
#include "FFObject.h"

class FFPhysicsWorld
{
protected:
	std::vector<FFObject*> _listDynObject;
	std::vector<FFObject*> _listWall;

public:
	FFPhysicsWorld();
	virtual ~FFPhysicsWorld();

	virtual void UpdateWorld(float deltaTime);
	virtual void SetSpeed(const FFVector3& speed);

	void AddObject(const FFObject* obj);
	void AddWall(const FFObject* wall);

protected:
	void FindObjectWallcolision();
	void FindObjectWObjectColision();

};

#endif //__FFPHYSICSWORLD_H__