#include "GameSceneChoose.h"


GameSceneChoose::GameSceneChoose(FFGameManager* gameManager, FF_DISPLAY_SIZE& size)
    :BaseChooseScene(gameManager,size)
{
    _maxCount = _gameManager != NULL ? _gameManager->GetGameSceneList()->size() : 0;
}


GameSceneChoose::~GameSceneChoose(void)
{

}


void GameSceneChoose::InitializePreview(FFVector3& pos)
{
    int count = 0;
    const std::vector<FFGameScene*>* list = _gameManager != NULL ? _gameManager->GetGameSceneList() : NULL;
    if(list != NULL)
    {
	    for(int j = 0; j < COLS; j++)
	    {
		    for(int i = 0; i < ROWS; i++)
		    {
                if(count < _maxCount)
                {
                    FFGameScene* scene = list->at(count);
                    std::string f = scene != NULL ? scene ->GetPreviewFileName().c_str() : "";
                    const orxCHAR* filename = f.c_str();
                    _arrPreview[i][j]._preview= new FFPreview(NULL,pos,NULL,filename,(ITEMCHOOSE)&GameSceneChoose::OnPreviewChoose,count++);
                    _arrPreview[i][j]._pos = pos;
			        
                }
                else
                {
                    _arrPreview[i][j]._preview= NULL;
                    _arrPreview[i][j]._pos = pos;
                }
                pos._y += DELTA_Y;
                
		    }
		    pos._y = BEGIN_Y;
		    pos._x += DELTA_X;
	    }
    }
}

void GameSceneChoose::InitializeLeftColumn(int i)
{
    int count = i;
    const std::vector<FFGameScene*>* list = _gameManager != NULL ? _gameManager->GetGameSceneList() : NULL;
    for(int i = ROWS-1;i >= 0; i--)
    {
        _arrPreview[i][0]._preview = NULL;
        if(!list || count == -1)
            continue;
        FFGameScene* scene = list->at(count);
        if(!scene)
            continue;
        std::string f = scene != NULL ? scene ->GetPreviewFileName().c_str() : "";
        const orxCHAR* filename = f.c_str();
        _arrPreview[i][0]._preview = new FFPreview(this,_arrPreview[i][0]._pos,NULL,filename,(ITEMCHOOSE)&GameSceneChoose::OnPreviewChoose,count--);
    }
}

void GameSceneChoose::InitializeRightColumn(int i)
{
    int count = i;
   
    const std::vector<FFGameScene*>* list = _gameManager != NULL ? _gameManager->GetGameSceneList() : NULL;
    for(int i = 0;i < ROWS; i++)
    {
        _arrPreview[i][4]._preview = NULL;
        if(!list || count >= _maxCount)
            continue;
        FFGameScene* scene = list->at(count);
        if(!scene)
            continue;
        std::string f = scene != NULL ? scene ->GetPreviewFileName().c_str() : "";
        const orxCHAR* filename = f.c_str();
        _arrPreview[i][4]._preview = new FFPreview(this,_arrPreview[i][4]._pos,NULL,filename,(ITEMCHOOSE)&GameSceneChoose::OnPreviewChoose,count++);
    }
}

void GameSceneChoose::OnPreviewChoose(int index)
{
	ChooseGameSceneEvent ev(FFUE_GAME_SCENE_CHOOSE,index);
	orxEVENT_SEND(orxEVENT_TYPE_USER_DEFINED,0,this,orxNULL,&ev);
}
