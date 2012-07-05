#ifndef __FFDYNAMICMOVESTRATEGYFACTORY_H__
#define __FFDYNAMICMOVESTRATEGYFACTORY_H__

#include "IDynamicMoveStrategy.h"



class FFDynamicMoveStrategyFactory
{
public:
	static IDynamicMoveStrategy* CreateMoveStrategy(DYNAMIC_STRATEGY strategy);
};


#endif //__FFDYNAMICMOVESTRATEGYFACTORY_H__