
#include "orx.h"
#include <vector>

using namespace std;

#define MAX_NAME 260

#define BUTTON_SECTION "Button"
#define CHECKBOX_SECTION "CheckButton"


#define ANIMATION_NORMAL "AnimationNormal"
#define ANIMATION_HOVER "AnimationHover"
#define ANIMATION_PRESS "AnimationPress"
#define ANIMATION_CHECK "AnimationCheck"

enum BUTTON_STATE
{
	BTN_NORMAL = 0,
	BTN_HOVER,
	BTN_PRESS
};

enum CHECKBOX_STATE
{
	CHB_NORMAL = 0,
	CHB_CHECK
};


enum GUI_EVENT_TYPE
{
	GET_BUTTON_CLICK,
	GET_CHECKBOX_CHECK,
	GET_CHECKBOX_UNCHEK
};

struct GUI_EVENT
{
	GUI_EVENT_TYPE	_event;
	orxCHAR			_name[MAX_NAME];
};


// define for choose btn animation
#define BTNRIGHT_ANIM_NORMAL	"NormalBtnRightAnim"
#define BTNRIGHT_ANIM_HOVER		"HoverBtnRightAnim"
#define BTNRIGHT_ANIM_PRESS		"PressBtnRightAnim"

#define BTNLEFT_ANIM_NORMAL		"NormalBtnLeftAnim"
#define BTNLEFT_ANIM_HOVER		"HoverBtnLeftAnim"
#define BTNLEFT_ANIM_PRESS		"PressBtnLeftAnim"

#define BUTTON_LEFT_NAME		"BtnLeft"
#define BUTTON_RIGHT_NAME		"BtnRight"
#define TEXT_CHOOSE				"CaptionChooseButton"

#define CHOOSEBUTTON_SECTION	"ChooseButton"

class ComboChooseButton
{
private:
	orxCHAR	_name[MAX_NAME];
	orxVECTOR	_position;

	orxOBJECT* _mainChoose;
	orxOBJECT* _leftButton;
	orxOBJECT* _rightButton;
	orxOBJECT* _captionChoose;

	vector<std::string> _items;
	int _currentItem;


public:
	ComboChooseButton(orxVECTOR& position);
	virtual ~ComboChooseButton();

	void Update(orxOBJECT* selectedObject);
	void SetNormal() {NormalRight();NormalLeft();}
	void AddItem(std::string item) {_items.push_back(item);}
	void SetFirstCurrent();

private:
	void NormalRight()	{ if(_rightButton != orxNULL) orxObject_SetTargetAnim(_rightButton,BTNRIGHT_ANIM_NORMAL);}
	void NormalLeft() { if(_leftButton != orxNULL) orxObject_SetTargetAnim(_leftButton,BTNLEFT_ANIM_NORMAL);}

	void HoverRight() {if(_rightButton != orxNULL) orxObject_SetTargetAnim(_rightButton,BTNRIGHT_ANIM_HOVER);}
	void HoverLeft() { if(_leftButton != orxNULL) orxObject_SetTargetAnim(_leftButton,BTNLEFT_ANIM_HOVER);}

	void PressRight() {if(_rightButton != orxNULL) orxObject_SetTargetAnim(_rightButton,BTNRIGHT_ANIM_PRESS);}
	void PressLeft() { if(_leftButton != orxNULL) orxObject_SetTargetAnim(_leftButton,BTNLEFT_ANIM_PRESS);}

	void SetCurrentItem(bool direction); // true - left, false - right
};


ComboChooseButton::ComboChooseButton(orxVECTOR& position)
{
	_position = position;
	_currentItem = -1;
	_mainChoose = orxObject_CreateFromConfig(CHOOSEBUTTON_SECTION);
	if(_mainChoose)
	{
		orxObject_SetPosition(_mainChoose,&_position);
		for(orxOBJECT* obj = orxObject_GetOwnedChild(_mainChoose); obj != orxNULL; obj = orxObject_GetOwnedSibling(obj))
		{
			const orxSTRING name = orxObject_GetName(obj);
			if(!orxString_Compare(name,BUTTON_LEFT_NAME))
			{
				_leftButton = obj;
			}
			else if(!orxString_Compare(name,BUTTON_RIGHT_NAME))
			{
				_rightButton = obj;
			}
			else if(!orxString_Compare(name,TEXT_CHOOSE))
			{
				_captionChoose = obj;
			}
		}

	}
}

ComboChooseButton::~ComboChooseButton()
{
	if(_mainChoose)
		orxObject_Delete(_mainChoose);
	_mainChoose = orxNULL;
	_leftButton = orxNULL;
	_rightButton = orxNULL;
	_captionChoose = orxNULL;
}


