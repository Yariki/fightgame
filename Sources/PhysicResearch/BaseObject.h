#ifndef __BASEOBJECT_H__
#define __BASEOBJECT_H__

#include "orx.h"

#define OBJECT_SECTION "Test"
#define WALL_SECTION "OneWall"

#define MASS_SECTION "Mass"
#define SPEED_SECTION "Speed"
#define FORCES_SECTION "Forces"
#define POSITION_SECTION "Position"

typedef enum 
{
	TE_STATIC,
	TE_DYNAMIC
} TYPE_ENTITY;

typedef enum 
{
	HS_NONE,
	HS_LEFT,
	HS_RIGHT

} HIT_SIDE;


class BaseObject
{
protected:
	orxOBJECT*	_object;
	orxVECTOR _pivot;
	orxVECTOR _position;
	orxVECTOR _size;
	orxVECTOR _speed;
	orxVECTOR _forces;
	orxVECTOR _acceleration;
	orxFLOAT _mass;

	TYPE_ENTITY _typeEntity;
	HIT_SIDE	_hitSide;

	orxAABOX	_aabox;


public:
	BaseObject(void);
	virtual ~BaseObject(void);
	virtual void Create();

	virtual void Update(float deltaTime){}

	void SetHitSide(HIT_SIDE hs){ _hitSide = hs; }
	HIT_SIDE GetHitSide() { return _hitSide;}


	const orxAABOX* GetAABox() {return &_aabox;}

protected:
	void UpdateAABox();

};

#endif //__BASEOBJECT_H__