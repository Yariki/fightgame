#ifndef __FFDEFINES_H__
#define  __FFDEFINES_H__

#define MAX_FILE_PATH 260

#define BTNS_FILE "../Data/Ini/Buttons.ini"

// names of section in main ini file
#define  FF_MAIN_VIEWPORT							"Viewport"



// name section in config-ini file
#define  FF_STATIC_OBCJECT_SECTION_NAME				"StaticEntity"
#define  FF_DYNAMIC_OBCJECT_SECTION_NAME			"DynamicEntity"
#define  FF_MOVABLE_OBCJECT_SECTION_NAME			"MovableEntity"
#define  FF_STATIC_ANIMATED_OBCJECT_SECTION_NAME	"StaticAnimatedEntity"
#define  FF_DYNAMIC_ANIMATED_OBCJECT_SECTION_NAME	"DynamicAnimatedEntity"
#define  FF_MOVABLE_ANIMATED_OBCJECT_SECTION_NAME	"MovableAnimatedEntity"


// names of animation for static and dynamic object
#define  FF_SD_ANIMATION_MAIN						"MainAnimation"
#define  FF_SD_ANIMATION_HELPER1					"Helper1Animation"
#define  FF_SD_ANIMATION_HELPER2					"Helper2Animation"
#define  FF_SD_ANIMATION_HELPER3					"Helper3Animation"

// names of animation for movable object
#define FF_M_LEFT_FOOT_LOWERKICK					"LeftFootLowerKick"
#define FF_M_LEFT_FOOT_UPPERKICK					"LeftFootUpperKick"
#define FF_M_LEFT_HAND_LOWERPUNCH					"LeftHandLowerPunch"
#define FF_M_LEFT_HAND_UPPERPUNCH					"LeftHandUpperPunch"
#define FF_M_LEFT_JUMP								"LeftJump"
#define FF_M_LEFT_STAND								"LeftStand"
#define FF_M_LEFT_WALKING							"LeftWalking"

#define FF_M_RIGHT_FOOT_LOWERKICK					"RightFootLowerKick"
#define FF_M_RIGHT_FOOT_UPPERKICK					"RightFootUpperKick"
#define FF_M_RIGHT_HAND_LOWERPUNCH					"RightHandLowerPunch"
#define FF_M_RIGHT_HAND_UPPERPUNCH					"RightHandUpperPunch"
#define FF_M_RIGHT_JUMP								"RightJump"
#define FF_M_RIGHT_STAND							"RightStand"
#define FF_M_RIGHT_WALKING							"RightWalking"


// names ob scene node
#define FF_GAME_SCENE								"GameScene"
#define FF_UI_SCENE									"UIScene"

// defines name of nodes in game xml file
#define FF_MANAGER_GAMESCENES						"GameScenes"
#define FF_MANAGER_UISCENES							"UIScenes"
#define FF_MANAGER_GAMESCENE						"GameScene"
#define FF_MANAGER_UISCENE							"UIScene"
#define FF_MANAGER__MAINSCENE_ATTRIBUTE				"MainScene"
#define FF_MANAGER_FILENAMESCENE_ATTRIBUTE			"Filename"


// ui input manager defines


#define	KEY_1				"K1"
#define	KEY_2				"K2"
#define	KEY_3				"K3"
#define	KEY_4				"K4"
#define	KEY_5				"K5"
#define	KEY_6				"K6"
#define	KEY_UP				"Up"
#define	KEY_DOWN			"Down"
#define	KEY_RIGHT			"Right"
#define	KEY_LEFT			"Left"
#define	KEY_LCTRL			"LeftCtrl"
#define	KEY_LSHIFT			"LeftShift"
#define	KEY_TAB				"Tab"
#define	KEY_SPACE			"Space"
#define	KEY_RETURN			"Enter"
#define	KEY_ESCAPE			"Escape"
#define	MOUSE_LEFT			"MouseLeft"
#define	MOUSE_RIGHT			"MouseRight"
#define	MOUSE_WHEEL_UP		"WheelUp"
#define	MOUSE_WHEEL_DOWN	"WheelDown"



#endif  __FFDEFINES_H__