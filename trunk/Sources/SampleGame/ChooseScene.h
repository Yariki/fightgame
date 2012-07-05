#ifndef __CHOOSESCENE_H_
#define __CHOOSESCENE_H_

#include "ffbaseuiscene.h"
#include "FFGameManager.h"
#include "FFButton.h"
#include "FFPreview.h"

#define ROWS 3
#define COLS 5

struct GridData
{
    orxVECTOR _pos;
    FFPreview* _preview;
};

class ChooseScene :
    public FFBaseUiScene
{
protected:
	GridData _arrPreview[ROWS][COLS];
	std::vector<FFButton*> _listButton;
    int _maxCount;
   

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

    void OnBackClick();
    void OnRightClick();
    void OnLeftClick();

    void ShiftLeft();
    void ShiftRight();
};

#endif //__CHOOSESCENE_H_