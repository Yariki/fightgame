#ifndef __PHYSICALWORLD_H__
#define __PHYSICALWORLD_H__

#include "StaticObject.h"
#include "DynamicObject.h"

#define WALLS_COUNT 1
#define OBJECT_COUNT 3


class PhysicsWorld
{
private:
	
	StaticObject* _walls[WALLS_COUNT];
	DynamicObject* _objects[OBJECT_COUNT];

public:
	PhysicsWorld(void);
	virtual ~PhysicsWorld(void);
	void Update(float deltaTime);

	void SetSpeed(const orxVECTOR*  speed);

private:
	void FindObjectWallColision();

	void FindObjectWObjectColision();

};

#endif //__PHYSICALWORLD_H__