#ifndef __CHOOSESCENE_H_
#define __CHOOSESCENE_H_

#include "ffbaseuiscene.h"


class ChooseScene :
    public FFBaseUiScene
{
protected:


public:
    ChooseScene(FFGameMamager* gameManager, FF_DISPLAY_SIZE& size);
    virtual ~ChooseScene(void);

	virtual orxSTATUS Load();
	virtual orxSTATUS Unload();
	virtual orxSTATUS Update(const orxCLOCK_INFO* pClockInfo);
	virtual void InitializeComponent();

	virtual void ShowGUI();
	virtual void HideGUI();

private:
	void OnShow();
	void OnClose();


};

#endif //__CHOOSESCENE_H_