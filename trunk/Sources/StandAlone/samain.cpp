
#include "orx.h"
#include "FFRadioButtonGroup.h"

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
    //static FFPreview* _preview;
    //static std::vector<FFButton*> _list;
    static FFRadioButtonGroup* _radioGroup;
    static FFRadioButtonGroup* _radioGroup1;

protected:
	StandAlone();
	StandAlone(const StandAlone&);
	StandAlone& operator=(const StandAlone&);

private:
	static StandAlone* _Instance;
	
};

StandAlone* StandAlone::_Instance = NULL;
orxOBJECT* StandAlone::_Object = NULL;
//FFPreview* StandAlone::_preview = NULL;
//std::vector<FFButton*> StandAlone::_list;
FFRadioButtonGroup* StandAlone::_radioGroup =  NULL;
FFRadioButtonGroup* StandAlone::_radioGroup1 =  NULL;

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
		orxSTATUS configFileLoad = orxConfig_Load("../data/Ini/Buttons.ini");
		if(configFileLoad == orxSTATUS_SUCCESS)
		{
			

            orxVECTOR pos;
            pos.fX = -450.0;
            pos.fY = -300.0;
            pos.fZ = 0.0;
            StandAlone::_radioGroup = new FFRadioButtonGroup(NULL,pos,NULL);
            StandAlone::_radioGroup->AddItem(string("Item 1"));
            StandAlone::_radioGroup->AddItem(string("Item 2"));
            StandAlone::_radioGroup->AddItem(string("Item 3"));
            pos.fY = 0;
            StandAlone::_radioGroup1 = new FFRadioButtonGroup(NULL,pos,NULL);
            StandAlone::_radioGroup1->AddItem(string("Item 1"));
            StandAlone::_radioGroup1->AddItem(string("Item 2"));
            StandAlone::_radioGroup1->AddItem(string("Item 3"));
            StandAlone::_radioGroup1->AddItem(string("Item 4"));
            StandAlone::_radioGroup1->AddItem(string("Item 5"));

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

	return orxSTATUS_SUCCESS;
}

void orxFASTCALL StandAlone::Update(const orxCLOCK_INFO* pClockInfo, void* pContext)
{
	/*if(orxInput_IsActive("Explosion"))
	{
 		orxObject_SetTargetAnim(StandAlone::_Object,"WalkRight");
	}
	else if(orxInput_IsActive("GoRight"))
	{
		orxObject_SetTargetAnim(StandAlone::_Object,"WalkRight");
	}
	else if(orxInput_IsActive("GoLeft"))
	{
		orxObject_SetTargetAnim(StandAlone::_Object,"WalkLeft");
	}
	else
	{
		orxObject_SetTargetAnim(StandAlone::_Object,"WalkRight");
	}*/
    orxVECTOR vPos;
	if(orxRender_GetWorldPosition(orxMouse_GetPosition(&vPos),&vPos))
	{
		orxOBJECT* obj = orxObject_Pick(&vPos);
      /*  for(size_t i = 0; i < StandAlone::_list.size(); i++)
        {
            StandAlone::_list.at(i)->Update(obj);
        }*/
        StandAlone::_radioGroup->Update(obj);
        StandAlone::_radioGroup1->Update(obj);
    }
}

orxSTATUS orxFASTCALL StandAlone::Run()
{
	return orxSTATUS_SUCCESS;
}

void orxFASTCALL StandAlone::Exit()
{
	//orxObject_Delete(StandAlone::_Object);
    /*if(StandAlone::_preview)
        delete StandAlone::_preview;*/
  /*  for(size_t i = StandAlone::_list.size(); i < StandAlone::_list.size(); i++)
    {
        delete StandAlone::_list.at(i);
    }
    StandAlone::_list.clear();   */ 

    if(StandAlone::_radioGroup)
        delete StandAlone::_radioGroup;
     if(StandAlone::_radioGroup1)
        delete StandAlone::_radioGroup1;

	return;
}


#endif //__STANDALONE_H__



int main(int argc, char** argv)
{
	orx_Execute(argc,argv,StandAlone::Init,StandAlone::Run,StandAlone::Exit);
	return 0;
}