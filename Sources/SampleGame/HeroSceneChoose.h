#ifndef __HEROSCENECHOOSE_H__
#define __HEROSCENECHOOSE_H__



#include "basechoosescene.h"
#include "FFRadioButtonGroup.h"
#include "SelectorHero.h"



class HeroSceneChoose :
	public BaseChooseScene
{
protected:
	FFRadioButtonGroup*  _radioButtonGroup;
	std::vector<SelectorHero*> _selectors; // it is two selectors: index  0 - first hero selector; index 1 - second hero selector
	int _currentChoose ;

public:
	HeroSceneChoose(FFGameManager* gameManager, FF_DISPLAY_SIZE& size);
	virtual ~HeroSceneChoose(void);

	virtual void ShowGUI();
	virtual void HideGUI();
	virtual orxSTATUS Unload();

protected:
	void UpdateGUI(orxOBJECT* obj);
	void InitializeComponent();

	void InitializePreview(orxVECTOR& pos);

private:

	void InitializeRightColumn(int i);
	void InitializeLeftColumn(int i);



	void OnPreviewChoose(int index);

};


#endif //__HEROSCENECHOOSE_H__