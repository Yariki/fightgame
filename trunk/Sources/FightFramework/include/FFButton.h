#ifndef __FFBUTTON_H__
#define __FFBUTTON_H__

#include "FFBaseControl.h"
#define BUTTON_ANIMATION_NORMAL		"NormalAnim"
#define BUTTON_ANIMATION_HOVER		"HoverAnim"
#define BUTTON_ANIMATION_PRESS		"PressAnim"

#define BUTTON_SECTION "Button"
#define BUTTON_CAPTION_NAME "Caption"


class FFButton : public FFBaseControl
{
protected:
	FF_UI_BUTTON_STATE _state;
    
	BUTTONCLICK _OnClick;

	bool _clickPress;
public:
	FFButton(FFBaseUiScene* parent,orxVECTOR& position, orxCHAR* name, BUTTONCLICK onckick);
	virtual ~FFButton();

	FF_UI_BUTTON_STATE GetState() {return _state;}
	void Update(orxOBJECT* obj);


protected:
	void SetState(FF_UI_BUTTON_STATE state) {_state = state;}
	void Normal();
	void Hover();
	void Press();


private:
    void CalcCaptionPosition();

};

#endif //__FFBUTTON_H__