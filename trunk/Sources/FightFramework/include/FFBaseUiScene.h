
#ifndef __FFBASEUISCENE_H__
#define __FFBASEUISCENE_H__

#include "FFScene.h"

class FFBaseUiScene : public FFScene
{
protected:
	bool _isReset;

public:
	FFBaseUiScene(FFBaseManager* gameManager,FF_DISPLAY_SIZE& size):FFScene(gameManager,size),_isReset(false) {}
	virtual ~FFBaseUiScene(){}

public:
	virtual orxSTATUS Update(const orxCLOCK_INFO* pClockInfo);

	virtual void HideGUI() = 0;
	virtual void ShowGUI() = 0;

protected:
	virtual void InitializeComponent() = 0;
	virtual void UpdateGUI(orxOBJECT* obj) = 0;
};



#endif //__FFBASEUISCENE_H__