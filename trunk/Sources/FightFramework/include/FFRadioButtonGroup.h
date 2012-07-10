#ifndef __FFRADIOBUTTONGROUP_H__
#define __FFRADIOBUTTONGROUP_H__

#include "FFRadioButton.h"

struct FFRadioItemData
{
	bool _isChecked;
	FFRadioButton* _item;
};

class FFRadioButtonGroup : public FFBaseControl
{
protected:
	std::vector<FFRadioItemData> _listButtons;
	int _lastSelectedIndex;
	

public:
	FFRadioButtonGroup(FFBaseUiScene* parent,orxVECTOR& position, orxCHAR* name);
	virtual ~FFRadioButtonGroup();

public:
	void Hide();
	void Show();
	void Update(orxOBJECT* obj);
	void AddItem(std::string itemName);


private:
	void OnChooseItem(int index);

};

#endif //__FFRADIOBUTTONGROUP_H__