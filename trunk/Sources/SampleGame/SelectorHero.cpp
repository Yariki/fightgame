#include "SelectorHero.h"


SelectorHero::SelectorHero(orxSTRING filename)
	:FFStaticObject(filename)
{
	Hide();
}


SelectorHero::~SelectorHero(void)
{
}

void SelectorHero::Hide()
{
	_isHide = false;
	if(_object)
		orxObject_Enable(_object,_isHide);
}

void SelectorHero::Show()
{
	_isHide = true;
	if(_object)
		orxObject_Enable(_object,_isHide);

}
