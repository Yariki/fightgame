#ifndef __FFRADIOBUTTON_H__
#define __FFRADIOBUTTON_H__

#include "FFBaseControl.h"

#define RADIO_SECTION "RadioButton"
#define RADIO_CAPTION_SECTION "CaptionRadioButton"

#define RADIO_ANIMATION_NORMAL "NormalCheckAnimRadio"
#define RADIO_ANIMATION_CHECK "PressCheckAnimRadio"

class FFRadioButtonGroup;

typedef (FFRadioButtonGroup::*RADIOCHOOSE)(int index);

class FFRadioButton: public FFBaseControl
{
protected:
    FF_UI_CHECKBOX_STATE _state;
    int _index;
    RADIOCHOOSE _OnChoose;
    FFRadioButtonGroup* _group;

public:
    FFRadioButton(FFBaseUiScene* parent,FFRadioButtonGroup* group, orxVECTOR& pos, orxCHAR* name, RADIOCHOOSE onchoose, int index);
    virtual ~FFRadioButton();

    void Update(orxOBJECT* obj);
    FF_UI_CHECKBOX_STATE GetState() {return _state;}

protected:
    void SetState(FF_UI_CHECKBOX_STATE state);
    void Normal();
    void Check();

    friend class FFRadioButtonGroup;
};

#endif