#ifndef __OPTIONSSCENE_H__
#define __OPTIONSSCENE_H__

#include "ffbaseuiscene.h"
#include "FFGameManager.h"
#include "FFCheckBox.h"
#include "FFComboChooseButton.h"
#include "FFButton.h"

class OptionsScene :
	public FFBaseUiScene
{
private:
	std::vector<FFCheckBox*> _listChecks;
	std::vector<FFComboChooseButton*> _listCombo;
	FFButton* _btnBack;
	
public:
	OptionsScene(FFGameManager* gameManager, FF_DISPLAY_SIZE& size);
	virtual ~OptionsScene(void);

public:
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

};

#endif //__OPTIONSSCENE_H__