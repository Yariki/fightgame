#include "FFBaseUiScene.h"

orxSTATUS FFBaseUiScene::Update(const orxCLOCK_INFO* pClockInfo)
{
	orxVECTOR vPos;
	if(orxRender_GetWorldPosition(orxMouse_GetPosition(&vPos),&vPos))
	{
		orxOBJECT* obj = orxObject_Pick(&vPos);
		if(obj == NULL && !_isReset)
			return orxSTATUS_SUCCESS;
		
		UpdateGUI(obj);

		if(obj)
		{
			_isReset = true;
		}
		else if(obj == NULL && _isReset)
			_isReset = false;
	}

	return orxSTATUS_SUCCESS;
}