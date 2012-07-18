#ifndef __MAINSCENE_H__
#define __MAINSCENE_H__



#include "ffbaseuiscene.h"
#include "FFGameManager.h"
#include "FFButton.h"



class MainScene :
    public FFBaseUiScene
{
private:

    std::vector<FFButton*> _buttons;

public:
    MainScene(FFGameManager* gameManager, FF_DISPLAY_SIZE& size);
    virtual ~MainScene();

public:
    virtual orxSTATUS Load();
    virtual orxSTATUS Unload();
    
    virtual void InitializeComponent();
    virtual void ShowGUI();
    virtual void HideGUI();

protected:
	void UpdateGUI(orxOBJECT* obj);

private:
    void OnShow();
    void OnClose();

    void OnStartClick();
    void OnChooseSceneClick();
	void OnChooseHeroClick();
    void OnConfigClick();
    void OnExitClick();


};



#endif //__MAINSCENE_H__