#ifndef __FFENUMS_H__
#define __FFENUMS_H__

enum FF_ANIMATION_OBJECT
{
	FFAO_MAIN = 0,
	FFAO_HELPER1,
	FFAO_HELPER2,
	FFAO_HELPER3,

};

enum FF_ANIMATION_DYNAMIC_OBJECT
{
	FFAD_LEFT = 0,
	FFAD_RIGHT,
	FFAD_DOWN,
	FFAD_UP
};


enum FF_STATIC_OBJECT_TYPE
{
	FFSOT_STATIC = 0,
	FFSOT_ANIMATED
};

enum FF_DYNAMIC_OBJECT_TYPE
{
	FFDOT_DYNAMIC = 0,
	FFDOT_ANIMATED
};

enum FF_MOVE_OPERATION
{
	FFMO_LEFT_FOOT_LOWERKICK = 0,
	FFMO_LEFT_FOOT_UPPERKICK,
	FFMO_LEFT_HAND_LOWERPUHCH,
	FFMO_LEFT_HAND_UPPERPUNCH,
	FFMO_LEFT_JUMP,
	FFMO_LEFT_STAND,
	FFMO_LEFT_WALKING,
	FFMO_RIGHT_FOOT_LOWERKICK,
	FFMO_RIGHT_FOOT_UPPERKICK,
	FFMO_RIGHT_HAND_LOWERPUHCH,
	FFMO_RIGHT_HAND_UPPERPUNCH,
	FFMO_RIGHT_JUMP,
	FFMO_RIGHT_STAND,
	FFMO_RIGHT_WALKING
};

enum FF_MOVE_DIRECTION
{
	FFMD_LEFT,
	FFMD_RIGHT
};

enum FF_SCENE_TYPE
{
	FFST_GAMESCENE = 0,
	FFST_UISCENE
};


// GUI enums begin

enum FF_UI_EVENT
{
	FFUE_UI_SCENE_SHOW,
	FFUE_UI_SCENE_CLOSE,
	FFUE_GAME_SCENE_SHOW,
	FFUE_GAME_SCENE_CLOSE,
	FFUE_BUTTON_CLICK,
	FFUE_CHECKBOX_CHECK,
	FFUE_CHECKBOX_UNCHECK,
	FFUE_COMBOBOX_CHANGE
};

enum FF_UI_BUTTON_STATE
{
	BTN_NORMAL = 0,
	BTN_HOVER,
	BTN_PRESS
};

enum FF__UI_CHECKBOX_STATE
{
	CHB_NORMAL = 0,
	CHB_CHECK
};



// GUI enums end

#endif //__FFENUMS_H__