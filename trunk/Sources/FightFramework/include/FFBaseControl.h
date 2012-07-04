#ifndef __FFBASECONTROL_H__
#define __FFBASECONTROL_H__

#include "FFInclude.h"
#include "FFBaseUiScene.h"
#include "FFInputManager.h"

#define MAX_NAME 260


typedef void (FFBaseUiScene::*BUTTONCLICK)(void);
typedef void (FFBaseUiScene::*CHECKCHANGE)(bool eventValue);
typedef void (FFBaseUiScene::*COMBOCHANGE)(std::string eventValue);
typedef void (FFBaseUiScene::*ITEMCHOOSE)(int eventValue);

class FFBaseControl
{
protected:
	FFBaseUiScene* _parentForm;

	orxOBJECT*	_mainObject;
	orxOBJECT* _captionObject;
	orxVECTOR _position;
	orxCHAR _caption[MAX_NAME];
	bool _isHide;
public:
	FFBaseControl(FFBaseUiScene* parent,orxVECTOR& position, orxCHAR* name);
	virtual ~FFBaseControl();

public:
	virtual void Hide();
	virtual void Show();
	bool IsHide() {return _isHide;}
    orxCHAR* const GetCaption() { return _caption; }
	virtual void Update(orxOBJECT* obj) = 0;
};


#endif //__FFBASECONTROL_H__