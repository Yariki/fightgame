
#include "FFPhysicsWorld.h"


FFPhysicsWorld::FFPhysicsWorld()
{

}

FFPhysicsWorld::~FFPhysicsWorld()
{
	_listDynObject.clear();
	_listWall.clear();
}

void FFPhysicsWorld::UpdateWorld(float deltaTime)
{
	for(size_t i = 0; i < _listDynObject.size(); i++)
	{
		_listDynObject.at(i)->UpdatePhysics(deltaTime);
	}
	for(size_t i = 0; i< _listWall.size();i++)
	{
		_listWall.at(i)->UpdatePhysics(deltaTime);
	}
	FindObjectWallcolision();
	FindObjectWObjectColision();
}

void FFPhysicsWorld::FindObjectWallcolision()
{
	for(size_t i = 0;i < _listDynObject.size(); i++)
		for(size_t j = 0;j < _listWall.size(); j++)
		{
			if(orxAABox_Test2DIntersection(_listDynObject.at(i)->GetAABox(),_listWall.at(j)->GetAABox()))
			{
				_listDynObject.at(i)->Stop();
			}
		}
}


void FFPhysicsWorld::FindObjectWObjectColision()
{
	bool hit = false;
	size_t size = _listDynObject.size();

	for(size_t i = 0; i < size; i++)
	{
		for(size_t j = i + 1; j < size;j++)
		{
			if(orxAABox_Test2DIntersection(_listDynObject.at(i)->GetAABox(),_listDynObject.at(j)->GetAABox()))
			{
				if(_listDynObject.at(i)->GetPosition()._x > _listDynObject.at(j)->GetPosition()._x)
				{
					_listDynObject.at(i)->SetHitSide(FHS_LEFT);
					_listDynObject.at(j)->SetHitSide(FHS_RIGHT);
				}
				else
				{
					_listDynObject.at(i)->SetHitSide(FHS_RIGHT);
					_listDynObject.at(j)->SetHitSide(FHS_LEFT);
				}

				if(_listDynObject.at(i)->IsMove()) 
					_listDynObject.at(i)->Stop();
				if(_listDynObject.at(j)->IsMove()) 
					_listDynObject.at(j)->Stop();
				hit = true;
				break;
			}
			else
			{
				_listDynObject.at(i)->SetHitSide(FHS_NONE);
				_listDynObject.at(j)->SetHitSide(FHS_NONE);
			}
		}
		if(hit)
			break;
	}
}

void FFPhysicsWorld::SetSpeed(const FFVector3& speed)
{
	for(size_t i = 0; i < _listDynObject.size();i++)
	{
		_listDynObject.at(i)->SetSpeed((FFVector3&)speed);
	}
}

void FFPhysicsWorld::AddObject(const FFObject* obj)
{
	
	_listDynObject.push_back((FFObject*)obj);
}

void FFPhysicsWorld::AddWall(const FFObject* wall)
{
	_listWall.push_back((FFObject*)wall);
}