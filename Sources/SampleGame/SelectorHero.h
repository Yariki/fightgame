#ifndef __SELECTORHERO_H__
#define __SELECTORHERO_H__

#include "FFStaticObject.h"

class SelectorHero :
	public FFStaticObject
{
protected:
	bool _isHide;

public:
	SelectorHero(orxSTRING filename);
	virtual ~SelectorHero(void);

	void Hide();
	void Show();

	bool IsHide() {return _isHide;}
	orxOBJECT* GetSelector() { return _object;}

};

#endif //__SELECTORHERO_H__