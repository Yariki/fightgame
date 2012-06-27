
#ifndef __IDYNAMICMOVESTRATEGY_H__
#define __IDYNAMICMOVESTRATEGY_H__

#include "FFInclude.h"

enum DYNAMIC_STRATEGY
{
	DS_LINE,
	DS_SIN
};



class IDynamicMoveStrategy
{
public:
	IDynamicMoveStrategy(void);
	virtual ~IDynamicMoveStrategy(void);

public:
	virtual FF_ANIMATION_DYNAMIC_OBJECT Calculate(orxVECTOR* outPos,const orxCLOCK_INFO* pClockInfo) = 0;
	virtual void						ReadConfiguration() = 0;

};


#endif //__IDYNAMICMOVESTRATEGY_H__
