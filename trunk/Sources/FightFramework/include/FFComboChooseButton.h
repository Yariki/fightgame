#ifndef __FFCOMBOCHOOSEBUTTON_H__
#define __FFCOMBOCHOOSEBUTTON_H__

#include "FFBaseControl.h"

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


class FFComboChooseButton: public FFBaseControl
{
protected:
	orxOBJECT* _leftButton;
	orxOBJECT* _rightButton;

	vector<string> _items;
	int _currentItem;

	COMBOCHANGE _OnChooseChange;

public:
	FFComboChooseButton(FFBaseUiScene* parent, FFVector3& position, orxCHAR* name, COMBOCHANGE oncombochange);
	virtual ~FFComboChooseButton();

	void Update(orxOBJECT* obj);
	void SetNormal() {NormalRight();NormalLeft();}
	void AddItem(string item);
	
protected:
	void NormalRight()	{ if(_rightButton != orxNULL) orxObject_SetTargetAnim(_rightButton,BTNRIGHT_ANIM_NORMAL);}
	void NormalLeft() { if(_leftButton != orxNULL) orxObject_SetTargetAnim(_leftButton,BTNLEFT_ANIM_NORMAL);}

	void HoverRight() {if(_rightButton != orxNULL) orxObject_SetTargetAnim(_rightButton,BTNRIGHT_ANIM_HOVER);}
	void HoverLeft() { if(_leftButton != orxNULL) orxObject_SetTargetAnim(_leftButton,BTNLEFT_ANIM_HOVER);}

	void PressRight() {if(_rightButton != orxNULL) orxObject_SetTargetAnim(_rightButton,BTNRIGHT_ANIM_PRESS);}
	void PressLeft() { if(_leftButton != orxNULL) orxObject_SetTargetAnim(_leftButton,BTNLEFT_ANIM_PRESS);}

	void SetCurrentItem(bool direction); // true - left, false - right


};



#endif //__FFCOMBOCHOOSEBUTTON_H__