void ComboChooseButton::Update(orxOBJECT* selectedObject)
{
	if(selectedObject == _leftButton)
		if(orxInput_IsActive("LeftPress")&& orxInput_HasNewStatus("LeftPress"))
		{
			PressLeft();
			//orxLOG("PRESS  FIRST LEFT!!!!");
			SetCurrentItem(true);
		}
		else if(orxInput_IsActive("LeftPress"))
		{
			PressLeft();
			//orxLOG("PRESS  LEFT!!!!");
		}
		else
		{
			HoverLeft();
			//orxLOG("HOVER LEFT!!!!");
		}
	else if(selectedObject == _rightButton)
		if(orxInput_IsActive("LeftPress")&& orxInput_HasNewStatus("LeftPress"))
		{
			PressRight();
			SetCurrentItem(false);
		}
		else if(orxInput_IsActive("LeftPress"))
		{
			PressRight();
		}
		else
			HoverRight();
	else
	{
		NormalLeft();
		NormalRight();
	}
}


void ComboChooseButton::SetFirstCurrent()
{
	if(_items.size() > 0)
	{
		_currentItem = 0;
		orxObject_SetTextString(_captionChoose,_items.at(0).c_str());
	}
}

void ComboChooseButton::SetCurrentItem(bool direction)
{
	if(direction)
	{
		_currentItem--;
		if(_currentItem < 0)
			_currentItem = _items.size() - 1;
	}
	else
	{
		_currentItem++;
		if(_currentItem >= _items.size())
			_currentItem = 0;
	}
	orxObject_SetTextString(_captionChoose,_items.at(_currentItem).c_str());
}

class CheckBox
{
private:
	orxCHAR  _normalAnim[MAX_NAME];
	orxCHAR _checkAnim[MAX_NAME];

	orxCHAR _name[MAX_NAME];

	orxVECTOR _position;

	orxOBJECT* _object;

	CHECKBOX_STATE  _state;



public:
	CheckBox(orxVECTOR& pos, orxCHAR* name);
	virtual ~CheckBox();

	CHECKBOX_STATE		GetState() {  return _state;}
	void				SetState(CHECKBOX_STATE state) {_state = state;}

	orxOBJECT*	const	GetObject() {return _object;}

	void				Normal() { if(_object) orxObject_SetTargetAnim(_object,_normalAnim); _state = CHB_NORMAL; }
	void				Check() { if(_object) orxObject_SetTargetAnim(_object,_checkAnim); _state = CHB_CHECK;}


	orxCHAR*			GetName()	{return _name;}

};

CheckBox::CheckBox(orxVECTOR& pos, orxCHAR* name)
{
	_position = pos;
	_object = orxObject_CreateFromConfig(CHECKBOX_SECTION);
	_state = CHB_NORMAL;
	if(_object && orxConfig_PushSection(CHECKBOX_SECTION) == orxSTATUS_SUCCESS)
	{
		orxString_Copy(_normalAnim,orxConfig_GetString(ANIMATION_NORMAL));
		orxString_Copy(_checkAnim,orxConfig_GetString(ANIMATION_CHECK));
		orxObject_SetPosition(_object,&_position);
		orxString_Copy(_name,name);
		for ( orxOBJECT* o = orxObject_GetOwnedChild(_object); o != orxNULL; o = orxObject_GetOwnedChild(o))
		{
			orxObject_SetTextString(o,_name);
		}
		orxConfig_PopSection();
	}
}

CheckBox::~CheckBox()
{
	if(_object)
		orxObject_Delete(_object);
}










class Button
{
private:
	orxCHAR  _normalAnim[MAX_NAME];
	orxCHAR _hoverAnim[MAX_NAME];
	orxCHAR _pressAnim[MAX_NAME];

	orxCHAR _name[MAX_NAME];
	
	orxVECTOR _position;

	orxOBJECT* _object;

	BUTTON_STATE  _state;


public:
	Button(orxVECTOR& vec, orxCHAR* name);
	virtual ~Button(void);

	BUTTON_STATE		GetState();
	void				SetState(BUTTON_STATE state);

	orxOBJECT*	const	GetObject();

	void				Normal() { if(_object) orxObject_SetTargetAnim(_object,_normalAnim); _state = BTN_NORMAL; }
	void				Hover() { if(_object) orxObject_SetTargetAnim(_object,_hoverAnim); _state = BTN_HOVER; }
	void				Press() { if(_object) orxObject_SetTargetAnim(_object,_pressAnim); _state = BTN_PRESS;}


	orxCHAR*			GetName()	{return _name;}

};


