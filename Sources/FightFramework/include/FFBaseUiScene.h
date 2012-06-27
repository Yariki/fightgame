
#ifndef __FFBASEUISCENE_H__
#define __FFBASEUISCENE_H__

#include "FFScene.h"

class FFBaseUiScene : public FFScene
{

public:
	FFBaseUiScene(FFGameManager* gameManager,FF_DISPLAY_SIZE& size):FFScene(gameManager,size) {}
	virtual ~FFBaseUiScene();

protected:
	virtual void InitializeComponent() = 0;
};



#endif //__FFBASEUISCENE_H__