

#include "FFLineMoveStrategy.h"



FFLineMoveStrategy::FFLineMoveStrategy(void)
{

}

FFLineMoveStrategy::~FFLineMoveStrategy(void)
{

}


FF_ANIMATION_DYNAMIC_OBJECT FFLineMoveStrategy::Calculate(orxVECTOR* outPos,const orxCLOCK_INFO* pClockInfo )
{
	switch(_direction)
	{
	case MD_X:
		return CalcX(outPos,pClockInfo);
	case MD_Y:
		return CalcY(outPos,pClockInfo);
	}

}

void FFLineMoveStrategy::ReadConfiguration()
{
	if(orxConfig_HasSection(LINE_MOVE_SECTION) == orxSTATUS_SUCCESS)
	{
		orxConfig_PushSection(LINE_MOVE_SECTION);
		orxConfig_GetVector(START_POSITION_VALUE,&_startPosition);
		orxConfig_GetVector(FINISH_POSITION_VALUE,&_finishPosition);
		_speed = orxConfig_GetFloat(SPEED_MOVE_VALUE);
		const orxCHAR* axis =  orxConfig_GetString(MOVE_AXIS_VALUE);
		if(orxString_Compare(axis,AXIS_X) == 0)
			_direction = MD_X;
		else if(orxString_Compare(axis,AXIS_Y) == 0)
			_direction = MD_Y;
		else if(orxString_Compare(axis,AXIS_XY) == 0)
			_direction = MD_XY;

		const orxCHAR* repeat = orxConfig_GetString(REPEAT_VALUE);
		if(orxString_Compare(repeat,REPEAT_TOLEFT) == 0)
			_repeat =  RD_TOLEFT;
		else if(orxString_Compare(repeat,REPEAT_TORIGHT) == 0)
			_repeat = RD_TORIGHT;
		else if(orxString_Compare(repeat,REPEAT_HBOTH) == 0)
		{
			_repeat = RD_BOTH;
			if(_startPosition.fX > _finishPosition.fX)
				_helperDir =  RD_TOLEFT;
			else
			{
				//orxVECTOR temp = _finishPosition;
				//_finishPosition =_startPosition;
				//_startPosition = temp;
				_helperDir = RD_TORIGHT;
			}
		}
		else if(orxString_Compare(repeat,REPEAT_TODOWN) == 0)
			_repeat = RD_TODOWN;
		else if(orxString_Compare(repeat,REPEAT_TOUP) == 0)
			_repeat = RD_TOUP;
		else if(orxString_Compare(repeat,REPEAT_VBOTH) == 0)
		{
			_repeat = RD_BOTH;
			if(_startPosition.fY > _finishPosition.fY)
				_helperDir =  RD_TOUP;
			else
			{
				/*orxVECTOR temp = _finishPosition;
				_finishPosition =_startPosition;
				_startPosition = temp;*/
				_helperDir = RD_TODOWN;
			}
		}

		
	}
}


FF_ANIMATION_DYNAMIC_OBJECT FFLineMoveStrategy::CalcX(orxVECTOR* outPos,const orxCLOCK_INFO* pClockInfo )
{
	switch(_repeat)
	{
	case RD_TOLEFT:
		if(_finishPosition.fX >= outPos->fX)
			outPos->fX = _startPosition.fX;
		else
		{
			orxFLOAT delta = _speed * pClockInfo->fDT;
			outPos->fX -= delta;
		}
		return FFAD_LEFT;
	case RD_TORIGHT:
		if(_finishPosition.fX <= outPos->fX)
			outPos->fX = _startPosition.fX;
		else
		{
			orxFLOAT delta = _speed * pClockInfo->fDT;
			outPos->fX += delta;
		}
		return FFAD_RIGHT;
	case RD_BOTH:
		switch(_helperDir)
		{
		case RD_TOLEFT:
			if(_finishPosition.fX >= outPos->fX)
			{
				orxVECTOR temp = _finishPosition;
				_finishPosition = _startPosition;
				_startPosition = temp;
				_helperDir = RD_TORIGHT;
				return FFAD_RIGHT;
			}
			else
			{
				orxFLOAT delta = _speed * pClockInfo->fDT;
				outPos->fX -= delta;
			}

			return FFAD_LEFT;
		case RD_TORIGHT:
			if(_finishPosition.fX <= outPos->fX)
			{
				orxVECTOR temp = _finishPosition;
				_finishPosition = _startPosition;
				_startPosition = temp;
				_helperDir = RD_TOLEFT;
				return FFAD_LEFT;
			}
			else
			{
				orxFLOAT delta = _speed * pClockInfo->fDT;
				outPos->fX += delta;
			}
			return FFAD_RIGHT;
		}
		break;
	}
	return FFAD_LEFT;
}

FF_ANIMATION_DYNAMIC_OBJECT FFLineMoveStrategy::CalcY(orxVECTOR* outPos,const orxCLOCK_INFO* pClockInfo )
{
	switch(_repeat)
	{
	case RD_TOUP:
		if(_finishPosition.fY >= outPos->fY)
			outPos->fY = _startPosition.fY;
		else
		{
			orxFLOAT delta = _speed * pClockInfo->fDT;
			outPos->fY -= delta;
		}
		return FFAD_UP;
	case RD_TODOWN:
		if(_finishPosition.fY <= outPos->fY)
			outPos->fY = _startPosition.fY;
		else
		{
			orxFLOAT delta = _speed * pClockInfo->fDT;
			outPos->fY += delta;
		}
		return FFAD_DOWN;
	case RD_BOTH:
		switch(_helperDir)
		{
		case RD_TOUP:
			if(_finishPosition.fY >= outPos->fY)
			{
				orxVECTOR temp = _finishPosition;
				_finishPosition = _startPosition;
				_startPosition = temp;
				_helperDir = RD_TODOWN;
				return FFAD_DOWN;
			}
			else
			{
				orxFLOAT delta = _speed * pClockInfo->fDT;
				outPos->fY -= delta;
			}

			return FFAD_UP;
		case RD_TODOWN:
			if(_finishPosition.fY <= outPos->fY)
			{
				orxVECTOR temp = _finishPosition;
				_finishPosition = _startPosition;
				_startPosition = temp;
				_helperDir = RD_TOUP;
				return FFAD_UP;
			}
			else
			{
				orxFLOAT delta = _speed * pClockInfo->fDT;
				outPos->fY += delta;
			}
			return FFAD_DOWN;
		}
		break;
	}
	return FFAD_DOWN;
}