Button::Button(orxVECTOR& vec,orxCHAR* name)
{
	_position = vec;
	_object = orxObject_CreateFromConfig(BUTTON_SECTION);
	if(_object && orxConfig_PushSection(BUTTON_SECTION) == orxSTATUS_SUCCESS)
	{
		orxString_Copy(_normalAnim,orxConfig_GetString(ANIMATION_NORMAL));
		orxString_Copy(_hoverAnim,orxConfig_GetString(ANIMATION_HOVER));
		orxString_Copy(_pressAnim,orxConfig_GetString(ANIMATION_PRESS));
		orxObject_SetPosition(_object,&_position);
		orxString_Copy(_name,name);
		for ( orxOBJECT* o = orxObject_GetOwnedChild(_object); o != orxNULL; o = orxObject_GetOwnedChild(o))
		{
			orxObject_SetTextString(o,_name);
		}
		orxConfig_PopSection();
	}
}

Button::~Button()
{
	if(_object)
		orxObject_Delete(_object);
}

BUTTON_STATE Button::GetState()
{
	return _state;
}

void Button::SetState(BUTTON_STATE state)
{
	_state = state;
}

orxOBJECT* const Button::GetObject()
{
	return _object;
}










class StandAlone
{
public:
	static StandAlone* Instance();
	static orxSTATUS orxFASTCALL EventHandler(const orxEVENT* pEvent);
	static orxSTATUS orxFASTCALL UserEventHandler(const orxEVENT* pEvent);
	static void orxFASTCALL Update(const orxCLOCK_INFO* pClockInfo, void* pContext);
	static orxSTATUS orxFASTCALL Init();
	static orxSTATUS orxFASTCALL Run();
	static void orxFASTCALL Exit();
	static orxOBJECT*  _Object;
	static vector<Button*> _listButtons;
	static vector<CheckBox*> _listCheck;
	static ComboChooseButton* _chooseButton;

protected:
	StandAlone();
	StandAlone(const StandAlone&);
	StandAlone& operator=(const StandAlone&);

private:
	static StandAlone* _Instance;
	
};

StandAlone* StandAlone::_Instance = NULL;
orxOBJECT* StandAlone::_Object = NULL;
vector<Button*> StandAlone::_listButtons;
vector<CheckBox*> StandAlone::_listCheck;
ComboChooseButton* StandAlone::_chooseButton = NULL;


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
	eResult = orxEvent_AddHandler(orxEVENT_TYPE_USER_DEFINED,UserEventHandler);
	pClock = orxClock_FindFirst(orx2F(-1.0f),orxCLOCK_TYPE_CORE);
	eResult = orxClock_Register(pClock,Update,orxNULL,orxMODULE_ID_MAIN,
		orxCLOCK_PRIORITY_NORMAL);

	if(eResult != orxSTATUS_FAILURE)
	{
		orxLOG("\nInit app");
		orxViewport_CreateFromConfig("Viewport");
		

		// create  object
		orxSTATUS configFileLoad = orxConfig_Load("../Data/Ini/Buttons.ini");
		if(configFileLoad == orxSTATUS_SUCCESS)
		{
			configFileLoad = orxInput_Load(orxSTRING_EMPTY);

			orxVECTOR startPos;
			startPos.fX = 0.0;
			startPos.fY = -100.0;
			startPos.fZ = 0.0;
			orxFLOAT delta = 50.0;
			orxCHAR name[MAX_NAME] = "Button %d";
			for(int i = 0; i < 3; i++)
			{
				orxCHAR temp[MAX_NAME];
				orxString_Print(temp,name,i);
				Button* btn = new Button(startPos,temp);
				StandAlone::Instance()->_listButtons.push_back(btn);
				startPos.fY += delta;
			}
			orxString_Copy(name,"Check %d");
			for(int i = 0 ; i< 3;i++)
			{
				orxCHAR temp[MAX_NAME];
				orxString_Print(temp,name,i);
				CheckBox* btn = new CheckBox(startPos,temp);
				StandAlone::Instance()->_listCheck.push_back(btn);
				startPos.fY += delta;

			}

			StandAlone::_chooseButton = new ComboChooseButton(startPos);
			orxCHAR t[MAX_NAME] = "Item %d";
			for(int i  = 0; i < 10; i++)
			{
				orxCHAR temp[MAX_NAME];
				orxString_Print(temp,t,i);
				StandAlone::_chooseButton->AddItem(temp);
			}
			StandAlone::_chooseButton->SetFirstCurrent();
		}
	}

	return eResult;
}

