#include "ChooseScene.h"


ChooseScene::ChooseScene(FFGameMamager* gameManager, FF_DISPLAY_SIZE& size)
    :FFBaseUiScene(gameManager,size)
{

}


ChooseScene::~ChooseScene(void)
{

}


orxSTATUS ChooseScene::Load()
{
    InitializeComponent();
    return orxSTATUS_SUCCESS;
}

orxSTATUS ChooseScene::Unload()
{

    return orxSTATUS_SUCCESS;
}

orxSTATUS ChooseScene::Update(const orxCLOCK_INFO* pClockInfo)
{

    return orxSTATUS_SUCCESS;
}

void ChooseScene::InitializeComponent()
{
}

void ChooseScene::ShowGUI()
{}

void ChooseScene::HideGUI()
{}

void ChooseScene::OnShow()
{}

void ChooseScene::OnClose()
{}


