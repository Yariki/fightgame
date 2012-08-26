
#ifndef __FFLINEMOVESTRATEGY_H__
#define __FFLINEMOVESTRATEGY_H__

#include "IDynamicMoveStrategy.h"
#include "FFVector3.h"

enum MOVE_DIRECTION
{
	MD_X = 0,
	MD_Y,
	MD_XY
};

enum REPEAT_DIRECTION
{
	RD_TOLEFT = 0,
	RD_TORIGHT,
	RD_TOUP,
	RD_TODOWN,
	RD_BOTH
};


#define LINE_MOVE_SECTION					"Line"

#define START_POSITION_VALUE				"Start"
#define FINISH_POSITION_VALUE				"Finish"
#define MOVE_AXIS_VALUE						"Axis"
#define SPEED_MOVE_VALUE					"Speed"
#define REPEAT_VALUE						"Repeat"

// possible value
#define AXIS_X								"x"
#define AXIS_Y								"y"
#define AXIS_XY								"xy"	
#define REPEAT_TOLEFT						"toleft"
#define REPEAT_TORIGHT						"toright"
#define REPEAT_HBOTH						"hboth"
#define REPEAT_TOUP							"toup"
#define REPEAT_TODOWN						"todown"
#define REPEAT_VBOTH						"vboth"


class FFLineMoveStrategy: public IDynamicMoveStrategy
{
protected:
	FFVector3			_startPosition;
	FFVector3			_finishPosition;
	orxFLOAT			_speed;
	MOVE_DIRECTION		_direction;
	REPEAT_DIRECTION    _repeat;
	REPEAT_DIRECTION	_helperDir;


public:
	FFLineMoveStrategy(void);
	virtual ~FFLineMoveStrategy(void);

	virtual FF_ANIMATION_DYNAMIC_OBJECT Calculate( orxVECTOR* outPos,const orxCLOCK_INFO* pClockInfo );

	virtual void						ReadConfiguration();

private:
	FF_ANIMATION_DYNAMIC_OBJECT			CalcX(FFVector3* outPos,const orxCLOCK_INFO* pClockInfo );
	FF_ANIMATION_DYNAMIC_OBJECT			CalcY(FFVector3* outPos,const orxCLOCK_INFO* pClockInfo );


};

#endif //__FFLINEMOVESTRATEGY_H__