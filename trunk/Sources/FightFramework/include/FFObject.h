#ifndef __FFOBJECT_H__
#define __FFOBJECT_H__

#include "FFInclude.h"
#include "FFVector3.h"

class FFObject
{
protected:
	FFVector3 _size;
	FFVector3	_position;
	FFVector3	_scale;
	FFVector3	_forces;
	FFVector3	_acceleration;
	FFVector3	_speed;
	float		_mass;

	orxCOLOR	_color;
	orxCHAR	_nameCfgFile[MAX_FILE_PATH];
	orxFLOAT	_rotation;
	orxOBJECT*	_object;

	FF_TYPE_ENTITY _typeEntity;
	FF_HIT_SIDE	_hitSide;

	orxAABOX _aabox;

public:
	FFObject(void);
	FFObject(orxSTRING filename);
	virtual ~FFObject(void);

public:
	virtual void		Create() = 0;
	virtual void		UpdatePhysics(float deltaTime) {}

	orxCOLOR			GetColor();
	void				SetColor(orxCOLOR& color);

	FFVector3			GetPosition();
	void				SetPosition(FFVector3& pos);

	orxFLOAT			GetRotation();
	void				SetRotation(orxFLOAT& rot);

	FFVector3			GetScale();
	void				SetScale(FFVector3& scale);

	FFVector3			GetSize();
	
	void				SetHitSide(FF_HIT_SIDE side) {_hitSide = side;}
	FF_HIT_SIDE			GetHitSide() {return _hitSide;}

	float				GetMass() {return _mass;}
	void				SetMass(float mass) {_mass = mass;}

	const FFVector3*	GetSpeed() {return &_speed;}
	void				SetSpeed(FFVector3& speed);

	const orxAABOX*		GetAABox() { return &_aabox;}

	FF_TYPE_ENTITY		GetTypeEntity() {return _typeEntity;}

	bool				IsMove();
	void				Stop();

protected:
	virtual void		UpdateAABox();


};

#endif //__FFOBJECT_H__