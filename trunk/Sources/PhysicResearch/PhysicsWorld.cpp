#include "PhysicsWorld.h"


PhysicsWorld::PhysicsWorld(void)
{
	_objects[0] = new DynamicObject();
	if(_objects[0])
		_objects[0]->Create();
	
	orxVECTOR pos;
	pos.fZ = 0.0f;
	_objects[1] = new DynamicObject();
	if(_objects[1])
	{
		pos.fX = -150.0;
		pos.fY = 100.0;
		_objects[1]->Create();
		_objects[1]->SetPosition(&pos);
	}
	_objects[2] = new DynamicObject();
	if(_objects[2])
	{
		pos.fX = 150.0;
		pos.fY = 100.0;
		_objects[2]->Create();
		_objects[2]->SetPosition(&pos);
	}


	_walls[0] = new StaticObject();
	if(_walls[0])
		_walls[0]->Create();
}


PhysicsWorld::~PhysicsWorld(void)
{
	for(int i = 0; i < OBJECT_COUNT;i++)
	{
		delete _objects[i];
		_objects[i] = NULL;
	}
	if(_walls[0])
		delete _walls[0];
}

void PhysicsWorld::Update(float deltaTime)
{
	for(int i = 0; i < OBJECT_COUNT; i++)
	{
		_objects[i]->Update(deltaTime);
	}

	FindObjectWallColision();
	FindObjectWObjectColision();
}

void PhysicsWorld::FindObjectWallColision()
{
	for(int i = 0; i < OBJECT_COUNT;i++)
		if(orxAABox_Test2DIntersection(_objects[i]->GetAABox(),_walls[0]->GetAABox()))
		{
			_objects[i]->Stop();
		}
}

void PhysicsWorld::FindObjectWObjectColision()
{
	bool hit = false;

	for(int i = 0; i < OBJECT_COUNT; i++)
	{
		for(int j = 0; j < OBJECT_COUNT;j++)
		{
			if(i == j) 
				continue;
			if(orxAABox_Test2DIntersection(_objects[i]->GetAABox(),_objects[j]->GetAABox()))
			{
				if(_objects[i]->GetPosition()->fX > _objects[j]->GetPosition()->fX)
				{
					_objects[i]->SetHitSide(HS_LEFT);
					_objects[j]->SetHitSide(HS_RIGHT);
				}
				else
				{
					_objects[i]->SetHitSide(HS_RIGHT);
					_objects[j]->SetHitSide(HS_LEFT);
				}

				if(_objects[i]->IsMove()) 
					_objects[i]->Stop();
				if(_objects[j]->IsMove()) 
					_objects[j]->Stop();
				hit = true;
				break;
			}
			else
			{
				_objects[i]->SetHitSide(HS_NONE);
				_objects[j]->SetHitSide(HS_NONE);
			}
		}
		if(hit)
			break;
	}
}

void PhysicsWorld::SetSpeed(const orxVECTOR* speed)
{
	if(_objects[0])
	{
		_objects[0]->SetSpeed(speed);
	}
}