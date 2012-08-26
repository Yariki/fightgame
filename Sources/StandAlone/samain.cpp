
#include "orx.h"
#include "FFRadioButtonGroup.h"
#include "FFMovableAnimatedObject.h"

#ifndef __STANDALONE_H__
#define __STANDALONE_H__

class StandAlone
{
public:
	static StandAlone* Instance();
	static orxSTATUS orxFASTCALL EventHandler(const orxEVENT* pEvent);
	static void orxFASTCALL Update(const orxCLOCK_INFO* pClockInfo, void* pContext);
	static orxSTATUS orxFASTCALL Init();
	static orxSTATUS orxFASTCALL Run();
	static void orxFASTCALL Exit();
	static orxOBJECT*  _BallObject;
	static orxOBJECT*  _WallObject;
	static FFMovableAnimatedObject * _moveObject;

protected:
	StandAlone();
	StandAlone(const StandAlone&);
	StandAlone& operator=(const StandAlone&);

private:
	static StandAlone* _Instance;
	
};

StandAlone* StandAlone::_Instance = NULL;
orxOBJECT* StandAlone::_BallObject = NULL;
orxOBJECT* StandAlone::_WallObject = NULL;
FFMovableAnimatedObject* StandAlone::_moveObject = NULL;


StandAlone* StandAlone::Instance()
{
	if(_Instance != NULL)
		return _Instance;
	_Instance = new StandAlone;
	return _Instance;
}

StandAlone::StandAlone()
{
}

orxSTATUS orxFASTCALL StandAlone::Init()
{
	orxSTATUS eResult;
	orxCLOCK* pClock;
	orxINPUT_TYPE   eType;
	orxENUM         eID;
	const orxSTRING zInputExplosion;

	eResult = orxEvent_AddHandler(orxEVENT_TYPE_LOCALE,EventHandler);
	//eResult = orxEvent_AddHandler(orxEVENT_TYPE_PHYSICS,EventHandler);
	pClock = orxClock_FindFirst(orx2F(-1.0f),orxCLOCK_TYPE_CORE);
	eResult = orxClock_Register(pClock,Update,orxNULL,orxMODULE_ID_MAIN,
		orxCLOCK_PRIORITY_NORMAL);

	if(eResult != orxSTATUS_FAILURE)
	{
		orxLOG("\nInit app");
		orxViewport_CreateFromConfig("Viewport");
		orxInput_Load(orxSTRING_EMPTY);
        FFInputManager::GetSingleton()->LoadInputSettings();
		// create  object
		orxSTATUS configFileLoad = orxConfig_Load("../data/Ini/PhysicTemplate.ini");
		if(configFileLoad == orxSTATUS_SUCCESS)
		{
			//_BallObject = orxObject_CreateFromConfig("Ball");
			_WallObject = orxObject_CreateFromConfig("Walls");
			
			_moveObject = new FFMovableAnimatedObject("../data/Ini/MovableAnimObject.ini");
			_moveObject->Create();
			_moveObject->SetController(FFInputManager::GetSingleton()->GetPlayerController(FFCI_SECOND));
			
			//orxConfig_Load("../data/Ini/MovableAnimObject.ini");
			//_BallObject = orxObject_CreateFromConfig("MovableAnimatedEntity");

			FFVector3 gravity;
			gravity._x = 0.0;
			gravity._y = 1000.0;
			gravity._z = 0.0;
			orxPhysics_SetGravity(gravity);
			orxConfig_Load("../data/Ini/PhysicTemplate.ini");
			
		}
	}

	return eResult;
}

orxSTATUS orxFASTCALL StandAlone::EventHandler(const orxEVENT* pEvent)
{
	orxANIM_EVENT_PAYLOAD *pstPayload;

	/* Gets event payload */
	pstPayload = (orxANIM_EVENT_PAYLOAD *)pEvent->pstPayload;

	/* Depending on event type */
	switch(pEvent->eID)
	{
	case orxANIM_EVENT_START:
		{
			/* Logs info */
			orxLOG("Animation <%s>@<%s> has started!", pstPayload->zAnimName, orxObject_GetName(orxOBJECT(pEvent->hRecipient)));

			break;
		}

	case orxANIM_EVENT_STOP:
		{
			/* Logs info */
			orxLOG("Animation <%s>@<%s> has stopped!", pstPayload->zAnimName, orxObject_GetName(orxOBJECT(pEvent->hRecipient)));

			break;
		}

	case orxANIM_EVENT_CUT:
		{
			/* Logs info */
			orxLOG("Animation <%s>@<%s> has been cut!", pstPayload->zAnimName, orxObject_GetName(orxOBJECT(pEvent->hRecipient)));

			break;
		}

	case orxANIM_EVENT_LOOP:
		{
			/* Logs info */
			orxLOG("Animation <%s>@<%s> has looped!", pstPayload->zAnimName, orxObject_GetName(orxOBJECT(pEvent->hRecipient)));

			break;
		}

	case orxANIM_EVENT_CUSTOM_EVENT:
		{
			/* Logs info */
			orxLOG("Animation <%s>@<%s> has sent the event [%s]!", pstPayload->zAnimName, orxObject_GetName(orxOBJECT(pEvent->hRecipient)), pstPayload->zCustomEventName);

			break;
		}
	}

	//if(pEvent->eID == orxPHYSICS_EVENT_CONTACT_ADD)
	//{
	//	orxOBJECT *obj1, *obj2;
	//	obj1 = orxOBJECT(pEvent->hRecipient);
	//	obj2 = orxOBJECT(pEvent->hSender);




	//	orxLOG("CONTACT ADD!!!!");

	//}


	return orxSTATUS_SUCCESS;
}

void orxFASTCALL StandAlone::Update(const orxCLOCK_INFO* pClockInfo, void* pContext)
{
	FFVector3 impulse;
	if(orxInput_IsActive("Right"))
	{
 		impulse._x = 0.25;
		impulse._y = 0.0;
		impulse._z = 0.0;
		//orxObject_ApplyImpulse(_BallObject,&impulse,NULL);
	}
	else if(orxInput_IsActive("Left"))
	{
		impulse._x = -0.25;
		impulse._y = 0.0;
		impulse._z = 0.0;
		//orxObject_ApplyImpulse(_BallObject,&impulse,NULL);
		
	}
	else if(orxInput_IsActive("Up"))
	{
		impulse._x = 0.0;
		impulse._y = -1.0;
		impulse._z = 0.0;
		//orxObject_ApplyForce(_BallObject,&impulse,NULL);

	}
	else if(orxInput_IsActive("Space"))
	{
		/*if(_BallObject)
		orxObject_Delete(_BallObject);
		_BallObject = */
		orxObject_CreateFromConfig("Ball");
	}
	if(_moveObject)
		_moveObject->Update(pClockInfo);

}

orxSTATUS orxFASTCALL StandAlone::Run()
{
	return orxSTATUS_SUCCESS;
}

void orxFASTCALL StandAlone::Exit()
{

	if(_BallObject)
		orxObject_Delete(_BallObject);
	if(_WallObject)
		orxObject_Delete(_WallObject);
	if(_moveObject)
		delete _moveObject;

	return;
}


#endif //__STANDALONE_H__



int main(int argc, char** argv)
{
	orx_Execute(argc,argv,StandAlone::Init,StandAlone::Run,StandAlone::Exit);
	return 0;
}