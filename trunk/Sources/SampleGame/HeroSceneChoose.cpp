#include "HeroSceneChoose.h"

#define FIRST_SELECTOR "../Data/Ini/TemplateSelectFirstHero.ini"
#define SECOND_SELECTOR "../Data/Ini/TemplateSelectSecondHero.ini"




HeroSceneChoose::HeroSceneChoose(FFGameManager* gameManager, FF_DISPLAY_SIZE& size)
	:BaseChooseScene(gameManager,size)
{
	_maxCount = _gameManager != NULL ? _gameManager->GetHeroPreviewList()->size() : 0;
}


HeroSceneChoose::~HeroSceneChoose(void)
{
	SAFEDELETE(_radioButtonGroup);
	for(size_t i = 0; i < _selectors.size(); i++)
	{
		delete _selectors.at(i);
		_selectors.at(i) = NULL;
	}
	_selectors.clear();
}


void HeroSceneChoose::InitializeComponent()
{
	__super::InitializeComponent();

	if(orxConfig_Load(BTNS_FILE) == orxSTATUS_SUCCESS)
	{
		orxVECTOR pos;
		pos.fX = BEGIN_X;
		pos.fY = BEGIN_Y - 60;
		pos.fZ = 0;
		_radioButtonGroup = new FFRadioButtonGroup(this,pos,NULL);
		_radioButtonGroup->AddItem(string("Choose FIRST  HERO!"));
		_radioButtonGroup->AddItem(string("Choose SECOND  HERO!"));
	}
	SelectorHero* sel = new SelectorHero(FIRST_SELECTOR);
	_selectors.push_back(sel);
	sel = new SelectorHero(SECOND_SELECTOR);
	_selectors.push_back(sel);
}

void HeroSceneChoose::InitializePreview(orxVECTOR& pos)
{
	int count = 0;
	const std::vector<std::string>* list = _gameManager != NULL ? _gameManager->GetHeroPreviewList() : NULL;
	if(list != NULL)
	{
		for(int j = 0; j < COLS; j++)
		{
			for(int i = 0; i < ROWS; i++)
			{
				if(count < _maxCount)
				{
					string scene = list->at(count);
					const orxCHAR* filename = scene.c_str();
					_arrPreview[i][j]._preview= new FFPreview(NULL,pos,NULL,filename,count++);
					_arrPreview[i][j]._pos = pos;

				}
				else
				{
					_arrPreview[i][j]._preview= NULL;
					_arrPreview[i][j]._pos = pos;
				}
				pos.fY += DELTA_Y;

			}
			pos.fY = BEGIN_Y;
			pos.fX += DELTA_X;
		}
	}
}


void HeroSceneChoose::InitializeLeftColumn(int i)
{
	int count = i;
	const std::vector<string>* list = _gameManager != NULL ? _gameManager->GetHeroPreviewList() : NULL;
	for(int i = ROWS-1;i >= 0; i--)
	{
		_arrPreview[i][0]._preview = NULL;
		if(!list || count == -1)
			continue;
		string scene = list->at(count);
		if(scene.length() == 0)
			continue;
		const orxCHAR* filename = scene.c_str();
		_arrPreview[i][0]._preview = new FFPreview(this,_arrPreview[i][0]._pos,NULL,filename,count--);
	}
}

void HeroSceneChoose::InitializeRightColumn(int i)
{
	int count = i;
	const std::vector<string>* list = _gameManager != NULL ? _gameManager->GetHeroPreviewList() : NULL;
	for(int i = 0;i < ROWS; i++)
	{
		_arrPreview[i][4]._preview = NULL;
		if(!list || count >= _maxCount)
			continue;
		string scene = list->at(count);
		if(scene.length() == 0 )
			continue;
		const orxCHAR* filename = scene.c_str();
		_arrPreview[i][4]._preview = new FFPreview(this,_arrPreview[i][4]._pos,NULL,filename,count++);
	}
}


void HeroSceneChoose::ShowGUI()
{
	__super::ShowGUI();
	if(_radioButtonGroup)
		_radioButtonGroup->Show();
}

void HeroSceneChoose::HideGUI()
{
	__super::HideGUI();
	if(_radioButtonGroup)
		_radioButtonGroup->Hide();
}


void HeroSceneChoose::UpdateGUI(orxOBJECT* obj)
{
	__super::UpdateGUI(obj);
	if(_radioButtonGroup)
		_radioButtonGroup->Update(obj);
}