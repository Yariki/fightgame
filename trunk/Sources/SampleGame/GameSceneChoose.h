#ifndef __GAMESCENECHOOSE_H__
#define __GAMESCENECHOOSE_H__

#include "basechoosescene.h"


class GameSceneChoose :
    public BaseChooseScene
{
public:
    GameSceneChoose(FFGameManager* gameManager, FF_DISPLAY_SIZE& size);
    virtual ~GameSceneChoose(void);

protected:
    void InitializePreview(orxVECTOR& pos);

private:
    void InitializeRightColumn(int i);
    void InitializeLeftColumn(int i);

	void OnPreviewChoose(int index);
};


#endif //__GAMESCENECHOOSE_H__
