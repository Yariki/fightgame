
#include "FFDynamicMoveStrategyFactory.h"
#include "FFLineMoveStrategy.h"


IDynamicMoveStrategy* FFDynamicMoveStrategyFactory::CreateMoveStrategy(DYNAMIC_STRATEGY strategy)
{
	IDynamicMoveStrategy* move = orxNULL;
	switch(strategy)
	{
	case DS_LINE:
		move = new FFLineMoveStrategy();
		return move;
	case DS_SIN:
		return orxNULL;
	}
	return orxNULL;
}