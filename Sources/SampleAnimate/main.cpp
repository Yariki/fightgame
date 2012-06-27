
#include "orx.h"

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
	static orxOBJECT*  _Object;

protected:
	StandAlone();
	StandAlone(const StandAlone&);
	StandAlone& operator=(const StandAlone&);

private:
	static StandAlone* _Instance;
	
};

StandAlone* StandAlone::_Instance = NULL;
orxOBJECT* StandAlone::_Object = NULL;

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

	eResult = orxEvent_AddHandler(orxEVENT_TYPE_ANIM,EventHandler);
	pClock = orxClock_FindFirst(orx2F(-1.0f),orxCLOCK_TYPE_CORE);
	eResult = orxClock_Register(pClock,Update,orxNULL,orxMODULE_ID_MAIN,
		orxCLOCK_PRIORITY_NORMAL);

	if(eResult != orxSTATUS_FAILURE)
	{
		orxLOG("\nInit app");
		orxViewport_CreateFromConfig("Viewport");
		

		// create  object
		orxSTATUS configFileLoad = orxConfig_Load("../Data/Ini/DynamicAminObject.ini");
		if(configFileLoad == orxSTATUS_SUCCESS)
		{
			orxInput_Load(orxSTRING_EMPTY);
			/*orxInput_GetBinding("Explosion",0,&eType,&eID);
			zInputExplosion = orxInput_GetBindingName(eType,eID);
			orxLOG("\n '%s' will Explosion Object",zInputExplosion);*/
			StandAlone::_Object = orxObject_CreateFromConfig("DynamicAnimatedEntity");
			orxObject_SetAnimFrequency(StandAlone::_Object,1.0f);
			orxObject_SetTargetAnim(StandAlone::_Object,"LeftAnim");
			orxLOG("\n Object was created");

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
			orxLOG("Animation <%s>@<%s> has started!", pstPayload->zAnimName);

			break;
		}

	case orxANIM_EVENT_STOP:
		{
			/* Logs info */
			orxLOG("Animation <%s>@<%s> has stopped!", pstPayload->zAnimName);

			break;
		}

	case orxANIM_EVENT_CUT:
		{
			/* Logs info */
		
			orxLOG("Animation <%s>@<%s> has been cut!", pstPayload->zAnimName);

			break;
		}

	case orxANIM_EVENT_LOOP:
		{
			/* Logs info */
			orxLOG("Animation <%s>@<%s> has looped!", pstPayload->zAnimName);

			break;
		}

	case orxANIM_EVENT_CUSTOM_EVENT:
		{
			/* Logs info */
			orxLOG("Animation <%s>@<%s> has sent the event [%s]!", pstPayload->zAnimName);

			break;
		}
	}

	return orxSTATUS_SUCCESS;
}

void orxFASTCALL StandAlone::Update(const orxCLOCK_INFO* pClockInfo, void* pContext)
{
	orxObject_SetTargetAnim(StandAlone::_Object,"LeftAnim");
}

orxSTATUS orxFASTCALL StandAlone::Run()
{
	return orxSTATUS_SUCCESS;
}

void orxFASTCALL StandAlone::Exit()
{
	orxObject_Delete(StandAlone::_Object);
	return;
}


#endif //__STANDALONE_H__



int main(int argc, char** argv)
{
	orx_Execute(argc,argv,StandAlone::Init,StandAlone::Run,StandAlone::Exit);
	return 0;
}