#ifndef __FFCHECKBOX_H__
#define __FFCHECKBOX_H__

#include "FFBaseControl.h"

#define CHECKBOX_SECTION "CheckButton"
#define CHECKBOX_CAPTION_SECTION "CaptionCheckButton"

#define CHECKBOX_ANIMATION_NORMAL "NormalCheckAnim"
#define CHECKBOX_ANIMATION_CHECK "PressCheckAnim"

class FFCheckBox : public FFBaseControl
{
protected:
	FF_UI_CHECKBOX_STATE _state;

	CHECKCHANGE _OnCheckChange;

public:
	FFCheckBox(FFBaseUiScene* parent, orxVECTOR& position, orxCHAR* name, CHECKCHANGE oncheckchange);
	virtual ~FFCheckBox();

	FF_UI_CHECKBOX_STATE GetState() {return _state;}
	void Update(orxOBJECT* obj);

protected:
	void SetState(FF_UI_CHECKBOX_STATE state) {_state = state;}

	void Normal();
	void Check();
};


#endif //__FFCHECKBOX_H__