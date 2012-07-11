#ifndef __CHOOSESCENE_H_
#define __CHOOSESCENE_H_

#include "ffbaseuiscene.h"
#include "FFGameManager.h"
#include "FFButton.h"
#include "FFPreview.h"

#define ROWS 3
#define COLS 5

#define BEGIN_X -375.0
#define BEGIN_Y -225.0

#define DELTA_X 150.0
#define DELTA_Y 150.0

struct GridData
{
    orxVECTOR _pos;
    FFPreview* _preview;
};

class BaseChooseScene :
    public FFBaseUiScene
{
protected:
	GridData _arrPreview[ROWS][COLS];
	std::vector<FFButton*> _listButton;
    int _maxCount;

public:
    BaseChooseScene(FFGameManager* gameManager, FF_DISPLAY_SIZE& size);
    virtual ~BaseChooseScene(void);

	virtual orxSTATUS Load();
	virtual orxSTATUS Unload();
	
	void InitializeComponent();

	virtual void ShowGUI();
	virtual void HideGUI();

protected:
	void UpdateGUI(orxOBJECT* obj);
    virtual void InitializePreview(orxVECTOR& pos) = 0;

private:
	void OnShow();
	void OnClose();

    void OnBackClick();
    void OnRightClick();
    void OnLeftClick();

    void ShiftLeft();
    void ShiftRight();

    virtual void InitializeRightColumn(int i) = 0;
    virtual void InitializeLeftColumn(int i) = 0;
};

#endif //__CHOOSESCENE_H_