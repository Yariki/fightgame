#ifndef __CHOOSESCENE_H_
#define __CHOOSESCENE_H_

#include "ffbaseuiscene.h"
#include "FFGameManager.h"
#include "FFButton.h"
#include "FFPreview.h"

#define COLS 3
#define ROWS 5

class ChooseScene :
    public FFBaseUiScene
{
protected:
	FFPreview* _arrPreview[COLS][ROWS];
	std::vector<FFButton*> _listButton;


public:
    ChooseScene(FFGameManager* gameManager, FF_DISPLAY_SIZE& size);
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