orxSTATUS orxFASTCALL StandAlone::UserEventHandler(const orxEVENT* pEvent)
{
	GUI_EVENT* ge =  (GUI_EVENT*)pEvent->pstPayload;

	if(ge)
	{
		switch(ge->_event)
		{
		case GET_BUTTON_CLICK:
			orxLOG("Button click: %s",ge->_name);
			break;
		case GET_CHECKBOX_CHECK:
			orxLOG("CheckBox checked: %s",ge->_name);
			break;
		case GET_CHECKBOX_UNCHEK:
			orxLOG("CheckBox unchecked: %s",ge->_name);
			break;
		}
		delete ge;
	}


	return orxSTATUS_SUCCESS;
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
	orxVECTOR vPos;
	if(orxRender_GetWorldPosition(orxMouse_GetPosition(&vPos),&vPos))
	{
		orxOBJECT* sobj = orxObject_Pick(&vPos);
		if(sobj)
		{
			orxOBJECT* obj = sobj;
			orxSTRUCTURE* struc = orxObject_GetOwner(obj);
			if( struc != orxNULL) 
				obj = (orxOBJECT*)struc;

			unsigned int size = StandAlone::Instance()->_listButtons.size();
			for(unsigned int i = 0; i < size;i++)
			{
				Button* btn = StandAlone::Instance()->_listButtons.at(i);
				if(obj == btn->GetObjectA())
				{
					if(orxInput_IsActive("LeftPress")&& orxInput_HasNewStatus("LeftPress"))//&& orxInput_HasNewStatus("RigthPress")
					{
						btn->Press();
						GUI_EVENT * ev = new GUI_EVENT();
						ev->_event = GET_BUTTON_CLICK;
						orxString_Copy(ev->_name,btn->GetName());
						orxEVENT_SEND(orxEVENT_TYPE_USER_DEFINED,0,btn,orxNULL,ev);
					}
					else if(orxInput_IsActive("LeftPress"))
					{
						btn->Press();
					}
					else
						btn->Hover();
					break;
				}

			}

			size = StandAlone::Instance()->_listCheck.size();
			for(unsigned int i = 0; i < size;i++)
			{
				CheckBox* btn = StandAlone::Instance()->_listCheck.at(i);
				if(obj == btn->GetObjectA())
				{
					if(orxInput_IsActive("LeftPress")&& orxInput_HasNewStatus("LeftPress") && btn->GetState() != CHB_CHECK)//&& orxInput_HasNewStatus("RigthPress")
					{
						btn->Check();
						GUI_EVENT * ev = new GUI_EVENT();
						ev->_event = GET_CHECKBOX_CHECK;
						orxString_Copy(ev->_name,btn->GetName());
						orxEVENT_SEND(orxEVENT_TYPE_USER_DEFINED,0,btn,orxNULL,ev);
					}
					else if(orxInput_IsActive("LeftPress")&& orxInput_HasNewStatus("LeftPress") && btn->GetState() == CHB_CHECK )
					{
						btn->Normal();
						GUI_EVENT * ev = new GUI_EVENT();
						ev->_event = GET_CHECKBOX_UNCHEK;
						orxString_Copy(ev->_name,btn->GetName());
						orxEVENT_SEND(orxEVENT_TYPE_USER_DEFINED,0,btn,orxNULL,ev);

					}
					break;
				}

			}

			StandAlone::_chooseButton->Update(sobj);

		}
		else
		{
			unsigned int size = StandAlone::Instance()->_listButtons.size();
			for(unsigned int i = 0; i < size;i++)
			{
				Button* btn = StandAlone::Instance()->_listButtons.at(i);
				if(btn->GetState() != BTN_NORMAL)
					btn->Normal();
			}

			size = StandAlone::Instance()->_listCheck.size();
			for(unsigned int i = 0; i < size;i++)
			{
				CheckBox* btn = StandAlone::Instance()->_listCheck.at(i);
				if(btn->GetState() == CHB_NORMAL)
					btn->Normal();
				else
					btn->Check();

			}
			StandAlone::_chooseButton->SetNormal();
		}
	}
}

orxSTATUS orxFASTCALL StandAlone::Run()
{
	return orxSTATUS_SUCCESS;
}

void orxFASTCALL StandAlone::Exit()
{
	if(StandAlone::_Object)
		orxObject_Delete(StandAlone::_Object);
	

	for(unsigned int i = 0; i < StandAlone::Instance()->_listButtons.size();i++)
	{
		delete StandAlone::Instance()->_listButtons.at(i);
	}
	for(unsigned int i = 0; i < StandAlone::Instance()->_listCheck.size();i++)
	{
		delete StandAlone::Instance()->_listCheck.at(i);
	}
	delete StandAlone::_chooseButton;

	StandAlone::Instance()->_listButtons.clear();
	StandAlone::Instance()->_listCheck.clear();

}






// main program

int main(int argc, char** argv)
{
	orx_Execute(argc,argv,StandAlone::Init,StandAlone::Run,StandAlone::Exit);
	return 0;
}