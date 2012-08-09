#include "FFApplication.h"
#include "FFInputManager.h"

FFApplication* FFApplication::_instance = NULL;


FFApplication::FFApplication(void)
{
	_manager = orxNULL;
}


FFApplication::~FFApplication(void)
{
	if(_manager)
	{
		delete _manager;
	}
	FFInputManager::GetSingleton()->UnloadSettings();
}


FFApplication* FFApplication::instance()
{
	if(_instance != NULL)
		return _instance;
	_instance = new FFApplication();
	return _instance;

}


orxSTATUS orxFASTCALL FFApplication::Init()
{
	FFApplication::instance()->Load();

	orxCLOCK* pClock  = orxClock_FindFirst(orx2F(-1.0f),orxCLOCK_TYPE_CORE);
	orxClock_Register(pClock,Update,orxNULL,orxMODULE_ID_MAIN,
		orxCLOCK_PRIORITY_NORMAL);

	orxSTATUS res =  orxEvent_AddHandler(orxEVENT_TYPE_USER_DEFINED,UserEventHandler);



	return res;
}

void FFApplication::Update(const orxCLOCK_INFO* pClockInfo,void* pContext)
{
	FFApplication::instance()->UpdateAll(pClockInfo);
}

orxSTATUS FFApplication::UserEventHandler(const orxEVENT* pEvent)
{
	SceneEvent* ev = static_cast<SceneEvent*>(pEvent->pstPayload);

	switch(ev->GetEvent())
	{
		case FFUE_APPLICATION_CLOSE:	
			orxLOG("FFUE_APPLICATION_CLOSE");
			//orxSystem_Exit();
			return orxSTATUS_SUCCESS;
	}

	FFApplication::instance()->UserEvent(pEvent);

	return orxSTATUS_SUCCESS;
}

orxSTATUS orxFASTCALL  FFApplication::Run()
{
	return orxSTATUS_SUCCESS;
}

void orxFASTCALL  FFApplication::Exit()
{
	delete FFApplication::instance();
	return;
}


void FFApplication::Main(int argc, char** argv)
{
	orx_Execute(argc,argv, FFApplication::Init, FFApplication::Run,FFApplication::Exit);
}

void FFApplication::UpdateAll(const orxCLOCK_INFO* pClockInfo)
{
	if(_manager)
	{
		_manager->Update(pClockInfo);
	}
}

void FFApplication::UserEvent(const orxEVENT* pEvent)
{
	if(_manager)
	{
		_manager->UserEventHandler(pEvent);
	}
}


void FFApplication::Load()
{
	if(orxConfig_HasSection(FF_MAIN_VIEWPORT) == orxTRUE)
	{
		orxViewport_CreateFromConfig(FF_MAIN_VIEWPORT);
		orxInput_Load(orxSTRING_EMPTY);
		FFInputManager::GetSingleton()->LoadInputSettings();
		_manager = new FFGameManager();
		_manager->Load();
	}
}
