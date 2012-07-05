
#include "orx.h"
#include "FFPreview.h"

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
    static FFPreview* _preview;
    static std::vector<FFPreview*> _listPreview;

protected:
	StandAlone();
	StandAlone(const StandAlone&);
	StandAlone& operator=(const StandAlone&);

private:
	static StandAlone* _Instance;
	
};

StandAlone* StandAlone::_Instance = NULL;
orxOBJECT* StandAlone::_Object = NULL;
FFPreview* StandAlone::_preview = NULL;
std::vector<FFPreview*> StandAlone::_listPreview;

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
		

		// create  object
		orxSTATUS configFileLoad = orxConfig_Load("../Data/Ini/StaticObject.ini");
		if(configFileLoad == orxSTATUS_SUCCESS)
		{
			orxInput_Load(orxSTRING_EMPTY);
			/*StandAlone::_Object = orxObject_CreateFromConfig("StaticEntity");

			orxOBJECT* obj = StandAlone::_Object;
			for ( orxOBJECT* o = orxObject_GetOwnedChild(obj); o != orxNULL; o = orxObject_GetOwnedSibling(o))
			{
				orxLOG("Name = %s",orxObject_GetName(o));
				orxObject_SetTextString(o,"Set Text");
			}*/
            orxVECTOR pos;
            pos.fX = -300.0;
            pos.fY = -300.0;
            pos.fZ = 0.0;
            float dx = 150;
            float dy = 150;
            for(int i = 0; i < 2;i++)
            {
                for(int j = 0 ; j < 5; j++)
                {
                    FFPreview* preview = new FFPreview(NULL,pos,NULL);       
                    StandAlone::_listPreview.push_back(preview);
                    pos.fX += dx;
                }
                pos.fX = -300;
                pos.fY += dy;
            }
             
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
        for(size_t i = 0; i < StandAlone::_listPreview.size(); i++)
        {
            StandAlone::_listPreview.at(i)->Update(obj);
        }
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
    for(size_t i = StandAlone::_listPreview.size(); i < StandAlone::_listPreview.size(); i++)
    {
        delete StandAlone::_listPreview.at(i);
    }
    StandAlone::_listPreview.clear();    
	return;
}


#endif //__STANDALONE_H__



int main(int argc, char** argv)
{
	orx_Execute(argc,argv,StandAlone::Init,StandAlone::Run,StandAlone::Exit);
	return 0;
}